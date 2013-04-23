#include <algo_cp.h>

int cp::func_cp(parser& pobj)
{
        vector<int> delay_vert_vec_cp = pobj.get_delay_vert_vec();
        vector<vector<int> > edges_vec_cp = pobj.get_edges_vec();
        vector<int> edge_wts_vec_cp = pobj.get_edge_wts_vec();

	for (uint i = 0; i < edge_wts_vec_cp.size(); i++) {
		if (edge_wts_vec_cp[i] == 0) {
			vector<int> temp_g0;
			temp_g0.push_back(edges_vec_cp[i][0]);
			temp_g0.push_back(edges_vec_cp[i][1]);
			g0_vertices.push_back(edges_vec_cp[i][0]);
			g0_vertices.push_back(edges_vec_cp[i][1]);
			g0_edges.push_back(temp_g0);
		}
	}

#ifdef DEBUG
	for (uint i = 0; i < g0_edges.size(); i++) {
		cout << "DEBUG: first vertex in g0: " << g0_edges[i][0];
		cout << "       second vertex in g0: " << g0_edges[i][1] << endl;
       	}
#endif

        sort(g0_vertices.begin(), g0_vertices.end());
       	g0_vertices.erase(unique(g0_vertices.begin(), g0_vertices.end()), g0_vertices.end());

#ifdef DEBUG
	for (uint i = 0; i < g0_vertices.size(); i++)
		cout << "DEBUG: vertex in g0: " << g0_vertices[i]<<endl;
#endif

	//DFS for topological sort
	for (uint i = 0; i < g0_vertices.size(); i++) {
		color.push_back("white");
		dis.push_back(0);
		fin.push_back(0);
	}

	time = 0;

	for (uint i = 0; i < g0_vertices.size(); i++)
		if (color[i] == "white")
			visit(i);

	vector<int> deltav;
	for (int i = topo_sort.size() - 1; i >= 0; i--) {
#ifdef DEBUG
		cout << "DEBUG: vertex in topo_sort: " << topo_sort[i]<<endl;
#endif
		deltav.push_back(-1);
	}

	int max = -1;
	for (int i = topo_sort.size() - 1; i >= 0; i--) {
		deltav[topo_sort[i]] = delay_vert_vec_cp[topo_sort[i]];
		max = -1;

		for (uint j = 0; j < g0_edges.size(); j++)
			if (topo_sort[i] == g0_edges[j][1])
				if (deltav[g0_edges[j][0]] > max)
					max = deltav[g0_edges[j][0]];

		if(max > -1)
			deltav[topo_sort[i]] = delay_vert_vec_cp[topo_sort[i]] + max;
	}

	max = -1;
	for (uint i = 0; i < deltav.size(); i++)
		if(deltav[i] > max)
			max = deltav[i];

	cout << "Initial clock period is: " << max << endl;
	return max;
}

void cp::visit(int u)
{
	color[u] = "gray";
	time++;
	dis[u] = time;

	vector<int> adj;

	for (uint i = 0; i < g0_edges.size(); i++)
		if (g0_vertices[u] == g0_edges[i][0])
			adj.push_back(g0_edges[i][1]);

	for (uint i = 0; i < adj.size(); i++)
		for (uint j = 0; j < g0_vertices.size(); j++)
			if (g0_vertices[j] == adj[i])
				if(color[j] == "white")
					visit(j);

	color[u] = "black";
	time++;
	fin[u] = time;

	topo_sort.push_back(g0_vertices[u]);
}
