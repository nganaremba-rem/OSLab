#include <stdio.h>

void takeUserInput(int*, int*, int*, int);
void sort(int*, int*, int*, int);
void display(int*, int*, int*, int);
void sortSameAT(int*, int*, int*, int);
void ganttChart(int*, int*, int*, int, int*, int*, int*);
void drawGanttChart(int*, int*, int*, int);
void calculateOther(int*, int*, int, int*, int*, int*, double*, double*);

int main(){
	int pid[10], at[10], bt[10], noOfProcess, tat[10], wt[10];
	double  avgTAT, avgWT; // double or float since a division might result decimal
	int ganttPID[10], ganttAT[10], ganttCompletion[10];

	printf("Enter the number of process: ");
	scanf("%i", &noOfProcess);

	// taking user input
	takeUserInput(pid,at,bt,noOfProcess);
	
	// Printing entered data
	printf("\n-- Entered Data ---");
	display(pid, at, bt, noOfProcess);

	// sort all 
	sort(pid, at, bt, noOfProcess);
	sortSameAT(pid, at, bt, noOfProcess);

	printf("\n-- After Sorting ---");
	display(pid, at, bt, noOfProcess);
	// calculation of Gantt Chart
	ganttChart(pid, at, bt, noOfProcess, ganttPID, ganttAT, ganttCompletion);
	// Calculation of Turn Around, Waiting time, Average Turn Around and Average Waiting time
	calculateOther(tat, wt, noOfProcess, at, ganttCompletion, bt,&avgTAT,&avgWT);

	// Printing all with Completion, Turn Around and Waiting time
	printf("\n--- FINAL RESULT ---");
	printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
	for(int i=0; i < noOfProcess; i++){
		printf("%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], ganttCompletion[i], tat[i], wt[i]);
	}
	//Printing Average Turn around and Waiting 
	printf("\nAverage Turn Around Time = %.2f units\n",avgTAT);
	printf("Average Waiting Time = %.2f units\n",avgWT);

	// drawing / displaying Gantt Chart
	drawGanttChart(ganttPID,ganttAT,ganttCompletion,noOfProcess);
}

void takeUserInput(int *pid, int *at, int *bt, int noOfProcess){
	for(int i=0; i<noOfProcess; i++){
		printf("\nEnter Process ID: ");
		scanf("%d", &pid[i]);
		printf("Enter Arrival time for P%d : ", pid[i]);
		scanf("%d", &at[i]);
		printf("Enter Burst Time for P%d : ", pid[i]);
		scanf("%d", &bt[i]);
	}
}


void sort(int *pid, int *at, int *bt, int noOfProcess){
	// Declaring temp variables to swap while sorting
	int pidTemp, atTemp, btTemp;
	// Selecting one element and comparing to every element one by one and sorting
	for(int i=0; i<noOfProcess; i++){
		for(int j=i; j<noOfProcess; j++){
			if(at[i] > at[j]){ // if the selected element is larger than comparing element then swap all
				pidTemp = pid[i]; // storing the larger data into temporay variable to swap
				atTemp = at[i];
				btTemp = bt[i];

				pid[i] = pid[j]; // since the data is already stored in temporary var now we can assigned smaller data into the index where larger data was present before
				at[i] = at[j];
				bt[i] = bt[j];

				pid[j] = pidTemp; // assigning the temporary data (larger) into the index where smaller data was before
				at[j] = atTemp;
				bt[j] = btTemp; 
			}
		}
	}
	return;
}

void display(int *pid, int *at, int *bt, int noOfProcess){
	// displaying like a table
	printf("\nPID\tAT\tBT\n");
	for(int i=0; i < noOfProcess; i++){
		printf("%d\t%d\t%d\n", pid[i], at[i], bt[i]);
	}
	return;
}

void sortSameAT(int *pid, int *at, int *bt, int noOfProcess){
	// sorting -> if they have same Arrival Time sort again order by lower Process ID
	int pidTemp, atTemp, btTemp;
	for(int i=0; i<noOfProcess; i++){
		for(int j=i; j<noOfProcess; j++){
			if(at[i] == at[j]){ // if arrival time is same
				if(pid[i] > pid[j]){ // if the selected process id is greater than swap with the smaller one
					pidTemp = pid[i]; // storing the larger data into temporay variable to swap
					atTemp = at[i]; // " " " " 
					btTemp = bt[i]; // " " " " 

					pid[i] = pid[j]; // since the data is already stored in temporary var now we can assigned smaller data into the index where larger data was present before
					at[i] = at[j]; // " " " " "
					bt[i] = bt[j]; // " " " "

					pid[j] = pidTemp; // assigning the temporary data (larger) into the index where smaller data was before
					at[j] = atTemp; // " " " "
					bt[j] = btTemp; // " " " "
				}
			}
		}
	}
}

void ganttChart(int *pid, int *at, int *bt, int noOfProcess, int *ganttPID, int *ganttAT, int *ganttCompletion){
	int prevCompletion = 0;

	for(int i=0; i<noOfProcess; i++){
		if(at[i]-prevCompletion > 0){ // if \there is a difference between the last completion time and new process arrival time
			ganttAT[i] = at[i];
			ganttPID[i] = pid[i];
			ganttCompletion[i] = at[i] + bt[i]; // CT = AT + BT
			prevCompletion = ganttCompletion[i];
		}else{ // if there is no difference between the last completion time and the new process arrival time
			ganttAT[i] = prevCompletion; // then prev completion will be the new arrival time 
			ganttPID[i] = pid[i];
			ganttCompletion[i] = ganttAT[i] + bt[i]; // CT = AT + BT
			prevCompletion = ganttCompletion[i];
		}
	}
}

void drawGanttChart(int *ganttPID, int *ganttAT, int *ganttCompletion, int noOfProcess){
	printf("\n\n---- Gantt Chart ----\n");
	for(int i=0; i<noOfProcess; i++){ // printing --- design xD
		printf("-------");
	}
	printf("\n");
	for(int i=0; i<noOfProcess; i++){
		if(i==0){ // if first element
			if(ganttAT[i] != 0){ // if the first arrival time is not 0
				printf(" // |");
			}
		}
		else if(ganttAT[i] != ganttCompletion[i-1]){ // if there is a difference between last completion and new process arrival time
			printf(" // |");
		}
		printf("  P%d |", ganttPID[i]);  // printing process ID
	}
	printf("\n");
	for(int i=0; i<noOfProcess; i++){  // closing the ----- design
		printf("-------");
	}
	printf("\n");
	for(int i=0; i<noOfProcess; i++){ // for printing completion time in gantt chart
		if(i==0){ // if first element
			if(ganttAT[i] != 0){ // if the first element doesn't starts from 0
				// code for null
				printf("      ");
			}
			printf("%d    %d",ganttAT[i], ganttCompletion[i]);
		}else{ // for the remaining elements
			if(ganttCompletion[i-1] == ganttAT[i]){ // if last completion time == new process arrival time
				printf("     %d", ganttCompletion[i]); 
			}else{ // if last element is not equal to new process arrival time
				printf("    %d     %d",ganttAT[i], ganttCompletion[i]);
			}
		}
	}
	printf("\n");
}

// function to calculate Turn Around time, Waiting time, Average TAT, Average WT
void calculateOther(int *tat, int *wt, int noOfProcess, int *at, int *ganttCompletion, int *bt, double *avgTAT, double *avgWT){
	int TATsum = 0, WTsum = 0;
	for(int i=0; i<noOfProcess; i++){
		tat[i] = ganttCompletion[i] - at[i]; // TAT = CT - AT
		wt[i] = tat[i] - bt[i]; // WT = TAT - BT
		TATsum += tat[i]; // taking the sum of all Turn Around time
		WTsum += wt[i]; // taking the sum of all Waiting time
	}

	// since it is assigning to a double datatype, the operands needs to by type cast into double
	*avgTAT = (double)TATsum/(double)noOfProcess; // calculating Average Turn Around Time
	*avgWT = (double)WTsum/(double)noOfProcess; // calcutating Average Waiting time
	return;
}
