
#ifndef KMM_GRAPH_H
#define KMM_GRAPH_H

#include "../types.h"
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

using namespace std;

class Kernel{
public:
    unordered_set<VertexID> kernel_set;
    unordered_map<VertexID,vector<VertexID>> neighbor_unkernel;
    unordered_map<VertexID,vector<VertexID>> neighbor_kernel;
};


class Graph{
public:
    int vNum,eNum;
    VertexID max_degree_id = 0;
    vector<int> node_degree;
    vector<VertexLabel> node_label;
    vector<set<VertexID>> node_adj;
    unordered_map<VertexLabel,unordered_set<VertexID>> label_set;//label: node_id ...
    vector<multiset<VertexLabel>> neighbor_label; //node_id: nei_node01_label...
    Kernel *kernel;
    map<pair<VertexLabel ,VertexLabel>,set<pair<VertexID ,VertexID>>> edge_count; // <label_a,label_b> -> {(0,1),(2,3) ...}  label_a < label_b
public:
    void readGraph(const string &path);

};









#endif //KMM_GRAPH_H
