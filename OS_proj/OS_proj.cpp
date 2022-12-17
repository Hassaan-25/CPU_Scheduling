#include<iostream>
#include<vector>
#include<algorithm>
#include<conio.h>
#include <iomanip>
#include <queue> 


using namespace std;
using std::vector;

struct Process {
	int BurstTime;
	int ArrivalTime;
	int id;
	Process(int _bt, int _id) {
		BurstTime = _bt;
		ArrivalTime = 0;
		id = _id;
	}

	Process(int _bt, int _at, int _id) {
		BurstTime = _bt;
		ArrivalTime = _at;
		id = _id;
	}
};
struct process_node {
	int pid;
	int arrival_time;
	int burst_time;
	int start_time;
	int completion_time;
	int turnaround_time;
	int waiting_time;
	int response_time;
};


class shortest_job_first {
public:
	void swap(int* x, int* y) //function to swap two entries
	{
		int temp = *x;
		*x = *y;
		*y = temp;
	}
	void arrange(int matrix[][6], int total)
	{

		for (int i = 0; i < total; i++) //arrangement on basis of burst time
		{
			for (int j = 0; j < total - i - 1; j++)
			{
				if (matrix[j][2] > matrix[j + 1][2])
				{
					for (int k = 0; k < 5; k++)
					{
						swap(&matrix[j][k], &matrix[j + 1][k]);
					}
				}

			}
		}
		for (int i = 0; i < total; i++) //arrangement on basis of arrival time
		{
			for (int j = 0; j < total - i - 1; j++)
			{
				if (matrix[j][2] == matrix[j + 1][2] || matrix[j][1] > matrix[j + 1][1])
				{
					for (int k = 0; k < 5; k++)
					{
						swap(&matrix[j][k], &matrix[j + 1][k]);
					}
				}
			}
		}
	}
	void calculations(int matrix[][6], int total)
	{
		int c, value;
		matrix[0][3] = matrix[0][1] + matrix[0][2];
		matrix[0][5] = matrix[0][3] - matrix[0][1];
		matrix[0][4] = matrix[0][5] - matrix[0][2];
		for (int i = 1; i < total; i++)
		{
			c = matrix[i - 1][3];
			int foo = matrix[i][2];
			for (int j = i; j < total; j++)
			{
				if (c >= matrix[j][1] && foo >= matrix[j][2])
				{
					foo = matrix[j][2];
					value = j;
				}
			}
			matrix[value][3] = c + matrix[value][2];
			matrix[value][5] = matrix[value][3] - matrix[value][1];
			matrix[value][4] = matrix[value][5] - matrix[value][2];
			for (int k = 0; k < 6; k++)
			{
				swap(&matrix[value][k], &matrix[i][k]);
			}
		}
	}
};

bool operator < (Process p1, Process p2) {
	if (p1.ArrivalTime < p2.ArrivalTime) {
		return true;
	}
	return false;
}

class Round_Robin_proj {
public:
	static bool compare1(process_node p1, process_node p2)
	{
		return p1.arrival_time < p2.arrival_time;
	}

	static bool compare2(process_node p1, process_node p2)
	{
		return p1.pid < p2.pid;
	}

};



class ProcessSchedule {
private:
	vector<Process> p, WaitingTime, sorted;
	double AvgTime;
	int realTime = 0;
	int n;
	double AvgWaitTime = 0;
public:
	ProcessSchedule(vector<Process>& incoming_P, int tProcess) {
		p = incoming_P;
		n = tProcess;
	}
	double AvgtimeWithoutArr() {
		int totalTime = 0;
		for (vector<Process>::iterator it = p.begin(); it != p.end(); it++) {
			totalTime += it->BurstTime;
		}
		return totalTime / n;
	}
	void dispProcesses() {
		cout << "Processes \t Burst Time \t Arrival Time" << endl;
		for (vector<Process>::iterator it = p.begin(); it != p.end(); it++) {
			cout << 'P' << it->id << " \t\t " << it->BurstTime << " \t\t " << it->ArrivalTime;
			cout << endl;
		}

		//cout << "\nThe average waiting time is: " << AvgtimeWithoutArr() << " ms." << endl;
	}

	vector<Process> sortingArr() {
		sorted = p;
		sort(sorted.begin(), sorted.end());
		cout << "Order of completion: ";
		for (vector<Process>::iterator it = sorted.begin(); it != sorted.end(); it++) {
			if (it == sorted.end() - 1) {
				cout << 'P' << it->id;
				break;
			}
			cout << 'P' << it->id << ", ";
		}
		return sorted;
	}
	void wait() {
		int LastArrTime = 0;
		int Waiting = 0;
		int TotalWtime = 0;
		vector<int> wait;
		vector<Process>::iterator next;
		for (vector<Process>::iterator it = sorted.begin();
			it != sorted.end();
			it++) {
			next = it;
			realTime += it->BurstTime;

			Waiting = realTime - it->ArrivalTime;
			cout << "The waiting time for P" << it->id << " is : " << Waiting << endl;
			wait.push_back(Waiting);
		}

		for (auto& n : wait)
			TotalWtime += n;
		cout << endl;
		cout << "The Average waiting time for the Processes is: " << CalAvgWait(AvgTime) << " ms";
	}

