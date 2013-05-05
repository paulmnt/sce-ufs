#include <sng.h>
#include <cfloat>
#include <fstream>
#include <sstream>
#include <string>

#include <p2out.h>

using namespace std;

#ifndef __SIPLEX_H__
#define __SIPLEX_H__


class tab_row {

public:
	void add_slack_var()
	{
		coeff.push_back(0);
	}

	void print();
	void print(ofstream &of, bool pivot, int pc);

	bool star;
	int label;
	vector<int> coeff;
	int ans;

	/* Only for printing it 7 */
	string ratio;
};

class simplex {

public:
	simplex(uint n, uint target_phi, p2out *p2, bool verbose)
	{
		num_vertices = n;
		phi = target_phi;
		/*
		 * Retiming vector variable labels range from 0 to
		 * num_vertices - 1 therefore slack variables first
		 * label is num_vertices.
		 */
		slack_var = num_vertices;

		print2 = p2;
		verb = verbose;
	}

	void print_tableau();
	void print_tableau(ofstream &of, int pc, int pr);

	void make_tableau(sng *g, uint **w, uint **d);
	void add_legal_constraints(sng *g);
	void add_timing_constraints(sng *g, uint **w, uint **d);
	void add_objective_func_row(sng *g);

	void func_clear_col(int pivot_column, int pivot_row, int width_matrix);
	int func_pivot_col(int first_starred_row, int width_matrix);
	int func_test_ratio(int pivot_col);
	void phase1();

	int func_pivot_col(int width_matrix);
	void phase2();

	void get_retiming_vector(int *r, uint n);

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

	p2out *print2;
	bool verb;

	int it;
};

#endif /* __SIPLEX_H__ */
