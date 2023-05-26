#ifndef KMM_INDEX_H
#define KMM_INDEX_H

#include "../types.h"
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <vector>
using namespace std;
class Index{
public:
    vector<unordered_set<VertexID>> com_index;  //data_id: query_id...
    vector<unordered_set<VertexID>> com_index_query; //query_id: data_id...
    vector<unordered_map<VertexID ,VertexLabel>> miss_index; //data_id: query_id->miss_query_label
    vector<unordered_set<VertexID>> error_index; //data_id: query_id...
public:
    Index(int queryNum,int dataNum);
    void print_miss_index();
    void print_com_index();
    void print_com_index_query();
    void print_error_index();

    void print_all();
};










#endif //KMM_INDEX_H
