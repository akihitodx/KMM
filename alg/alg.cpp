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
        for(VertexID query_node: label_set){
            //度不满足匹配条件
            if(query.node_degree[query_node] > data.node_degree[data_node]){
                continue;
            }
            if(com_Match(query.neighbor_label[query_node],data.neighbor_label[data_node])){
                //满足完全匹配基本条件
                index.com_index[data_node].insert(query_node);
                index.com_index_query[query_node].insert(data_node);
            }else{
                //如果不满足包含，进行缺一比较  返回值>=0 则是缺失的标签 -1则不满足缺一
                auto tar = miss_Match(query.neighbor_label[query_node],data.neighbor_label[data_node]);
                if( tar != -1){
                    //满足缺一 添加进索引  data_id: query_id->miss_query_label ...
                    index.miss_index[data_node][query_node] = tar;
                }else{
                    index.error_index[data_node].insert(query_node);
                }
            }

        }
    }
}

void updateIndex(VertexID node, VertexID nei ,Graph &query, Graph &data, Index &index){
    data.neighbor_label[node].insert(data.node_label[nei]);
    data.node_adj[node].insert(nei);

    vector<VertexID> com;
    for(auto it: index.miss_index[node]){
        if(it.second== data.node_label[nei]){
            //构成完全匹配
            com.push_back(it.first);
        }
    }
    for(VertexID query_id: com){
        index.com_index[node].insert(query_id);
        index.com_index_query[query_id].insert(node);
        index.miss_index[node].erase(query_id);
    }

    for(auto it: index.error_index[node]){
        //对于失败匹配 尝试进行缺一匹配
        VertexLabel tar = miss_Match(query.neighbor_label[it],data.neighbor_label[node]);
        if(tar!= -1){ //构成了缺一匹配
            index.miss_index[node][it] = tar;
        }
    }

}