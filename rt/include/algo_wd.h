#ifndef __WD_H__
#define __WD_H__

#include <sng.h>
#include <climits>
#include <algorithm>

#include <p1out.h>

class wd {

public:
	wd(uint size, uint **wptr, uint **dptr, p1out *p1)
	{
		n = size;
		w = wptr;
		d = dptr;
		if (p1 != NULL)
			print1 = p1;
		else
			print1 = NULL;

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
	uint **w;

private:
	uint **d;
	uint n;
	sng *g;

	vector<uint> sorted_d;

	p1out *print1;
};

#endif
