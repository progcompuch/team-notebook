// Dinic Max Flow O(V^2 E)
struct FlowEdge{
    int u,v;
    ll cap, flow = 0;
    FlowEdge(int u,int v,ll cap):u(u),v(v),cap(cap){}
};
struct Dinic{
    const ll flow_inf = 1e18;
    vector<FlowEdge> edges;
    vector< vector<int> > gr;
    int s,t,n,m=0;
    vector<int> lvl,idx;
    Dinic (int n,int s,int t):n(n),s(s),t(t){
        gr.resize(n);
        lvl.resize(n);
        idx.resize(n);
    }
    void add_edge(int u,int v,ll cap){
        edges.emplace_back(u,v,cap);
        edges.emplace_back(v,u,0); //cap si bidireccional
        gr[u].push_back(m++);
        gr[v].push_back(m++);
    }
    bool run_bfs(){
        queue<int> bfs;
        bfs.push(s);
        fill(lvl.begin(),lvl.end(),-1);
        lvl[s] = 0;
        while (!bfs.empty()){
            int no = bfs.front();
            bfs.pop();
            for (int ne:gr[no]){
                if (lvl[edges[ne].v] == -1 && edges[ne].cap - edges[ne].flow > 0){
                    lvl[edges[ne].v] = lvl[no] + 1;
                    bfs.push(edges[ne].v);
                }
            }
        }
        return lvl[t] != -1;
    }
    ll dfs(int u,ll cflow){
        if (cflow == 0 || u == t) return cflow;
        while (idx[u] < gr[u].size()){
            int edg = gr[u][idx[u]++];
            int v = edges[edg].v;
            if (lvl[u]+1 == lvl[v] && edges[edg].cap - edges[edg].flow > 0){
                ll rflow = dfs(v,min(cflow,edges[edg].cap - edges[edg].flow));
                if (rflow){
                    edges[edg].flow += rflow;
                    edges[edg^1].flow -= rflow;
                    return rflow;
                }
            }
        }
        return 0;
    }
    ll flow(){
        ll f = 0;
        while (true){
            if (run_bfs()){
                fill(idx.begin(),idx.end(),0);
                ll cf;
                while (cf = dfs(s,flow_inf)) f += cf;
            } else break;
        }
        return f;
    }
};
