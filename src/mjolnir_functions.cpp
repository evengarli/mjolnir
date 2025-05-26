#include <netdb.h>
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>
#include <fcntl.h>
#include <ctime>
#include "mjolnir_functions.h"


using namespace std;

void basic_scan(int start, int end, const string &ip, bool to_file, const string &filename) {
    cout << "------------------------------------------------------" << endl;
    cout << "Scanning " << ip << " from port " << start << " to port " << end << endl;
    cout << "------------------------------------------------------" << endl;


    struct addrinfo hints = {};
    hints.ai_family = AF_UNSPEC;
    hints.ai_flags = AI_CANONNAME;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    struct addrinfo *res;

    int noRes = getaddrinfo(ip.c_str(), NULL,&hints,&res);
    if(noRes != 0) {
        cout << "error " << endl;
        exit(1);
    }

    struct sockaddr_in* res_addr = (struct sockaddr_in*)res->ai_addr;

    struct sockaddr_in myAddr;
    myAddr.sin_family = AF_INET;
    myAddr.sin_addr.s_addr = res_addr->sin_addr.s_addr;
    fd_set fdset;
    struct timeval timeout;
    if(to_file == false) {
        for(int i = start; i <= end; i++) {
            int sockfd = socket(AF_INET, SOCK_STREAM, 0);

            myAddr.sin_port = htons(i);

            fcntl(sockfd, F_SETFL, O_NONBLOCK);

            connect(sockfd, (struct sockaddr*)&myAddr, sizeof(myAddr));

            timeout.tv_sec = 1;
            timeout.tv_usec = 0;

            FD_ZERO(&fdset);
            FD_SET(sockfd, &fdset);
            if(select(sockfd + 1, NULL, &fdset, NULL, &timeout) == 1) {
                int so_error;
                socklen_t len = sizeof(so_error);

                getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &so_error, &len);

                if(so_error == 0) {
                    int len = to_string(i).length();
                    int spaces = 8 - len;

                    cout << i;

                    while(spaces > 0) {
                        cout << " ";
                        spaces--;
                    }
                    cout << "OPEN" << endl;
                }
            }   
            close(sockfd);
        }
        freeaddrinfo(res);
    } else if(to_file == true) {
        time_t timestamp;
        time(&timestamp);
        char timeT[20];
        strftime(timeT, 20, "%Y-%m-%d %H:%M:%S", localtime(&timestamp));
        string final_filename = filename + ".mjolnir";
        ofstream MyFile(final_filename);
        MyFile << "--------------------------------------------------" << endl;
        MyFile << "Scan Report for: " << ip << endl;
        MyFile << "Port Range: " << start << "-" << end << endl;
        MyFile << "Date: " << timeT << endl;
        MyFile << "--------------------------------------------------" << endl;

        for(int i = start; i <= end; i++) {
            int sockfd = socket(AF_INET, SOCK_STREAM, 0);

            myAddr.sin_port = htons(i);

            fcntl(sockfd, F_SETFL, O_NONBLOCK);

            connect(sockfd, (struct sockaddr*)&myAddr, sizeof(myAddr));

            timeout.tv_sec = 1;
            timeout.tv_usec = 0;

            FD_ZERO(&fdset);
            FD_SET(sockfd, &fdset);
            if(select(sockfd + 1, NULL, &fdset, NULL, &timeout) == 1) {
                int so_error;
                socklen_t len = sizeof(so_error);

                getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &so_error, &len);

                if(so_error == 0) {
                    int len = to_string(i).length();
                    int spaces = 8 - len;

                    cout << i;
                    MyFile << i;

                    while(spaces > 0) {
                        cout << " ";
                        MyFile << " ";
                        spaces--;
                    }
                    cout << "OPEN" << endl;
                    MyFile << "OPEN" << endl;
                }
            }
            close(sockfd);
        }
        MyFile << "--------------------------------------------------" << endl;
        MyFile.close();
        freeaddrinfo(res);
    }
}

void fast_scan(const string &ip, bool to_file, const string &filename) {
    cout << "------------------------------------------------------" << endl;
    cout << "----------------------FAST-SCAN-----------------------" << endl;
    cout << "IP: " << ip << endl;
    vector<int> common_ports = {20, 21, 22, 23, 25, 53, 67, 68, 69, 80, 110, 111, 123, 135, 137, 138, 139, 143, 161, 162, 179, 389, 443, 445, 465, 514, 515, 587, 631, 636, 993, 995, 1080, 1433, 1521, 1723, 1883, 2049, 2181, 3306, 3389, 3690, 4000, 5432, 5900, 5984, 6379, 8000, 8080, 8443};


    struct addrinfo hints = {};
    hints.ai_family = AF_UNSPEC;
    hints.ai_flags = AI_CANONNAME;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    
    struct addrinfo *res;
    int noRes = getaddrinfo(ip.c_str(), NULL, &hints,&res);

    if(noRes != 0) {
        cout << "Error with getaddrinfo" << endl;
        exit(1);
    }
    
    struct sockaddr_in* res_addr = (struct sockaddr_in*)res->ai_addr;

    struct sockaddr_in myAddr;
    myAddr.sin_family = AF_INET;
    myAddr.sin_addr.s_addr = res_addr->sin_addr.s_addr;
    fd_set fdset;
    struct timeval timeout;

    for(int port : common_ports) {
        int sockfd = socket(AF_INET, SOCK_STREAM, 0);

        myAddr.sin_port = htons(port);
        fcntl(sockfd, F_SETFL, O_NONBLOCK);

        connect(sockfd, (struct sockaddr*)&myAddr, sizeof(myAddr));

        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        FD_ZERO(&fdset);
        FD_SET(sockfd, &fdset);

        if(select(sockfd + 1, NULL, &fdset, NULL, &timeout) == 1) {
            int so_error;
            socklen_t len = sizeof(so_error);

            getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &so_error, &len);
            
            if(so_error == 0) {
                int len = to_string(port).length();
                int spaces = 8-len;
                cout << port;
                while(spaces > 0) {
                    cout << " ";
                    spaces--;
                }
                cout << "OPEN" << endl;
            }
            
        }
        close(sockfd);
    }






}

