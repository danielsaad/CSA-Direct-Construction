/* 
 * File:   misc.cpp
 * Author: daniel
 *
 * Created on 3 de Agosto de 2015, 15:46
 */

#include <iostream>
#include "suffixSorting.hpp"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    int v[6] = {'d','a','b','r','a',0};
    int v2[6];
    suffixSort(v,v2,5,256,1,3);
    for(int i=0;i<6;i++){
        cout << "ISA[" << i << "] = " << v[i] << "\n";
    }
    for(int i=0;i<6;i++){
        cout << "SA[" << i << "] = " << v2[i] << "\n";
    }
    return 0;
}

