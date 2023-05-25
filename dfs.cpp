#include <bits/stdc++.h>
#include <omp.h>

using namespace std;

class Graph
{
public:
    vector<vector<int>> graph;
    vector<bool> visited;
    int vertices = 0;
    int edges = 0;

    Graph()
    {
        cout << "\nEnter number of nodes: ";
        cin >> vertices;
        cout << "\nEnter number of edges: ";
        cin >> edges;

        graph.assign(vertices, vector<int>());

        int x, y;
        for (int i = 0; i < edges; ++i)
        {
            cout << "\nEnter edge: ";
            cin >> x >> y;
            addEdge(x, y);
        }
    }

    void addEdge(int x, int y)
    {
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    void printGraph()
    {
        for (int i = 0; i < vertices; ++i)
        {
            cout << i << " -> ";
            for (auto j = graph[i].begin(); j != graph[i].end(); ++j)
                cout << *j << " ";
            cout << endl;
        }
    }

    void initializeVisited()
    {
        visited.assign(vertices, false);
    }

    void dfs(int i)
    {
        stack<int> s;
        s.push(i);
        visited[i] = true;

        while (!s.empty())
        {
            int curr = s.top();
            cout << curr << " ";
            s.pop();
            for (auto j = graph[curr].begin(); j != graph[curr].end(); ++j)
            {
                if (!visited[*j])
                {
                    s.push(*j);
                    visited[*j] = true;
                }
            }
        }
    }

    void parallel_dfs(int i)
    {
        stack<int> s;
        s.push(i);
        visited[i] = true;

        while (!s.empty())
        {
            int curr = s.top();
            cout << curr << " ";
#pragma omp critical
            s.pop();
#pragma omp parallel for
            for (auto j = graph[curr].begin(); j != graph[curr].end(); ++j)
            {
                if (!visited[*j])
#pragma omp critical
                {
                    s.push(*j);
                    visited[*j] = true;
                }
            }
        }
    }
};

int main()
{
    Graph g;
    cout << "\nAdjacency List:" << endl;
    g.printGraph();
    cout << endl;

    g.initializeVisited();
    cout << "\nNormal DFS: ";
    auto start = chrono::high_resolution_clock::now();
    g.dfs(0);
    auto end = chrono::high_resolution_clock::now();
    cout << "\nTime taken = " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;

    g.initializeVisited();
    cout << "\nParallel DFS: ";
    start = chrono::high_resolution_clock::now();
    g.parallel_dfs(0);
    end = chrono::high_resolution_clock::now();
    cout << "\nTime taken = " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;

    // g.initializeVisited();
    // cout << "\nParallel DFS: ";
    // auto s = omp_get_wtime();
    // g.parallel_dfs(0);
    // auto e = omp_get_wtime();
    // cout << "\nTime taken = " << (e - s) << endl;

    return 0;
}