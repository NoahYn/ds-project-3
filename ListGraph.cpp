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

void ListGraph::getAdjacentEdges(int vertex, map<int, int>* m)
{
//	*m = m_List[vertex];
}

void ListGraph::insertEdge(int from, int to, int weight)
{
	m_List[from].insert({to, weight});
}

bool ListGraph::printGraph(ofstream *fout)
{
	for(int i=0; i<m_Size; i++)
	{
		*fout<<"["<<i<<"]";

		for(auto it_=m_List[i].begin(); it_!=m_List[i].end() && *fout<<" -> "; it_++)
		{
			*fout<<"("<<it_->first<<","<<it_->second<<")";
		}
		*fout<<'\n';
	}
	*fout<<'\n';
	return true;
}