#ifndef __UFS_H__
#define __UFS_H__

#include <vector>
#include <iostream>

using namespace std;

/**
 * Possible values are
 * '0', '1', '-'
 */
class cube {
public:
	void add(const char v) {
		vars.push_back(v);
	}

	void print() {
		int len = vars.size();
		for (int i = 0; i < len; i++)
			cout << vars[i];
		cout << endl;
	}

	vector<char> vars;
};


class cover {
public:
	void add_cube(const cube &c) {
		cubes.push_back(c);
	}

	void print() {
		int len = cubes.size();
		for (int i = 0; i < len; i++)
			cubes[i].print();
		cout << endl;
	}

	vector<cube> cubes;
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
	vector<node> n;
};


class ufs {
public:

	void covers_to_level();

	/* The output is the vector of levels */
	vector<level> out;
};

#endif
