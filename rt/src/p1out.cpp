#include <p1out.h>

void p1out::it0(uint area)
{
	stringstream ss;
	ss << "#0. Initial area: " << area;
	print_item(p1_013, ss.str());
}


void p1out::it1(int *r, uint n)
{
	print_item(p1_013, "Optimal retiming vector");
	p1_013  << r[0] << " ";
	for (uint i = 1; i < n; i++) {
		if (!(i % 10))
			p1_013 << endl;
		if (i == n - 1)
			/* Don't want a space after last element */
			break;
		p1_013  << r[i] << " ";
	}
	p1_013 << r[n - 1] << endl;
}
