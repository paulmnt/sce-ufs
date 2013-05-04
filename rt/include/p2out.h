#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <climits>

#include <sng.h>

using namespace std;

#ifndef __P2OUT_H__
#define __P2OUT_H__


/* Normal mode outputs */
#define P2_013 "-part2-summary.txt"
#define P2_2 "-part2-CDFG-output.txt"
#define P2_4 "-part2-c-vector.txt"
#define P2_5 "-part2-complete-constraint.txt"
#define P2_6 "-part2-reduced-constraint.txt"

/* Verbose mode outputs (./retime --verbose) */
#define P2_7 "-part2-simplex.txt"

#define print_item(of, s)						\
	of << "----------------------------------------------" << endl; \
	of << s << endl;						\
	of << "----------------------------------------------" << endl; \
	of << endl


struct p2_triple {
	uint i;
	int ic;
	uint j;
	int jc;
	int ans;

	bool leq;
	bool opt;
};

class p2out {

public:
	p2out(string s, bool b)
	{
		name = s;
		verb = b;

		p2_013.open((name + string(P2_013)).c_str());
		p2_2.open((name + string(P2_2)).c_str());
		p2_4.open((name + string(P2_4)).c_str());
		p2_5.open((name + string(P2_5)).c_str());
		p2_6.open((name + string(P2_6)).c_str());
		if (verb) {
			p2_7.open((name + string(P2_7)).c_str());
		}
		print_item(p2_013, ("S.N.G. name: " + name));
	}

	~p2out()
	{
		p2_013.close();
		p2_2.close();
		p2_4.close();
		p2_5.close();
		p2_6.close();
		if (verb) {
			p2_7.close();
		}
	}


	void it0(uint area);
	void it1(int *r, uint n);
	void it3(uint area);

	void it2(sng *g);

	void it4(sng *g);

	void it5();
	void it6();

	void it7(vector<uint> &r, uint n);


	void it8a(sng *g, uint it, uint phi);
	void it8b(sng *g, uint it, uint phi);
	void it8c(sng *g, uint it, uint phi);

	void add_constraint(p2_triple &t)
	{
		constraints.push_back(t);
	}

private:
	string name;
	bool verb;
	ofstream p2_013;
	ofstream p2_2;
	ofstream p2_4;
	ofstream p2_5;
	ofstream p2_6;
	ofstream p2_7;

	vector<p2_triple> constraints;
};

#endif /* __P2OUT_H__ */
