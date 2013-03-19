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

	void print() {
		int len = vars.size();
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
	cover() {
		len = 0;
	}

	void add_cube(const cube &c) {
		cubes.push_back(c);
		len++;
	}


	void del_column(int j) {
		for (int i = 0; i < len; i++)
			cubes[i].del(j);
	}

	void print() {
		int len = cubes.size();
		for (int i = 0; i < len; i++)
			cubes[i].print();
		cout << endl;
	}


	vector<cube> cubes;
	int len;
};


/**
 * A node is a structure containing the information
 * of a node of the recursion tree.
 */
class node {
public:
	int id;
	int splitvar;
	string rule;
	int sim;
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

	vector<node> nodes;
	int len;
};

/**
 * Function Similarity with Unate Recursive Paradigm
 *
 * This class containes all the methods to run the
 * function similarity evalutation tool.
 *
 * TERMINATION RULES
 * B1:  Both covers are empty.
 * B2:  Both covers are a tautology.
 * B3:  One cover is empty.
 * B4:  One cover is a tautology.
 * B5:  One cover is empty and one is a tautology.
 * B6:  Both covers have a single cube.
 * B7:  One cover has a single cube and the other
 *      has non intersecting cubes.
 *      (Requires the flag --single_disjoint)
 * B8:  Both covers have multiple non intersecting
 *      cubes. (Requires the flag --multi_disjoint)
 * B9:  Both covers show single input dependence
 *      (same varible)
 * B10: Both covers show single input dependence
 *      (different variables)

 * M1:  When a cover has less than X cubes, apply
 *      SCC(). (Requires flag "--scc X")
 */
class ufs {
public:
	void cofactor(const cover &f, const cover &g,
		cover &pcof, cover &pcog,
		cover &ncof, cover &ncog);

	/*
	 * Simple tatutology checking: this check does not
	 * go through a complete tautology checking, because
	 * it would be as expensive as making more splitting
	 * steps. This function just checks for quick rules
	 * for termination, taken from "Tautology Checking"
	 * but does not go through recursion.
	 * Called by rule B2 and B4 and B5
	 */
	bool is_tautology(const cover &f);

	/* Similarity between two cubes. Called by ule B6 */
	float similarity(const cube &c1, const cube &c2);
	int total_ones(const cube &c1, const cube &c2);
	int common_ones(const cube &c1, const cube &c2);


	/* The output is the vector of levels */
	vector<level> out;

};

#endif
