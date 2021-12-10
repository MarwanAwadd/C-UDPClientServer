#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <string>
using namespace std;

class UDPClient
{
public:
    UDPClient();
    void Running();

private:
    void Receive();
    void Send(string m);
    string EncryptDecrypt(string message);

    char buffer[1000];
    int sockfd, n;
    char PrivateKey = '@';
};

#endif
