#include <parser.h>

class cp{

private:

        vector<vector<int> > g0_edges;
        vector<int> g0_vertices;
        vector<string> color;
	vector<int> dis;
	vector<int> fin;
	int time;
	vector<int> topo_sort;


public:

	int func_cp(parser& pobj);
	void visit(int u);

};
