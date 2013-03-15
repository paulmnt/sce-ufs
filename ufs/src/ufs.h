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
 * @fanout is the output part, which is fixed
 * to 2.
 */
template <int VARS>
class cube {
public:
	short fanin[VARS];
	short fanout[2];
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
	cover()
	{
		splitvar = 0;
	}

	void add_cube(const cube<VARS> &c)
	{
		cubes.push_back(c);
	}

	vector<cube<VARS> > cubes;
	int splitvar;
};

template <int VARS>
class ufs {
public:
	ufs(const cover<VARS> &c)
	{
		cov = c;
	}

	static cover<VARS> cov;
};

#endif