	double CalAvgWait(int tTime) {
		return AvgWaitTime = tTime / n;
	}

};
void displayFCFS() {
	vector<Process> p;
	int totalNumber;
	int id = 0, bt, at;
	char exit = ' ';
	cout << endl;
	do {
		cout << "Enter the Process details for the Process P" << id << endl;
		cout << "Enter the Process Burst Time: ";
		cin >> bt;
		while (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "Input is invalid, try again" << endl;
			cin >> bt;
		}
		cout << "Enter the Process Arrival Time: ";
		cin >> at;
		while (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "Input is invalid, try again" << endl;
			cin >> at;
		}
		Process newP(bt, at, id);
		p.push_back(newP);
		id++;
		cout << "Are these all the processes you want? (y/n)" << endl;
		cin >> exit;
		if (exit == 'y')
			break;
		while (cin.fail()) {
			cin.clear();
			cout << "Input is invalid, try again" << endl;
			cin >> exit;
		}
		cout << endl;
	} while (exit != 'Y' || exit != 'y');

	totalNumber = p.size();

	ProcessSchedule scheduler(p, totalNumber);
	scheduler.dispProcesses();
	cout << endl;

	scheduler.sortingArr();
	cout << endl;
	scheduler.wait();
	cout << endl;

	cout << endl;


}

