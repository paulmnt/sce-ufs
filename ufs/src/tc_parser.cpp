#include "tc_parser.h"

/*
#define _get_char(offset)						\
	{								\
		for (int i = 0; i < offset; i++) {			\
			if (!fpla.good() || !gpla.good())		\
				cout << "Input format error" << endl;	\
			fpla >> cf;					\
			gpla >> cg;					\
		}							\
	}
*/

#define _get_string(offset)				\
	{						\
		for (int i = 0; i < offset; i++) {	\
			fpla >> s1;			\
			gpla >> s2;			\
		}					\
	}


int tc_parser::read_params()
{
	int l;

	_get_string(2);

	/* Read number of inputs */
	if (s1.compare(s2) != 0)
		cout << "Numbers of inputs mismatch" << endl;
	stringstream(s1) >> l;
	cout << "Number of inputs: " << l << endl;

	/* skip number of outputs */
	_get_string(2);

	return l;
}

void tc_parser::read_covers(cover &f, cover &g)
{
	/* Read input part */
	_get_string(1)

	while (s1.compare(".e") != 0) {
		cube cf;
		cube cg;
		for (int i = 0; i < lits; i++) {
			cf.add(s1[i]);
			cg.add(s2[i]);
		}

		/* Skip output and read next */
		_get_string(2);

		f.add_cube(cf);
		g.add_cube(cg);
	}

#ifdef DEBUG
	/* DEBUG */
	cout << "DEBUG: printing input covers" << endl;
	f.print();
	g.print();
#endif

}
