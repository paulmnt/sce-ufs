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

	_get_string(2)

	/* Read number of inputs */
	if (s1.compare(s2) != 0)
		cout << "Numbers of inputs mismatch" << endl;
	l = s1[3];
	cout << "Number of inputs: " << l << endl;

	/* skip number of outputs */
	_get_string(2)

	return l;
}

/*
void tc_parser::read_covers(cover &f, cover &g)
{
	cube c1;
	cube c2;

	while (1) {
		_get_char(1);
		if (cf == '.')
			break;
		for (int i = 1; i < lits; i++) {
			c1.add(cf);
			c2.add(cg);

			cout << i << ": " << cf << " " << cg << endl;

			_get_char(1);
		}

		f.add_cube(c1);
		g.add_cube(c2);
		/* skip output */
/*		_get_char(1);
	}
*/
	/* DEBUG */
/*	f.print();
	g.print();
}
*/

void tc_parser::read_covers(cover &f, cover &g)
{
	cube c1;
	cube c2;

	/* Read input part */
	_get_string(1)

	while (s1.compare(".e") != 0) {
		for (int i = 0; i < lits; i++) {
			c1.add(s1[i]);
			c2.add(s2[i]);

			/* Skip output and read next */
			_get_string(2);
		}

		f.add_cube(c1);
		g.add_cube(c2);
	}

	/* DEBUG */
	f.print();
	g.print();
}


/*
void tc_parser::dump_file()
{
	string s;
	infile >> s;
	if (s.compare(".i") == 0) {
		infile >> lits;
		cout << "Number of inputs: " << lits << endl;
	}
	for (int i = 0; i < lits; i ++) {
		char c = 97 + i;
		cout << c << " ";
	}
	cout << "F G" << endl;
	while (infile.good()) {
		infile >> s;
		if (s.compare(".e") == 0)
			break;

		for (int i = 1; i < lits + 2; i ++) {
			cout << s << " ";
			infile >> s;
		}
		cout << s << endl;
	}
}

*/
