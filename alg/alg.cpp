#include "alg.h"

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

void Kernel_Match(Graph &query, Graph &data, Index &index, Match &match){
    if (match.count == match.kernel_path.size()) {
        match.res.push_back(match.match_table);
        return;
    }

    VertexID is_query = match.kernel_path[match.count].first;
    VertexID next = match.kernel_path[match.count].second;



    for (auto m_id: match.match_table[is_query]) {
        for (auto i: data.node_adj[m_id]) {
            if (data.node_label[i] != query.node_label[next]  ||  index.com_index[i].find(next) == index.com_index[i].end()) {
                continue;
            }
            auto old_match = match.match_table;
            ++match.count;
            match.match_table[next].push_back(i);


            bool flag = false;
            if(match.kernel_matched.count(next) == 0 ){
                flag = unKernel_Match(next,i,query,data,index,match);

            }
            if(flag){
                match.kernel_matched.insert(next);
                Kernel_Match(query, data, index,match);
                match.kernel_matched.erase(next);
                --match.count;
                match.match_table = old_match;
            } else{
                --match.count;
                match.match_table[next].pop_back();
            }



        }
    }

}

bool unKernel_Match(VertexID is_query,VertexID data_node, Graph &query, Graph &data, Index &index, Match &match){
    auto unkernel_set = query.kernel->neighbor_unkernel[is_query];
    for(VertexID qid: unkernel_set){
        vector<VertexID> temp;
        for (auto i: data.node_adj[data_node]) {
            if (data.node_label[i] != query.node_label[qid] ||
                index.com_index[i].find(qid) == index.com_index[i].end()) {
                continue;
            }
            temp.push_back(i);
        }
        if(temp.empty()) return false;
        if (match.match_table[qid].empty()) {
            match.match_table[qid] = temp;
        } else {
            vector<int> change;
            set_intersection(match.match_table[qid].begin(), match.match_table[qid].end(), temp.begin(),
                             temp.end(), back_inserter(change));
            if (change.empty()) return false;
            match.match_table[qid] = {change.begin(),change.end()};
        }
    }
    return true;
}

void subgraph_Match(VertexID left_node,VertexID right_node,Graph &query,Graph &data, Index &index, Match &match){
    VertexLabel left_label = data.node_label[left_node];
    VertexLabel right_label = data.node_label[right_node];
//    if(data.node_label[left_node]==data.node_label[right_node]){
//        //考虑等价->同构
//    }
    int flag=0;
    set<pair<VertexID,VertexID>> match_edge;
    auto it = query.edge_count.find({left_label,right_label});
    if(it != query.edge_count.end()){
        flag = 1;
        match_edge = it->second;
    } else{
        it = query.edge_count.find({right_label,left_label});
        if(it != query.edge_count.end()){
            flag = -1;
            match_edge = it->second;
        } else{
            return;
        }
    }
    vector<pair<VertexID , VertexID>> should_match;
    auto com_left = index.com_index[left_node];
    auto com_right = index.com_index[right_node];
    if(flag==1){
        for(auto edge: match_edge){
            if (com_left.find(edge.first) != com_left.end() && com_right.find(edge.second) != com_right.end()) {
                should_match.emplace_back(edge);
            }
        }
         for(auto edge: should_match){
            bool left_is_kernel = query.kernel->kernel_set.find(edge.first) != query.kernel->kernel_set.end();
            bool right_is_kernel = query.kernel->kernel_set.find(edge.second) != query.kernel->kernel_set.end();
            bool ff;
            if(left_is_kernel && right_is_kernel){
                ff = match.set_Match_double(query,data,index,edge.first,left_node,edge.second,right_node);
                if(!ff) continue;
                Kernel_Match(query,data,index,match);
            } else{
                if(left_is_kernel){
                    ff = match.set_Match_single(query,data,index,edge.first,left_node,edge.second,right_node);
                    if(!ff) continue;
                    Kernel_Match(query,data,index,match);
                } else{
                    ff = match.set_Match_single(query,data,index,edge.second,right_node,edge.first,left_node);
                    if(!ff) continue;
                    Kernel_Match(query,data,index,match);
                }
            }
        }
    }else{
        for(auto edge: match_edge){
            if (com_left.find(edge.second) != com_left.end() && com_right.find(edge.first) != com_right.end()) {
                should_match.emplace_back(edge);
            }
        }
        for(auto edge: should_match){
            bool left_is_kernel = query.kernel->kernel_set.find(edge.second) != query.kernel->kernel_set.end();
            bool right_is_kernel = query.kernel->kernel_set.find(edge.first) != query.kernel->kernel_set.end();
            bool ff;
            if(left_is_kernel && right_is_kernel){
                ff = match.set_Match_double(query,data,index,edge.second,left_node,edge.first,right_node);
                if(!ff) continue;
                Kernel_Match(query,data,index,match);
            } else{
                if(left_is_kernel){
                    ff = match.set_Match_single(query,data,index,edge.second,left_node,edge.first,right_node);
                    if(!ff) continue;
                    Kernel_Match(query,data,index,match);
                } else{
                    ff = match.set_Match_single(query,data,index,edge.first,right_node,edge.second,left_node);
                    if(!ff) continue;
                    Kernel_Match(query,data,index,match);
                }
            }
        }
    }

}

void do_func(VertexID a,VertexID b,Graph &query, Graph &data,Index &index){
    clock_t begin,end;
    double elapsedTime;
    begin = clock();
    updateIndex(a,b,query,data,index);
    updateIndex(b,a,query,data,index);
    Match *match = new Match();
    subgraph_Match(a,b,query,data,index,*match);
    end = clock();
    elapsedTime = static_cast<double>(end-begin) / CLOCKS_PER_SEC;
    cout<<"elapsedTime:"<<elapsedTime<<endl;
    match->print_res();
    delete match;
}