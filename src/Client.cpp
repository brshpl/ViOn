// Class must be implemented by Vladimir Lunkin
#include <Client.h>

void Client::connectToServer(const std::string &host, int port) {}

void Client::createNewFile() {}

void Client::connectToFile(std::string file_id) {}

void Client::sendChanges(const Change &buf) {}

Change Client::recvChanges() { return Change(); }
