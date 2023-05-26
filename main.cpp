#include <iostream>
#include <fstream>
#include "structure/graph.h"
#include "structure/index.h"

using namespace std;

int main(){
//    string path = "../test/insert/query_graph/Q_0";
    string query_path = "../test/querySet";
    Graph* query = new Graph();
    query->readGraph(query_path);

    string data_path = "../test/dataSet";
    Graph* data = new Graph();
    query->readGraph(query_path);

    Index* index = new Index(query->vNum, data->vNum);











    return 0;

}