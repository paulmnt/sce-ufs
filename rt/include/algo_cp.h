#ifndef __CP_H__
#define __CP_H__

#include <sng.h>

class cp{

private:
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
