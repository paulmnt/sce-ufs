#ifndef __WD_H__
#define __WD_H__

#include <sng.h>
#include <climits>
#include <algorithm>

class wd {

public:
	wd(uint size, uint **wptr, uint **dptr)
	{
		n = size;
		w = new uint*[n];
		d = new uint*[n];
		w1 = new uint*[n];
		d1 = new uint*[n];
		for (uint i = 0; i < n; i++) {
			w[i] = new uint[n];
			d[i] = new uint[n];
			w1[i] = new uint[n];
			d1[i] = new uint[n];
		}
	}

	void init_wd(sng *graph);
	void compute_wd();

private:
	void copy_wd();

	uint **w;
	uint **d;
	uint **w1;
	uint **d1;
	uint n;
	sng *g;
};

#endif
