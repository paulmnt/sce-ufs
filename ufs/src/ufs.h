#ifndef __UFS_H__
#define __UFS_H__

#ifdef DEBUG
#include <assert.h>
#endif

#include <vector>
#include <iostream>

using namespace std;

/**
 * Possible values are
 * '0', '1', '-'
 */
class cube {
public:
	cube() {
		len = 0;
	}

	void add(const char v) {
		vars.push_back(v);
		len++;
	}

	void del(int i) {
		vars.erase(vars.begin() + i);
		len--;
	}

	void print() const
	{
		for (int i = 0; i < len; i++)
			cout << vars[i];
		cout << endl;
	}

	vector<char> vars;
	int len;
};

/**
 * A cover is a vector of cubes
 */
class cover {
public:
	cover(int l) {
		len = 0;
		lits = l;
		dep.resize(l);
		ones.resize(l);
		zeros.resize(l);
		dcs.resize(l);
		varid.resize(l);
		for (int i = 0; i < l; i++) {
			dep[i] = 0;
			ones[i] = 0;
			zeros[i] = 0;
			dcs[i] = 0;
			varid[i] = i;
		}
	}

	void add_cube(const cube &c) {
		/* Add a cube to the cover */
		cubes.push_back(c);
		len++;
		/* and keep data structure coherent  */
		for (int i = 0; i < lits; i++) {
			if (c.vars[i] == '-')
				dcs[i]++;
			else {
				dep[i]++;
				if (c.vars[i] == '1')
					ones[i]++;
				else
					zeros[i]++;
			}
		}
	}

	void del_column(int j) {
		/* Keep data structure coherent */
		lits--;
		dep.erase(dep.begin() + j);
		ones.erase(ones.begin() + j);
		zeros.erase(zeros.begin() + j);
		dcs.erase(dcs.begin() + j);
		/* then erase column */
		for (int i = 0; i < len; i++) {
			cubes[i].del(j);
		}
	}

	void print() const
	{
		for (int i = 0; i < len; i++)
			cubes[i].print();
		cout << endl;
	}

	bool empty() const
	{
		if (!len)
			return true;
		return false;
	}

	vector<cube> cubes;
	int len;
	int lits;

	/*
	 * Following vectors must have the size equal
	 * to the number of literals shown in the cover
	*/

	/* Keep track of dependency */
	vector<int> dep;
	/* Keep track of unateness */
	vector<int> ones;
	vector<int> zeros;
	vector<int> dcs;
	vector<int> varid;
};


/**
 * A node is a structure containing the information
 * of a node of the recursion tree.
 */
class node {
public:
	void print() const {
		cout << id << ". ";
		if (splitvar < 0)
			cout << rule;
		else
			cout << "x" << splitvar;
		if (sim < 0)
			cout << endl;
		else
			cout << " " << sim << endl;
	}

	int id;
	int splitvar;
	string rule;
	float sim;
};

/**
 * A level is a vector of nodes
 */
class level {
public:
	level() {
		len = 0;
	}

	void add_node(const node &n) {
		nodes.push_back(n);
		len++;
	}

	void print() const {
		for (int i = 0; i < len; i++)
			nodes[i].print();
	}

	vector<node> nodes;
	int len;
};

/**
 * Function Similarity with Unate Recursive Paradigm
 *
 * This class containes all the methods to run the
 * function similarity evalutation tool.
 *
 */
class ufs {
public:
	ufs(bool b7, bool b8, int m14, bool verb,
		cover *F, cover *G, int l)
	{
		use_b7 = b7;
		use_b8 = b8;
		use_m14 = m14;
		use_verb = verb;
		len = 0;
		lits = l;
		f = F;
		g = G;
		pcof = new cover(l);
		pcog = new cover(l);
		ncof = new cover(l);
		ncog = new cover(l);
	}

	/* Returns termination rule number or 0 */
	int check_rules(const cover &f, const cover &g);


	void cofactor(int sv);

	void apply_rule(const string rule, cover &f, cover &g);

	float simeval(const string rule, const cover &f, const cover &g);

	void print_levels() const {
		for (int i = 0; i < len; i++) {
			cout << "==level " << i + 1 << "==" << endl;
			out[i].print();
			if (i != len - 1)
				cout << endl;
		}
	}

	/* The output is the vector of levels */
	vector<level> out;
	int len;

private:
	bool use_b7, use_b8, use_verb;
	int use_m14;

	int lits;

	/*
	 * These are used as temporary variables during recursion,
	 * thus we don't need memory to store intermediate covers.
	 * When verbose mode is enabled the intermediate PLAs are
	 * printed before the temporary covers are overwritten.
	 */
	cover *f, *g;
	cover *pcof, *pcog, *ncof, *ncog;
};

#endif
