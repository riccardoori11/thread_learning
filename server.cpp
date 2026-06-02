#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>


auto handleRequest(){}




int main(){

		
		int server_socket = socket(AF_INET, SOCK_STREAM,0);

		sockaddr_in server = {AF_INET, htons(8080),INADDR_ANY};

		int addresslength = sizeof(server);

		if (bind(server_socket,(sockaddr*)&server,addresslength) < 0){
				std::cerr << "Failed to bind" << "\n";
				close(server_socket);
				return 1;
		}

		if (listen(server_socket,1) < 0){
				std::cerr << "Failed to listen" << "\n";
				close(server_socket);
				return 1;
		}
		
		int client_socket = accept(server_socket,(sockaddr*) &server,(socklen_t*)&addresslength);
		
		if (client_socket < 0){
				std::cerr << "Failed to accept client socket" << "\n";
				close(server_socket);
				return 1;
		}
		

		std::string buffer(4096,'\0');
		

		if(recv(client_socket,buffer.data(),buffer.size(),0)< 0){
				std::cerr << "Failed to receive buffer" << "\n";
				close(server_socket);
				return 1;
		}	

		std::cout << buffer << std::endl;

		close(server_socket);


		



		return 0;
}
