#ifndef _LIST_H_
#define _LIST_H_

#include "Graph.h"

class ListGraph : public Graph
{
private:
	map<int, int> *m_List;

public:
	ListGraph(bool type, int size);
	~ListGraph();

	void getOutgoingEdges(int vertex, map<int, int> &m);
	void getAdjacentEdges(int vertex, map<int, int> &m);
	void insertEdge(int from, int to, int weight);
	bool printGraph(ofstream *fout);
};

#endif