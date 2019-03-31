#include <iostream>
#include <cstdlib>
#include <string>
#include <queue>
#include <array>
#include <sstream>

using namespace std;

//------------------------------------------------------------------------------------------------------------------------------------
// HELPER CLASSES AND FUNCTIONS
//------------------------------------------------------------------------------------------------------------------------------------

//Program class which specifies one program
struct Program{
	//takes note of index, arrival time, burst time, priority and remaning time left to run
	//current time represents how much time it spent running in a CPU burst (for preemptive scheduling purposes)
	int index; int arrival; int burst; int priority;
	int runningTime; int currentTime;

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
		runningTime++;
		currentTime++;
	}
};

//helper function for quicksort
void swap(Program* a, Program* b){
	Program t = *a;
	*a = *b;
	*b = t;
}

//quickSort for the array, sort the array with the least arrival time first to the highest arrival time
void quicksort(Program* arr, int low, int high){
	Program pivot = arr[high];
	int left = low;
	int right = high-1;

	while(left<right){
		while(arr[left].arrival<pivot.arrival){
			left++;
		}
		while(arr[right].arrival>pivot.arrival){
			right--;
		}
		if(right<=left){
			break;
		}
		swap(&arr[left],&arr[right]);
		left++;
		right--;
	}

	if(arr[left].arrival>arr[high].arrival){
		swap(&arr[left], &arr[high]);
	}

	if(left-1>low){
		quicksort(arr, low, left-1);
	}
	if(left+1<high){
		quicksort(arr, left+1, high);
	}
}

//returns number of array elements that can be added to the program
int checkArrival(Program* arr, int size, int cp, int timer){
	//check top of array and see if arrival time matches the current time
	int counter = 0;
	Program next = arr[cp];
	//check the next things in the array until the arrival time is different
	while(cp+counter<size && next.arrival <= timer){
		counter++;
		next = arr[cp+counter];
	}
	//return number of elements to be added
	return counter;
}//SJFCompare class used when inserting Programs in the priority queue in the SJF Schduling method



//------------------------------------------------------------------------------------------------------------------------------------
// FCFS
//------------------------------------------------------------------------------------------------------------------------------------

//FCFSCompare class used when inserting Programs in the priority queue in the FCFS Schduling method
struct FCFSCompare{
public:
	bool operator()(Program& p1, Program& p2){
		//false compares the next item in the queue, true inserts the program before the program it's currently being compared to
		if(p1.arrival > p2.arrival){
			return true;
		}
		else if(p1.arrival == p2.arrival){
			if(p1.index > p2.index){
				return true;
			}
		}

		return false;
	}
};

string fcfs(Program* arr, int size){
	string output; stringstream out;
	priority_queue<Program, vector<Program>, FCFSCompare> pq;
	int timer = 0;
	int cp = 0;

	//push all of the elements that arrive at 0 inside
	int initialChecker = checkArrival(arr, size, cp, timer);
		if(initialChecker>0){
			for(int i=0; i<initialChecker; i++){
				pq.push(arr[cp]);
				cp++;
			}
	}
	//run while pq is not empty and while not all the programs have been added to the priority queue
	while(cp<size || !pq.empty()){
		Program p = pq.top();
		pq.pop();

		while(p.burst!=p.runningTime){
			//check if any of the processes enter with the timer
			int progChecker = checkArrival(arr, size, cp, timer);
			if(progChecker>0){
				for(int i=0; i<progChecker; i++){
					pq.push(arr[cp]);
					cp++;
				}
			}

			p.run();
			timer++;
		}

		out << timer << " " << p.index << " " << p.currentTime << "X" << endl;

	}

	output = out.str();
	return output;
}

//------------------------------------------------------------------------------------------------------------------------------------
// SJF
//------------------------------------------------------------------------------------------------------------------------------------

//SJFCompare class used when inserting Programs in the priority queue in the SJF Schduling method
struct SJFCompare{
public:
	bool operator()(Program& p1, Program& p2){
		//false compares the next item in the queue, true inserts the program before the program it's currently being compared to
		//check p1 is longer than p2
		if(p1.burst > p2.burst){
			return true;
		}
		else if(p1.burst == p2.burst){
			if(p1.index > p2.index){
				return true;
			}
		}

		return false;
	}
};

string sjf(Program* arr, int size){
	string output; stringstream out;
	priority_queue<Program, vector<Program>, SJFCompare> pq;
	int timer = 0;
	int cp = 0;

	//push all of the elements that arrive at 0 inside
	int initialChecker = checkArrival(arr, size, cp, timer);
		if(initialChecker>0){
			for(int i=0; i<initialChecker; i++){
				pq.push(arr[cp]);
				cp++;
			}
	}

	//run while pq is not empty and while not all the programs have been added to the priority queue
	while(cp<size || !pq.empty()){
		Program p = pq.top();
		pq.pop();

		while(p.burst!=p.runningTime){
			//check if any of the processes enter with the timer
			int progChecker = checkArrival(arr, size, cp, timer);
			if(progChecker>0){
				for(int i=0; i<progChecker; i++){
					pq.push(arr[cp]);
					cp++;
				}
			}

			p.run();
			timer++;
		}

		out << timer << " " << p.index << " " << p.currentTime << "X" << endl;

	}

	output = out.str();
	return output;
}

