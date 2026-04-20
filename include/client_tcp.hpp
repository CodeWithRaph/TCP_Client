#ifndef CLIENT_TCP_HPP
#define CLIENT_TCP_HPP

#include <string>
#include <arpa/inet.h>

/**
 * @brief Client TCP
 */
class TCPClient {
private:
    int sock;
    struct sockaddr_in server;
    std::string ip;
    int port;

public:
    /**
     * @brief Constructeur
     * @param ipAddress Adresse IP du serveur TCP
     * @param portNumber Port d'écoute
     */
    TCPClient(const std::string& ipAddress, int portNumber);

    /**
     * @brief Méthode de connexion
     * Tentative de connexion en boucle si le serveur est inaccessible.
     */
    void connectToServer();

    /**
     * @brief Méthode d'envoi de message
     * @param message Contenu textuel du message
     */
    void sendMessage(const std::string& message);

    /**
     * @brief Attend une réponse du serveur (bloquant) et la retourne.
     */
    std::string receiveMessage();

    /**
     * @brief Boucle itérative
     * Permet au client d'envoyer plusieurs message.
     * A condition que le programme reste en état d'éxécution.
     */
    void run();

    /** 
     * @brief Destructeur
     */
    ~TCPClient();
};

#endif