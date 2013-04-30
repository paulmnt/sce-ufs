#include <iostream>
#include <p1out.h>

#include <sng.h>
#include <parser.h>
#include <algo_wd.h>
#include <algo_feas.h>

using namespace std;

static char *INFILE;        // Input file passed from command line
static bool verb = false;   // Verbose disabled by default
static bool minphi = true;  // Default mode is minimum cycle
static int target_phi = 0;  // target clock cycle
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

	sng *graph  = NULL;  // Synch. Network Graph
	uint phi;            // Cycle
	int *r = NULL;       // Retiming vector

	/* Open and parse input file */
	parser ip;
	graph = ip.parse_file(INFILE);
	if (!graph)
		return 1;

	/* Open output files */
	string name = graph->get_name();
	p1out print1(name, verb);

	if (minphi) {
		/* Item 0: Initial Area */
		print1.it0(graph->get_area());

		/* OPT2 */

		/* Step 1: Compute W and D */
		uint n = graph->get_num_vertices();
		uint **w = new uint*[n];
		uint **d = new uint*[n];
		for (uint i = 0; i < n; i++) {
			w[i] = new uint[n];
			d[i] = new uint[n];
		}
		wd wdobj(n, w, d, &print1);
		wdobj.init_wd(graph);
		/* Method returns initial cycle */
		phi = wdobj.compute_wd();
		/* Item 4: WD Matrices */
		print1.it4(w, d, n);
		/* Item 5: Initial clock cycle */
		print1.it5(phi);

		/* Step 2: Sort elements in the range of D */
		wdobj.sort_d();

		/* Step 3: Binary search the minimum cycle phi with FEAS */
		feas feasobj(graph, n, &print1);
		r = new int[n];
		feasobj.init_r(r);
		uint max_ind;
		uint min_ind = 0;
		uint ind;

		for (uint h = 0; h < wdobj.get_target_phi_list_size(); h++) {
			if (wdobj.get_target_phi(h) == phi) {
				max_ind = h;
				break;
			}
		}
		/* We assume zero cycle not feasible (true for any circuit) */
		ind = max_ind / 2;
		while (ind != min_ind) {
			uint c = wdobj.get_target_phi(ind);
			if (feasobj.func_feas(c, r)) {
				phi = c;
				max_ind = ind;
			} else
				min_ind = ind;
			ind = (max_ind + min_ind) / 2;
		}
		/* Step 4: Print output */
#ifdef INFO
		cout << "INFO: Minimum feasible cycle is " << phi << endl;
		cout << "      Retiming vector is ";
		for (uint i = 0; i < n; i++)
			cout << r[i] << " ";
		cout << endl;
		for (uint i = 0; i < graph->get_num_edges(); i++)
			graph->print_edge(i);
#endif
		/* Item 1: Optimal retiming vector */
		print1.it1(r, n);
		/* Item 3: Optimal clock cycle */
		print1.it3(phi);
		/* Item 2: Retimed Synchronous Network Graph */
		print1.it2(graph);
	} else
		//TODO!!!!
		cout << "INFO: Minimum Area mode not implemented yet" << endl;

	/* p1out destructor closes output files */



	return 0;
}
