#include "tc_parser.h"

#define _get_char(offset, cf,cg)					\
	{								\
		for (int i = 0; i < offset; i++) {			\
			if (!fpla.good() || !gpla.good())		\
				cout << "Input format error" << endl;	\
			fpla >> cf;					\
			gpla >> cg;					\
		}							\
	}

int tc_parser::read_params() {
	char cf, cg;
	int l;

	/* Read number of inputs */
	_get_char(3, cf, cg);
	if (cf != cg)
		cout << "Numbers of inputs mismatch" << endl;
	l = cf - '0';
	cout << "Number of inputs: " << l << endl;

	return l;
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
