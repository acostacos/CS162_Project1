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

	swap(&arr[left], &arr[high]);

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
}

//SJFCompare class used when inserting Programs in the priority queue in the SJF Schduling method
//Can use the ff code instead of compare struc
/*
sort(p,p+n, [](const Node a, const Node b) -> bool{
	// comparator logic
});
*/
struct SJFCompare{
public:
	bool operator()(Program& p1, Program& p2){
		//false compares the next item in the queue, true inserts the program before the program it's currently being compared to
		//cout << p1.index << " and " << p2.index << endl;

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

struct SRTFCompare{
public:
	bool operator()(Program& p1, Program& p2){
		//false compares the next item in the queue, true inserts the program before the program it's currently being compared to
		//cout << p1.index << " and " << p2.index << endl;

		//check p1 is longer than p2
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

	//push all of the elements that arrive at 0 inside
	int initialChecker = checkArrival(arr, size, cp, timer);
		if(initialChecker>0){
			for(int i=0; i<initialChecker; i++){
				cout << arr[cp].index << endl;
				pq.push(arr[cp]);
				cp++;
			}
	}

	//run while pq is not empty and while not all the programs have been added to the priority queue
	while(cp<size || !pq.empty()){
		Program p = pq.top();
		pq.pop();

		cout << "Top: " << p.index << endl;;

		while(p.burst!=0){
			//check if any of the processes enter with the timer
			int progChecker = checkArrival(arr, size, cp, timer);
			if(progChecker>0){
				for(int i=0; i<progChecker; i++){
					cout << arr[cp].index << endl;
					pq.push(arr[cp]);
					cp++;
				}
			}

			p.run();
			timer++;
		}

		out << timer << " " << p.index << " " << p.runningTime << "X" << endl;

	}

	output = out.str();
	return output;
}


string srtf(Program* arr, int size){
	string output; stringstream out;
	priority_queue<Program, vector<Program>, SRTFCompare> pq;
	int timer = 0;
	int cp = 0;

	//push all of the elements that arrive at 0 inside
	int initialChecker = checkArrival(arr, size, cp, timer);
		if(initialChecker>0){
			for(int i=0; i<initialChecker; i++){
				cout << arr[cp].index << endl;
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
			pq.push(p);
			switchChecker = false;
		}

		p = pq.top();
		pq.pop();

		cout << "Top: " << p.index << endl;;

		while(p.burst!=0){
			//check if any of the processes enter with the timer
			int progChecker = checkArrival(arr, size, cp, timer);
			if(progChecker>0){
				for(int i=0; i<progChecker; i++){
					cout << arr[cp].index << endl;
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

		out << timer << " " << p.index << " " << p.runningTime << "X" << endl;

	}

	output = out.str();
	return output;
}

/*

PN, PP, RR

string pn(){

}

string pp(){
	
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

		//Sort array to make the least access time first and the greatest access time last
		quicksort(list, 0, numPros-1);

		for(int j=0; j<numPros; j++){
			cout << "Created Program: Index - " << list[j].index << ", Arrival - " << list[j].arrival << ", Burst - " << list[j].burst << ", Priority - " << list[j].priority << endl;
		}

		if(type=="SJF"){
			cout << sjf(list, numPros);
		}

		if(type=="STRF"){
			cout << srtf(list, numPros);
		}
	}

	return 0;
}
