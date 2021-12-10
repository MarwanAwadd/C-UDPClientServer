#include "UDPClient.h"
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <chrono>
using namespace std::chrono;
using namespace std;

#define PORT 5000
#define MAXLINE 1000
struct sockaddr_in servaddr;

UDPClient ::UDPClient()
{
}

string UDPClient ::EncryptDecrypt(string message)
{
    int len = message.length();
    string newS = "";

    for (int i = 0; i < len; i++)
    {
        message[i] = message[i] ^ this->PrivateKey;
        newS += message[i];
    }

    return newS;
}

void UDPClient ::Send(string m)
{

    string encryption = EncryptDecrypt(m);

    char *message = new char[encryption.length()];
    for (int i = 0; i < encryption.length(); i++)
    {
        message[i] = encryption[i];
    }

    sendto(sockfd, message, MAXLINE, 0, (struct sockaddr *)NULL, sizeof(servaddr));
}

void UDPClient ::Receive()
{
    bzero(buffer, sizeof(buffer));
    int n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)NULL, NULL);
    if (n < 0)
    {
        cout << "Error occured, datagrams lost" << endl;
    }
    else
    {
        string output(buffer);
        cout << output << endl;
    }
}

void UDPClient ::Running()
{
    string messageInput;
    string ip = "0.0.0.0";
    cout << "Enter server IP Address: ";
    cin >> ip;
    // clear servaddr
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_addr.s_addr = inet_addr(ip.c_str());
    servaddr.sin_port = htons(PORT);
    servaddr.sin_family = AF_INET;

    // create datagram socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    // connect to server
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("\n Error : Connect Failed \n");
        exit(0);
    }

    while (messageInput != "q")
    {
        getline(cin, messageInput);
        if (messageInput != "q")
        {

            Send(messageInput);
            cout << "Echo from server: ";
            Receive();
        }
        else
        {
            string quit = "Client has left the server.";
            char *message = new char[quit.length()];
            for (int i = 0; i < quit.length(); i++)
            {
                message[i] = quit[i];
            }
            Send(quit);
            Receive();

            close(sockfd);
        }
    }
}