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

//    string path = "../test/insert/query_graph/Q_0";
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

    begin = clock();
    updateIndex(3,2,*query,*data,*index);
    updateIndex(2,3,*query,*data,*index);
    Match* m1 = new Match();
    flag = m1->set_Match_single(*query,*data,*index,1,3,0,2);
    if(!flag) return 3;
    Kernel_Match(*query,*data,*index,*m1);

    end = clock();
    elapsedTime = static_cast<double>(end-begin) / CLOCKS_PER_SEC;
    cout<<"elapsedTime:"<<elapsedTime<<endl;
    m1->print_res();


    begin = clock();
    updateIndex(6,13,*query,*data,*index);
    updateIndex(13,6,*query,*data,*index);
    Match* m2 = new Match();
    flag = m2->set_Match_single(*query,*data,*index,2,6,3,13);
//    m2->set_Match_double(*query,*data,*index,2,6,4,13);
    if(!flag) return 3;
    Kernel_Match(*query,*data,*index,*m2);

    end = clock();
    elapsedTime = static_cast<double>(end-begin) / CLOCKS_PER_SEC;
    cout<<"elapsedTime:"<<elapsedTime<<endl;
    m2->print_res();

    begin = clock();
    updateIndex(11,12,*query,*data,*index);
    updateIndex(12,11,*query,*data,*index);
    Match* m3 = new Match();
    flag = m3->set_Match_single(*query,*data,*index,4,11,3,12);
    if(!flag) return 3;
    Kernel_Match(*query,*data,*index,*m3);

    end = clock();
    elapsedTime = static_cast<double>(end-begin) / CLOCKS_PER_SEC;
    cout<<"elapsedTime:"<<elapsedTime<<endl;
    m3->print_res();











    return 0;

}