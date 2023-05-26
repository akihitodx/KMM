#include "index.h"


Index::Index(int queryNum, int dataNum) {
    com_index.resize(dataNum); //完全匹配集 数据节点索引
    miss_index.resize(dataNum); //缺一匹配 数据节点索引 data_id: query_id->miss_query_id ...
    com_index_query.resize(queryNum); //完全匹配集 查询节点索引
}
