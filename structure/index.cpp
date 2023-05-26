#include "index.h"
#include <iostream>

Index::Index(int queryNum, int dataNum) {
    com_index.resize(dataNum); //完全匹配集 数据节点索引
    miss_index.resize(dataNum); //缺一匹配 数据节点索引 data_id: query_id->miss_query_id ...
    com_index_query.resize(queryNum); //完全匹配集 查询节点索引
    error_index.resize(dataNum);
}

void Index::print_com_index() {
    cout<<"com_index================"<<endl;
    int n = 0;
    for (auto i: this->com_index) {
        cout<<n++<<": ";
        for (auto j: i) {
            cout<<j<<" ";
        }
        cout<<endl;
    }
    cout<<"================"<<endl;
}

void Index::print_miss_index() {
    cout << "miss_index================" << endl;
    int n = 0;
    for (auto i: this->miss_index) {
        cout<<n++<<": ";
        for (auto j: i) {
            cout<<j.first<<"->"<<j.second<<" ";
        }
        cout<<endl;
    }
    cout<<"================"<<endl;
}

void Index::print_com_index_query() {
    cout<<"com_index_query================"<<endl;
    int n = 0;
    for (auto i: this->com_index_query) {
        cout<<n++<<": ";
        for (auto j: i) {
            cout<<j<<" ";
        }
        cout<<endl;
    }
    cout<<"================"<<endl;
}
void Index::print_error_index() {
    cout<<"error_index================"<<endl;
    int n = 0;
    for (auto i: this->error_index) {
        cout<<n++<<": ";
        for (auto j: i) {
            cout<<j<<" ";
        }
        cout<<endl;
    }
    cout<<"================"<<endl;
}
void Index::print_all() {
    print_com_index();
    print_com_index_query();
    print_miss_index();
}