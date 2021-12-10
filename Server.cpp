// As for the server, the server first resets the server address variable for the socket to be 0s to make sure 
// that its empty then gives it the current ip address of the computer running the server IP. After that the 
// server creates a udp socket and binds it to the server address in order to constantly listen to any address 
// attempting to contact the server. Then we created an infinite loop where the code expects to receive a message 
// from a client and records the client address from the receive, decrypts the message then prints out the 
// encrypted message followed by the encrypted message, showing with each the address of the client sending the 
// message to the server's terminal. After receiving, the server then sends an echo of the message sent by the 
// client back to the client in decrypted form.

#include "UDPServer.h"

int main(int argc, char const *argv[])
{
    UDPServer Server;
    Server.Running();

    return 0;
}
