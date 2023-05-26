#ifndef KMM_ALG_H
#define KMM_ALG_H

#include "../structure/graph.h"
#include "../structure/index.h"

void preProsessing(Graph &query, Graph &data,Index &index);

void updateIndex(VertexID node, VertexID nei ,Graph &query, Graph &data, Index &index);





#endif //KMM_ALG_H
