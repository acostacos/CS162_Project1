#include <iostream>
#include <cstdlib>
#include <string>
#include <queue>
#include <array>
#include <sstream>

using namespace std;

//Program class which specifies one program
struct Program{
	//takes note of index, arrival time, burst time, priority and remaning time left to run
	int index; int arrival; int burst; int priority;
	int runningTime;

	Program(){
		index = 0;
		arrival = 0;
		burst = 0;
		priority = 0;
		runningTime = 0;
	}
	Program(int i, int a, int b, int p){
		index = i;
		arrival = a;
		burst = b;
		priority = p;
	}
	//lets the process run in the cpu for one clock cycle. Burst needed decreases and time spent running increases
	void run(){
		burst--;
		runningTime++;
	}
};


//SJFCompare class used when inserting Programs in the priority queue in the SJF Schduling method
struct SJFCompare{
public:
	bool operator()(Program& p1, Program& p2){
		//false: moves on to the next element, true: places element before current element
		//p2 is the program being pushed

		if(p1.arrival >= p2.arrival){

		}
	}
};

/*
FCFS

string fcfs(){

}
*/

string sjf(Program* arr, int size){
	string output; stringstream out;
	priority_queue<Program, vector<Program>, SJFCompare> pq;
	int timer = 0;
	int cp = 0;

	//Sort array to make the least access time first and the greatest access time last

	//Put the first element in the priority queue and increase timer by that amount

	while(!pq.empty()){
		Program p = pq.top();
		pq.pop();

		while(p.getBurst()!=0){
			//check if any of the processes enter with the timer
			p.run();
			timer++;
		}
		out << timer << " " << p.index << " " << p.runningTime << "X" << endl;
	}

	output = out.str();
	return output;
}

/*

SRTF, P, RR

string srtf(){

}

string p(){

}

string rr(int q){

}

*/

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

		Program list[numPros];

		for(int j=0; j<numPros; j++){
			int arrival; int burst; int priority; 
			cin >> arrival;
			cin >> burst;
			cin >> priority;

			Program p(j+1, arrival, burst, priority);
			list[j] = p;
		}

		if(type=="SJF"){
			cout << sjf(list, numPros);
		}
	}

	return 0;
}
