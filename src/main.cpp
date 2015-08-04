#include <iostream>
#include <string>
#include "csa_hon.hpp"

int main(){
	csa_hon<20,10>   csa;
	std::string path("/home/daniel/Desktop/teste.txt");
	csa.construct(path);
//        for(int64_t i=0;i<csa.size();i++){
//            std::cout << "psi(" << i << ") = " << csa.psi(i) <<"\n";
//        }
//        for(int64_t i=0;i<csa.size();i++){
//            std::cout << "SA[" << i << "] = " << csa[i] <<"\n";
//        }
	return 0;
}
