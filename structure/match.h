#ifndef KMM_MATCH_H
#define KMM_MATCH_H

#include "../types.h"
#include "graph.h"
#include "index.h"
#include <vector>
using namespace std;

class Match{
public:
    int count = 0;
    vector<pair<VertexID ,VertexID>> kernel_path;
    vector<VertexID> unkernel_path;
    vector<vector<vector<VertexID>>> res;
    vector<vector<VertexID>> match_table;
    unordered_set<VertexID> kernel_matched;
public:
    void set_Match(Graph &query,Graph &data,Index &index,VertexID is_query,VertexID data_node);
    void getPath(Graph &query,VertexID a);
    void getPath(Graph &query,int a,int b);

    void getUnkernel_path(Graph &query, int a);
    void print_res();
};

#endif //KMM_MATCH_H
