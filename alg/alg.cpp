#include "alg.h"
#include <algorithm>

bool com_Match(multiset<int> &queryNode,multiset<int> &dataNode){
    // dataNode 包含 querNode
    return includes(dataNode.begin(),dataNode.end(),queryNode.begin(),queryNode.end());
}

VertexLabel miss_Match(multiset<int> &queryNode,multiset<int> &dataNode){
    vector<int> target;
    set_difference(queryNode.begin(),queryNode.end(),dataNode.begin(),dataNode.end(),back_inserter(target));
    if(target.size()==1){
        return target[0];
    }
    return -1;
}


void preProsessing(Graph &query, Graph &data,Index &index){
    for(VertexID data_node = 0; data_node<data.vNum; ++data_node){
        auto label_set = query.label_set[data.node_label[data_node]];
        for(VertexLabel query_node: label_set){
            //度不满足匹配条件
            if(query.node_degree[query_node] > data.node_degree[data_node]){
                continue;
            }
            if(com_Match(query.neighbor_label[query_node],data.neighbor_label[data_node])){
                index.com_index[data_node].insert(query_node);
                index.com_index_query[query_node].insert(data_node);
//                index.miss_index[data_node].insert({query_node,-1});
            }

        }
    }
}