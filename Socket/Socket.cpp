#include <iostream>
//#include <stdexcept>

#include <cstring>
#include <netdb.h>       // gethostbyname
#include <netinet/in.h>  // struct sockaddr_in
#include <sys/socket.h>  // socket(), AF_INET/PF_INET
#include <unistd.h>

#include "Socket.h"

// global
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

    struct sockaddr_in resolve(const char* host, int port) {
        struct hostent* hp = gethostbyname(host);
        if (hp == nullptr) {
            throw std::runtime_error("resolve error: " + std::string(strerror(errno)));
        }

        char** pAddr = hp->h_addr_list;
        while (*pAddr) {
            auto* ipf = reinterpret_cast<unsigned char*>(*pAddr);
            uint32_t cur_interface_ip = 0;
            auto* rimap_local_ip_ptr = reinterpret_cast<uint8_t*>(&cur_interface_ip);
            rimap_local_ip_ptr[0] = ipf[0];
            rimap_local_ip_ptr[1] = ipf[1];
            rimap_local_ip_ptr[2] = ipf[2];
            rimap_local_ip_ptr[3] = ipf[3];
            std::cerr << "resolved: " << int2ipv4(cur_interface_ip) << std::endl;
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

Socket::Socket() : sock(-1) {}

Socket::Socket(int _sock) : sock(_sock) {}

Socket::~Socket() {
    this->close();
}

void Socket::setSndTimeout(int sec, int microsec) noexcept(false) {
    struct timeval tv{};
    tv.tv_sec = sec;
    tv.tv_usec = microsec;

    if (setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv)) != 0) {
        throw std::runtime_error("set sndtimeout: " + std::string(strerror(errno)));
    }
}

void Socket::setRcvTimeout(int sec, int microsec) noexcept(false) {
    struct timeval tv{};
    tv.tv_sec = sec;
    tv.tv_usec = microsec;

    if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) != 0) {
        throw std::runtime_error("set rcvtimeout: " + std::string(strerror(errno)));
    }
}

void Socket::setReuseAddr(int _sock) noexcept(false) {
    int yes = 1;
    if (setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        ::close(_sock);
        throw std::runtime_error("setopt: " + std::string(strerror(errno)));
    }
}

void Socket::connect(const std::string& host, int port) noexcept(false) {
    struct sockaddr_in addr = resolve(host.data(), port);

    int _sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_sock <= 0) {
        throw std::runtime_error("error to create socket: " +
                                 std::string(strerror(errno)));
    }

    int connected = ::connect(_sock, (struct sockaddr*)&addr, sizeof(addr));
    if (connected == -1) {
        ::close(_sock);
        throw std::runtime_error("connect error: " + std::string(strerror(errno)));
    }

    sock = _sock;
}

void Socket::send(const std::string& str) noexcept(false) {
    size_t left = str.size();
    ssize_t sent = 0;
    int flags = 0;
    while (left > 0) {
        sent = ::send(sock, str.data() + sent, str.size() - sent, flags);
        if (sent == -1) {
            throw std::runtime_error("write failed: " + std::string(strerror(errno)));
        }

        left -= sent;
    }
}

void Socket::send_size(size_t bytes) noexcept(false) {
    if (::send(sock, (char*)&bytes, sizeof(size_t), 0) == -1) {
        throw std::runtime_error("write failed: " + std::string(strerror(errno)));
    }
}

size_t Socket::recv_size() noexcept(false) {
    size_t bytes;
    int n = ::recv(sock, (char*)&bytes, sizeof(size_t), 0);

    std::cout << bytes << std::endl;

    if (n == -1 || n == 0) {
        throw std::runtime_error("read size failed: " + std::string(strerror(errno)));
    }

    return bytes;
}


std::string Socket::recv(size_t bytes) noexcept(false) {
    char* buf = new char[bytes];
    size_t r = 0;
    while (r != bytes) {
        ssize_t rc = ::recv(sock, buf + r, bytes - r, 0);
        std::cerr << "recv_ex: " << rc << " bytes\n";

        if (rc == -1 || rc == 0) {
            delete[] buf;
            throw std::runtime_error("read failed: " + std::string(strerror(errno)));
        }
        r += rc;
    }

    std::string ret(buf, buf + bytes);
    delete[] buf;
    return ret;
}

std::string Socket::recv_loop() noexcept(false) {
    char buf[256];
    std::string ret;
    while (true) {
        int n = ::recv(sock, buf, sizeof(buf), MSG_NOSIGNAL);
        if (n == -1 && errno != EAGAIN) {
            throw std::runtime_error("read failed: " + std::string(strerror(errno)));
        }
        if (n == 0 || n == -1) {
            std::cout << "timeout on rcv n = " << n << std::endl;
            break;
        }

        ret.append(buf, n);
        while (ret.back() == '\r' || ret.back() == '\n') {
            ret.pop_back();
            std::cout << " --- !Встретили конец строки! --- смоти recv_loop()" << std::endl;
        }
    }

    std::cout << "Size buf_rcv = " << ret.size() << std::endl;
    return ret;
}

void Socket::createServerSocket(
        uint32_t port,
        uint32_t listen_queue_size) noexcept(false) {
    int _sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_sock <= 0) {
        throw std::runtime_error("socket: " + std::string(strerror(errno)));
    }

    setReuseAddr(_sock);

    struct sockaddr_in serv_addr{};
    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);

    if (::bind(_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        ::close(_sock);
        throw std::runtime_error("bind: " + std::string(strerror(errno)));
    }

    ::listen(_sock, listen_queue_size);
    sock = _sock;
}

std::shared_ptr<Socket> Socket::accept() noexcept(false) {
    struct sockaddr_in client{};
    memset(&client, 0, sizeof(client));
    socklen_t client_len = sizeof(client);
    std::cerr << "ready for accept new clients: " << std::endl;

    int client_sock = ::accept(sock, (struct sockaddr*)&client, &client_len);
    if (-1 == client_sock) {
        return std::shared_ptr<Socket>();
    }
    std::cerr << "new client: " << client_sock
              << ", from: " << int2ipv4(client.sin_addr.s_addr) << std::endl;

    return std::make_shared<Socket>(client_sock);
}

void Socket::close() const {
    if (sock > 0)
        ::close(sock);
}
