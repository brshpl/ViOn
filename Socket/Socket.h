#ifndef VION_SOCKET_SOCKET_H_
#define VION_SOCKET_SOCKET_H_


#include <memory>

class Socket {
public:
    Socket();
    explicit Socket(int _sock);
    ~Socket();

public:
    [[nodiscard]] int get_socket() const noexcept { return sock; }
    void connect(const std::string& host, int port) noexcept(false);
    void send(const std::string& s) noexcept(false);
    std::string recv_loop() noexcept(false);
    void setRcvTimeout(int sec, int microsec) noexcept(false);
    void setReuseAddr(int _sock) noexcept(false);
    void createServerSocket(uint32_t port,
                            uint32_t queue_size) noexcept(false);
    [[nodiscard]] std::shared_ptr<Socket> accept() noexcept(false);
    void close() const;

private:
    int sock;
};


#endif  // VION_SOCKET_SOCKET_H_
