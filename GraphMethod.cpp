#include "GraphMethod.h"

bool BFS(Graph *graph, int vertex, ofstream *fout)
{
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
        for (auto iter : m)
        {
            if (!visited[iter.first] && (*fout << " -> "))
            {
                q.push(iter.first);
                *fout << iter.first;
                visited[iter.first] = true;
            }
        }
    }
    *fout << "\n";

    return true;
}

bool DFS(Graph *graph, int vertex, ofstream *fout)
{
    int size = graph->getSize();
    bool visited[size] = {false};
    stack<int> s;
    map<int, int> m;
    map<int, int>::reverse_iterator riter;

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
    for (auto iter : m)
    {
        if (!visit->at(iter.first))
        {
            DFS_R(graph, visit, iter.first, fout);
        }
    }

    return true;
}

bool Kruskal(Graph *graph, ofstream *fout)
{

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