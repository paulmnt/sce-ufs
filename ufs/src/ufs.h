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
		for (int i = 0; i < l; i++) {
			dep[i] = 0;
			ones[i] = 0;
			zeros[i] = 0;
			dcs[i] = 0;
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
 *      (Requires the flag --single_disjoint or
 *       --multi_disjoint)
 * B8:  Both covers have multiple non intersecting
 *      cubes. (Requires the flag --multi_disjoint)
 * B9:  Both covers show single input dependence
 *      (same varible)
 * B10: Both covers show single input dependence
 *      (different variables)
 *
 * UNATENESS
 * U1:  Both covers are positive/negative unate
 *      on the same variable with no DCs. Prune the
 *      tree.
 * U2:  Both covers are unate on the same variable
 *      with no DCs, but one is positive, while the
 *      other is negative. Prune the tree.
 * U3:  One cover is positive/negative unate in a
 *      variable Xi. Pick Xi as splitting variable
 *      to einforce B3 for one child.
 *
 * Miscellaneus rules for potential speed up
 * M1:  When a cover has less than X cubes, apply
 *      SCC(). (Requires flag "--scc X")
 *
 * Splitting variable choice
 * Try rule U3 first.
 * Pick a binate variable to try to keep the tree
 * balanced, thus increasing the probability that
 * the simple rule B6 applies.
 *
 * Shannon decomposition:
 * At each level do:
 *  - sum of the similarities of children to obtain
 *    the similarity of the cofactors at the current
 *    level.
 *  - divide by two to report the similarity weight
 *    to the upper level. TODO: CHECK!!!
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
