#include <iostream>
#include<cstring>
#include <cerrno>
#include <sys/select.h>
#include <vector>
#include <sys/time.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <filesystem>


const int minFD = 0;
namespace fs = std::filesystem;

int main(){
		std::vector<int> clients;
		std::string path = "/home/riccardo/c++_server";
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
								if (bytes < 0 ){
										std::cerr<<"recv failed "<<strerror(errno)<<std::endl;	
										close(client_fd);
										iterator = clients.erase(iterator);
								}
								if (bytes == 0){
										std::cout<<"Client has disconnected"<<std::endl;
										close(client_fd);
										iterator = clients.erase(iterator);
								}
								if (bytes > 0){
										std::string message(buffer.data(),bytes);
										bool FileFound = false;	
										for (const auto & entry : fs::directory_iterator(path)){
												if (message == entry.path().filename().string()){
														FileFound = true;
														break;
												}	
										}	
										if (FileFound){
												std::cout<<"The file exists"<<std::endl;
												std::string response ="The file exists\n" ;
												send(client_fd,response.data(),response.size(),0);
										}
										else{
												std::cerr<<"File not found"<<std::endl;
												std::string response ="The file does not exist\n" ;
												send(client_fd,response.data(),response.size(),0);
										}
										++iterator;
								}
								}else{++iterator;}
				}
		
		}
		close(server_socket);
		return 0;
}
