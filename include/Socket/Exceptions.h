#include <exception>

#include "Socket.h"

namespace utils {
    class SocketException: public std::exception {
    public:
        explicit SocketException(const std::string& msg)
                : m_msg(msg) {}

        const char* what() const noexcept override {
            return m_msg.c_str();
        }

    private:
        std::string m_msg;
    };

    class HostentNotReceived: public SocketException {
    public:
        HostentNotReceived()
                : SocketException(std::string(hstrerror(h_errno))) {}
    };

    class SocketError: public SocketException {
    public:
        explicit SocketError(const std::string& msg)
                : SocketException(msg + std::string(strerror(errno))) {}
    };

    class FailedSetOpt: public SocketError {
    public:
        explicit FailedSetOpt(const std::string& msg)
                : SocketError(msg) {}
    };

    class SocketNotCreated: public SocketError {
    public:
        explicit SocketNotCreated(const std::string& msg)
                : SocketError(msg) {}
    };

    class NotConnected: public SocketError {
    public:
        explicit NotConnected(const std::string& msg)
                : SocketError(msg) {}
    };

    class BindError: public SocketError {
    public:
        explicit BindError(const std::string& msg)
                : SocketError(msg) {}
    };

    class SndError: public SocketError {
    public:
        explicit SndError(const std::string& msg)
                : SocketError(msg) {}
    };

    class RcvError: public SocketError {
    public:
        explicit RcvError(const std::string& msg)
                : SocketError(msg) {}
    };
}  // namespace utils
