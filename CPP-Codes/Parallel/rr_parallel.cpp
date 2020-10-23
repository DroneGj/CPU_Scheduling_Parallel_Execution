#include <iostream>
#include <algorithm> 
#include <iomanip>
#include <queue> 
#include <cstring>
#include <omp.h>
#include <time.h>
using namespace std;

struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};

bool compare1(process p1, process p2) 
{ 
    return p1.arrival_time < p2.arrival_time;
}

bool compare2(process p1, process p2) 
{  
    return p1.pid < p2.pid;
}

int main() {

    int pro = 100, qunat=10;
    int arr[100] = {95, 79, 21, 44, 14, 55, 46, 32, 83, 92, 47, 8, 49, 51, 75, 48, 74, 49, 41, 35, 82, 76, 79, 20, 31, 35, 42, 72, 53, 87, 40, 70, 65, 11, 7, 93, 11, 49, 21, 38, 54, 14, 93, 86, 14, 67, 15, 36, 99, 87, 88, 59, 89, 99, 6, 74, 5, 88, 70, 15, 90, 15, 77, 4, 7, 60, 81, 30, 92, 52, 50, 97, 65, 21, 96, 63, 38, 62, 13, 7, 91, 82, 38, 23, 23, 82, 71, 88, 4, 12, 94, 25, 73, 24, 87, 7, 75, 72, 96, 38};
    int bur[100] = {88, 49, 53, 14, 62, 74, 99, 88, 52, 8, 85, 5, 59, 8, 48, 44, 92, 89, 22, 42, 18, 52, 22, 43, 11, 60, 29, 100, 47, 0, 4, 8, 53, 13, 40, 95, 80, 60, 73, 55, 66, 76, 60, 31, 31, 68, 63, 6, 51, 81, 93, 96, 84, 73, 68, 27, 68, 91, 66, 57, 11, 53, 68, 52, 56, 20, 98, 89, 13, 57, 89, 65, 84, 47, 95, 33, 97, 26, 80, 31, 55, 37, 28, 19, 33, 85, 7, 52, 81, 45, 42, 99, 57, 37, 98, 77, 3, 1, 84, 33};

    double time_spent = 0.0;
    int n;
    int tq;
    struct process p[100];
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

    // cout<<"Enter the number of processes: ";
    // cin>>n;
    n = pro;
    // cout<<"Enter time quantum: ";
    // cin>>tq;
    tq = qunat;

    for(int i = 0; i < n; i++) {
        // cout<<"Enter arrival time of process "<<i+1<<": ";
        // cin>>p[i].arrival_time;
        p[i].arrival_time = arr[i];
        // cout<<"Enter burst time of process "<<i+1<<": ";
        // cin>>p[i].burst_time;
        p[i].burst_time = bur[i];
        burst_remaining[i] = p[i].burst_time;
        p[i].pid = i+1;
        // cout<<endl;
    }
    clock_t begin = clock();
    sort(p,p+n,compare1);

    queue<int> q;
    int current_time = 0;
    q.push(0);
    int completed = 0;
    int mark[100];
    memset(mark,0,sizeof(mark));
    mark[0] = 1;

    while(completed != n) {
        idx = q.front();
        q.pop();

        if(burst_remaining[idx] == p[idx].burst_time) {
            p[idx].start_time = max(current_time,p[idx].arrival_time);
            total_idle_time += p[idx].start_time - current_time;
            current_time = p[idx].start_time;
        }

        if(burst_remaining[idx]-tq > 0) {
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
#pragma omp parallel for schedule(static, n)
        for(int i = 1; i < n; i++) {
            if(burst_remaining[i] > 0 && p[i].arrival_time <= current_time && mark[i] == 0) {
                q.push(i);
                mark[i] = 1;
            }
        }
        if(burst_remaining[idx] > 0) {
            q.push(idx);
        }

        if(q.empty()) {
            for(int i = 1; i < n; i++) {
                if(burst_remaining[i] > 0) {
                    q.push(i);
                    mark[i] = 1;
                    break;
                }
            }
        }


    }

    avg_turnaround_time = (float) total_turnaround_time / n;
    avg_waiting_time = (float) total_waiting_time / n;
    avg_response_time = (float) total_response_time / n;
    cpu_utilisation = ((p[n-1].completion_time - total_idle_time) / (float) p[n-1].completion_time)*100;
    throughput = float(n) / (p[n-1].completion_time - p[0].arrival_time);

    sort(p,p+n,compare2);

    cout<<endl;
    cout<<"#P\t"<<"AT\t"<<"BT\t"<<"ST\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"RT\t"<<"\n"<<endl;

    for(int i = 0; i < n; i++) {
        cout<<p[i].pid<<"\t"<<p[i].arrival_time<<"\t"<<p[i].burst_time<<"\t"<<p[i].start_time<<"\t"<<p[i].completion_time<<"\t"<<p[i].turnaround_time<<"\t"<<p[i].waiting_time<<"\t"<<p[i].response_time<<"\t"<<"\n"<<endl;
    }
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    cout << "RR Parallel\n";
    cout<<"Average Turnaround Time = "<<avg_turnaround_time<<endl;
    cout<<"Average Waiting Time = "<<avg_waiting_time<<endl;
    cout<<"Average Response Time = "<<avg_response_time<<endl;
    cout<<"CPU Utilization = "<<cpu_utilisation<<"%"<<endl;
    cout<<"Throughput = "<<throughput<<" process/unit time"<<endl;
    cout << "Time elpased = " << time_spent << "seconds";
}
