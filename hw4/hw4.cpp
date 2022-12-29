#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

bool compare(pair<int,int> a, pair<int,int> b){
    return a.second < b.second;
}

bool compare1(pair<int,pair<int,int>> a, pair<int,pair<int,int>> b){
    if (a.second.second == b.second.second)
        return a.second.first < b.second.first;
    else 
        return a.second.second < b.second.second;
}

int main(){
    int fifo_fault = 0;
    int leru_fault = 0;
    int lfu_fault = 0;

    int frame;
    int length;
    

    cin >> frame;
    cin >> length;
    vector <int> a(length);
    for(int i = 0; i < length; i++){
        cin >> a[i];
    }

    vector <pair<int,int>> fifo;
    bool full = false;
    int start = 0;

    for (int i = 0; i < length; i++){
        sort(fifo.begin(), fifo.end(), compare);
        bool same = false;
        if((fifo.size()-start) == frame) full =true;

        if (fifo.size() == 0){
            fifo.push_back(make_pair(a[i],i));
            // cout << a[i] << " " << i << " " << "fault" << endl;
            fifo_fault++;
        }
        else{
            if(!full){
                int j= 0;
                for(; j < fifo.size(); j++){
                    if(a[i] == fifo[j].first) {
                        // fifo[j].second=i;
                        // cout << fifo[j].first << " " << i << endl;
                        same = true;
                        break;
                    }
                }
                if(!same){
                    fifo.push_back(make_pair(a[i],i));
                    // cout << a[i] << " " << i << " " << "fault" << endl;
                    fifo_fault++;
                }   
            }
            else{
                int j= start;
                for(; j < fifo.size(); j++){
                    if(a[i] == fifo[j].first) {
                        // fifo[j].second=i;
                        same = true;
                        // cout << fifo[j].first << " " << i << endl;
                        break;
                    }
                }
                if(!same){
                    fifo.push_back(make_pair(a[i],i));
                    // cout << a[i] << " " << i << " " << "fault" << endl;
                    start++;
                    fifo_fault++;
                }
            }
        }
    }

    cout << fifo_fault << endl;

    vector <pair<int,int>> leru;
    full = false;
    start = 0;

    for (int i = 0; i < length; i++){
        sort(leru.begin(), leru.end(), compare);
        bool same = false;
        if((leru.size()-start) == frame) full =true;

        if (leru.size() == 0){
            leru.push_back(make_pair(a[i],i));
            // cout << a[i] << " " << i << " " << "fault" << endl;
            leru_fault++;
        }
        else{
            if(!full){
                int j= 0;
                for(; j < leru.size(); j++){
                    if(a[i] == leru[j].first) {
                        leru[j].second=i;
                        // cout << fifo[j].first << " " << i << endl;
                        same = true;
                        break;
                    }
                }
                if(!same){
                    leru.push_back(make_pair(a[i],i));
                    // cout << a[i] << " " << i << " " << "fault" << endl;
                    leru_fault++;
                }   
            }
            else{
                int j= start;
                for(; j < leru.size(); j++){
                    if(a[i] == leru[j].first) {
                        leru[j].second=i;
                        same = true;
                        // cout << fifo[j].first << " " << i << endl;
                        break;
                    }
                }
                if(!same){
                    leru.push_back(make_pair(a[i],i));
                    // cout << a[i] << " " << i << " " << "fault" << endl;
                    start++;
                    leru_fault++;
                }
            }
        }
    }

    cout << leru_fault << endl;

    vector <pair<int,pair<int,int>>> lfu;
    full = false;
    start = 0;

    for (int i = 0; i < length; i++){
        sort(lfu.begin()+start, lfu.end(), compare1);
        // for (int j = start; j < lfu.size(); j++){
        //     cout << lfu[j].first << " ";
        // }
        // cout << endl;
        bool same = false;
        if((lfu.size()-start) == frame) full =true;

        if (lfu.size() == 0){
            lfu.push_back(make_pair(a[i],make_pair(i,1)));
            // cout << a[i] << " " << i << " " << "fault" << endl;
            lfu_fault++;
        }
        else{
            if(!full){
                int j= 0;
                for(; j < lfu.size(); j++){
                    if(a[i] == lfu[j].first) {
                        lfu[j].second.second+=1;
                        // cout << lfu[j].first << " " << lfu[j].second.first  << " " << lfu[j].second.second << endl;
                        same = true;
                        break;
                    }
                }
                if(!same){
                    lfu.push_back(make_pair(a[i],make_pair(i,1)));
                    // cout << a[i] << " " << i << " " << "fault" << endl;
                    lfu_fault++;
                }   
            }
            else{
                int j= start;
                for(; j < lfu.size(); j++){
                    if(a[i] == lfu[j].first) {
                        lfu[j].second.second+=1;
                        same = true;
                        // cout << lfu[j].first << " " << lfu[j].second.first << " " << lfu[j].second.second << endl;
                        break;
                    }
                }
                if(!same){
                    lfu.push_back(make_pair(a[i],make_pair(i,1)));
                    // cout << a[start] <<  a[i] << " " << i << " " << "fault" << endl;
                    start++;
                    lfu_fault++;
                }
            }
        }
    }

    cout << lfu_fault << endl;

    return 0;
}