// LCA with SparseTable and Euler Tour
// Requires sparse table of pair<int,int> with min operation
// O(n log n) preprocessing, O(1) query
struct LCA{
	SparseTable st;
	int time=0;
	vector <pair<int,int>> euler;
	vector <int> left, right;
	vector <bool> vis;
	LCA(vector <vector <int>> &adj, int root=0){
		int n = int(adj.size());
		left.resize(n);
		right.resize(n);
		vis.assign(n, false);
		dfs(root, adj);
		st = SparseTable(euler);
	}

	void dfs(int u, vector<vector<int>> &adj, int depth=0){
		vis[u] = 1;
		left[u] = int(euler.size());
		euler.push_back({depth,u});
		for(int v : adj[u]){
			if(!vis[v]) dfs(v, adj, depth+1);
			right[u] = int(euler.size());
			euler.push_back({depth,u});
		}
	}

	int query(int u, int v){
		if(left[u] > right[v]) swap(u,v);
		return st.query(left[u], right[v]);
	}
};
