#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#include <climits>

using namespace std;

/* =======================
   Union-Find (Disjoint Set)
   ======================= */

class UnionFind {
    vector<int> parent, rank;

public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n,0);

        for(int i=0;i<n;i++)
            parent[i] = i;
    }

    int find(int x) {
        if(parent[x] != x)
            parent[x] = find(parent[x]);   // Path compression
        return parent[x];
    }

    void unite(int x,int y) {
        int rootX = find(x);
        int rootY = find(y);

        if(rootX != rootY) {
            if(rank[rootX] < rank[rootY])
                parent[rootX] = rootY;

            else if(rank[rootX] > rank[rootY])
                parent[rootY] = rootX;

            else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

/* =======================
   Graph Class
   ======================= */

class Graph {

    int V;
    bool directed;

    vector<vector<pair<int,int>>> adj;
    vector<tuple<int,int,int>> edges;

public:

    Graph(int vertices,bool dir=false) {
        V = vertices;
        directed = dir;
        adj.resize(V);
    }

    void addEdge(int u,int v,int w) {

        if(u>=V || v>=V || u<0 || v<0) {
            cout<<"Invalid vertex index. Vertices must be between 0 and "<<V-1<<endl;
            return;
        }

        if(w < 0)
            cout<<"Warning: Dijkstra does NOT support negative weights.\n";

        adj[u].push_back({v,w});
        edges.push_back({w,u,v});

        if(!directed)
            adj[v].push_back({u,w});
    }

    /* =======================
       BFS
       ======================= */

    void BFS(int start) {

        if(start >= V) {
            cout<<"Invalid start vertex\n";
            return;
        }

        vector<bool> visited(V,false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout<<"BFS Traversal: ";

        while(!q.empty()) {

            int node = q.front();
            q.pop();

            cout<<node<<" ";

            for(auto &neighbor : adj[node]) {

                int v = neighbor.first;

                if(!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }

        cout<<endl;
    }

    /* =======================
       DFS
       ======================= */

    void DFSUtil(int node,vector<bool> &visited) {

        visited[node] = true;
        cout<<node<<" ";

        for(auto &neighbor : adj[node]) {

            int v = neighbor.first;

            if(!visited[v])
                DFSUtil(v,visited);
        }
    }

    void DFS(int start) {

        if(start >= V) {
            cout<<"Invalid start vertex\n";
            return;
        }

        vector<bool> visited(V,false);

        cout<<"DFS Traversal: ";

        DFSUtil(start,visited);

        cout<<endl;
    }

    /* =======================
       Connected Components
       ======================= */

    void connectedComponents() {

        vector<bool> visited(V,false);
        int count = 0;

        cout<<"Connected Components:\n";

        for(int i=0;i<V;i++) {

            if(!visited[i]) {

                count++;

                DFSUtil(i,visited);

                cout<<endl;
            }
        }

        cout<<"Total Components: "<<count<<endl;
    }

    /* =======================
       Dijkstra
       ======================= */

    void dijkstra(int src) {

        if(src >= V) {
            cout<<"Invalid source\n";
            return;
        }

        vector<int> dist(V,INT_MAX);
        vector<int> parent(V,-1);

        priority_queue<
            pair<int,int>,
            vector<pair<int,int>>,
            greater<pair<int,int>>
        > pq;

        dist[src] = 0;
        pq.push({0,src});

        while(!pq.empty()) {

            int u = pq.top().second;
            int d = pq.top().first;

            pq.pop();

            if(d > dist[u])
                continue;

            for(auto &neighbor : adj[u]) {

                int v = neighbor.first;
                int weight = neighbor.second;

                if(dist[u] + weight < dist[v]) {

                    dist[v] = dist[u] + weight;

                    parent[v] = u;

                    pq.push({dist[v],v});
                }
            }
        }

        cout<<"Shortest distances from "<<src<<":\n";

        for(int i=0;i<V;i++)
            cout<<i<<" -> "<<dist[i]<<endl;

        cout<<"\nPaths:\n";

        for(int i=0;i<V;i++) {

            if(dist[i] == INT_MAX)
                continue;

            vector<int> path;

            for(int v=i; v!=-1; v=parent[v])
                path.push_back(v);

            reverse(path.begin(),path.end());

            cout<<"Path to "<<i<<": ";

            for(int v : path)
                cout<<v<<" ";

            cout<<endl;
        }
    }

    /* =======================
       Kruskal MST
       ======================= */

    void kruskalMST() {

        if(directed) {
            cout<<"Kruskal MST only works on undirected graphs.\n";
            return;
        }

        sort(edges.begin(),edges.end());

        UnionFind uf(V);

        int totalWeight = 0;

        cout<<"MST Edges:\n";

        for(auto &edge : edges) {

            int w,u,v;

            tie(w,u,v) = edge;

            if(uf.find(u) != uf.find(v)) {

                uf.unite(u,v);

                totalWeight += w;

                cout<<u<<" - "<<v<<" : "<<w<<endl;
            }
        }

        cout<<"Total MST Weight: "<<totalWeight<<endl;
    }

    /* =======================
       Topological Sort
       ======================= */

    void topologicalSort() {

        if(!directed) {
            cout<<"Topological sort only valid for directed graphs.\n";
            return;
        }

        vector<int> indegree(V,0);

        for(int u=0;u<V;u++)
            for(auto &neighbor : adj[u])
                indegree[neighbor.first]++;

        queue<int> q;

        for(int i=0;i<V;i++)
            if(indegree[i]==0)
                q.push(i);

        vector<int> topo;

        while(!q.empty()) {

            int u = q.front();
            q.pop();

            topo.push_back(u);

            for(auto &neighbor : adj[u]) {

                int v = neighbor.first;

                if(--indegree[v]==0)
                    q.push(v);
            }
        }

        if(topo.size()!=V) {
            cout<<"Graph contains a cycle.\n";
            return;
        }

        cout<<"Topological Order: ";

        for(int node : topo)
            cout<<node<<" ";

        cout<<endl;
    }
};

/* =======================
   Main
   ======================= */

int main() {

    int V,E;

    cout<<"Enter number of vertices and edges:\n";
    cin>>V>>E;

    bool directed;

    cout<<"Is graph directed? (1=yes 0=no): ";
    cin>>directed;

    Graph g(V,directed);

    cout<<"Enter edges (u v weight):\n";

    for(int i=0;i<E;i++) {

        int u,v,w;

        cin>>u>>v>>w;

        g.addEdge(u,v,w);
    }

    int choice;

    while(true) {

        cout<<"\nMenu\n";
        cout<<"1 BFS\n";
        cout<<"2 DFS\n";
        cout<<"3 Connected Components\n";
        cout<<"4 Dijkstra\n";
        cout<<"5 Kruskal MST\n";
        cout<<"6 Topological Sort\n";
        cout<<"0 Exit\n";

        cin>>choice;

        if(choice==0)
            break;

        int start;

        switch(choice) {

            case 1:
                cout<<"Start vertex: ";
                cin>>start;
                g.BFS(start);
                break;

            case 2:
                cout<<"Start vertex: ";
                cin>>start;
                g.DFS(start);
                break;

            case 3:
                g.connectedComponents();
                break;

            case 4:
                cout<<"Source vertex: ";
                cin>>start;
                g.dijkstra(start);
                break;

            case 5:
                g.kruskalMST();
                break;

            case 6:
                g.topologicalSort();
                break;
        }
    }

    return 0;
}