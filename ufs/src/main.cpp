#include <iostream>
#include <string>
#include <sstream>
#include "tc_parser.h"
#include "ufs.h"

using namespace std;

#define FPLA "../tb/f.pla"
#define GPLA "../tb/g.pla"


static bool single_disjoint = false;
static bool multi_disjoint = false;
static int scc = 0;
static int flags_count = 1;


/* Returns the index of the argument if found. 0 otherwise */
static int flag_found(int argc, char **argv, const string &flag) {
	for (int i = 1; i < argc; i++) {
		if (flag.compare(argv[i]) == 0)
			return i;
	}
	return 0;
}

static int parse_flags(int argc, char **argv)
{
	/* Print help */
	if (flag_found(argc, argv, "--help")) {
		cout << "Usage: ufs [flags] <input_file_1> <input_file_2>" << endl;
		cout << "To display options: ufs --help" << endl;
		cout << endl;
		return 2;
	}
	/* Handle flags */
	if (flag_found(argc, argv, "--single_disjoint")) {
		flags_count++;
		single_disjoint = true;
		cout << "INFO: Rule B7 (single disjoint) enabled" << endl;
	}
	if (flag_found(argc, argv, "--multi_disjoint")) {
		flags_count++;
		single_disjoint = true;
		multi_disjoint = true;
		cout << "INFO: Rule B7 (single disjoint) enabled" << endl;
		cout << "INFO: Rule B8 (multi_disjoint) enabled" << endl;
	}
	if (int index = flag_found(argc, argv, "--scc")) {
		flags_count += 2;
		if (argc <= index + 1) {
			cout << "ERROR: Flag --scc requires number of cubes" << endl;
			cout << "To display options: ufs --help" << endl;
			return 1;
		}
		stringstream ss(argv[index + 1]);
		ss >> scc;
		if (!scc) {
			cout << "ERROR: Flag --scc requires number of cubes" << endl;
			cout << "To display options: ufs --help" << endl;
			return 1;
		}
		cout << "INFO: Rule M1 (SCC) enabled on covers with at most ";
		cout << scc << " cubes" << endl;
	}
	if (argc > flags_count) {
		cout << "ERROR: unrecognized flags" << endl;
			cout << "To display options: ufs --help" << endl;
			return 1;
	}
	return 0;

}

int main(int argc, char **argv) {

	cout << "Function Similarity - Unate Recursive Paradigm" << endl << endl;
	if (parse_flags(argc, argv))
		return 1;

	/* Open input files and read input # */
	char *f1 = (char *)FPLA;
	char *f2 = (char *)GPLA;
	tc_parser in(f1, f2);
	int lits = in.get_lits();

	/* Load covers */
	cover F(lits), G(lits);
	in.read_covers(F, G);

	/* UFS */
	ufs u;
	cover pf(lits), pg(lits), nf(lits), ng(lits);
	u.cofactor(F, G, pf, pg, nf, ng);

	u.similarity(F.cubes[0], G.cubes[0]);

	return 0;
}
