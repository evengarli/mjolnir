#include <netdb.h>
#include <iostream>
#include <string>
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
#include <fstream>
#include "mjolnir_functions.h"

using namespace std;



int main(int argc, char* argv[]) {
    string ip;
    int start = 0;
    int end = 0;

    bool to_file = false;
    string filename;
    bool fast_true = false;
    bool pR_true = false;
    if(argc <= 1) {
        cout << "Usage: mjolnir -ip <ip> -pR <port range>" << endl;
        exit(1);
    }

    for(int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-pR") == 0) {
            string portRange = argv[i + 1];
            size_t dashPos = portRange.find('-');
            if(dashPos == string::npos) {
                cout << "Invalid port range" << endl;
                exit(1);
            }
            pR_true = true;
            start = stoi(portRange.substr(0, dashPos));
            end = stoi(portRange.substr(dashPos + 1));
        } else if(strcmp(argv[i], "-ip") == 0) {
            ip = argv[i+1];
        } else if(strcmp(argv[i], "-h") == 0) {
            cout << "Usage: mjolnir -ip <ip> -pR <port range>" << endl;
            return 0;
        } else if(strcmp(argv[i], "-f") == 0) {
            fast_true = true;
        } else if(strcmp(argv[i], "-o") == 0) {
            to_file = true;
            filename = argv[i+1];
        }
    }
    if(pR_true == true && fast_true == true) {
        cout << "Invalid use, type 'man mjolnir' or visit the Github Repo for help" << endl;
        exit(1);
    }
    if(pR_true == true) {
        if((ip.empty() || start == 0 || end == 0) && fast_true == false) {
            cout << "Usage: mjolnir -ip <ip> -pR <port range>" << endl;
            exit(1);
        }
        if((start <= 0 || end > 65535) && fast_true == false) {
            cout << "Invalid range" << endl;
            exit(1);
        }
        basic_scan(start, end, ip, to_file, filename);
        return 0;
    } else if(fast_true == true) {
        if(ip.empty()) {
            cout << "Use: 'mjolnir -h' for help" << endl;
            exit(1);
        }

        fast_scan(ip, to_file, filename);

    }






    return 0;
}
