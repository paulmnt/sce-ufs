#ifndef __CP_H__
#define __CP_H__

#include <sng.h>

class cp{

private:

        vector<vector<int> > g0_edges;
        vector<int> g0_vertices;
        vector<string> color;
	vector<int> dis;
	vector<int> fin;
	int time;
	vector<int> topo_sort;

	sng *graph;
	vector<vertex *> topo_sorted;

public:
	cp(sng *g)
	{
		graph = g;
	}

	int func_cp();
	void visit(vertex *u);

};

#endif /* __CP_H__ */
