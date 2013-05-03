#ifndef __FEAS_H__
#define __FEAS_H__

#include <sng.h>
#include <algo_cp.h>
#include <p1out.h>

/**
 * FEAS is used to implement OPT2. The algorithm returns true if the given
 * target cycle @c is both feasible and legal.
 * @g is the synchronous network graph, given as input, while the resuling
 * retiming vector is stored into @r
 */

class feas{

public:
	feas(sng *graph, uint num_vertices, p1out *p1)
	{
		g = graph;
		n = num_vertices;
		print1 = p1;
	}

	void init_r(int *r)
	{
		for (uint i = 0; i < n; i++)
			r[i] = 0;
	}

	bool func_feas(uint c, int *r);

	void compute_retiming(uint c, int *r);
	void update_retiming(int *src, int *dst);
	void copy_retiming(int *src, int *dst);

private:
	cp cpobj;
	sng *g;
	uint n;

	p1out *print1;
};

#endif /* __FEAS_H__ */
