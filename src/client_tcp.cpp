#include "client_tcp.hpp"
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

TCPClient::TCPClient(const std::string& ipAddress, int portNumber)
    : ip(ipAddress), port(portNumber) {

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Erreur création socket");
        exit(EXIT_FAILURE);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if (inet_pton(AF_INET, ip.c_str(), &server.sin_addr) <= 0) {
        perror("Adresse invalide");
        exit(EXIT_FAILURE);
    }
}

void TCPClient::connectToServer() {
    int connexion;

    do {
        connexion = connect(sock, (struct sockaddr*)&server, sizeof(server));

        if (connexion < 0) {
            std::cout << "Tentative de connexion au serveur...\n";
            sleep(3);
        }

    } while (connexion < 0);

    std::cout << "Connecté au serveur (" << ip << ":" << port << ") !" << std::endl;
}

void TCPClient::sendMessage(const std::string& message) {
    send(sock, message.c_str(), message.length(), 0);
}

std::string TCPClient::receiveMessage() {
    char buffer[1024];
    int n = recv(sock, buffer, 1023, 0); // bloquant

    if (n <= 0) {
        return "";
    }

    buffer[n] = '\0';
    return std::string(buffer);
}

void TCPClient::run() {
    std::string message;

    while (true) {
        std::cout << "Quel est ton message ? ";
        std::getline(std::cin, message);

        sendMessage(message);

        // Attend la réponse serveur
        std::string reply = receiveMessage();
        if (reply.empty()) {
            std::cout << "Serveur déconnecté (ou erreur recv)." << std::endl;
            break;
        }

        std::cout << "Réponse serveur: " << reply << std::endl;
    }
}

TCPClient::~TCPClient() {
    close(sock);
    std::cout << "Socket fermée." << std::endl;
}