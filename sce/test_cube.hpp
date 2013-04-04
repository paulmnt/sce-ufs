#ifndef _INCL_SING_CUBE
#define INCL_SING_CUBE


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <map>
#include <utility>

using namespace std;

class sing_cube{

private:
	vector<string> cube_ord;		//save order of cubes in vector
	vector<char> var_ord;			//save ordr of variables in vector
	vector<int> cube_id;			//IDs of all the cubes
	int num_fns;				// number of functions
	int num_vars;				// number of variables

	struct points{			//points (R,C) where matrix has value 1
		int r;
		int c;
	};

	vector<points> pts_vec;

	struct col_set{				//set of columns for each row
		int row;
		vector<int> set_cols;
	};

	vector<col_set> vec_col_set;

	struct rectangles{			//set of rectangles
		vector<int> R;
		vector<int> C;
	};

	vector<rectangles> vec_rect;

public:

	void parse_file(char* string, const char* pc, const char* pv, const char* pm, const char* pp); //parse input file
	void print_rectangles(int pp);	//compute prime rectangles
	int get_literals_after_ext(vector<int>&, vector<int>&, vector<int>&);	//find number of literals after single-cube extraction

};

#endif 
