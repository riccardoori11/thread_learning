#include <iostream>
#include <thread>
#include <atomic>


class MyClass{
		
		public:
				static std::atomic<int> counter;



};

std::atomic<int> MyClass::counter{0};

void mythread(std::string a){

				
		for (int i = 0; i < 1000000; i++){
				++MyClass::counter;
		}
		
		std::cout << "Done" << std::endl;	
		
}

int main(){

		

		std::cout<< "main: begin  counter =  " << MyClass::counter << "\n" <<std::endl;

		std::thread p1(mythread,"Hello");
		std::thread p2(mythread,"World!");

		p1.join();
		p2.join();

		std::cout << "main: end counter = " << MyClass::counter << "\n" << std::endl;
		

		return 0;
}
