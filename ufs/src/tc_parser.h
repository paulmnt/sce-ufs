#ifndef __TC_PARSER_H__
#define __TC_PARSER_H__

#include <iostream>
#include <string>
#include <fstream>

#include "ufs.h"

using namespace std;

/**
 * Two covers input file parser
 * This class parses a simplified pla like file, which
 * takes .i parameter, but does not accept .o, being
 * the number of outputs always equal to 2.
 *
 * Inputs values can be 1, 0, - (i.e. don't care).
 * The output part tells whether the cube contributes
 * or not to each of the two functions, therefore
 * only 1 (does contribute) or 0 (does not contribute)
 * are allowed values.
 *
 * .e sets the end of the list of cubes.
 *
 * The contructor takes @filename as the only parameter
 */
class tc_parser {

public:
	tc_parser(char *filename) {
		infile.open(filename);
		lits = read_params()
	}

	~tc_parser() {
		infile.close();
	}

	void dump_file();


private:
	int read_params();

	ifstream infile;
	int lits;

};

#endif /* __TC_PARSER_H__ */
