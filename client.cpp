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

				
					
				while(1){

						std::string input;
						std::getline(std::cin,input);
						
						
	
						send(client_socket,input.data(),input.size(),0);


						std::string buffer(4096,'\0');	
						ssize_t bytes = recv(client_socket,buffer.data(),buffer.size(),0);

						if (bytes > 0){
								std::cout << buffer << std::endl;
						}	
						else{
								std::cout << "Failed to receive from server" << std::endl;
						}
					
				}	

				

				




				return 0;
		}
