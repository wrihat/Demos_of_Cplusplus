#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
using namespace std;
#define PORT 8080
#define BUFFER_SIZE 1024
int main() {
    //配置工作：服务端fd、连接上来的客户机fd、地址信息
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    //创建服务端监听fd
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("set server socket failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    //初始化fd
    if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, & opt, sizeof(opt))) {
        perror("setcockopt failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    //
    address.sin_family = AF_INET;       //IP类型
    address.sin_addr.s_addr = INADDR_ANY;  //地址
    address.sin_port = htons(PORT);         //端口
    
    if(bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    } 
    if(listen(server_fd, 3) < 0) {  // listen是将fd设置为listen状态，进程/线程本身并不会阻塞，而是accept会发生阻塞
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    cout<<"Echo server is listening on port "<<PORT <<endl;
    if((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept failed.");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    while(true) {
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_read = read(new_socket, buffer, BUFFER_SIZE);
        if(bytes_read <= 0) {
            cout<<"Client disconnected or read error."<<endl;
            break;
        }
        cout<<"Received: "<<buffer<<endl;
        send(new_socket, buffer, bytes_read, 0);
        cout<<"Echoed Back to client."<<endl;
    }
    close(new_socket);
    close(server_fd);

    return 0;
}

