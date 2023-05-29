#include "match.h"
#include <iostream>
#include <queue>
void Match::print_res() {
    cout<<"res=================="<<endl;
    for(auto i: res){
        for(auto j : i){
            cout<<"(";
            for(auto k : j){
                cout<<k<<" ";
            }
            cout<<")";
        }
        cout<<endl<<"====================="<<endl;
    }
}

void Match::getPath(Graph &query, int a) {
    queue<VertexID> qqq;
    queue<VertexID> other;
    unordered_set<int> matched;
    matched.insert(a);
    for(auto i : query.kernel->neighbor_kernel[a]){
        qqq.push(i);
        other.push(a);
    }
    while(!qqq.empty()){
        auto temp = qqq.front();
        qqq.pop();
        matched.insert(temp);
        auto f = other.front();
        other.pop();
        kernel_path.emplace_back(f,temp);
        for(auto i : query.kernel->neighbor_kernel[temp]){
            if(matched.find(i)==matched.end()){
                qqq.push(i);
                other.push(temp);
            }
        }
    }
    getUnkernel_path(query,a);
}

void Match::getUnkernel_path(Graph &query, int a){
    queue<int> q;
    unordered_set<int> ss = query.kernel->kernel_set;
    q.push(a);
    ss.erase(a);
    while(!q.empty()){
        int temp = q.front();
        q.pop();
        unkernel_path.push_back(temp);
        for(auto i: query.kernel->neighbor_kernel[temp]){
            if(ss.find(i) != ss.end()){
                q.push(i);
                ss.erase(i);
            }

        }
    }
}