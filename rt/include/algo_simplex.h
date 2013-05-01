#include <sng.h>

#ifndef __SIPLEX_H__
#define __SIPLEX_H__


class tab_row {

public:
	void add_slack_var()
	{
		coeff.push_back(0);
	}

	void print();

	bool star;
	int label;
	vector<int> coeff;
	int ans;
};

class simplex {

public:
	simplex(uint n)
	{
		num_vertices = n;
		/*
		 * Retiming vector variable labels range from 0 to
		 * num_vertices - 1 therefore slack variables first
		 * label is num_vertices.
		 */
		slack_var = num_vertices;
	}

	void print_tableau();
	void make_tableau(sng *g, uint **w, uint **d);

private:
	/* variables from 0 to num_vertices - 1 are the ri */
	int num_vertices;
	vector<tab_row > matrix;
	vector<int> result;

	/*
	 * Retiming vector variable labels range from 0 to num_vertices - 1
	 * therefor slack variables first label is num_vertices.
	 */
	uint slack_var;
};

#endif /* __SIPLEX_H__ */