//------------------------------------------------------------------------------------------------------------------------------------
// SRTF
//------------------------------------------------------------------------------------------------------------------------------------

//SRTFcompare class used when inserting Programs in the priority queue in the SRTF Schduling method
struct SRTFCompare{
public:
	bool operator()(Program& p1, Program& p2){
		//false compares the next item in the queue, true inserts the program before the program it's currently being compared to
		//check p1 has a greater remaining time left than p2
		if(p1.burst-p1.runningTime > p2.burst-p2.runningTime){
			return true;
		}
		else if(p1.burst-p1.runningTime == p2.burst-p2.runningTime){
			if(p1.index > p2.index){
				return true;
			}
		}

		return false;
	}
};

string srtf(Program* arr, int size){
	string output; stringstream out;
	priority_queue<Program, vector<Program>, SRTFCompare> pq;
	int timer = 0;
	int cp = 0;

	//push all of the elements that arrive at 0 inside
	int initialChecker = checkArrival(arr, size, cp, timer);
		if(initialChecker>0){
			for(int i=0; i<initialChecker; i++){
				pq.push(arr[cp]);
				cp++;
			}
	}

	//assignChecker is used to store whether a program was preemptively swapped or not. It only controls whether to discard the program, or put it back in the queue
	bool switchChecker = false;
	Program p;
	//run while pq is not empty and while not all the programs have been added to the priority queue
	//to check remaining time: burst-runningTime
	while(cp<size || !pq.empty()){
		if(switchChecker){
			//set the currentTime to 0 if you put the process back in the queue
			p.currentTime = 0;
			pq.push(p);
			switchChecker = false;
		}

		if(!pq.empty()){
			p = pq.top();
			pq.pop();
		}

		while(p.burst!=p.runningTime){
			//check if any of the processes enter with the timer
			int progChecker = checkArrival(arr, size, cp, timer);
			if(progChecker>0){
				for(int i=0; i<progChecker; i++){
					pq.push(arr[cp]);
					cp++;
				}
			}

			//Preemptive: Check if top of the queue has less remaining time left. If it does, make it the current running process
			Program ptemp = pq.top();
			if(ptemp.burst-ptemp.runningTime < p.burst-p.runningTime){

				switchChecker = true;
				break;
			}

			p.run();
			timer++;
		}

		out << timer << " " << p.index << " " << p.currentTime << "X" << endl;

	}

	output = out.str();
	return output;
}

//------------------------------------------------------------------------------------------------------------------------------------
// PRIORITY
//------------------------------------------------------------------------------------------------------------------------------------

//PCompare class used when inserting Programs in the priority queue in the Priority Schduling method
struct PCompare{
public:
	bool operator()(Program& p1, Program& p2){
		//false compares the next item in the queue, true inserts the program before the program it's currently being compared to
		//check p1 has a higher priority than p2
		if(p1.priority> p2.priority){
			return true;
		}
		//if priority is the same, check the one with the less index
		else if(p1.priority == p2.priority){
			if(p1.index > p2.index){
				return true;
			}
		}

		return false;
	}
};

//------------------------------------------------------------------------------------------------------------------------------------
// NON-PREEMPTIVE
//------------------------------------------------------------------------------------------------------------------------------------

string pn(Program* arr, int size){
	string output; stringstream out;
	priority_queue<Program, vector<Program>, PCompare> pq;
	int timer = 0;
	int cp = 0;

	//push all of the elements that arrive at 0 inside
	int initialChecker = checkArrival(arr, size, cp, timer);
		if(initialChecker>0){
			for(int i=0; i<initialChecker; i++){
				pq.push(arr[cp]);
				cp++;
			}
	}

	//run while pq is not empty and while not all the programs have been added to the priority queue
	while(cp<size || !pq.empty()){
		Program p = pq.top();
		pq.pop();

		while(p.burst!=p.runningTime){
			//check if any of the processes enter with the timer
			int progChecker = checkArrival(arr, size, cp, timer);
			if(progChecker>0){
				for(int i=0; i<progChecker; i++){
					pq.push(arr[cp]);
					cp++;
				}
			}

			p.run();
			timer++;
		}

		out << timer << " " << p.index << " " << p.currentTime << "X" << endl;

	}

	output = out.str();
	return output;
}

//------------------------------------------------------------------------------------------------------------------------------------
// PREEMPTIVE
//------------------------------------------------------------------------------------------------------------------------------------

