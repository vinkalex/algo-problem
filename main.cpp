#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>

using namespace std;

const int INF = 10000000;

struct Vertex {
    int Path;
    int Depth;
};

class Edge {
public:
    int from;
    int to;
    int time2;
    int time;
    int line;

    Edge() = default;

    Edge(int From, int To, int Time, int Time2, int Line) {
        from = From;
        to = To;
        time = Time;
        time2 = Time2;
        line = Line;
    }

};

class Graph {
public:
    int Size;
    vector<Vertex> Data;
    vector<vector<Edge>> Edge_list;

    Graph() = default;

    Graph(int size) : Size(size) {
        Data.resize(Size);
        Edge_list.resize(Size);
    };

    pair<int, vector<int>> BFS(int vertex_start, int start_time, int finish) {
        set<pair<int, int>> q;
        for (auto &v: Data) {
            v.Depth = INF;
        }
        Data[vertex_start].Depth = start_time;
        Data[vertex_start].Path = -1;
        q.insert(make_pair(start_time, vertex_start));
        while (!q.empty()) {
            auto vertex = *(q.begin());
            int vertex_data = vertex.second;
            q.erase(vertex);
            for (auto e : Edge_list[vertex_data]) {
                int curr_time = ((Data[e.from].Depth - e.time2 + e.line - 1) / e.line) * e.line + e.time2;
                if (Data[e.to].Depth > curr_time + e.time) {
                    if (Data[e.to].Depth != INF) {
                        q.erase(make_pair(Data[e.to].Depth, e.to));
                    }
                    Data[e.to].Path = vertex_data;
                    Data[e.to].Depth = curr_time + e.time;
                    q.insert(make_pair(Data[e.to].Depth, e.to));
                }
            }
        }
        vector<int> path;
        int curr_v = finish;
        do {
            path.push_back(curr_v);
            curr_v = Data[curr_v].Path;
        } while (curr_v != -1);
        reverse(path.begin(), path.end());
        return make_pair(Data[finish].Depth, path);
    }

};


int main() {
    int n, size;
    cin >> n >> size;

    Graph g(size);

    for (int i = 0; i < n; i++) {
        int m, x;
        cin >> m >> x;
        int prev = -1;
        int prev_time = 0;
        for (int j = 0; j < m; j++) {
            int v, time = 0;
            cin >> v;
            if (prev != -1) {
                cin >> time;
                g.Edge_list[prev].push_back(Edge(prev, v, time, prev_time, x));
            }
            prev = v;
            prev_time += time;
        }
    }

    int k;
    cin >> k;

    for (int i = 0; i < k; i++) {
        int start_time, start, finish;
        cin >> start_time >> start >> finish;
        auto res = g.BFS(start, start_time, finish);
        cout << "Время прибытия на станцию :" << res.first << endl;
        cout << "Путь:" << endl;
        for (auto v: res.second) {
            cout << v << ' ';
        }
        cout << endl;
    }

    return 0;
}
