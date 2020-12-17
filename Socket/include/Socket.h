#ifndef VION_SOCKET_INCLUDE_SOCKET_H_
#define VION_SOCKET_INCLUDE_SOCKET_H_


#include <memory>

namespace utils {
    class Socket {
    public:
        Socket();

        explicit Socket(int sock);

        ~Socket();

    public:
        [[nodiscard]] int getSocket() const noexcept;

        void connect(const std::string &host, int port) noexcept(false);

        void send(const std::string &s) const noexcept(false);

        std::string recv() const noexcept(false);

        void setSndTimeout(int sec, int microsec = 0) noexcept(false);

        void setRcvTimeout(int sec, int microsec = 0) noexcept(false);

        static void setReuseAddr(int sock) noexcept(false);

        void createServerSocket(uint32_t port,
                                uint32_t queue_size) noexcept(false);

        [[nodiscard]] std::shared_ptr<Socket> accept() const noexcept(false);

        void close() const;

    private:
        int sock_;
    };
}  // namespace utils

#endif  // VION_SOCKET_INCLUDE_SOCKET_H_
