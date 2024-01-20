#include "serverM.h"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int serverSUDPport = 41000387;
int serverLUDPport = 42000387;
int serverHUDPport = 43000387;

int UDPport = 44000387;
int TCPport = 45000387;
int buffer_size = 1024;


void start_mainserver() {
    std::cout << "start_mainserver function" << std::endl;

    //open the UDP socket that connect with backend
    MainServer_UDPClientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if(MainServer_UDPClientSocket == -1){
        std::cout << "Can not create the MainServer-Backend client UDP socket" << std::endl;
        return;
    }

    char g[] = 3;
     
    struct sockaddr_in MainServerUDP_ClientAddr;
    MainServerUDP_ClientAddr.sin_family = AF_INET;
    MainServerUDP_ClientAddr.sin_port = htons(UDPport);
    inet_pton(AF_INET, "127.0.0.1", &MainServerUDP_ClientAddr.sin_addr);

    bind(MainServer_UDPClientSocket, (struct sockaddr*)&MainServerUDP_ClientAddr, sizeof(MainServerUDP_ClientAddr));
}
void end_mainserver(){
    if(MainServer_ClientUDPSocket != -1){
        close(MainServer_ClientUDPSocket);
    }

    if(MainServer_ClientTCPSocket != -1){
        close(MainServer_ClientTCPSocket);
    }
}

std::string receiveClientReq() {
    std::cout << "receiveClientReq function" << std::endl;
    return "receiveClientReq";
}
void sendResult(int ans){
    std::cout << "sendResult function" << std::endl;
}




int serverType(char req[]) {
    std::cout << "serverType function" << std::endl;

    if (req[0] == 'S') {
        std::cout << "The first character is 's'" << std::endl;
        return 1;
    } 
    else if (req[0] == 'L') {
        std::cout << "The first character is 'l'" << std::endl;
        return 2;
    } 
    else if (req[0] == 'H') {
        std::cout << "The first character is 'h'" << std::endl;
        return 3;
    } else {
        std::cout << "The first character is not 's', 'l', or 'h'" << std::endl;
        return -1;
    }
    return -1;
}

void ReqToBackend(int servertype, char req[]) {
    std::cout << "sendReqToBackend function" << std::endl;

    struct sockaddr_in serverAddr;
    switch (servertype){
    case 1:
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(serverSUDPport);
        break;
    case 2:
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(serverLUDPport);
        break;
    case 3:
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(serverHUDPport);
        break;
    default:
        break;
    }
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    sendto(MainServer_UDPClientSocket, req, strlen(req), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    char buffer[buffer_size];
    recvfrom(MainServer_UDPClientSocket, buffer, sizeof(buffer), 0, nullptr, nullptr);
    std::cout << "Server response: " << buffer << std::endl;

    //TODO get response and send back to client!!

}

int main() {

    std::cout << "main function" << std::endl;
    start_mainserver();
    int servertype = serverType("S146");
    ReqToBackend(servertype, "S146");

    return 0;
}