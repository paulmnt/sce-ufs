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
	simplex(uint n, uint target_phi)
	{
		num_vertices = n;
		phi = target_phi;
		/*
		 * Retiming vector variable labels range from 0 to
		 * num_vertices - 1 therefore slack variables first
		 * label is num_vertices.
		 */
		slack_var = num_vertices;
	}

	void print_tableau();
	void make_tableau(sng *g, uint **w, uint **d);
	void add_legal_constraints(sng *g);
	void add_timing_constraints(sng *g, uint **w, uint **d);
	void add_objective_func_row(sng *g);

private:
	/* variables from 0 to num_vertices - 1 are the ri */
	uint num_vertices;
	uint phi;
	vector<tab_row > matrix;
	vector<int> result;

	/*
	 * Retiming vector variable labels range from 0 to num_vertices - 1
	 * therefor slack variables first label is num_vertices.
	 */
	uint slack_var;

	/* Vector of starred rows indices */
	vector<uint> stars;
};

#endif /* __SIPLEX_H__ */
