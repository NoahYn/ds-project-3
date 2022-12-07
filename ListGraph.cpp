#include "ListGraph.h"

ListGraph::ListGraph(bool type, int size) : Graph(type, size)
{
	m_Type = type;
	m_List = new map<int, int>[size];
}

ListGraph::~ListGraph()
{
	delete[] m_List;
}

void ListGraph::getAdjacentEdges(int vertex, map<int, int> &m)
{
	if (vertex >= getSize())
		return;

	//	m = m_List[vertex]; // direction ver
	int size = getSize();

	for (int i = 0; i < size; i++)
	{
		map<int, int>::iterator iter = m_List[i].find(vertex);
		map<int, int>::iterator iter2 = m_List[vertex].find(i);
		int weight = 0;
		int weight2 = 0;

		if (iter != m_List[i].end())
			weight = iter->second;
		if (iter2 != m_List[vertex].end())
			weight2 = iter2->second;
		if (weight || weight2)
			m.insert({i, min(weight, weight2)});
	}
}

void ListGraph::insertEdge(int from, int to, int weight)
{
	m_List[from].insert({to, weight});
}

bool ListGraph::printGraph(ofstream *fout)
{
	for (int i = 0; i < m_Size; i++)
	{
		*fout << "[" << i << "]";

		for (auto it_ = m_List[i].begin(); it_ != m_List[i].end() && *fout << " -> "; it_++)
		{
			*fout << "(" << it_->first << "," << it_->second << ")";
		}
		*fout << '\n';
	}
	*fout << '\n';
	return true;
}