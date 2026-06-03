#include <iostream>
#include <atomic>
#include<thread>

static int cpt{0};

static std::atomic<int> counter = std::atomic<int>{0};

void myfunction(){
		
		
		for (int i = 0; i < 1000000;++i){
				++cpt;
				++counter;
		}
	}



int main(){


			
		std::thread t1(myfunction);
		std::thread t2(myfunction);

		t1.join();
		t2.join();
		
		std::cout << "Main done with cpt = " << cpt << "\n";
		std::cout << "Main done with cpt = " << counter << "\n";
			
		return 0;
}
