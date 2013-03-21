#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "tc_parser.h"
#include "ufs.h"

using namespace std;

#define FPLA "../tb/f.pla"
#define GPLA "../tb/g.pla"
#define TREE "recursionTree.txt"

static bool single_disjoint = false;
static bool multi_disjoint = false;
static int scc = 0;
static bool verb = false;
static int flags_count = 1;

/* TODO: implement VERBOSE and other rules! */

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
		cout << "Usage: ufs [flags]" << endl;
		cout << endl;
		cout << " --help            : Displays options" << endl;
		cout << endl;
		cout << " --verbose         : Enables verbose mode and prints all" << endl;
		cout << "                     the intermediate PLAs into all-PLAs" << endl;
		cout << endl;
		cout << " --single_disjoint : Enables rule B7 to terminate if one" << endl;
		cout << "                     cover has a single cube, while the" << endl;
		cout << "                     other has non intersecting cubes." << endl;
		cout << endl;
		cout << " --multi_disjoint  : Enables rule B8 to terminate if both" << endl;
		cout << "                     covers have non intersecting cubes." << endl;
		cout << endl;
		cout << " --scc X           : (Not Implemented) SCC on covers with" << endl;
		cout << "                     at most X cubes before rule checking" << endl;
		cout << endl;
		return 2;
	}
	/* Handle flags */
	if (flag_found(argc, argv, "--verbose")) {
		flags_count++;
		verb = true;
		cout << "INFO: Verbose mode enabled" << endl;
	}
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
		cout << "INFO: Rule M16 (SCC) enabled on covers with at most ";
		cout << scc << " cubes" << endl;
		cout << "      Rule M16 is not actually implemented in this version";
		cout << " because not a requirement" << endl;
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
	ufs u(single_disjoint, multi_disjoint, scc, verb, lits);

	float sim = u.simeval(F, G);
	cout << "Function similarity is " << sim << endl;

	/* Print output */
	ofstream of(TREE);
	u.print_levels(of);
	of.close();

	return 0;
}
