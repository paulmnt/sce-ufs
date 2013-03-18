#include <iostream>
#include <string>
#include "tc_parser.h"
#include "ufs.h"

using namespace std;

#define FPLA "../tb/f.pla"
#define GPLA "../tb/g.pla"



bool flag_found(int argc, char **argv, const string &flag) {
	for (int i = 1; i < argc; i++) {
		if (flag.compare(argv[i]) == 0)
			return true;
	}
	return false;
}



int main(int argc, char **argv) {

	cout << "Function Similarity - Unate Recursive Paradigm" << endl << endl;

	/* Print help */
	if (flag_found(argc, argv, "--help")) {
		cout << "Usage: ufs [flags] <input_file_1> <input_file_2>" << endl;
		cout << "To display options: ufs --help" << endl;
		cout << endl;
		return 0;
	}

	/* Open input files and read input # */
	char *f1 = (char *)FPLA;
	char *f2 = (char *)GPLA;
	tc_parser in(f1, f2);

	/* Load covers */
	cover F, G;
	in.read_covers(F, G);

	/* UFS class */
	ufs u;
	cover pf, pg, nf, ng;
	u.cofactor(F, G, pf, pg, nf, ng);

	u.similarity(F.cubes[0], G.cubes[0]);

	return 0;
}
