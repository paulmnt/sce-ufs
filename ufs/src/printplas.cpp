#include "printplas.h"

#define DIR "all-PLAs"

void printplas::print(int levelid, int nodeid, const cover &f, const cover &g)
{
	mkdir(DIR, 0775);
	stringstream ssf, ssg;;

	ssf << DIR << "/" << levelid << "." << nodeid << ".F.pla";
	const string tmpf = ssf.str();
	const char *cstrf = tmpf.c_str();
	ofstream outf(cstrf);

	ssg << DIR << "/" << levelid << "." << nodeid << ".G.pla";
	const string tmpg = ssg.str();
	const char *cstrg = tmpg.c_str();
	ofstream outg(cstrg);

	outf << ".i " << f.lits << endl;
	outf << ".o 1" << endl;
	f.print(outf);
	outf << ".e";

	outg << ".i " << g.lits << endl;
	outg << ".o 1" << endl;
	g.print(outg);
	outg << ".e";

	outf.close();
	outg.close();
}
