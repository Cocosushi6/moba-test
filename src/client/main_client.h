#ifndef SRC_CLIENT_MAIN_CLIENT_H_
#define SRC_CLIENT_MAIN_CLIENT_H_

#include <SFML/Network.hpp>

void drawMenu();
void initWindow();
void connectCallback(sf::IpAddress address);
int main_client(int argv, char** argc);



#endif /* SRC_CLIENT_MAIN_CLIENT_H_ */
