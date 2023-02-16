struct cenDec{
    // cen_p[i]: el padre de i en el grafo de centroides
    // cen_d[i][j]: distancia entre j y su correspondiente centroide en el nivel i
    // cen_h[i] es la lista de hijos de i en el grafo de centroides
    vector<int> cen_p, path;
    vector< vector<int> > &gr, cen_d, cen_h;
    vector<bool> on;
    int n,cen_r;
    int pathm(int no,int p){
        path[no] = 1;
        for (int ne:gr[no]){
            if (on[ne] && ne != p){
                path[no] += pathm(ne,no);
            }
        }
        return path[no];
    }
    void dec(int c,int p,int l){
        pathm(c,-1);
        int cen = c, las = -1;
        while (cen != las){
            las = cen;
            for (int ne:gr[cen]){
                if (on[ne] && path[ne] > path[cen]/2){
                    cen = ne;
                    break;
                }
            }
            path[las] -= path[cen];
            path[cen] += path[las];
        }
        cen_p[cen] = p;
        if (p != -1) cen_h[p].push_back(cen);
        if (l > cen_d.size()) cen_d.push_back(vector<int>(n,-1));
        cen_d[l-1][cen] = 0;
        queue<int> bfs;
        bfs.push(cen);
        while (!bfs.empty()){
            int cno = bfs.front();
            bfs.pop();
            for (int ne:gr[cno]){
                if (on[ne] && cen_d[l-1][ne] == -1){
                    cen_d[l-1][ne] = cen_d[l-1][cno] + 1;
                    bfs.push(ne);
                }
            }
        }
        on[cen] = false;
        for (int ne:gr[cen]){
            if (on[ne]){
                dec(ne,cen,l+1);
            }
        }
    }
    cenDec(vector< vector<int> > &_gr):gr(_gr){
        n = gr.size();
        path.resize(n);
        cen_p.resize(n);
        cen_h.resize(n);
        on.assign(n,true);
        dec(0,-1,1);
        for (int i=0;i<n;i++){
            if (cen_p[i] == -1){
                cen_r = i;
                break;
            }
        }
    }
};