#include <iostream>
#include <fstream>
#include <ctime>
#include "structure/graph.h"
#include "structure/index.h"
#include "alg/alg.h"
using namespace std;

int main(){
    clock_t begin,end;
    double elapsedTime;
    bool flag;

    string query_path = "../test/insert/query_graph/Q_0";
    string data_path = "../test/insert/data_graph/data.graph";
    string insert_path = "../test/insert/data_graph/insertion.graph";

//    string query_path = "../test/querySet";
//    string data_path = "../test/dataSet";
//    string insert_path = "../test/insert_demo";

    Graph* query = new Graph();
    query->readGraph(query_path);
    query->set_kernel();
    Graph* data = new Graph();
    data->readGraph(data_path);
    Index* index = new Index(query->vNum,data->vNum);
    preProsessing(*query,*data,*index);


    ifstream ifs;
    ifs.open(insert_path);
    if(!ifs.is_open()){
        cout << insert_path << " open failed" << endl;
        exit(0);
    }
    char t;
    int a,b,c;
    int i = 0;
    vector<pair<int,int>> res;
    vector<int> res1;
    while(!ifs.eof()){
        cout<<i++;
        ifs>>t >>a >>b>>c;
        bool f = do_func(a,b,*query,*data,*index);
        if(f){
            res1.push_back(1);
//            res.emplace_back(a,b);

        }
    }
    for(auto i : res){
        cout<<i.first<<" "<<i.second<<endl;
    }
    cout<<res1.size();
//    do_func(8816,8817,*query,*data,*index);
//    do_func(105621,227771,*query,*data,*index);
//    do_func(180767,328784 ,*query,*data,*index);

    delete query;
    delete data;
    delete index;

    return 0;
/*
    string query_path = "../test/querySet";
    Graph* query = new Graph();
    query->readGraph(query_path);
    query->set_kernel();
    string data_path = "../test/dataSet";
    Graph* data = new Graph();
    data->readGraph(data_path);

    Index* index = new Index(query->vNum, data->vNum);
    preProsessing(*query,*data,*index);
    index->print_all();

    do_func(2,3,*query,*data,*index);
    do_func(6,13,*query,*data,*index);
    do_func(11,12,*query,*data,*index);



    delete query;
    delete data;
    delete index;





    return 0;
*/
    begin = clock();
    updateIndex(3,2,*query,*data,*index);
    updateIndex(2,3,*query,*data,*index);
    Match* m1 = new Match();

    subgraph_Match(2,3,*query,*data,*index,*m1);

//    flag = m1->set_Match_single(*query,*data,*index,1,3,0,2);
//    if(!flag) return 3;
//
//    Kernel_Match(*query,*data,*index,*m1);

    end = clock();
    elapsedTime = static_cast<double>(end-begin) / CLOCKS_PER_SEC;
    cout<<"elapsedTime:"<<elapsedTime<<endl;
    m1->print_res();


    begin = clock();
    updateIndex(6,13,*query,*data,*index);
    updateIndex(13,6,*query,*data,*index);
    Match* m2 = new Match();

    subgraph_Match(6,13,*query,*data,*index,*m2);

//    flag = m2->set_Match_single(*query,*data,*index,2,6,3,13);
////    m2->set_Match_double(*query,*data,*index,2,6,4,13);
//    if(!flag) return 3;
//    Kernel_Match(*query,*data,*index,*m2);

    end = clock();
    elapsedTime = static_cast<double>(end-begin) / CLOCKS_PER_SEC;
    cout<<"elapsedTime:"<<elapsedTime<<endl;
    m2->print_res();

    begin = clock();
    updateIndex(11,12,*query,*data,*index);
    updateIndex(12,11,*query,*data,*index);
    Match* m3 = new Match();

    subgraph_Match(11,12,*query,*data,*index,*m3);

//    flag = m3->set_Match_single(*query,*data,*index,4,11,3,12);
//    if(!flag) return 3;
//    Kernel_Match(*query,*data,*index,*m3);

    end = clock();
    elapsedTime = static_cast<double>(end-begin) / CLOCKS_PER_SEC;
    cout<<"elapsedTime:"<<elapsedTime<<endl;
    m3->print_res();











    return 0;

}