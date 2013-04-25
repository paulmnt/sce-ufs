#ifndef __FEAS_H__
#define __FEAS_H__

#include "sng.h"

/**
 * FEAS is used to implement OPT2. The algorithm returns true if the given
 * target cycle @c is both feasible and legal.
 * @g is the synchronous network graph, given as input, while the resuling
 * retiming vector is stored into @r
 */

class feas{

public:
	bool func_feas(sng *g, int c, int *r);

};

#endif /* __FEAS_H__ */
