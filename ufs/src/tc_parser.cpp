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

#define _get_strings(offset, file1, file2, str1, str2)	\
	{						\
		for (int i = 0; i < offset; i++) {	\
			file1 >> str1;			\
			file2 >> str2;			\
		}					\
	}

#define _get_string(offset, file, str)			\
	{						\
		for (int i = 0; i < offset; i++) {	\
			file >> str;			\
		}					\
	}

int tc_parser::read_params()
{
	int l;

	_get_strings(2, fpla, gpla, s1, s2);

	/* Read number of inputs */
	if (s1.compare(s2) != 0)
		cout << "Numbers of inputs mismatch" << endl;
	stringstream(s1) >> l;
	cout << "Number of inputs: " << l << endl;

	/* skip number of outputs */
	_get_strings(2, fpla, gpla, s1, s2);

	return l;
}

void tc_parser::read_covers(cover &f, cover &g)
{
	/* Read input part */
	_get_string(1, fpla, s1)
	_get_string(1, gpla, s2)

	while (s1.compare(".e") != 0) {
		cube cf;
		for (int i = 0; i < lits; i++) {
			cf.add(s1[i]);
		}

		/* Skip output and read next */
		_get_string(2, fpla, s1);

		f.add_cube(cf);
	}

	while (s2.compare(".e") != 0) {
		cube cg;
		for (int i = 0; i < lits; i++) {
			cg.add(s2[i]);
		}

		/* Skip output and read next */
		_get_string(2, gpla, s2);

		g.add_cube(cg);
	}

#ifdef DEBUG
	/* DEBUG */
	cout << "DEBUG: printing input covers" << endl;
	f.print();
	g.print();
#endif

}
