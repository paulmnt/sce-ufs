#include "ufs.h"

void ufs::cofactor(const cover &f, const cover &g,
		   cover &pcof, cover &pcog,
		   cover &ncof, cover &ncog)
{
	int sv = 0;
	//sv = pick_split_var();

	/* Fsv */
	for (int i = 0; i < f.len; i++) {
		if (f.cubes[i].vars[sv] != '0')
			pcof.add_cube(f.cubes[i]);
	}
	pcof.del_column(sv);

	/* Fsv' */
	for (int i = 0; i < f.len; i++) {
		if (f.cubes[i].vars[sv] != '1')
			ncof.add_cube(f.cubes[i]);
	}
	ncof.del_column(sv);

	/* Gsv */
	for (int i = 0; i < g.len; i++) {
		if (g.cubes[i].vars[sv] != '0')
			pcog.add_cube(g.cubes[i]);
	}
	pcog.del_column(sv);

	/* Gsv' */
	for (int i = 0; i < g.len; i++) {
		if (g.cubes[i].vars[sv] != '1')
			ncog.add_cube(g.cubes[i]);
	}
	ncog.del_column(sv);


#ifdef DEBUG
	cout << "Splitting variable: x" << sv << endl;
	cout << "DEBUG: printing positive cofactor of F" << endl;
	pcof.print();
	cout << "DEBUG: printing negative cofactor of F" << endl;
	ncof.print();
	cout << "DEBUG: printing positive cofactor of G" << endl;
	pcog.print();
	cout << "DEBUG: printing negative cofactor of G" << endl;
	ncog.print();
#endif

}
