#ifndef __UFS_H__
#define __UFS_H__

#include <vector>

using namespace std;

/**
 * Structure for a single cube in a cover
 *
 * @fanin is the input par, which has variable
 * number of entries (@VARS).
 *
 * The fanout is always 1 and there is no need
 * to store it.
 */
template <int VARS>
class cube {
public:
	short fanin[VARS];
};


/**
 * A cover is a structure containing a vector of
 * multioutput cubes
 *
 * If it represents a cofactor we keep track of
 * the splitting variable @splitvar. If not, we
 * set @splitvar to 0.
 */
template <int VARS>
class cover {
public:
	void add_cube(const cube<VARS> &c)
	{
		cubes.push_back(c);
	}

	vector<cube<VARS> > cubes;
};

class node {
public:
	int id;
	int splitvar;
	string rule;
	int sim;
};

class levels {
public:
	vector<node> n;
};

class ufs {
public:
	ufs(const cover<VARS> &c1, const cover<VARS> &c2, const int lits)
	{
		F = c1;
		G = c2;

	}

	void covers_to_level();

	cover<VARS> F;
	cover<VARS> G;

	vector<levels> out;
};

#endif
