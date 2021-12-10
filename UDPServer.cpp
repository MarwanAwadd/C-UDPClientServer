#include "UDPServer.h"
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

#define PORT 5000
#define MAXLINE 1000
struct sockaddr_in servaddr;

UDPServer ::UDPServer()
{
}

string UDPServer ::EncryptDecrypt(char *message)
{
    int len = strlen(message);
    string newS = "";

    for (int i = 0; i < len; i++)
    {
        message[i] = message[i] ^ this->PrivateKey;
        newS += message[i];
    }

    return newS;
}

void UDPServer ::EmptyBuffer()
{
    int i = 0;
    while (buffer[i] != '\0')
    {
        buffer[i] = '\0';
        i++;
    }
}

string UDPServer ::Receive(struct sockaddr_in &cliaddr)
{
    bzero(buffer, sizeof(buffer));
    socklen_t len;
    len = sizeof(cliaddr);
    int n = recvfrom(this->listenfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&cliaddr, &len);
    buffer[n] = '\0';

    cout << "Client " << cliaddr.sin_addr.s_addr << " (Encrypted): ";
    puts(buffer);
    string dec = EncryptDecrypt(buffer);
    cout << "Client " << cliaddr.sin_addr.s_addr << " (Decrypted): " << dec << endl;

    return dec;
}

void UDPServer ::Send(char *message, struct sockaddr_in &cliaddr)
{
    sendto(this->listenfd, message, MAXLINE, 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
}

void UDPServer ::Running()
{
    struct sockaddr_in cliaddr;
    bzero(&servaddr, sizeof(servaddr));

    this->length = sizeof(servaddr);
    bzero(&servaddr, length);
    this->listenfd = socket(AF_INET, SOCK_DGRAM, 0);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    servaddr.sin_family = AF_INET;

    bind(this->listenfd, (struct sockaddr *)&servaddr, this->length);

    for (;;)
    {
        string dec = Receive(cliaddr);

        char *echo = new char[dec.length()];

        for (int i = 0; i < dec.length(); i++)
        {
            echo[i] = dec[i];
        }
        Send(echo, cliaddr);
    }
}
