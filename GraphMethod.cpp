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
	int size = graph->getSize();
	map <int, int> m[size];
	for (int i = 0; i < size; i++) 
		graph->getIncomingEdges(i, m[i]);
	
	int dist[size];
	int prev[size];
	fill(dist, dist+size, UNREACHABLE);
	fill(prev, prev+size, -1);
	dist[s_vertex] = 0;

	for (int i = 0; i < size; i++) {
		auto it = m[i].find(s_vertex);
		if (it != m[i].end()) {
			dist[i] = it->second;
			prev[i] = s_vertex;
		}
	}
	
	for (int k = 2; k < size; k++) {
		for (int v = 0; v < size; v++) {
			for (auto i : m[v]) {
				if (dist[v] > dist[i.first] + i.second) {
					dist[v] = dist[i.first] + i.second;		
					prev[v] = i.first;	
				}
			}
		}
	}
	
	int neg_cycle_chk = dist[e_vertex];
	for (int v = 0; v < size; v++) {
		if (v == s_vertex)
			continue;
		for (auto i : m[v]) {
			if (dist[v] > dist[i.first] + i.second) {
				dist[v] = dist[i.first] + i.second;				
				prev[v] = i.first;	
				return false;
			}
		}
	}

	*fout << "====== Bellman-Ford ======\n";
	
	if (dist[e_vertex] == UNREACHABLE) {
		*fout << "x\n";
		*fout << "=======================\n\n";
		return true;;
	}
	vector<int> path;
	int curr = e_vertex;
	while (prev[curr] >= 0) {
		path.push_back(curr);
		curr = prev[curr];
	} 
	for (auto ri = path.rbegin(); ri != path.rend(); ri++) {
		*fout << prev[*ri] << " -> ";
	}
	*fout << e_vertex << "\n";
	*fout << "cost : " << dist[e_vertex] << "\n";	
	*fout << "==========================\n\n"; // TODO negative cycle error

    return true;
}

/*
0 → 2 → 5 → 6
cost : 11

음수인 weight가 있는 경우에도 동작하며 start vertex에서 end vertex로 도달할 수 없는 경우 ‘x’를 출력한다. 
모든 vertex에 연결된 edge정보를 반복적으로 갱신 (visited 안쓰고 distance, prev, path만)
2. 각 vertex에 대하여 주변 edge로의 거리를 보다 짧은 경로로 갱신
3. 2를 vertex수만큼 반복
4. 2를 한 번 더 수행했을 때 거리가 갱신된다면 음수사이클 발생
Bellman-Ford 알고리즘은 Start vertex와 End vertex를 입력 받아 최단 경로와 거리를 구한다. Weight가 음수인 경우에도 정상 동작하며, 음수 사이클이 발생할 경우 에러를 출력한다. 
*/

bool FLOYD(Graph *graph, ofstream *fout)
{
	int size = graph->getSize();
	
//	A[i][j] = length[i][j];

	for (int k = 0; k < size; k++) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
//				A[i][j] = min(A[i][j], A[i][k] + A[k][j]);
			}
		}
	}

	*fout << "======== FLOYD ========\n";
	for (int i = 0; i < size; i++)
		*fout << "["<<i<<"] ";
	for (int i = 0; i < size; i++) {
		*fout << "["<<i<<"] ";
		
		*fout << endl;
	}
	// TODO negative cycle
	*fout << "=======================\n\n";
    return true;
}

/*
음수사이클 -> 에러
기준 vertex에서 도달할 수 없는 vertex의 경우 ‘x’를 출력한다. 
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
*/