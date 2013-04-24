#include <algo_cp.h>

int cp::func_cp()
{

#ifdef DEBUG
	cout << "DEBUG: CP... DFS on G0" << endl;
#endif

	//DFS for topological sort
	graph->clear_color();

	for (uint i = 0; i < graph->get_num_vertices(); i++) {
		vertex *u = graph->get_vertex(i);
		if (u->get_color() == WHITE)
			visit(u);
	}

	reverse(topo_sorted.begin(), topo_sorted.end());

#ifdef DEBUG
	cout << "       vertex in topo_sort: ";
	for (uint i = 0; i < topo_sorted.size(); i++)
		cout  << topo_sorted[i]->get_id() << " ";
	cout << endl;
#endif

/*
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
*/
	return 0;
}

void cp::visit(vertex *u)
{
#ifdef DEBUG
	cout << "       Visiting " << u->get_id() << "..." << endl;
#endif
	u->set_color(GRAY);

	for (uint i = 0; i < u->out.size(); i++) {
		vertex *next = u->out[i]->dst;
		if (!u->out[i]->weight && (next->get_color() == WHITE))
			visit(next);
	}

	u->set_color(BLACK);
	topo_sorted.push_back(u);
}
