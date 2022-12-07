#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <cstring>
#include <string.h>
#include <fstream>
#include <map>
#include <set>
#include <math.h>
#include <vector>
#include <algorithm>
#include <deque>
#include <queue>
#include <stack>

using namespace std;

#define MAX 999999

class Graph
{
protected:
	bool m_Type; // 0:List 1:Matrix
	int m_Size;

public:
	Graph(bool type, int size)
	{
		m_Type = type;
		m_Size = size;
	}
	~Graph() {}

	bool getType() { return m_Type; }
	int getSize() { return m_Size; }

	virtual void getAdjacentEdges(int vertex, map<int, int> &m) = 0;
	virtual void insertEdge(int from, int to, int weight) = 0;
	virtual bool printGraph(ofstream *fout) = 0;
};

#endif
