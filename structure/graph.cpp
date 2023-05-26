#include "graph.h"
#include <fstream>
#include <iostream>
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
