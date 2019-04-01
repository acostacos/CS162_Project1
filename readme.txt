-------------------------
CPU Scheduler
-------------------------

-------------------------
Global Variables
-------------------------
float cpuCounter - takes note of how many seconds the CPU was used
float cpuUtil[] - takes note of CPU Utilization for each clock cycle

int doneCounter - takes note of how many programs have finished
int throughput[] - takes note of throughput for each clock cycle

int isWaiting[] - takes note if the process is waiting
int waiting[] - takes note of waiting time for each process

int turnaround[] - takes note of turnaround time for each process
int response[] - takes note of the response time for each process

-------------------------
Functions and Structures
-------------------------

struct Program 
-Program class which specifies one program to be run in the CPU
-takes note of index, arrival time, burst time, priority, total running time and current time running of each program
-Program() - default constructor - sets all values to 0
-Program(int i, int a, int b, int p) - assigned constructor, sets values based on parameters
-void run() - makes the program run for one clock cycle, increments the runningTime and currentTime by 1

void quicksort(Program* arr, int low, int high)
-Used to perform quicksort on an array of programs
-Arranges them based on their arrival time
-From least arrival time to the highest arrival time

swap(Program* a, Program* b)
-helper function for quicksort()
-swaps the pointers for 2 different programs (thus swapping their position in the array)

updateThroughput(int timer)
-upates the thoughtput based on the given clock cycle

updateUtilization(int timer)
-updates the utilization based on the given clock cycle

void updateResponse(int i, int timer)
-updates the response time based on the given program and clock cycle

void updateTurnaround(int i, int timer)
-updates the turnaround time based on the given program and clock cycle

void updateWaiting(int i, int timer)
-updates the waiting time based on the given program and clock cycle

--------------------------------------------------------
Functions and Structures Under CPU Scheduling Algorithms
--------------------------------------------------------

struct FCFSCompare
-used as the comparer for the priority queue
-compares the arrival time (puts least in front and greatest at end)
-if there is a tie, lower index goes first

string fcfs(Program* arr, int size)
-function implementing the First Come First Serve algorithm
-uses a priority queue to hold the elements (priority queue uses FCFSCompare)
-adds the program into the priority queue when the arrival time has arrived
-runs the program until the running time is equal to the burst
-prints output once the program is done running
-Does this until all the programs have been placed in the priority queue and executed

struct SJFCompare
-used as the comparer for the priority queue
-compares the burst (puts least in front and greatest at end)
-if there is a tie, lower index goes first

string sjf(Program* arr, int size)
-similar to fcfs
-function implementing the Shortest Job First algorithm
-uses a priority queue to hold the elements (priority queue uses SJFCompare)
-adds the program into the priority queue when the arrival time has arrived
-runs the program until the running time is equal to the burst
-prints output once the program is done running
-Does this until all the programs have been placed in the priority queue and executed

struct SRTFCompare
-used as the comparer for the priority queue
-compares the remaining time which is given by burst-runningTime (puts least in front and greatest at end)
-if there is a tie, lower index goes first

string srtf(Program* arr, int size)
-function implementing the Shortest Remaining Time First algorithm
-uses a priority queue to hold the elements (priority queue uses SRTFCompare)
-adds the program into the priority queue when the arrival time has arrived
-runs the program until the running time is equal to the burst
-Preemptive - IF A program has less remaining time than the current running program, the program is pushed back into the queue and the top is selected as the running program
-prints output once the program is done running
-Does this until all the programs have been placed in the priority queue and executed

struct PCompare
-used as the comparer for the priority queue for PN and PP
-compares the priority (puts least in front and greatest at end)
-if there is a tie, lower index goes first

string pn(Program* arr, int size)
-similar to fcfs and sjf
-function implementing the Priority Non-Preemptive algorithm
-uses a priority queue to hold the elements (priority queue uses PCompare)
-adds the program into the priority queue when the arrival time has arrived
-runs the program until the running time is equal to the burst
-prints output once the program is done running
-Does this until all the programs have been placed in the priority queue and executed

string pp(Program* arr, int size)
-function implementing the Priority Preemptive algorithm
-uses a priority queue to hold the elements (priority queue uses PCompare)
-adds the program into the priority queue when the arrival time has arrived
-runs the program until the running time is equal to the burst
-Preemptive - IF A program has less priority than the current running program, the program is pushed back into the queue and the top is selected as the running program
-prints output once the program is done running
-Does this until all the programs have been placed in the priority queue and executed

struct RRCompare
-used as the comparer for the priority queue for RR
-compares the arrival time (puts least in front and greatest at end)
-if there is a tie, lower index goes first

string rr(Program* arr, int size, int quanTime)
-function implementing the Round Robin algorithm
-uses a priority queue to hold the elements (priority queue uses RRCompare)
-adds the program into the priority queue when the arrival time has arrived
-runs the program for the number of clock cycles depending on the quantum time
-If a program is added, it will be placed at the end of the queue
-prints output once the program is done running (even if it does not run for the complete quantum time)
-Does this until all the programs have been placed in the priority queue and executed

-------------------------
Main
-------------------------

main
-accepts all the inputs and creates an array of programs based on those
-calls a quick sort method to sort the programs of the array by arrival time
-calls the CPU scheduling algorithm function based on the input
-prints the average response time, wait time, and turn around time
-prints the throughput and cpu utilization based on user input

Inputs (in order):
int numTest - number of test cases
int numPros - number of programs in the test case 
string type - type of scheduling algorithm
int q - quantum time (only if type is Round Robin)
int arrival - arrival time of the current program
int burst - burst of the current program
int priority - priority of the current program
int tInput - clock cycle by where to compute for the throughput
int cInput - clock cycle by where to compute for the CPU utilization

