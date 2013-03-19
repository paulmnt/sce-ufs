#include <iostream>
#include <string>
#include <sstream>
#include "tc_parser.h"
#include "ufs.h"

using namespace std;

#define FPLA "../tb/f.pla"
#define GPLA "../tb/g.pla"


/* Returns the index of the argument if found. 0 otherwise */
int flag_found(int argc, char **argv, const string &flag) {
	for (int i = 1; i < argc; i++) {
		if (flag.compare(argv[i]) == 0)
			return i;
	}
	return 0;
}



int main(int argc, char **argv) {

	bool single_disjoint = false;
	bool multi_disjoint = false;
	int scc = 0;

	cout << "Function Similarity - Unate Recursive Paradigm" << endl << endl;

	/* Print help */
	if (flag_found(argc, argv, "--help")) {
		cout << "Usage: ufs [flags] <input_file_1> <input_file_2>" << endl;
		cout << "To display options: ufs --help" << endl;
		cout << endl;
		return 0;
	}
	if (flag_found(argc, argv, "--single_disjoint")) {
		single_disjoint = true;
		cout << " INFO: Rule B7 (single disjoint) enabled" << endl;
	}
	if (flag_found(argc, argv, "--multi_disjoint")) {
		multi_disjoint = true;
		cout << "INFO: Rule B8 (multi_disjoint) enabled" << endl;
	}
	if (int index = flag_found(argc, argv, "--scc")) {
		stringstream ss(argv[index + 1]);
		ss >> scc;
		cout << "INFO: Rule M1 (SCC) enabled on covers with less than ";
		cout << scc << " cubes" << endl;
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
