#include "tc_parser.h"

int tc_parser::read_params() {


}

void tc_parser::dump_file()
{
	if (!infile.good()) {
		cout << "Input format error" << endl;
		return;
	}
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

