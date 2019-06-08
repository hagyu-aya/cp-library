template<typename T>
class Dinic{
    struct Edge{
        int to, rev;
        T cap;
        Edge(int to, int rev, T cap) : to(to), rev(rev), cap(cap){}
    };

    vector<vector<Edge>> g; // グラフ
    vector<int> level, iter; // スタートからの距離、どこまで調べ終わったか
    int size;
public:
    Dinic(int size) : g(size, vector<Edge>()), size(size){}

    void init(int size){
        g = vector<vector<Edge>>(size, vector<Edge>());
        this->size = size;
    }

    void add_edge(int from, int to, T cap){
        g[from].push_back(Edge(to, g[to].size(), cap));
        g[to].push_back(Edge(from, g[from].size() - 1, 0));
    }

    void bfs(int s){
        level = vector<int>(size, -1);
        queue<int> que;
        level[s] = 0;
        que.push(0);
        while (!que.empty()){
            int v = que.front(); que.pop();
            for(auto && e : g[v]){
                if(e.cap > 0 && level[e.to] < 0){
                    level[e.to] = level[v] + 1;
                    que.push(e.to);
                }
            }
        }
    }

    int dfs(int v, int t, int f){
        if(v == t) return f;
        for(int i = iter[v]; i < g[v].size(); ++i){
            Edge &e = g[v][i];
            if(e.cap > 0 && level[v] < level[e.to]){
                int d = dfs(e.to, t, min(f, e.cap));
                if(d > 0){
                    e.cap -= d;
                    g[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    int max_flow(int s, int t){
        int flow = 0;
        while(true){
            bfs(s);
            if(level[t] < 0) return flow;
            iter = vector<int>(size);
            int f;
            while((f = dfs(s, t, INF)) > 0) flow += f;
        }
    }
};

