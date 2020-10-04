//
// Created by Amanuel Chukala on 5/7/2020.
//
#include <string.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

struct Process {
    int pid, arrival_time, burst_time, cpu_t = 0, finish_time = 0, waiting_time =0;
};
int totalburst_time = 0, totoalWaiting_time = 0, totalTurnaround_t = 0;
vector <Process> process_queue;
vector <Process> ready_queue;
vector <Process> finished_process;

void display(char msg[]);
void fcfs_scheduler(string input_file);
void srtf_scheduler(string input_file);
void rr_scheduler(string input_file, int qt);
int main(int argc, char* argv[]) {

    string arg1(argv[1]); //convert pointer argv to string
    string arg2(argv[2]);
    if((arg2 == "FCFS") || (arg2 == "fcfs"))
    {
        char scheduler_alg[] = "FCFS";
        display(scheduler_alg);
        fcfs_scheduler(arg1);
    }
    else if((arg2 == "SRTF") || (arg2 == "srtf"))
    {
        char scheduler_alg[] = "SRTF";
        display(scheduler_alg);
        srtf_scheduler(arg1);
    }

    else if((arg2 == "RR" )|| (arg2 == "rr"))
    {
        int arg3 = stoi(argv[3]);
        char scheduler_alg[] = "RR";
        display(scheduler_alg);
        rr_scheduler(arg1, arg3);
    }
    else
        {
        cout << "please enter the right scheduling algorithm!";
        exit(1);
        }
        return 0;
}

