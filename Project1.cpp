#include <iostream>
#include <cstdlib>
#include <string>
#include <queue>

using namespace std;

//Program class which specifies one program
class Program{
	//takes note of index, arrival time, burst time, priority and remaning time left to run
private:
	int index; int arrival; int burst; int priority;
	int runningTime;
public:
	Program(){
		index = 0;
		arrival = 0;
		burst = 0;
		priority = 0;
	}
	Program(int i, int a, int b, int p){
		index = i;
		arrival = a;
		burst = b;
		priority = p;
	}

	int getIndex(){
		return index;
	}

	int getArrival(){
		return arrival;
	}

	int getBurst(){
		return burst;
	}

	int getPriority(){
		return priority;
	}

	int getTime(){
		return runningTime;
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
		bool result = false;

		if(p1.getArrival() < p2.getArrival()){
			if(p1.getBurst() < p2.getBurst()){
				result = true;
			}
			else if(p1.getBurst() == p2.getBurst()){
				if(p1.getIndex() < p2.getIndex()){
					result = true;
				}
			}

		}
		else if(p1.getArrival() == p2.getArrival()){
			if(p1.getIndex() < p2.getIndex()){
				result = true;
			}
		}

		return result;
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
	int timer;

	for(int i=0; i<size; i++){
		pq.push(arr[i]);
	}

	while(!pq.empty()){
		Program p = pq.top();
		pq.pop();
		while(p.getBurst()!=0){
			p.run();
			timer++;
		}
		out << timer << " " << p.getIndex() << " " << p.getTime() << "X" << endl;
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
			cout << sjf(list, sizeof(list));
		}
	}

	return 0;
}
