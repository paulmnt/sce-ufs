#include <algo_cp.h>

int cp::func_cp()
{

#ifdef DEBUG
	cout << "DEBUG: RUNNING CP... DFS on G0" << endl;
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

	for (uint i = 0; i < topo_sorted.size(); i++) {
		vertex *u = topo_sorted[i];
		uint u_delay = u->get_delay();
		uint src_delta_max = 0;
		for (uint j = 0; j < u->in.size(); j++)
			if (!u->in[j]->weight) {
				uint src_delta = u->in[j]->src->get_delta();
				if (src_delta > src_delta_max)
					src_delta_max = src_delta;
			}
		u->set_delta(u_delay + src_delta_max);
	}


#ifdef DEBUG
	cout << "DEBUG: vertex deltas in topo_sort: ";
	for (uint i = 0; i < topo_sorted.size(); i++)
		cout  << topo_sorted[i]->get_delta() << " ";
	cout << endl;
#endif

	uint max = 0;
	for (uint i = 0; i < topo_sorted.size(); i++) {
		uint delta = topo_sorted[i]->get_delta();
		if (delta > max)
			max = delta;
	}

#ifdef DEBUG
	cout << "DEBUG: CP... Initial clock period is: " << max << endl;
#endif
	return max;
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