void fcfs_scheduler(string input_file)
{
    int line = 0;
    int column1 = 0;
    int column2 = 0;
    int current_pid = 0;
    Process current_process;
    ifstream inFile;
    inFile.open(input_file);

    if (!inFile)
    {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    while (inFile >> line)
    {
        inFile >> column1;
        inFile >> column2;
        totalburst_time = totalburst_time + column2;
        Process temp_process;
        temp_process.pid = line;
        temp_process.arrival_time = column1;
        temp_process.burst_time = column2;
        process_queue.push_back(temp_process);
    }
    inFile.close();

    current_pid = process_queue[0].pid;
    current_process = process_queue[0];
    process_queue.erase(process_queue.begin());
    cout << "P" << current_pid;

    for (int i = 0; i <= totalburst_time-1; i++)
    {
        current_process.finish_time++;
        current_process.cpu_t++;
        current_process.burst_time = current_process.burst_time - 1;
        for (int s = 0; s < process_queue.size(); s++)
        {
            if (process_queue[s].arrival_time > i) break;
            else
                process_queue[s].waiting_time++;
            totoalWaiting_time++;
        }
        if (current_process.burst_time == 0 )
        {
            if(current_process.burst_time == 0 && process_queue.size() ==0)
            {
                finished_process.push_back(current_process);
                for (int t = 0; t < finished_process.size(); t++)
                {
                    if (current_process.pid == finished_process[t].pid)
                        finished_process[t].finish_time = i + 1;
                }
                break;
            }
            finished_process.push_back(current_process);
            for (int t = 0; t < finished_process.size(); t++)
            {
                if (current_process.pid == finished_process[t].pid)
                    finished_process[t].finish_time = i + 1;
            }
            current_process = process_queue[0];
            process_queue.erase(process_queue.begin());
            current_pid = current_process.pid;
            cout << "P" << current_pid;
        }
        else cout << "  ";
    }
    cout << endl;

    for (int x = 0; x < totalburst_time; x++) cout << "* ";
    cout << "\n(each star represents one ms)\n";

    cout <<"+------------------------------------------------------------------------------+\n";
    cout << "PID " << " Arrival "<< " CPU-Burst "<< " Finish "
         << " Waiting-Time "<< " Turnaround "<< " No.of Context-Switch \n";
    for(int j = 0; j < finished_process.size(); j++) {
        cout << fixed << setprecision(1)
             << " " << setw(5) << left << finished_process[j].pid
             << " " << setw(7) << left << finished_process[j].arrival_time
             << " " << setw(11) << left << finished_process[j].cpu_t
             << " " << setw(10) << left << finished_process[j].finish_time
             << " " << setw(12) << left << finished_process[j].waiting_time
             << " " << setw(10) << left << finished_process[j].finish_time - finished_process[j].arrival_time;
        totalTurnaround_t = totalTurnaround_t + (finished_process[j].finish_time - finished_process[j].arrival_time);
        cout << " " << setw(5) << left << 0 << endl;
    }
    cout <<"\n+------------------------------------------------------------------------------+\n";
    cout << fixed << setprecision(2)
         << "\nAverage CPU burst time = " << (float)totalburst_time/finished_process.size() << " ms, \n"
         << "Average waiting time = " << (float)totoalWaiting_time/finished_process.size()<< " ms\n"
         << "Average turn-around time = " << (float)totalTurnaround_t/finished_process.size() << " ms, \n"
         << "Total No. of Context Switching Performed = " << 0 << endl;
}

void srtf_scheduler(string input_file) {
    int line = 0;
    int column1 = 0;
    int column2 = 0;
    int current_pid;
    Process current_process;;
    bool upcoming_process = true;
    ifstream inFile;
    inFile.open(input_file);

    if (!inFile)
    {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    while (inFile >> line)
    {
        inFile >> column1;
        inFile >> column2;
        totalburst_time = totalburst_time + column2;
        Process temp_process;
        temp_process.pid = line;
        temp_process.arrival_time = column1;
        temp_process.burst_time = column2;
        process_queue.push_back(temp_process);
    }
    inFile.close();

    current_pid = process_queue[0].pid;
    current_process = process_queue[0];
    process_queue.erase(process_queue.begin());
    cout << "P" << current_pid;

    for (int i = 1; i <= totalburst_time; ++i)
    {
        if (process_queue.size() == 0) upcoming_process = false;
        current_process.burst_time = current_process.burst_time - 1;
        current_process.finish_time++;
        current_process.cpu_t++;
        for(int s = 0; s < process_queue.size(); s++)
        {
            if(process_queue[s].arrival_time > i) break;
            else
                process_queue[s].waiting_time++;
            totoalWaiting_time++;
        }

        for(int t = 0; t < ready_queue.size(); t++)
        {
            ready_queue[t].waiting_time++;
            totoalWaiting_time++;
        }


        if (current_process.burst_time == 0)
        {
            finished_process.push_back(current_process);
            for (int t = 0; t < finished_process.size(); t++)
            {
                if (current_process.pid == finished_process[t].pid)
                    finished_process[t].finish_time = i+1;
            }

            if (upcoming_process)
            {
                if (process_queue[0].burst_time > ready_queue[0].burst_time)
                {
                    ready_queue.push_back(current_process);
                    current_process = ready_queue[0];
                    ready_queue.erase(ready_queue.begin());
                    current_pid = current_process.pid;
                    cout << "P" << current_pid;
                } else
                    {
                    current_process = process_queue[0];
                    process_queue.erase(process_queue.begin());
                    current_pid = current_process.pid;
                    cout << "P" << current_pid;
                }
            }
            else if(ready_queue.size() != 0)
            {
                current_process = ready_queue[0];
                ready_queue.erase(ready_queue.begin());
                current_pid = current_process.pid;
                cout << "P" << current_pid;
            }
            else break;

        } else if (i == process_queue[0].arrival_time)
        {
            if (process_queue[0].burst_time < current_process.burst_time)
            {
                //has_priority =
                ready_queue.push_back(current_process);
                current_process = process_queue[0];
                process_queue.erase(process_queue.begin());
                current_pid = current_process.pid;
                cout << "P" << current_pid;
            } else
                {
                ready_queue.push_back(process_queue[0]);
                process_queue.erase(process_queue.begin());
                cout << "  ";

            }
        }
        else cout << "  ";
    }
    finished_process.push_back(current_process);
    cout << endl;
    for (int x = 0; x < totalburst_time; x++) cout << "* ";
    cout << "\n(each star represents one ms)\n";
    cout <<"+------------------------------------------------------------------------------+\n";
    cout << "PID " << " Arrival "<< " CPU-Burst "<< " Finish "
         << " Waiting-Time "<< " Turnaround "<< " No.of Context-Switch \n";
    for(int j = 0; j < finished_process.size()-1; j++) {
        cout << fixed << setprecision(1)
             << " " << setw(5) << left << finished_process[j].pid
             << " " << setw(7) << left << finished_process[j].arrival_time
             << " " << setw(11) << left << finished_process[j].cpu_t
             << " " << setw(10) << left << finished_process[j].finish_time
             << " " << setw(12) << left << finished_process[j].waiting_time
             << " " << setw(10) << left << finished_process[j].finish_time - finished_process[j].arrival_time;
        totalTurnaround_t = totalTurnaround_t + (finished_process[j].finish_time - finished_process[j].arrival_time);
        cout << " " << setw(5) << left << 0 << endl;
    }
    cout << fixed << setprecision(2)
         << "\nAverage CPU burst time = " << (float)totalburst_time/finished_process.size() << " ms, \n"
         << "Average waiting time = " << (float)totoalWaiting_time/finished_process.size()<< " ms\n"
         << "Average turn-around time = " << (float)totalTurnaround_t/finished_process.size() << " ms, \n"
         << "Total No. of Context Switching Performed = " << 0 << endl;
}

void rr_scheduler(string input_file, int qt)
{
    int quantum_time = qt;
    int line = 0;
    int column1 = 0;
    int column2 = 0;
    ifstream inFile;
    int current_pid;
    Process current_process;
    bool upcoming_process = true;
    inFile.open(input_file);

    if (!inFile)
    {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    while (inFile >> line)
    {
        inFile >> column1;
        inFile >> column2;
        totalburst_time = totalburst_time + column2;
        Process temp_process;
        temp_process.pid = line;
        temp_process.arrival_time = column1;
        temp_process.burst_time = column2;
        process_queue.push_back(temp_process);
    }
    inFile.close();

    current_pid = process_queue[0].pid;
    current_process = process_queue[0];
    process_queue.erase(process_queue.begin());
    cout << "P" << current_pid << "";

    for (int i = 0; i <= totalburst_time-1; i++)
    {
        if (process_queue.size() == 0) upcoming_process = false;
        quantum_time--;
        current_process.finish_time++;
        current_process.cpu_t++;
        current_process.burst_time = current_process.burst_time - 1;

        for(int s = 0; s < process_queue.size(); s++)
        {
            if(process_queue[s].arrival_time > i) break;
            else
                process_queue[s].waiting_time++;
            totoalWaiting_time++;
        }

        for(int t = 0; t < ready_queue.size(); t++)
        {
            ready_queue[t].waiting_time++;
            totoalWaiting_time++;
        }

        if (current_process.burst_time == 0)
        {

            finished_process.push_back(current_process);
            quantum_time = qt;
            for (int t = 0; t < finished_process.size(); t++)
            {
                if (current_process.pid == finished_process[t].pid)
                    finished_process[t].finish_time = i+1;
            }

            if (upcoming_process && (process_queue[0].arrival_time <= i))
            {
                current_process = process_queue[0];
                process_queue.erase(process_queue.begin());
                current_pid = current_process.pid;
                cout << "P" << current_pid << "";
            }
            else if(ready_queue.size() != 0)
            {
                current_process = ready_queue[0];
                ready_queue.erase(ready_queue.begin());
                current_pid = current_process.pid;
                cout << "P" << current_pid;
            }
            else break;
        }
        else if (quantum_time == 0)
        {
            quantum_time = qt;
            if (upcoming_process && (process_queue[0].arrival_time <= i))
            {
                ready_queue.push_back(current_process);
                current_process = process_queue[0];
                process_queue.erase(process_queue.begin());
                current_pid = current_process.pid;
                cout << "P" << current_pid << "";
            } else
                {
                ready_queue.push_back(current_process);
                current_process = ready_queue[0];
                ready_queue.erase(ready_queue.begin());
                current_pid = current_process.pid;
                cout << "P" << current_pid << "";
                }
        } else cout << "  ";

    }

    cout << endl;
    for (int x = 0; x < totalburst_time; x++) cout << "* ";
    cout << "\n(each star represents one ms)\n\n";
    cout <<"+------------------------------------------------------------------------------+\n";
    cout << "PID " << " Arrival "<< " CPU-Burst "<< " Finish "
         << " Waiting-Time "<< " Turnaround "<< " No.of Context-Switch \n";
    for(int j = 0; j < finished_process.size(); j++) {
        cout << fixed << setprecision(1)
             << " " << setw(5) << left << finished_process[j].pid
             << " " << setw(7) << left << finished_process[j].arrival_time
             << " " << setw(11) << left << finished_process[j].cpu_t
             << " " << setw(10) << left << finished_process[j].finish_time
             << " " << setw(12) << left << finished_process[j].waiting_time
             << " " << setw(10) << left << finished_process[j].finish_time - finished_process[j].arrival_time;
        totalTurnaround_t = totalTurnaround_t + (finished_process[j].finish_time - finished_process[j].arrival_time);
        cout << " " << setw(5) << left << 0 << endl;
    }
    cout <<"+------------------------------------------------------------------------------+\n";
    cout << fixed << setprecision(2)
         << "\nAverage CPU burst time = " << (float)totalburst_time/finished_process.size() << " ms, \n"
         << "Average waiting time = " << (float)totoalWaiting_time/finished_process.size()<< " ms\n"
         << "Average turn-around time = " << (float)totalTurnaround_t/finished_process.size() << " ms, \n"
         << "Total No. of Context Switching Performed = " << 0 << endl;
}

void display(char msg[]){

    char alg_type[10];
    strcpy(alg_type, msg);
    printf("\n************************************************************\n"
           "************ Scheduling algorithm : %s *******************\n"
           "************************************************************\n\n", alg_type);
}