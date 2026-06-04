#include <iostream>
#include <sys/select.h>
#include <ctime>
#include <vector>
#include <sys/time.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>


const int minFD = 0;

int main(){
		
		std::vector<int> clients;
		
		int server_socket = socket(AF_INET, SOCK_STREAM,0);

		sockaddr_in server;
		
		server.sin_family = AF_INET;
		server.sin_port = htons(8080);
		server.sin_addr.s_addr= INADDR_ANY;


		int addresslength = sizeof(server);

		if (bind(server_socket,(sockaddr*)&server,addresslength) < 0){
				std::cerr << "Failed to bind" << std::endl;
				close(server_socket);
				return 1;
		}
		if (listen(server_socket,1) < 0){
				std::cerr << "Failed to listen" << std::endl;
				close(server_socket);
				return 0;
		}

		while(1){

				fd_set readFDs;
				FD_ZERO(&readFDs);
								
					
				FD_SET(server_socket, &readFDs);
				int maxFD = server_socket;

				for (auto x: clients ){
						
						FD_SET(x,&readFDs);
						
						if (maxFD < x){
								maxFD = x;
						}
				}
				
				int rc = select(maxFD + 1,&readFDs,nullptr,nullptr,nullptr);

				if (rc < 0){
						
						std::cerr << "Failed to select" << std::endl;
				}
				
				// check if server socket is ready
				if (FD_ISSET(server_socket,&readFDs)){
						int client_socket = accept(server_socket,(sockaddr*)&server,(socklen_t*)&addresslength);

						if (client_socket > 0){
								clients.push_back(client_socket);
						}
				}

								
				for (auto iterator = clients.begin(); iterator != clients.end(); ){
						auto client_fd = *iterator;	
						

						std::string buffer(4096,'\0');

						if (FD_ISSET(client_fd,&readFDs)){
								
								
								ssize_t bytes = recv(client_fd,buffer.data(),buffer.size(),0);
								std::string message(buffer.data(),bytes);
								
								if (bytes > 0 ){

										if (message == "0"){
												// Get the current time as a time_t value
												
												std::time_t currentTime = std::time(nullptr);

												// Convert to a human-readable string using ctime()
												char* timeString = std::ctime(&currentTime);
												std::string response = "It is currently ";
												response += timeString;
												send(client_fd,response.data(),response.size(),0);
											
										}
										else{
												std::cout << "Unknown message" << std::endl;
										}
										++iterator;
								}
								
								else{
										close(client_fd);
										iterator = clients.erase(iterator);

								}
								
									
						}else{++iterator;}
						
							

				}

		}
		


		close(server_socket);


		



				return 0;
		}
