#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <climits>

#include <sng.h>

using namespace std;

#ifndef __P1OUT_H__
#define __P1OUT_H__


/* Normal mode outputs */
#define P1_013 "-part1-summary.txt"
#define P1_2 "-part1-CDFG-output.txt"
#define P1_457 "-part1-WD.txt"
/* Verbose mode outputs (./retime --verbose) */
#define P1_6 "-part1-Floyd-Warshall.txt"
#define P1_8 "-part1-FEAS.txt"

#define print_item(of, s)						\
	of << "----------------------------------------------" << endl; \
	of << s << endl;						\
	of << "----------------------------------------------" << endl; \
	of << endl

class p1out {

public:
	p1out(string s, bool b)
	{
		name = s;
		verb = b;

		p1_013.open((name + string(P1_013)).c_str());
		p1_2.open((name + string(P1_2)).c_str());
		p1_457.open((name + string(P1_457)).c_str());
		if (verb) {
			p1_6.open((name + string(P1_6)).c_str());
			p1_8.open((name + string(P1_8)).c_str());
		}
		print_item(p1_013, ("S.N.G. name: " + name));

	}

	~p1out()
	{
		p1_013.close();
		p1_2.close();
		p1_457.close();
		if (verb) {
			p1_6.close();
			p1_8.close();
		}
	}


	void it0(uint area);
	void it1(int *r, uint n);
	void it3(uint phi);

	void it2(sng *g);

	void it4(uint **w, uint **d, uint n);
	void it5(uint phi);
	void it7(vector<uint> &r, uint n);

	void it6(uint **w, uint **d, uint n, uint it);

	void it8a(sng *g, uint it, uint phi);
	void it8b(sng *g, uint it, uint phi);
	void it8c(sng *g, uint it, uint phi);

private:
	string name;
	bool verb;
	ofstream p1_013;
	ofstream p1_2;
	ofstream p1_457;
	ofstream p1_6;
	ofstream p1_8;


};

#endif /* __P1OUT_H__ */
