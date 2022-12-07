#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(bool type, int size) : Graph(type, size)
{
	m_Mat = new int*[size];
	for(int i=0; i<size; i++)
	{
		m_Mat[i] = new int[size];
		memset(m_Mat[i], 0, sizeof(int)*size);
	}
}

MatrixGraph::~MatrixGraph()
{
	for(int i=0; i<getSize(); i++)
	{
		delete[] m_Mat[i];
	}
	delete[] m_Mat;
}

void MatrixGraph::getAdjacentEdges(int vertex, map<int, int>* m)
{
	if (vertex >= getSize()) {
		return;
	}
//	for (int i=0; i<getSize(); i++) {
//		if (m_Mat[vertex][i]) {
//			m->insert({i, m_Mat[vertex][i]});
//		}
//	}
//	for (auto iter : *m) {
//		cout << iter.first << iter.second << '\n';
//	}
}

void MatrixGraph::insertEdge(int from, int to, int weight)
{
	m_Mat[from][to] = weight;
}

bool MatrixGraph::printGraph(ofstream *fout)
{
	if( m_Size < 0 )
		return 0;

	*fout<<'\t';
	for(int i=0; i<m_Size; i++)
	{
		*fout<<"["<<i<<"]"<<'\t';
	}
	*fout<<'\n';

	for(int i=0; i<m_Size; i++)
	{
		*fout<<"["<<i<<"]";
		for(int j=0; j<m_Size && *fout<<'\t'; j++)
		{
			*fout<<m_Mat[i][j];
		}
		*fout<<endl;
	}

	return true;
}
