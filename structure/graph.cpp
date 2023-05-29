#include "graph.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

void Graph::readGraph(const string &path){
    ifstream ifs;
    ifs.open(path);
    if(!ifs.is_open()){
        cout << path << " open failed" << endl;
        exit(0);
    }
    int count_v=0, count_e=0;
    char type;
    VertexID id_0,id_1;
    VertexLabel v_label;
    EdgeLabel e_label;
    ifs >>type;
    while(type=='v'){
        ifs >>id_0 >>v_label;
        this->node_label.push_back(v_label);
        this->label_set[v_label].insert(id_0);
        ++count_v;
        ifs >> type;
    }
    this->node_degree.resize(count_v,0);
    this->neighbor_label.resize(count_v);
    this->node_adj.resize(count_v);
    this->vNum = count_v;
    while(!ifs.eof()){
        ifs >>id_0 >>id_1 >>e_label;
        ++count_e;
        this->node_degree[id_0]++;
        this->node_degree[id_1]++;
        this->neighbor_label[id_0].insert(node_label[id_1]);
        this->neighbor_label[id_1].insert(node_label[id_0]);
        this->node_adj[id_0].insert(id_1);
        this->node_adj[id_1].insert(id_0);
        pair<int,int> label_group;
        if(node_label[id_0]<node_label[id_1]){
            label_group = {node_label[id_0],node_label[id_1]};
            this->edge_count[label_group].insert({id_0, id_1});
        }else{
            label_group = {node_label[id_1],node_label[id_0]};
            this->edge_count[label_group].insert({id_1, id_0});
        }
        ifs >> type;
    }
    ifs.close();
    this->eNum = count_e;
    for(auto i : this->node_degree){
        if(this->node_degree[this->max_degree_id] < i){
            this->max_degree_id = i;
        }
    }

}
int findMax(const unordered_set<int> &adj,const vector<int> &degree){
    int maxDegree = -1;
    int maxId = -1;
    for(auto i : adj){
        if (maxDegree<degree[i]){
            maxDegree = degree[i];
            maxId = i;
        }
    }
    return maxId;
}

void Graph::set_kernel(){
    this->kernel = new Kernel();
    priority_queue<pair<int&,VertexID>> queue;
    auto degree = this->node_degree;
    unordered_set<VertexID> adj;
    this->kernel->kernel_set.insert(this->max_degree_id);
    degree[max_degree_id] = -1;
    int node_count = this->vNum - 1;
    //初始化
    for(VertexID node: this->node_adj[max_degree_id]){
        if(--degree[node] == 0){
            --node_count;
            continue;
        }
        queue.emplace(degree[node],node);
        adj.insert(node);
    }
    //寻找核心
    int max_loc = -1;
    while(node_count>0) {
        max_loc = findMax(adj, degree);
        this->kernel->kernel_set.insert(max_loc);
        adj.erase(max_loc);
        --node_count;
        degree[max_loc] = -1;
        for (VertexID node: this->node_adj[max_loc]) {
            if (degree[node] < 0) continue;
            if (--degree[node] == 0) {
                --node_count;
                continue;
            }
            if (adj.count(node) == 0) {
                adj.insert(node);
            }
        }
    }
    //set neighbor_kernel
    for(auto id: this->kernel->kernel_set){
        auto nei = this->node_adj[id];
        for(auto i:nei){
            if(this->kernel->kernel_set.find(i)!=this->kernel->kernel_set.end()){
                this->kernel->neighbor_kernel[id].push_back(i);
            }
        }
    }
    //set neighbor_unkernel
    for(auto i : this->kernel->kernel_set){
        vector<VertexID> adj_s (this->node_adj[i].begin(),this->node_adj[i].end());  //节点的所有邻居
        vector<VertexID> ker (this->kernel->kernel_set.begin(),this->kernel->kernel_set.end());
        sort(ker.begin(),ker.end());
        set_difference(adj_s.begin(),adj_s.end(),ker.begin(),ker.end(), back_inserter(this->kernel->neighbor_unkernel[i]));
    }
}
