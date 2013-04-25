#ifndef __FEAS_H__
#define __FEAS_H__

#include <sng.h>
#include <algo_cp.h>

/**
 * FEAS is used to implement OPT2. The algorithm returns true if the given
 * target cycle @c is both feasible and legal.
 * @g is the synchronous network graph, given as input, while the resuling
 * retiming vector is stored into @r
 */

class feas{

public:
	feas(sng *graph)
	{
		g = graph;
		cpobj = new cp(graph);
	}

	uint get_initial_phi()
	{
		uint phi = cpobj->func_cp();
		cout << "Initial clock period is: " << phi << endl;
		return phi;
	}
	bool func_feas(int c, int *r);

private:
	cp *cpobj;
	sng *g;

};

#endif /* __FEAS_H__ */
