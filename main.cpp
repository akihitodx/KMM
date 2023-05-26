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
    index->print_all();


//a









    return 0;

}