#ifndef KMM_ALG_H
#define KMM_ALG_H

#include "../structure/graph.h"
#include "../structure/index.h"
#include "../structure/match.h"

void preProsessing(Graph &query, Graph &data,Index &index);

void updateIndex(VertexID node, VertexID nei ,Graph &query, Graph &data, Index &index);

void Kernel_Match(VertexID main, Graph &query, Graph &data, Index &index, Match &match, vector<vector<VertexID>> &match_table);



#endif //KMM_ALG_H
