#include <iostream>

#include "Server.h"
#include "ServerImpl.h"


Server::Server(uint32_t port, uint32_t queue_size)
        : p_impl_(std::make_unique<ServerImpl>(port, queue_size)) {}

void Server::start() {
    p_impl_->startImpl();
}

Server::~Server() = default;
