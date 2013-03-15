#include <iostream>
#include <string>
#include "tc_parser.h"
#include "ufs.h"

using namespace std;


bool flag_found(int argc, char **argv, const string &flag) {
	for (int i = 1; i < argc; i++) {
		if (flag.compare(argv[i]) == 0)
			return true;
	}
	return false;
}



int main(int argc, char **argv) {

	cout << "Function Similarity - Unate Recursive Paradigm" << endl << endl;

	if (argc < 2) {
		cout << "Usage: ufs [flags] <input_file>" << endl;
		cout << "To display options: ufs --help" << endl;
		return -1;
	}

	if (flag_found(argc, argv, "--help")) {
		cout << "Flags:" << endl;
		return 0;
	}

	tc_parser *data = new tc_parser(argv[argc - 1]);
	data->dump_file();

	return 0;
}
