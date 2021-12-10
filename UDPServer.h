#ifndef UDPSERVER_H
#define UDPSERVER_H

#include<string>
using namespace std;

class UDPServer
{
public:
    UDPServer();
    void Running();

private:
    string Receive(struct sockaddr_in &cliaddr);
    void Send(char *message, struct sockaddr_in &cliaddr);
    string EncryptDecrypt(char *message);
    void EmptyBuffer();

    char buffer[100000];
    int length;
    int listenfd;
    char PrivateKey = '@';

};

#endif
