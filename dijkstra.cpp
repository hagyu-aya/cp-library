template<typename T>
void dijkstra_init(const int s){
    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> que;
    vector<T> d(n, INF);
    d[s] = 0;
    que.push({T(0), s});
    
    while(!que.empty()){
        T c = que.top().first;
        int v = que.top().second;
        que.pop();
        
        for(auto && e : g[v]){
            if(d[e.to] > c + e.cost){
                d[e.to] = c + e.cost;
                que.push({d[e.to], e.to});
            }
        }
    }
}