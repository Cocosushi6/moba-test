#include <iostream>
#include <string>

#include "client/main_client.h"
#include "server/main_server.h"

using namespace std;
using namespace sf;

int main(int argv, char** argc) {	
	cout << "Welcome to this Game called <undefined> version 0.0.0.1 ! " << endl;
	cout << "Please choose to launch the game as client or server. A window will appear in both cases. " << endl;
	cout << "In case you don't know what to do, type 1" << endl;
	cout << "1. Client" << endl;
	cout << "2. Server" << endl;

	std::string serverAddress;
	int port = -1;
	int choice = 0;

	//TODO enhance this loop for security (check ip address validity and all)
	do {
		cin >> choice;
		if(choice != 1 && choice != 2) {
			cout << "Please type a number between 1 & 2" << endl;
		} else if(choice == 1) {
//			cout << "Great ! Now, please enter server ip address in the form abc.def.ghi.jkl (eg : 127.0.0.1)" << endl;
//			cin >> serverAddress;
			cout << "And now the port you want your client to be opened at : " << endl;
			cin >> port;

			if(port < 1024 || port > 65535) {
				port = 1662;
			}
			serverAddress = "127.0.0.1";
		}
	} while(choice != 1 && choice != 2);

	if(choice == 1) {
		main_client(serverAddress, port);
	} else if(choice == 2) {
		main_server(0, NULL);
	}

	cout << "Game ended !" << endl;

	return 0;
}


