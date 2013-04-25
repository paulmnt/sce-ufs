#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <sng.h>
#include <parser.h>
#include <algo_wd.h>
#include <algo_feas.h>

using namespace std;

static char *INFILE;        // Input file passed from command line
static bool verb = false;   // Verbose disabled by default
static bool minphi = true;  // Default mode is minimum cycle
static int target_phi = 0;         // target clock cycle
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
		cout << "Usage: retime [flags] --f <input_file>" << endl;
		cout << endl;
		cout << " --help            : Displays options" << endl;
		cout << endl;
		cout << " --verbose         : Enables verbose mode and prints all" << endl;
		cout << endl;
		cout << " --phi <cycle>     : The tool has two modes of operation. When" << endl;
		cout << "                     --phi is specified, mode (2) is enabled." << endl;
		cout << "                     Tool Modes:" << endl;
		cout << "                     (1) Get minimum clock cycle (default)" << endl;
		cout << "                     (2) Get minimum area given target cycle" << endl;
		cout << endl;
		return 2;
	}
	/* Handle flags */
	if (flag_found(argc, argv, "--verbose")) {
		flags_count++;
		verb = true;
		cout << "INFO: Verbose mode enabled" << endl;
	}
	if (int index = flag_found(argc, argv, "--phi")) {
		flags_count += 2;
		minphi = false;
		if (argc <= index + 1) {
			cout << "ERROR: Mode --phi requires target cycle" << endl;
			cout << "To display options: retime --help" << endl;
			return 1;
		}
		stringstream ss(argv[index + 1]);
		ss >> target_phi;
		if (!target_phi || target_phi < 1) {
			cout << "ERROR: Mode --phi requires target cycle > 0" << endl;
			cout << "To display options: retime --help" << endl;
			return 1;
		}
		cout << "INFO: Minimum area mode enabled with target cycle " << target_phi << endl;
	}
	if (minphi)
		cout << "INFO: Minimum cycle mode enabled" << endl;
	if (int index = flag_found(argc, argv, "--f")) {
		flags_count += 2;
		if (argc <= index + 1) {
			cout << "ERROR: --f must be followed by input file path" << endl;
			cout << "To display options: retime --help" << endl;
			return 1;
		}
		INFILE = argv[index + 1];
	} else {
		cout << "ERROR: Input file not specified." << endl;
		cout << "To display options: retime --help" << endl;
		cout << "Usage: retime [flags] --f <input_file>" << endl;
		return 1;
	}

	if (argc != flags_count) {
		cout << "ERROR: Unrecognized flag." << endl;
		cout << "To display options: retime --help" << endl;
		cout << "Usage: retime [flags] --f <input_file>" << endl;
		return 1;
	}
	return 0;
}


int main(int argc, char **argv) {

	cout << "Retiming Tool Started" << endl << endl;
	int pf = parse_flags(argc, argv);
	if (pf ==2)
		return 0;
	if (pf)
		return 1;

	sng *graph  = NULL; // Synch. Network Graph
	int phi;            // Cycle
	int *r;             // Retiming vector

	/* Open and parse input file */
	parser ip;
	graph = ip.parse_file(INFILE);
	if (!graph)
		return 1;

	if (minphi) {
		/* OPT2 */

		/* Step 1: Compute W and D */
		uint n = graph->get_num_vertices();
		uint **w = NULL;
		uint **d = NULL;
		wd wdobj(n, w, d);
		wdobj.init_wd(graph);
		wdobj.compute_wd();

		/* Step 2: Sort elements in the range of D */
		wdobj.sort_d();

		/* Step 3: Binary search the minimum cycle phi with FEAS */
		feas feasobj(graph);
		phi = feasobj.get_initial_phi();
		for (uint h = 0; h < wdobj.get_target_phi_list_size(); h++) {

		}

		/* Step 4: TODO Apply retiming vector to the graph */

	} else
		//TODO!!!!
		cout << "INFO: Minimum Area mode not implemented yet" << endl;



	/* Print output */
/*
	ofstream of(TREE);
	u.print_levels(of);
	of.close();
	ofstream test("print_sim.txt");
	test << sim << endl;
	test.close();
*/

	return 0;
}
