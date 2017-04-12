#include <iostream>
#include "client/main_client.h"
#include "server/main_server.h"

using namespace std;

int main() {
	
	cout << "Welcome to this Game called <undefined> version 0.0.0.1 ! " << endl;
	cout << "Please choose to launch the game as client or server. A window will appear in both cases. " << endl;
	cout << "In case you don't know what to do, type 1" << endl;
	cout << "1. Client" << endl;
	cout << "2. Server" << endl;

	int choice = 0; do {
		cin >> choice;
		if(choice != 1 && choice != 2) {
			cout << "Please type a number between 1 & 2" << endl;
		}
	} while(choice != 1 && choice != 2);

	if(choice == 1) {
		main_client(0, NULL);
	} else if(choice == 2) {
		main_server(0, NULL);
	}

	cout << "Game ended !" << endl;

	return 0;
}


