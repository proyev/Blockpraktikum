#include <iostream>

namespace myNamespace {

	namespace oldVersion{
	
		void print(int num){
			std::cout << "old: " << num << std::endl;
		}
	
	}

	inline namespace newVersion{
	
		void print(int i){
			std::cout << "new: " << i << std::endl;
		}

		void printX(){
		
		}
	}
}

namespace std{

	void printInfo();

	void printInfo1(){
		cout << "Info" << endl;
	}

}

//void std::printInfo2(){
//	std::cout << "Some other info" << std::endl;
//}

int main(){
	myNamespace::oldVersion::print(1);
	myNamespace::newVersion::print(1);
	myNamespace::print(1);	

	namespace x = myNamespace;
	using namespace x;
	x::print(2);

	//cout << "Test" << endl;
	
//	std::printInfo2();
	std::printInfo1();

	return 0;
}
