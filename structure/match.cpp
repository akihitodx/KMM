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

void Match::getPath(Graph &query, int is_query) {
    queue<VertexID> qqq;
    queue<VertexID> other;
    unordered_set<int> matched;
    matched.insert(is_query);
    for(auto i : query.kernel->neighbor_kernel[is_query]){
        qqq.push(i);
        other.push(is_query);
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

}

void Match::getUnkernel_path(Graph &query, int is_query){
    queue<int> q;
    unordered_set<int> ss = query.kernel->kernel_set;
    q.push(is_query);
    ss.erase(is_query);
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
void Match::set_Match(Graph &query,Graph &data,Index &index,VertexID is_query,VertexID data_node){
    getPath(query,is_query);
    getUnkernel_path(query,is_query);
    this->match_table.resize(query.vNum);
    this->match_table[is_query].push_back(data_node);

    for(VertexID id: query.kernel->neighbor_unkernel[is_query]){
        vector<VertexID> temp;
        for (auto i: data.node_adj[data_node]) {
            if (data.node_label[i] != query.node_label[id]  ||  index.com_index[i].find(id) == index.com_index[i].end()) {
                continue;
            }
            temp.push_back(i);
        }
        this->match_table[id] = temp;
    }
    this->kernel_matched.insert(is_query);
}