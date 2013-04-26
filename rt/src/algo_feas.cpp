#include "algo_feas.h"

void feas::retime_sng(int *r)
{
	uint edges_num = g->get_num_edges();
	for (uint i = 0; i < edges_num; i++) {
		edge *e = g->get_edge(i);
		uint u = e->src->get_id();
		uint v = e->dst->get_id();
		uint w = e->weight;
		e->weight = w + r[v] - r[u];
	}

#ifdef DEBUG
	for (uint i = 0; i < edges_num; i++) {
		cout << "DEBUG: ";
		g->print_edge(i);
	}
#endif

}

void feas::revert_sng(int *r)
{
	uint edges_num = g->get_num_edges();
	for (uint i = 0; i < edges_num; i++) {
		edge *e = g->get_edge(i);
		uint u = e->src->get_id();
		uint v = e->dst->get_id();
		uint w = e->weight;
		e->weight = w - r[v] + r[u];
	}

}

void feas::compute_retiming(uint c, int *r)
{
	for (uint i = 0; i < n; i++) {
		if (g->get_vertex_delta(i) > c)
			r[i]++;
	}
}

void feas::update_retiming(int *src, int *dst)
{
	for (uint i = 0; i < n; i++)
		dst[i] += src[i];
}

bool feas::func_feas(uint c, int *r) {

	/* Initialize vector r and create a temporary vector */
	int *retime_vect = new int[n];
	init_r(r);
	uint phi;

	for (uint k = 0; k < n - 1; k++) {
		init_r(retime_vect);
		phi = cpobj.func_cp(g);
		compute_retiming(c, retime_vect);
		update_retiming(retime_vect, r);
#ifdef DEBUG
		cout << "DEBUG: Retiming vector at iteration " << k << ": ";
		for (uint i = 0; i < n; i++)
			cout << r[i] << " ";
		cout << endl;
#endif
		retime_sng(retime_vect);
	}

	phi = cpobj.func_cp(g);
	cout << "INFO: Target cycle was " << c << ", achieved is " << phi << endl;

	delete[] retime_vect;
	if (phi <= c)
		return true;

	revert_sng(r);
	return false;
}
