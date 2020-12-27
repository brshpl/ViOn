#pragma once

#include <memory>

namespace utils {
    class Socket {
    public:
        Socket();
        ~Socket();
        explicit Socket(int sock);

    public:
        void createServerSocket(uint32_t port,
                                uint32_t queue_size) noexcept(false);
        [[nodiscard]] std::shared_ptr<Socket> accept() const noexcept(false);
        void connect(const std::string &host, int port) noexcept(false);
        void setSndTimeout(int sec, int microsec = 0) noexcept(false);
        void setRcvTimeout(int sec, int microsec = 0) noexcept(false);
        static void setReuseAddr(int sock) noexcept(false);
        void send(const std::string &s) const noexcept(false);
        std::string recv() const noexcept(false);
        [[nodiscard]] int getSocket() const noexcept;
        void close() const;

    private:
        int sock_;
    };
}  // namespace utils
