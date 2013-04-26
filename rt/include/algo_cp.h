#ifndef __CP_H__
#define __CP_H__

#include <sng.h>

class cp{

private:
	vector<vertex *> topo_sorted;

public:

	int func_cp(sng *graph);
	void visit(vertex *u);

};

#endif /* __CP_H__ */
