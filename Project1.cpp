#include <iostream>
#include <cstdlib>
#include <string>
#include <queue>

using namespace std;

//Program class which specifies one program
class Program{
	//takes note of index, arrival time, burst time and priority
	int index; int arrival; int burst; int priority;

	Program(int i; int a, int b, int p){
		index = i;
		arrival = a;
		burst = b;
		priority = p;
	}
	
}

string fcfs(){

}

string sjf(){

}

string srtf(){

}

string p(){

}

string rr(int q){

}

int main(){

	/*
	Code to get a line of input and parse it to interger

	string iNumTest; int numTest;
	getline(cin, iNumTest);
	numTest = atoi(iNumTest.c_str());
	*/

	int numTest;
	cin >> numTest;

	for(int i=0; i<numTest; i++){
		int numPros; string type;
		cin >> numPros;
		cin >> type;

		if(type=="RR"){
			int q;
			cin >> q;
		}

		for(int j=0; j<numPros; j++){
			int arrival; int burst; int priority; 
			cin >> arrival;
			cin >> burst;
			cin >> priority;

			
		}
	}

	return 0;
}
