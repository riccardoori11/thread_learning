#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>


int main(){

		int client_socket = socket(AF_INET,SOCK_STREAM,0);

		sockaddr_in server = {AF_INET,htons(8080), 0};

		if (connect(client_socket,(sockaddr*)&server,sizeof(server)) < 0){
				std::cerr << "Failed to connect " << "\n";
				close(client_socket);
				return 1;
		}	

		
		std::string buffer = "Hello World!";
		if(send(client_socket,buffer.data(),buffer.size(),0)<0){
				std::cerr << "Failed to send to server" << "\n";
				close(client_socket);
				return 1;
		}

		close(client_socket);




		return 0;
}
