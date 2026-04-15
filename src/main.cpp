#include "client_tcp.hpp"

int main() {
    TCPClient client("127.0.0.1", 8080);

    client.connectToServer();
    client.run();

    return 0;
}