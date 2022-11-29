#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct process{
    int pid = 0;
    int arrival_time = 0;
    int burst_time = 0;
    int wait_time = 0;
    int turnaround_time = 0;
    bool finish = false;
    bool in_queue = false;
};

int main(){
    int num_process = 0;
    int quantum = 0;

    cin >> num_process;
    vector <process> List(num_process);
    vector <int> tt;
    for (int i = 0; i < num_process; i++){
        List[i].pid = i;
        cin >> List[i].arrival_time;
        tt.push_back(List[i].arrival_time);
    }

    for (int i = 0; i < num_process; i++){
        cin >> List[i].burst_time;
    }
    cin >> quantum;
    
    int count = 0;
    int time = 0;
    int index = -1;
    bool all_finish = true;
    queue <int> current;
    current.push(0);
    List[0].in_queue = true;
    queue <int> fcfs;
    int last = -1;
    while (count < num_process){
        if (!current.empty()){
            int id = current.front();
            if(List[id].burst_time <= quantum){
                List[id].wait_time += time - List[id].arrival_time;
                time += List[id].burst_time;
                List[id].turnaround_time = time - tt[id];
                List[id].finish = true;
                current.pop();
                count += 1;
            }
            else {
                List[id].burst_time -= quantum;
                List[id].wait_time += time - List[id].arrival_time;
                time += quantum;
                current.pop();
                List[id].arrival_time = time;
                for(int i = 0; i < num_process; i++){
                    if (List[i].arrival_time <= time && !List[i].in_queue && List[i].finish == false){
                        current.push(i);
                        List[i].in_queue = true;
                    }
                }
                fcfs.push(id);
            }
            // cout << time << " " << List[id].pid << " " << List[id].burst_time << endl;
            
        }
        else if(!fcfs.empty()){
            int id = fcfs.front();
            List[id].burst_time -= 1;
            if (last != id){
                List[id].wait_time += time - List[id].arrival_time;
                last = id;
            }
            time += 1;
            // cout << time << " " << List[id].pid << " " << List[id].burst_time << endl;
            for(int i = 0; i < num_process; i++){
                if (List[i].arrival_time <= time && !List[i].in_queue && List[i].finish == false){
                    current.push(i);
                    List[i].in_queue = true;
                    last = -1;
                    List[id].arrival_time = time;
                    fcfs.pop();
                    fcfs.push(id);
                }
            }

            if(List[id].burst_time == 0){
                List[id].turnaround_time = time - tt[id];
                List[id].finish = true;
                fcfs.pop();
                count += 1;
            }
        }
    }
    
    int total_w= 0, total_t = 0; 
    for (int i = 0; i < num_process; i++){
        total_w += List[i].wait_time;
        total_t += List[i].turnaround_time;
        cout << List[i].wait_time << " " << List[i].turnaround_time << "\n";
    }

    cout << total_w << " " << total_t << endl; 

    return 0;
}