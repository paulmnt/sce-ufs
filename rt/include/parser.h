#ifndef __PARSER_H__
#define __PARSER_H__

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <utility>
#include <sstream>

using namespace std;

class parser{

private:
	int num_vertices;		//total number of vertices, including v_0
	vector<int> delay_vert_vec;	// vertex and its corresponding delay
        vector<vector<int> > edges_vec;	//edges
        vector<int> edge_wts_vec;	//weight of each edge stored in a vector


public:
	void parse_file(char* file);
	int get_num_vertices();
	vector<int> get_delay_vert_vec();
	vector<vector<int> > get_edges_vec();
	vector<int> get_edge_wts_vec();

};


#endif /* __PARSER_H__ */