string pp(Program* arr, int size){
	string output; stringstream out;
	priority_queue<Program, vector<Program>, PCompare> pq;
	int timer = 0;
	int cp = 0;

	//push all of the elements that arrive at 0 inside
	int initialChecker = checkArrival(arr, size, cp, timer);
		if(initialChecker>0){
			for(int i=0; i<initialChecker; i++){
				pq.push(arr[cp]);
				cp++;
			}
	}

	//assignChecker is used to store whether a program was preemptively swapped or not. It only controls whether to discard the program, or put it back in the queue
	bool switchChecker = false;
	Program p;
	//run while pq is not empty and while not all the programs have been added to the priority queue
	while(cp<size || !pq.empty()){
		if(switchChecker){
			//set the currentTime to 0 if you put the process back in the queue
			p.currentTime = 0;
			pq.push(p);
			switchChecker = false;
		}

		if(!pq.empty()){
			p = pq.top();
			pq.pop();
		}

		while(p.burst!=p.runningTime){
			//check if any of the processes enter with the timer
			int progChecker = checkArrival(arr, size, cp, timer);
			if(progChecker>0){
				for(int i=0; i<progChecker; i++){
					pq.push(arr[cp]);
					cp++;
				}
			}

			//Preemptive: Check if top of the queue has less remaining time left. If it does, make it the current running process
			Program ptemp = pq.top();
			if(ptemp.priority < p.priority){
				switchChecker = true;
				break;
			}

			p.run();
			timer++;
		}

		out << timer << " " << p.index << " " << p.currentTime << "X" << endl;

	}

	output = out.str();
	return output;
}

//------------------------------------------------------------------------------------------------------------------------------------
// RR
//------------------------------------------------------------------------------------------------------------------------------------

//RRCompare class used when inserting Programs in the priority queue in the RR Schduling method
struct RRCompare{
public:
	bool operator()(Program& p1, Program& p2){
		//false compares the next item in the queue, true inserts the program before the program it's currently being compared to
		if(p1.arrival > p2.arrival && p1.runningTime >= p2.arrival){
			if(p1.index > p2.index){
				return true;
			}
		}
		else if(p1.arrival == p2.arrival){
			if(p1.index > p2.index){
				return true;
			}
		}

		return false;
	}
};

string rr(Program* arr, int size, int quanTime){
	string output; stringstream out;
	priority_queue<Program, vector<Program>, RRCompare> pq;
	int timer = 0;
	int cp = 0;

	//push all of the elements that arrive at 0 inside
	int initialChecker = checkArrival(arr, size, cp, timer);
		if(initialChecker>0){
			for(int i=0; i<initialChecker; i++){
				pq.push(arr[cp]);
				cp++;
			}
	}
	//run while pq is not empty and while not all the programs have been added to the priority queue
	while(cp<size || !pq.empty()){
		Program p = pq.top();
		pq.pop();

		for(int i = 0; i < quanTime; i++){
			//check if any of the processes enter with the timer
			int progChecker = checkArrival(arr, size, cp, timer);
			if(progChecker>0){
				for(int j=0; j<progChecker; j++){
					pq.push(arr[cp]);
					cp++;
				}
			}

			p.run();
			timer++;
			p.index++;
			Program ptemp = pq.top();
			if(p.runningTime == p.burst){
				p.index = p.index-p.burst;
				out << timer << " " << p.index << " " << p.currentTime << "X" << endl;
				break;
			}
		}
		if(p.runningTime != p.burst){
			out << timer << " " << p.index << " " << p.currentTime << "X" << endl; 
			pq.push(p);
		}
	}
	output = out.str();
	return output;
}

//------------------------------------------------------------------------------------------------------------------------------------
// MAIN FUNCTION
//------------------------------------------------------------------------------------------------------------------------------------

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

		/*if(type=="RR"){
			int q;
			cin >> q;
		}*/

		Program list[numPros];

		for(int j=0; j<numPros; j++){
			int arrival; int burst; int priority; 
			cin >> arrival;
			cin >> burst;
			cin >> priority;

			Program p(j+1, arrival, burst, priority);
			list[j] = p;
		}

		//Sort array to make the least access time first and the greatest access time last
		quicksort(list, 0, numPros-1);

		for(int j=0; j<numPros; j++){
			cout << "Created Program: Index - " << list[j].index << ", Arrival - " << list[j].arrival << ", Burst - " << list[j].burst << ", Priority - " << list[j].priority << endl;
		}

		if(type=="FCFS"){
			cout << fcfs(list, numPros);
		}

		if(type=="SJF"){
			cout << sjf(list, numPros);
		}

		if(type=="SRTF"){
			cout << srtf(list, numPros);
		}

		if(type=="RR"){
			cout << rr(list, numPros, 10);
		}

		if(type=="PN"){
			cout << pn(list, numPros);
		}

		if(type=="PP"){
			cout << pp(list, numPros);
		}
	}

	return 0;
}
