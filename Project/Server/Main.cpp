#include <iostream>

#include "Server.h"

void main()
{
	std::cout << "Alpha Strike server running..." << std::endl;

	Server *server = new Server();

	while (server->update()){
		
	}
	
	delete server;
}