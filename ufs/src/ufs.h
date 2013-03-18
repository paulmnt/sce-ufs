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


class ufs {
public:
	void cofactor(const cover &f, const cover &g,
		cover &pcof, cover &pcog,
		cover &ncof, cover &ncog);

	int common_ones(const cube &c1, const cube &c2);

	/* This does not consider intersection! */
	int total_ones(const cube &c1, const cube &c2);

	float similarity(const cube &c1, const cube &c2);

	/* The output is the vector of levels */
	vector<level> out;

};

#endif
