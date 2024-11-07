#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
using namespace std;
#define BUFFER_SIZE 1024
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080

int main() {
    int sock;
    struct sockaddr_in server_address;
    char buffer[BUFFER_SIZE];
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation error" << std::endl;
        return -1;
    }
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);
    if(inet_pton(AF_INET, SERVER_IP, &server_address.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        return -1;
    } 
    if(connect(sock, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        std::cerr << "Connection failed" << std::endl;
        return -1; 
    }
    cout<<"Connected to server at "<<SERVER_IP<<endl;
    while(true) {
        cout<<"Enter Message:"<<endl;
        string message;
        getline(cin, message);
        if(message.empty()){
            continue;
        }
        send(sock, message.c_str(), message.size(), 0);
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_received = recv(sock, buffer, BUFFER_SIZE, 0);
        if(bytes_received <=0) {
            cerr<<"Server disconnected or receive error."<<endl;
            break;
        }
        cout<<"Echo from server: \n"<<buffer<<endl;

    }
    close(sock);

    return 0;
}

