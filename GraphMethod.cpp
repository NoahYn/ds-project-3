#include "GraphMethod.h"
#define INSERTION_SIZE 6

bool BFS(Graph *graph, int vertex, ofstream *fout)
{
	*fout << "======== BFS ========\n";
	*fout << "startvertex : " << vertex << "\n";
	
    int size = graph->getSize();
    bool visited[size] = {false};
    queue<int> q;
    map<int, int> m;

    visited[vertex] = true;
    q.push(vertex);
    *fout << vertex;

    while (!q.empty())
    {
        vertex = q.front();
        q.pop();
        graph->getAdjacentEdges(vertex, m);
        for (auto i_m : m)
        {
            if (!visited[i_m.first] && (*fout << " -> "))
            {
                q.push(i_m.first);
                *fout << i_m.first;
                visited[i_m.first] = true;
            }
        }
    }

	*fout << "\n=====================\n";
    return true;
}

bool DFS(Graph *graph, int vertex, ofstream *fout)
{
	*fout << "======== DFS ========\n";
	*fout << "startvertex : " << vertex << "\n";
	
    int size = graph->getSize();
    bool visited[size] = {false};
    stack<int> s;
    map<int, int> m;

    s.push(vertex);

    while (!s.empty())
    {
        vertex = s.top();
        if (!visited[vertex])
        { // some vertex stacked twice
            visited[vertex] = true;
            if (find(visited, visited + size, false) != visited + size) // find false
                *fout << vertex << " -> ";
            else // all is true, last operation
                *fout << vertex << "\n";
        }
        s.pop();

        graph->getAdjacentEdges(vertex, m);
        for (auto it = m.rbegin(); it != m.rend(); it++)
        {
            int n = it->first;
            if (!visited[n])
            {
                s.push(n);
            }
        }
        m.clear();
    }

	*fout << "=====================\n";
    return true;
}

bool DFS_R(Graph *graph, vector<bool> *visit, int vertex, ofstream *fout)
{
    visit->at(vertex) = true;
    if (find(visit->begin(), visit->end(), false) != visit->end()) // find false
        *fout << vertex << " -> ";
    else // all is true, last operation
        *fout << vertex << "\n";

    map<int, int> m;
    graph->getAdjacentEdges(vertex, m);
    for (auto i_m : m)
    {
        if (!visit->at(i_m.first))
        {
            DFS_R(graph, visit, i_m.first, fout);
        }
    }

    return true;
}

void Insertion_Sort(vector<struct edge> &edges, struct edge to_insert, int i)
{
	while (i >= 0 && to_insert.weight < edges[i].weight) {
		edges[i+1] = edges[i];
		i--;
	}
	edges[i+1] = to_insert;
}

void Quick_Sort(vector<struct edge> &edges, int low, int high)
{
    if (low < high)
    {
		int seg_size = high - low + 1;
        if (seg_size <= INSERTION_SIZE)
        {
			for (int i = low; i < high; i++)
	            Insertion_Sort(edges, edges[i+1], i);
            return;
        }
        int i = low;
        int j = high + 1;
 	    int pivot = edges.at(low).weight;
        do {
            do i++; while (edges.at(i).weight < pivot);
            do j--; while (edges.at(j).weight > pivot);
            if (i < j) iter_swap(edges.begin()+i, edges.begin()+j);
        } while (i < j);
		iter_swap(edges.begin()+low, edges.begin()+j);
        Quick_Sort(edges, low, j-1);
    	Quick_Sort(edges, j+1, high);
    }
}

bool Kruskal(Graph *graph, ofstream *fout)
{
    int size = graph->getSize();
    vector<struct edge> edges;
    struct edge temp;

    map<int, int> m;
    for (int i = 0; i < size; i++)
    {
        temp.v1 = i;
        graph->getAdjacentEdges(i, m);
        for (auto i_m : m)
        {
			if (i_m.first < i)
				continue;
            temp.v2 = i_m.first;
            temp.weight = i_m.second;
            edges.push_back(temp);
        }
        m.clear();
    }
    Quick_Sort(edges, 0, edges.size()-1);
	for (int i = 0; i < size; i++) {
		m.insert({i, i});
	} // initializing set

	map <int,int> mst[size];
	int mst_degree = 1;
	for (auto i_edge = edges.begin(); i_edge != edges.end() && mst_degree < size ; i_edge++) {
		if (m.find(i_edge->v1) != m.find(i_edge->v2)) { // each vertices are in the different set -> connect
			m.find(i_edge->v1)->second = m.find(i_edge->v2)->second; // union
			mst[i_edge->v1].insert({i_edge->v2, i_edge->weight});
			mst[i_edge->v2].insert({i_edge->v1, i_edge->weight});
			mst_degree++;
		}
	}
	if (mst_degree != size) // can't make MST
		return false;

	*fout << "======== Kruskal ========\n";
	int cost = 0;
	for (int i = 0; i < size; i++) {
		*fout << "["<<i<<"] ";
		for (auto i_mst : mst[i]) {
			*fout << i_mst.first << "("<<i_mst.second<<") ";
			cost += i_mst.second;
		}
		*fout << "\n";
	}
	cost /= 2;
	*fout << "cost : " << cost << "\n";
    *fout << "=========================\n";
	return true;
}

bool Dijkstra(Graph *graph, int vertex, ofstream *fout)
{

    return true;
}

bool Bellmanford(Graph *graph, int s_vertex, int e_vertex, ofstream *fout)
{

    return true;
}

bool FLOYD(Graph *graph, ofstream *fout)
{

    return true;
}