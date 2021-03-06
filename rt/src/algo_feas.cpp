#include "algo_feas.h"


void feas::compute_retiming(uint c, int *r)
{
	for (uint i = 0; i < n; i++)
		if (g->get_vertex_delta(i) > c)
			r[i]++;
}

void feas::update_retiming(int *src, int *dst)
{
	for (uint i = 0; i < n; i++)
		dst[i] += src[i];
}

void feas::copy_retiming(int *src, int *dst)
{
	for (uint i = 0; i < n; i++)
		dst[i] = src[i];
}

bool feas::func_feas(uint c, int *rptr) {

#ifdef INFO
	cout << "INFO: STEP 3: running FEAS with target cycle " << c << endl;
#endif
	/*
	 * Initialize vector r and create 2 temporary vectors:
	 * retime_vect is reset to zero at each iteration of FEAS
	 * r is incrementally updated at each iteration and after
	 * the loop exists it contains the final retiming vector.
	 * If the target cycle is feasible r gets copied to the
	 * input vector rptr, passed by reference from the caller.
	 * Ig the cycle is not feasible, then both r and rptr
	 * are used to restore the graph.
	 * This way we avoid having a working copy of the circuit.
	 */
	int *retime_vect = new int[n];
	int *r = new int[n];
	init_r(r);
	uint phi;

	/*
	 * Restore original graph in case this is not the first call to FEAS
	 * Notice that rptr is zero initialized if it's first call!
	 */
	g->revert_sng(rptr);

	for (uint k = 0; k < n; k++) {
		phi = cpobj.func_cp(g);

		/* Item 8: FEAS Combinational Component Graph (verbose) */
		print1->it8a(g, k, c);
		print1->it8b(g, k, c);
		print1->it8c(g, k, c);

		if (phi <= c)
			/* Found a feasible retiming */
			break;
		if (k == n - 1)
			/* The target cycle is not feasible */
			break;

		init_r(retime_vect);
		compute_retiming(c, retime_vect);
		update_retiming(retime_vect, r);
#ifdef DEBUG
		cout << "DEBUG: Retiming vector at iteration " << k << ": ";
		for (uint i = 0; i < n; i++)
			cout << r[i] << " ";
		cout << endl;
#endif
		g->retime_sng(retime_vect);
	}

#ifdef INFO
	cout << "      FEAS: Target cycle was " << c << ", achieved is " << phi << endl;
#endif

	delete[] retime_vect;
	if (phi <= c) {
		copy_retiming(r, rptr);
		delete[] r;
		return true;
	} else {
		g->revert_sng(r);
		g->retime_sng(rptr);
		delete[] r;
		return false;
	}
}
