#include "GraphMethod.h"
#define INSERTION_SIZE 6
#define UNREACHABLE 1000000000

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

	*fout << "\n=====================\n\n";
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

	*fout << "=====================\n\n";
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
    *fout << "=========================\n\n";
	return true;
}

bool Dijkstra(Graph *graph, int vertex, ofstream *fout)
{
	int i;
	int size = graph->getSize();

	map <int, int> m[size];
	for (i = 0; i < size; i++) {
		graph->getOutgoingEdges(i, m[i]);
		for (auto i_m : m[i]) 
			if (i_m.second < 0) return false; // negative weight!
	}

	*fout << "======== Dijkstra ========\n";
	*fout << "startvertex : " << vertex << "\n";

	int prev[size];
	int dist[size];
	int used[size];
	fill(prev, prev+size, -1);
	fill(dist, dist+size, UNREACHABLE);
	fill(used, used+size, 0);
	
	dist[vertex] = 0;
	prev[vertex] = -1;
	used[vertex] = 1;
	for (auto i_m : m[vertex]) {
		prev[i_m.first] = vertex;
		dist[i_m.first] = i_m.second;
	}

	for (int k = 0; k < size-2; k++) {
		int min_vertex = UNREACHABLE;
		for (i = 0; i < size; i++) {
			if (!used[i] && dist[i] < min_vertex) {
				min_vertex = dist[i];
				vertex = i;
			}
		}
		used[vertex] = 1;
		for (auto i_m : m[vertex]) {
			if (dist[i_m.first] > dist[vertex] + i_m.second) {
				prev[i_m.first] = vertex;
				dist[i_m.first] = dist[vertex] + i_m.second;
			}
		}
	}

	for (int i = 0; i < size; i++) {
		if (dist[i] == 0)
			continue;
		*fout << "["<<i<<"] ";
		if (dist[i] == UNREACHABLE) {
			*fout << "x\n";
			continue;
		}
		vector<int> path;
		int curr = i;
		while (prev[curr] >= 0) {
			path.push_back(curr);
			curr = prev[curr];
		} 
		for (auto ri = path.rbegin(); ri != path.rend(); ri++) {
			*fout << prev[*ri] << " -> ";
		}
		*fout << i;
		*fout << " ("<<dist[i]<<")\n";
	}

	*fout << "==========================\n\n";
    return true;
}

bool Bellmanford(Graph *graph, int s_vertex, int e_vertex, ofstream *fout)
{

    return true;
}

/*
입력한 vertex가 그래프에 존재하지 않거나, 음수 사이클이 발생한 경우 log.txt에 오류 코드 800을 출력한다.
====== Bellman-Ford =======
0 → 2 → 5 → 6
cost : 11
=======================
Start Vertex를 기준으로 Bellman-Ford를 수행하여 End vertex까지의 최단 경로와 거리를 구하여 log.txt에 저장한다. 음수인 weight가 있는 경우에도 동작하며 start vertex에서 end vertex로 도달할 수 없는 경우 ‘x’를 출력한다. 
모든 vertex에 연결된 edge정보를 반복적으로 갱신 (visited 안쓰고 distance, ㅔprev   path만)
1. 시작 vertex의 거리를 0으로 초기화, 다른 vertex로의 거리를 무한대로 초기화
2. 각 vertex에 대하여 주변 edge로의 거리를 보다 짧은 경로로 갱신
3. 2를 vertex수만큼 반복
4. 2를 한 번 더 수행했을 때 거리가 갱신된다면 음수사이클 발생
Bellman-Ford 알고리즘은 Start vertex와 End vertex를 입력 받아 최단 경로와 거리를 구한다. Weight가 음수인 경우에도 정상 동작하며, 음수 사이클이 발생할 경우 에러를 출력한다. 
void MatrixWDigrpah::BellmanFord(const int n, const int s) {
	for (int i=0; i<n; i++) dist[i] = length[s][i]; 
			// initialize k == 1
	for (int k=2; k<=n-1; k++)
		for (v != s && v has incoming edge w)
				for (each <w.v>) 
					dist[v] = min(dist[v], dist[w] + length[w][v]);
}
*/

bool FLOYD(Graph *graph, ofstream *fout)
{

    return true;
}

/*
FLOYD (FLOYD) 모든 vertex의 쌍에 대해서 Start vertex 에서 Endvertex로 가는 데 필요한 최소 비용을 행렬 형태로 출력한다. 기준 vertex에서 도달할 수 없는 vertex의 경우 ‘x’를 출력한다. 
명령어를 수행할 수 없거나 음수 사이클이 발생한 경우 log.txt에 오류 코드 900을 출력한다.
======== FLOYD ========
[0] [1] [2] [3] [4] [5] [6]
[0]  0   6   2   9   5   10   11
[1]  x   x   0   5   18   x   8
…
[6]  x   x   x  14  10   x   0
=====================
1. 모든 vertex를 순차적으로 선택
2. 선택된 vertex를 경유하는 모든 vertex쌍의 최단 거리 업데이트
3. 모든 vertex에 대해 2를 반복
FLOYD는 입력 인자 없이 모든 쌍에 대하여 최단 경로 행렬을 구한다. Weight가 음수인 경우에도 정상 동작하며, 음수 사이클이 발생할 경우 에러를 출력한다. 
A[i][j] = length[i][j];
for (int k=1; k<=n; k++) 
	for (int i=1; i<=n; i++)
		for (int j=1; j<=n; k++) 
			A[i][j] = min(A[i][j], A[i][k] + A[k][j]);
*/