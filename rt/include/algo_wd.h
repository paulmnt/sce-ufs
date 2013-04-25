#ifndef __WD_H__
#define __WD_H__

#include <sng.h>
#include <climits>
#include <algorithm>

class wd {

public:
	wd(uint size, uint **wptr, int **dptr)
	{
		n = size;
		w = new uint*[n];
		d = new int*[n];
		for (uint i = 0; i < n; i++) {
			w[i] = new uint[n];
			d[i] = new int[n];
		}
	}

	void init_wd(sng *graph);
	void compute_wd();

private:
	void copy_wd();

	uint **w;
	int **d;
	uint n;
	sng *g;
};

#endif