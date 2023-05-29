#include <iostream>
#include <fstream>
#include "structure/graph.h"
#include "structure/index.h"
#include "alg/alg.h"
using namespace std;

int main(){
//    string path = "../test/insert/query_graph/Q_0";
    string query_path = "../test/querySet";
    Graph* query = new Graph();
    query->readGraph(query_path);

    string data_path = "../test/dataSet";
    Graph* data = new Graph();
    data->readGraph(data_path);

    Index* index = new Index(query->vNum, data->vNum);
    preProsessing(*query,*data,*index);
    index->print_all();

    updateIndex(3,2,*query,*data,*index);
    updateIndex(2,3,*query,*data,*index);
    index->print_all();

    query->set_kernel();


    Match* m1 = new Match();
    m1->set_Match(*query,*data,*index,1,3);
//    m1->getPath(*query,1);
//    match_table[1].push_back(3);
    Kernel_Match(*query,*data,*index,*m1);
    m1->print_res();

    updateIndex(6,13,*query,*data,*index);
    updateIndex(13,6,*query,*data,*index);
    Match* m2 = new Match();
    m2->set_Match(*query,*data,*index,2,6);
    Kernel_Match(*query,*data,*index,*m2);
    m2->print_res();
cout<<"!!!!!!!!!!!!!!!!!!!!"<<endl;
    updateIndex(11,12,*query,*data,*index);
    updateIndex(12,11,*query,*data,*index);
    Match* m3 = new Match();
    m3->set_Match(*query,*data,*index,4,11);
    Kernel_Match(*query,*data,*index,*m3);
    m3->print_res();

//a









    return 0;

}