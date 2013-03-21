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
		varid.erase(varid.begin() + j);
		/* then erase column */
		for (int i = 0; i < len; i++) {
			cubes[i].del(j);
		}
		/* When there are no variables, it's empty! */
		if (!lits)
			len = 0;
	}

	void print() const
	{
		for (int i = 0; i < len; i++)
			cubes[i].print();
		/*
		cout << "VARIDs: ";
		for (int i = 0; i < lits; i++) {
			cout << varid[i] << " ";
		}

		cout << "ONES: ";
		for (int i = 0; i < lits; i++) {
			cout << ones[i] << " ";
		}
		cout << endl;
		cout << "ZEROS: ";
		for (int i = 0; i < lits; i++) {
			cout << zeros[i] << " ";
		}
		*/
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
		if (splitvar < 0)
			cout << rule;
		else
			cout << "x" << splitvar;
		if (sim < 0)
			cout << endl;
		else
			cout << " " << sim << endl;
	}

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
		for (int i = 0; i < len; i++) {
			cout << i + 1 << ". ";
			nodes[i].print();
		}
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
	ufs(bool b7, bool b8, int m16, bool verb, int l)
	{
		current_level = 0;
		use_b7 = b7;
		use_b8 = b8;
		use_m16 = m16;
		use_verb = verb;
		len = 0;
		lits = l;
	}

	/* Returns termination rule number or 0 */
	int check_rules(const cover &f, const cover &g, int *sv);

	void cofactor(const cover &f, const cover &g,
		cover &pcof, cover &pcog,
		cover &ncof, cover &ncog, int sv);

	void apply_rule(const string rule, cover &f, cover &g);

	float simeval(const cover &f, const cover &g);

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
	int current_level;

	bool use_b7, use_b8;

	/* TODO: implement verbose! */
	bool use_verb;

	/* TODO: SCC not implemented and not required */
	int use_m16;

	int lits;

	/* Private recursive function */
	float similarity(const cover &f, const cover &g, int levelid);
	void add_level(level l) {
		out.push_back(l);
		len++;
	}
};


#endif
