    /*

        CS431 Scheduling Program
        Austin Sypolt
        10/28/19

    */
    
    #include <iostream>
    #include <iomanip>
    #include <fstream>
    #include <algorithm> 
    #include <iostream> 
    #include <cstdio>
    #include <ctime>
    using namespace std;


    int FIFO(int& programCount){
        int totalTime = 0;
        int avgTime;
        int count;
        int programNumber;
        int programTime;
        int response = 0;
        int averageResponse = 0;
        int waitTime = 0;
        int averageWait = 0;

        ifstream inFile;
        inFile.open("data.txt");
        
        cout <<endl<<endl;
        cout << "          |First in First Out Scheduling|" << endl;
        cout << "Process #  " << "Reponse Time  " << "Turnaround Time  " << "Wait time  " << endl; 
        while (!inFile.eof()) {
            if(count == programCount){ //Define input size
                break;
            }
            
            inFile >> programNumber >> programTime;
            totalTime = totalTime + programTime;
        
            cout << programNumber <<  "            " << totalTime <<  "           " <<  programTime << "               " << totalTime - programTime <<endl;
            response = totalTime + response;        
            waitTime = (totalTime - programTime) + waitTime;
            

            count++;
        }

        inFile.close();
        
        avgTime = totalTime/programCount;
        averageResponse = response/programCount;
        averageWait = waitTime/programCount;

        cout<<endl;
        cout << "Total Time:              " << totalTime << endl; 
        cout << "Average Turnaround Time: " << avgTime << endl; 
        cout << "Average Response Time:   " << averageResponse << endl;
        cout << "Average Wait Time:       " << averageWait << endl;
        
        cout<<endl<<endl;
        return 0;
    }

    void swap(int *xp, int *yp, int *xp2, int *yp2)  
    {  
        int temp = *xp;  
        *xp = *yp;  
        *yp = temp; 

        int temp2 = *xp2;  
        *xp2 = *yp2;  
        *yp2 = temp2;   
    }  

    int shortestJobFirst(int& programCount){
        ifstream inFile;
        inFile.open("data.txt");
        int count = 0;
        int programNumber[programCount] = {0};
        int programTime[programCount] = {0};
        int tmpTime;
        int tmpNumber;
        int totalTime = 0;
        int response = 0;
        int waitTime = 0;

        cout <<endl<<endl;
        cout << "          |Shortest Job First Scheduling|" << endl;
        cout << "Process #  " << "Reponse Time  " << "Turnaround Time  " << "Wait time  " << endl; 
        while (!inFile.eof()) {
            inFile >> programNumber[count] >> programTime[count];
            count++;
        }
        inFile.close();

        for(int i = 0; i<programCount-1; i++){
            for(int j = 0; j<programCount-i-1; j++){
                if(programTime[j] > programTime[j+1]){
                    swap(&programTime[j], &programTime[j+1], &programNumber[j], &programNumber[j+1]);
                }
            }
        }

        for(int i = 0; i<programCount; i++){
            totalTime = totalTime + programTime[i];
            response = totalTime + response; 
            waitTime = (totalTime - programTime[i]) + waitTime;
            cout << programNumber[i] <<  "             " << totalTime <<  "           " <<  programTime[i] << "               " << totalTime - programTime[i] <<endl;
        }
        
        
        int avgTime = totalTime/programCount;
        int averageResponse = response/programCount;
        int averageWait = waitTime/programCount;

        cout<<endl;
        cout << "Total Time:              " << totalTime << endl; 
        cout << "Average Turnaround Time: " << avgTime << endl; 
        cout << "Average Response Time:   " << averageResponse << endl;
        cout << "Average Wait Time:       " << averageWait << endl;
        
        cout<<endl<<endl;
        return 0;
    }

void findWaitingTime(int programNumber[], int programCount, int programTime[], int quantum) 
{ 
    int wt[programCount];
    int remainingProgramTime[programCount]; 
    for (int i = 0 ; i < programCount ; i++) 
        remainingProgramTime[i] =  programTime[i]; 
  
    int t = 0; // Current time 
    int totalTime = 0;
    int waitTime = 0;
    int response = 0;

    while (1) 
    { 
        bool done = true; 
        for (int i = 0 ; i < programCount; i++){ 
            if (remainingProgramTime[i] > 0) 
            { 
                done = false; // There is a pending process 
                if (remainingProgramTime[i] > quantum) 
                { 
                    t += quantum; 
                    remainingProgramTime[i] -= quantum; 
                } 
                else
                { 
                    t = t + remainingProgramTime[i]; 
                    wt[i] = t - programTime[i]; 
                    remainingProgramTime[i] = 0; 
                } 
            } 
        } 

        if (done == true) 
          break; 
    } 
    for(int i = 0; i<programCount; i++){
        totalTime = totalTime + programTime[i];
        response = programTime[i] + wt[i];
        waitTime = waitTime + wt[i];
        cout << i+1 <<  "             " << programTime[i] + wt[i] <<  "           " <<  programTime[i] << "               " << wt[i] <<endl;
        }

        int avgTime = totalTime/programCount;
        int averageResponse = response/programCount;
        int averageWait = waitTime/programCount;

        cout<<endl;
        cout << "Total Time:              " << totalTime << endl; 
        cout << "Average Turnaround Time: " << avgTime << endl; 
        cout << "Average Response Time:   " << averageResponse << endl;
        cout << "Average Wait Time:       " << averageWait << endl;
} 
  

    int roundRobin(int& programCount){
        ifstream inFile;
        inFile.open("data.txt");

        int count = 0;
        int programNumber[programCount] = {0};
        int programTime[programCount] = {0};

        cout <<endl<<endl;
        cout << "          |Round Robin Scheduling|" << endl;
        cout << "Process #  " << "Reponse Time  " << "Turnaround Time  " << "Wait time  " << endl; 

        while (!inFile.eof()) {
            inFile >> programNumber[count] >> programTime[count];
            count++;
        }

        int quantum = 10; //Time Quantum
        findWaitingTime(programNumber, programCount, programTime, quantum); 
    }

    int main() {
        ifstream inFile;
        int inFileProgramCount = 10; //Define number of elements that will be read from data.txt file
        
        inFile.open("data.txt");
        if (!inFile) {    
            cout << "Unable to open file." << endl;
        }
        else{
            FIFO(inFileProgramCount);
            shortestJobFirst(inFileProgramCount);
            roundRobin(inFileProgramCount);
            cout<<endl<<endl;
        }

        return 0;
    }