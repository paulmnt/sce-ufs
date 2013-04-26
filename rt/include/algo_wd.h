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
		for (uint i = 0; i < n; i++) {
			w[i] = new uint[n];
			d[i] = new uint[n];
		}
	}

	void init_wd(sng *graph);
	uint compute_wd();
	void sort_d();

	uint get_target_phi_list_size()
	{
		return sorted_d.size();
	}
	uint get_target_phi(uint i)
	{
		if (i < sorted_d.size())
			return sorted_d[i];
		else {
			cout << "ERROR: sorted_d index out of bound" << endl;
			return UINT_MAX;
		}
	}

private:
	uint **w;
	uint **d;
	uint n;
	sng *g;

	vector<uint> sorted_d;
};

#endif
