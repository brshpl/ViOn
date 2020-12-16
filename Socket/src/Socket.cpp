#include <iostream>

#include <cstring>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include "Exceptions.h"
#include "Socket.h"


namespace utils {
    std::string int2ipv4(uint32_t ip) {
        char buf[128];
        snprintf(buf, sizeof(buf), "%u.%u.%u.%u",
                 (ip & 0xFF),
                 (ip & 0xFF00) >> 8,
                 (ip & 0xFF0000) >> 16,
                 (ip & 0xFF000000) >> 24);
        return buf;
    }

    namespace {

        struct sockaddr_in resolve(const char *host, int port) {
            struct hostent *hp = gethostbyname(host);
            if (hp == nullptr) {
                throw HostentNotReceived();
            }

            char **pAddr = hp->h_addr_list;
            while (*pAddr) {
                auto *ipf = reinterpret_cast<unsigned char *>(*pAddr);

                std::cerr << "resolved: ";
                for (int i = 0; i < 4; ++i) {
                    std::cerr << (int) ipf[i] << ((i == 3) ? '\n' : '.');
                }

                ++pAddr;
            }

            struct sockaddr_in addr{};
            memset(&addr, 0, sizeof(addr));
            addr.sin_family = AF_INET;
            addr.sin_port = htons(port);
            memcpy(&addr.sin_addr, hp->h_addr, hp->h_length);

            return addr;
        }

    }  // namespace

    Socket::Socket() : sock_(-1) {}

    Socket::Socket(int _sock) : sock_(_sock) {}

    Socket::~Socket() {
        this->close();
    }

    void Socket::setSndTimeout(int sec, int microsec) noexcept(false) {
        struct timeval tv{};
        tv.tv_sec = sec;
        tv.tv_usec = microsec;

        if (setsockopt(sock_, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv)) != 0) {
            throw FailedSetOpt("set sndtimeout: ");
        }
    }

    void Socket::setRcvTimeout(int sec, int microsec) noexcept(false) {
        struct timeval tv{};
        tv.tv_sec = sec;
        tv.tv_usec = microsec;

        if (setsockopt(sock_, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) != 0) {
            throw FailedSetOpt("set rcvtimeout: ");
        }
    }

    void Socket::setReuseAddr(int _sock) noexcept(false) {
        int yes = 1;
        if (setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
            ::close(_sock);
            throw FailedSetOpt("set reuse addr: ");
        }
    }

    void Socket::connect(const std::string &host, int port) noexcept(false) {
        struct sockaddr_in addr = resolve(host.data(), port);

        int sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (sock <= 0) {
            throw SocketNotCreated("connect: ");
        }

        int connected = ::connect(sock, (struct sockaddr *) &addr, sizeof(addr));
        if (connected == -1) {
            ::close(sock);
            throw NotConnected("connect: ");
        }

        sock_ = sock;
    }

    void Socket::send(const std::string &str) const noexcept(false) {
        size_t left = str.size();
        ssize_t sent = 0;
        int flags = 0;

        if (::send(sock_, (char *) &left, sizeof(size_t), flags) == -1) {
            throw SndError("write bytes failed: ");
        }

        while (left > 0) {
            sent = ::send(sock_, str.data() + sent, str.size() - sent, flags);
            if (sent == -1) {
                throw SndError("write failed: ");
            }

            left -= sent;
        }
    }

    std::string Socket::recv() const noexcept(false) {
        size_t bytes;
        int n = ::recv(sock_, (char *) &bytes, sizeof(size_t), 0);
        if (n == -1 || n == 0) {
            throw RcvError("read size failed: ");
        }

        char *buf = new char[bytes];
        size_t r = 0;
        while (r != bytes) {
            ssize_t rc = ::recv(sock_, buf + r, bytes - r, 0);

            if (rc == -1 || rc == 0) {
                delete[] buf;
                throw RcvError("read failed: ");
            }
            r += rc;
        }

        std::string ret(buf, buf + bytes);
        delete[] buf;
        return ret;
    }

    void Socket::createServerSocket(
            uint32_t port,
            uint32_t listen_queue_size) noexcept(false) {
        int sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (sock <= 0) {
            throw SocketNotCreated("create server: ");
        }

        setReuseAddr(sock);

        struct sockaddr_in serv_addr{};
        memset(&serv_addr, 0, sizeof(serv_addr));

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        serv_addr.sin_port = htons(port);

        if (::bind(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
            ::close(sock);
            throw BindError("create server: ");
        }

        ::listen(sock, listen_queue_size);
        sock_ = sock;
    }

    std::shared_ptr<Socket> Socket::accept() const noexcept(false) {
        struct sockaddr_in client{};
        memset(&client, 0, sizeof(client));
        socklen_t client_len = sizeof(client);
        std::cerr << "ready for accept new clients: " << std::endl;

        int client_sock = ::accept(sock_, (struct sockaddr *) &client, &client_len);
        if (client_sock == -1) {
            return std::shared_ptr<Socket>();
        }
        std::cerr << "new client: " << client_sock
                  << ", from: " << int2ipv4(client.sin_addr.s_addr) << std::endl;

        return std::make_shared<Socket>(client_sock);
    }

    void Socket::close() const {
        if (sock_ > 0)
            ::close(sock_);
    }

    int Socket::getSocket() const noexcept {
        return sock_;
    }
}  // namespace utils
