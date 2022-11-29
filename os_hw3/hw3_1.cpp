#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int running = -1;

struct process{
    int pid = 0;
    int arrival_time = 0;
    int burst_time = 0;
    int wait_time = 0;
    int turnaround_time = 0;
    bool finish = false;
    bool running = false;
};

bool compare(process a, process b){
    if (a.burst_time == b.burst_time) {
        if (a.pid == running)
            return true;
        else if(b.pid == running)
            return false;
        else 
            return a.pid < b.pid;
    }
    else return a.burst_time < b.burst_time;
}

bool compare_arrival(process a, process b){
    return a.arrival_time < b.arrival_time;
}

bool compare_id(process a, process b){
    return a.pid < b.pid;
}

int main(){
    int num_process = 0;

    cin >> num_process;
    vector <process> List(num_process);
    for (int i = 0; i < num_process; i++){
        List[i].pid = i;
        cin >> List[i].arrival_time;
    }

    for (int i = 0; i < num_process; i++){
        cin >> List[i].burst_time;
    }
    
    int count = 0;
    int time = 0;
    int index = -1;
    bool all_finish = true;
    vector <process> current = List;
    sort(List.begin(), List.end(), compare_arrival);
    while (count < num_process){
        all_finish = true;
        sort(current.begin(), current.end(), compare);
        int temp = 0;
        for (int i = 0; i < num_process; i++){
            if (current[i].arrival_time <= time && !current[i].finish){
                temp = i;
                running = current[i].pid;
                index = current[i].pid;
                current[i].burst_time-=1;
                break;
            }
        }

        for (int i = 0; i < num_process; i++){
            if (List[i].pid == index){
                // cout << time << " " << List[i].pid << " " << current[temp].burst_time << endl;
                List[i].wait_time += time - current[temp].arrival_time;
                time += 1;
                current[temp].arrival_time = time;
                if (current[temp].burst_time == 0){
                    count += 1;
                    current[temp].finish = true;
                    List[i].turnaround_time = time - List[i].arrival_time;
                }
                break;
            }
        }
        // cout << count << endl;
    }
    int total_w= 0, total_t = 0; 
    sort(List.begin(), List.end(), compare_id);
    for (int i = 0; i < num_process; i++){
        total_w += List[i].wait_time;
        total_t += List[i].turnaround_time;
        cout << List[i].wait_time << " " << List[i].turnaround_time << "\n";
    }

    cout << total_w << " " << total_t << endl; 

    return 0;
}