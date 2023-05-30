#ifndef KMM_ALG_H
#define KMM_ALG_H

#include "../structure/graph.h"
#include "../structure/index.h"
#include "../structure/match.h"

void preProsessing(Graph &query, Graph &data,Index &index);

void updateIndex(VertexID node, VertexID nei ,Graph &query, Graph &data, Index &index);

void Kernel_Match(Graph &query, Graph &data, Index &index, Match &match);

bool unKernel_Match(VertexID is_query,VertexID data_node, Graph &query, Graph &data, Index &index, Match &match);

void subgraph_Match(VertexID left_node,VertexID right_node,Graph &query,Graph &data, Index &index, Match &match);

void do_func(Graph &query, Graph &data,Index &index);

#endif //KMM_ALG_H