void dispSJF() {
	shortest_job_first obj;
	int dataMatrix[10][6]; //2D array for data input
	int num_processes;  // total number of processes
	cout << "Enter number of Processes: ";
	cin >> num_processes;
	for (int i = 0; i < num_processes; i++)
	{
		cout << "Process P" << i + 1 << "\n";
		cout << "Enter Process Id: "; //first coloumn corresponds to process ID
		cin >> dataMatrix[i][0];
		cout << "Enter Arrival Time: ";//second coloumn corresponds to arrival time
		cin >> dataMatrix[i][1];
		cout << "Enter Burst Time: ";//third coloumn corresponds to burst time
		cin >> dataMatrix[i][2];
	}
	cout << "Before Sorting\n";
	cout << "Process ID\tArrival Time\tBurst Time\n";
	for (int i = 0; i < num_processes; i++)
	{
		cout << dataMatrix[i][0] << "\t\t" << dataMatrix[i][1] << "\t\t" << dataMatrix[i][2] << "\n";
	}

	obj.arrange(dataMatrix, num_processes);
	obj.calculations(dataMatrix, num_processes);
	cout << "Final Result:\n";
	cout << "Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";//fourth=waiting time,fifth=TAT
	double wait = 0;//to get total of waiting time
	for (int i = 0; i < num_processes; i++)
	{
		cout << dataMatrix[i][0] << "\t\t" << dataMatrix[i][1] << "\t\t" << dataMatrix[i][2] << "\t\t" << dataMatrix[i][4] << "\t\t" << dataMatrix[i][5] << "\n";
		wait = wait + dataMatrix[i][4];
	}
	cout << "\nAverage waiting time : " << wait / num_processes << ".03" << endl;


}
int main() {
	cout << "--------------------\t WELCOME TO CPU SCHEDULING SIMULATION \t ---------------------\n";
	cout << "\t\tBasic Information:\n";
	cout << "CPU Scheduling is a process of determining which process \nwill own CPU for execution while another process is on hold. \nThe main task of CPU scheduling is to make sure that whenever the CPU remains idle, \nthe OS at least select one of the processes available in the ready queue for execution.\n";
	cout << endl;
	char returnBack;
	do {
		cout << "What type of scheduling algorithm do you want?" << endl;
		cout << "1. First Come, First Served \n2. Shortest Job First \n3. RoundRobin" << endl;
		int choice;
		cin >> choice;
		while (cin.fail() || choice > 3 || choice < 0) {
			cin.clear();
			cin.ignore();
			cout << "Input is invalid, try again" << endl;
			cout << "What type of scheduling algorithm do you want?" << endl;
			cout << "1. First Come, First Served \n2. Shortest Job First \n3. RoundRobin" << endl;
			cin >> choice;
		}
		system("cls");
		switch (choice)
		{
		case 1:
			system("color 02");
			cout << "Welcome to FCFS scheduling, get average waiting time and order of completion";
			cout << "First Come First Served is a First in, first out type \nof algorithm that helps the processor to provide the resources to the first process that comes in.\n";
			displayFCFS();
			break;
		case 2:
			system("color 04");
			cout << "Welcome to SJF scheduling, get average waiting time and order of completion";
			cout << endl;
			dispSJF();
			break;
		case 3:
			Round_Robin_proj pj;
			int n;
			int tq;
			struct process_node p[100];
			float avg_turnaround_time;
			float avg_waiting_time;
			float avg_response_time;
			float cpu_utilisation;
			int total_turnaround_time = 0;
			int total_waiting_time = 0;
			int total_response_time = 0;
			int total_idle_time = 0;
			float throughput;
			int burst_remaining[100];
			int idx;

			cout << setprecision(2) << fixed;
			cout << "Welcome to the Round Robin Algorthim\nA round robin is an arrangement of choosing all elements in a group equally in some rational order, \nusually from the top to the bottom of a list and then starting again at the top of the list and so on.";
			cout << "\nEnter the number of processes: ";
			cin >> n;
			cout << "Enter time quantum: ";
			cin >> tq;

			for (int i = 0; i < n; i++) {
				cout << "Enter arrival time of process_node " << i + 1 << ": ";
				cin >> p[i].arrival_time;
				cout << "Enter burst time of process_node " << i + 1 << ": ";
				cin >> p[i].burst_time;
				burst_remaining[i] = p[i].burst_time;
				p[i].pid = i + 1;
				cout << endl;
			}

			sort(p, p + n, Round_Robin_proj::compare1);

			queue<int> q;
			int current_time = 0;
			q.push(0);
			int completed = 0;
			int mark[100];
			memset(mark, 0, sizeof(mark));
			mark[0] = 1;

			while (completed != n) {
				idx = q.front();
				q.pop();

				if (burst_remaining[idx] == p[idx].burst_time) {
					p[idx].start_time = max(current_time, p[idx].arrival_time);
					total_idle_time += p[idx].start_time - current_time;
					current_time = p[idx].start_time;
				}

				if (burst_remaining[idx] - tq > 0) {
					burst_remaining[idx] -= tq;
					current_time += tq;
				}
				else {
					current_time += burst_remaining[idx];
					burst_remaining[idx] = 0;
					completed++;

					p[idx].completion_time = current_time;
					p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
					p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
					p[idx].response_time = p[idx].start_time - p[idx].arrival_time;

					total_turnaround_time += p[idx].turnaround_time;
					total_waiting_time += p[idx].waiting_time;
					total_response_time += p[idx].response_time;
				}

				for (int i = 1; i < n; i++) {
					if (burst_remaining[i] > 0 && p[i].arrival_time <= current_time && mark[i] == 0) {
						q.push(i);
						mark[i] = 1;
					}
				}
				if (burst_remaining[idx] > 0) {
					q.push(idx);
				}

				if (q.empty()) {
					for (int i = 1; i < n; i++) {
						if (burst_remaining[i] > 0) {
							q.push(i);
							mark[i] = 1;
							break;
						}
					}
				}


			}

			avg_turnaround_time = (float)total_turnaround_time / n;
			avg_waiting_time = (float)total_waiting_time / n;
			avg_response_time = (float)total_response_time / n;
			cpu_utilisation = ((p[n - 1].completion_time - total_idle_time) / (float)p[n - 1].completion_time) * 100;
			throughput = float(n) / (p[n - 1].completion_time - p[0].arrival_time);

			sort(p, p + n, Round_Robin_proj::compare2);

			cout << endl;
			cout << "#P\t" << "AT\t" << "BT\t" << "ST\t" << "CT\t" << "TAT\t" << "WT\t" << "RT\t" << "\n" << endl;

			for (int i = 0; i < n; i++) {
				cout << p[i].pid << "\t" << p[i].arrival_time << "\t" << p[i].burst_time << "\t" << p[i].start_time << "\t" << p[i].completion_time << "\t" << p[i].turnaround_time << "\t" << p[i].waiting_time << "\t" << p[i].response_time << "\t" << "\n" << endl;
			}
			cout << "Average Turnaround Time = " << avg_turnaround_time << endl;
			cout << "Average Waiting Time = " << avg_waiting_time << endl;
			cout << "Average Response Time = " << avg_response_time << endl;
			cout << "CPU Utilization = " << cpu_utilisation << "%" << endl;
			cout << "Throughput = " << throughput << " process_node/unit time" << endl;
			break;


		}
		cout << endl;
		cout << endl;
		cout << "Do you want re simulate the process scheduling?" << endl;
		cin >> returnBack;
		while (cin.fail()) {
			cin.ignore();
			cin.clear();
			cout << "Invalid Input" << endl;
			cout << "Do you want re simulate the process scheduling?(y/n)" << endl;
		}
		system("cls");
	} while (returnBack != 'Y');

}
