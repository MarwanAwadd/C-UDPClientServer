//The approach for the client is to run on a loop where it checks if the input is ‘q’ where a client 
// should quit and leave the server. In that loop, the client first enters the IP address of the computer 
// running the server.  The client then sets up the server address for the socket to be created from client 
// to server by assigning port number (ours was set to 5000). After that we create a socket for the client 
// and server and use the connect function to make sure that the socket is connected to client and server, 
// the code exits and terminates if they do not connect. The client then proceeds to input a message in the 
// form of a string through the terminal until the user sends ‘q’ where the message “User has left the server” 
// is sent to the server and the client code terminates. When the client sends, the string is first encrypted 
// then the data is changed from string to char * in order to fit the function sendto which takes in a message 
// buffer of type char * and the send function sends regardless of the connection since the socket between the 
// client and server is set to be a UDP socket by having the parameter SOCK_DGRAM. After that the client attempts 
// to receive a response from the server to indicate that the message has been successfully received by the server, 
// if the message is not sent then the terminal for the client program prints “Error occurred, datagrams lost”.

#include "UDPClient.h"

int main(int argc, char const *argv[])
{
    UDPClient Client;
    Client.Running();

    return 0;
}
