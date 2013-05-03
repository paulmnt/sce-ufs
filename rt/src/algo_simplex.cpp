#include <algo_simplex.h>

void tab_row::print()
{
	cout << " ";
	if (star)
		cout << "*";
	else
		cout << " ";
	if (label < 10)
		cout << " ";
	cout << label << " | ";

	for (uint i = 0; i < coeff.size(); i++) {
		if (coeff[i] < 10 || coeff[i] > -10)
			cout << " ";
		if (coeff[i] >= 0)
			cout << " ";
		cout << coeff[i] << " ";
	}
	cout << "| ";
	if (ans < 10 || ans > -10)
		cout << " ";
	if (ans >= 0)
		cout << " ";
	cout << ans << endl;
}

void simplex::print_tableau()
{
	cout << "     | ";
	for (uint i = 0; i < slack_var; i++) {
		if (i < 10)
			cout << " ";
		cout << " " << i << " ";
	}
	cout << "|" << endl;

	cout << "------";
	for (uint i = 0; i < slack_var; i++)
		cout << "----";
	cout <<"------" << endl;

	for (uint i = 0; i < matrix.size() - 1; i++)
		matrix[i].print();

	cout << "------";
	for (uint i = 0; i < slack_var; i++)
		cout << "----";
	cout <<"------" << endl;

	matrix[matrix.size() - 1].print();
}

void simplex::add_legal_constraints(sng *g)
{
	/* Add constraints to make retiming vector legal
	 *
	 *                       | ...  i ...  j ... k ... |
	 *                       ---------------------------
	 *	                 .                         .
	 *	                 .                         .
	 * ri - rj <= wij ---> k | ...  1 ... -1 ... 1 ... | wij
	 *	                 .                         .
	 *	                 .                         .
	 */
	for (uint i = 0; i < g->get_num_edges(); i++) {
		edge *e = g->get_edge(i);
		vertex *u = e->src;
		vertex *v = e->dst;

		/* Add a column to the tableau */
		for (uint j = 0; j < matrix.size(); j++)
			matrix[j].add_slack_var();

		/* Prepare new row */
		tab_row row;
		row.label = slack_var;
		row.ans = e->weight;

		for (uint k = 0; k < slack_var; k++)
			if (k == u->get_id())
				row.coeff.push_back(1);
			else if (k == v->get_id())
				row.coeff.push_back(-1);
			else
				row.coeff.push_back(0);

		/* Slack variable coeff. is 1 in the initial tableau 8 */
		row.coeff.push_back(1);
		if (row.coeff[slack_var] < 0) {
			row.star = true;
			stars.push_back(matrix.size());
		} else
			row.star = false;
		slack_var++;

		/* Add row to tableau */
		matrix.push_back(row);
	}
}


void simplex::add_timing_constraints(sng *g, uint **w, uint **d)
{
	/* Add constraints to make retiming vector feasible
	 *
	 *                                 | ...  i ...  j ... k ... |
	 *                                 ---------------------------
	 *	                           .                         .
	 *	                           .                         .
	 * ri - rj <= W(vi, vj) - 1 ---> k | ...  1 ... -1 ... 1 ... | W(vi, vj) - 1
	 *	                           .                         .
	 *	                           .                         .
	 */
	for (uint i = 0; i < num_vertices; i++)
		for (uint j = 0; j < num_vertices; j++) {
			if (d[i][j] <= phi)
				continue;
			if (d[i][j] - g->get_vertex_delay(i) > phi)
				continue;
			if (d[i][j] - g->get_vertex_delay(j) > phi)
				continue;

			/* Add a column to the tableau */
			for (uint k = 0; k < matrix.size(); k++)
				matrix[k].add_slack_var();

			/* Prepare new row */
			tab_row row;
			row.label = slack_var;
			int leq = 1;
			if ((int) w[i][j] - 1 < 0)
				/* ans must be positive */
				leq = -1;
			row.ans = leq * (w[i][j] - 1);

			for (uint k = 0; k < slack_var; k++)
				if (k == i)
					row.coeff.push_back(1 * leq);
				else if (k == j)
					row.coeff.push_back(-1 * leq);
				else
					row.coeff.push_back(0);

			/*
			 * Slack variable coeff. is 1 in the initial tableau
			 * while surplus variable coeff. is -1
			 */
			row.coeff.push_back(1 * leq);
			if (row.coeff[slack_var] < 0) {
				row.star = true;
				stars.push_back(matrix.size());
			} else
				row.star = false;
			slack_var++;

			/* Add row to tableau */
			matrix.push_back(row);
		}
}

void simplex::add_objective_func_row(sng *g)
{
	/* Add the objective function row */

	/* Add a column to the tableau */
	for (uint j = 0; j < matrix.size(); j++)
		matrix[j].add_slack_var();

	/* Prepare new row */
	tab_row row;
	row.label = slack_var;
	row.ans = 0;

	for (uint k = 0; k < slack_var; k++)
		if (k < num_vertices)
			/*
			 * Notice that sign is changed twice:
			 * 1. we want to convert the minimization
			 * problem into a maximization one.
			 * 2. when making the tableau we move
			 * all coefficients of the objective function
			 * to the left hand side
			 */
			row.coeff.push_back(g->get_vertex_c(k));
		else
			row.coeff.push_back(0);

	/* Slack variable coeff. is 1 in the initial tableau */
	row.coeff.push_back(1);
	if (row.coeff[slack_var] < 0) {
		row.star = true;
		stars.push_back(matrix.size());
	} else
		row.star = false;
	slack_var++;

	/* Add row to tableau */
	matrix.push_back(row);
}

void simplex::make_tableau(sng *g, uint **w, uint **d)
{
	add_legal_constraints(g);
	add_timing_constraints(g, w, d);
	add_objective_func_row(g);
#ifdef INFO
	cout << "INFO: Printing initial tableau" << endl;
	print_tableau();
#endif
}



void simplex::func_clear_col(int pivot_col, int pivot_row, int width)
{

	int pivot = matrix[pivot_row].coeff[pivot_col];

	for (int i = 0; i < (int) matrix.size(); i++) {
		int c1, c2;

		if (i == pivot_row)
			continue;
		int coeff = matrix[i].coeff[pivot_col];
		if (!coeff)
			continue;

		for (int j = 0; j < width; j++) {
			/* Notice that the pivot is always positive! */
			c1 = pivot * matrix[i].coeff[j];
			c2 = coeff * matrix[pivot_row].coeff[j];
			matrix[i].coeff[j] = c1 - c2;
		}
		c1 = pivot * matrix[i].ans;
		c2 = coeff * matrix[pivot_row].ans;
		matrix[i].ans = c1 - c2;
	}

        matrix[pivot_row].label = pivot_col;

	if (!stars.size())
		/* Phase 2 already started */
		return;

	/* Phase 1: Recheck stars */
	stars.clear();
	for (uint i = 0; i < matrix.size(); i++)
		if (matrix[i].coeff[matrix[i].label] < 0) {
			stars.push_back(i);
			matrix[i].star = true;
		} else
			matrix[i].star = false;
}


int simplex::func_pivot_col(int first_starred_row, int width_matrix)
{
	/* Phase 1 */
        int max = -1;
        int pivot_column = -1;

	for (int i = 0; i < width_matrix; i++)
		if (matrix[first_starred_row].coeff[i] > max) {
			max = matrix[first_starred_row].coeff[i];
			pivot_column = i;
		}

	return pivot_column;
}

int simplex::func_pivot_col(int width_matrix)
{
	/* Phase 2 */
	int row = matrix.size() - 1;
	int max = -1;
        int pivot_col = -1;

	for (int j = 0; j < width_matrix; j++)
		if (matrix[row].coeff[j] < 0)
			if (abs(matrix[row].coeff[j]) > max) {
				max = abs(matrix[row].coeff[j]);
				pivot_col = j;
			}

	return pivot_col;
}

int simplex::func_test_ratio(int pivot_col)
{
	int pivot_row = -1;
	double min = DBL_MAX;

	for (int i = 0; i < (int) matrix.size() - 1; i++)
		if (matrix[i].coeff[pivot_col] > 0) {
			double tmp;
			tmp = (double) matrix[i].ans / (double) matrix[i].coeff[pivot_col];
			if (tmp > min)
				continue;
			if (tmp == min) {
				if (matrix[pivot_row].star)
					continue;
				if (!matrix[i].star)
					continue;
			}
			min = tmp;
			pivot_row = i;
		}

	return pivot_row;
}

void simplex::phase1()
{
	while (stars.size() > 0) {
		/* Pick first starred row and remove it form starred list */
		int first_starred_row = stars[0];

		int pivot_column;
		int pivot_row;
		int width_matrix = slack_var;

		pivot_column = func_pivot_col(first_starred_row, width_matrix);
#ifdef DEBUG
		cout << "DEBUG: pivot column is: " << pivot_column << endl;
#endif
		if (pivot_column < 0)
			return;

		pivot_row = func_test_ratio(pivot_column);
#ifdef DEBUG
		cout << "       pivot row is: " << pivot_row << endl;
#endif
		if (pivot_row < 0)
			return;

		func_clear_col(pivot_column, pivot_row, width_matrix);
#ifdef DEBUG
		cout << "DEBUG: Printing current tableau" << endl;
		print_tableau();
#endif
	}
}


void simplex::phase2()
{
	int pivot_column;
	int pivot_row;
	int width_matrix = slack_var;

	do {
		pivot_column = func_pivot_col(width_matrix);
#ifdef DEBUG
		cout << "DEBUG: pivot column is: " << pivot_column << endl;
#endif
		pivot_row = func_test_ratio(pivot_column);
#ifdef DEBUG
		cout << "       pivot row is: " << pivot_row << endl;
#endif
		if (pivot_row < 0)
			break;

		func_clear_col(pivot_column, pivot_row, width_matrix);
#ifdef DEBUG
		cout << "DEBUG: Printing current tableau" << endl;
		print_tableau();
#endif
	} while (pivot_column != 0);

#ifdef INFO
	cout << "INFO: Printing final tableau" << endl;
	print_tableau();
#endif

	/* Initialize result vector */
	for (uint i = 0; i < slack_var; i++)
		result.push_back(0);

	/* Notice that matrix size is always less than slack_var */
	for (uint i = 0; i < matrix.size(); i++)
		/* Given the constraints the result is proven to be integer! */
		result[matrix[i].label] = matrix[i].ans / matrix[i].coeff[matrix[i].label];

#ifdef INFO
	cout << "INFO: Printing solution of SIMPLEX..." << endl;
	for (uint i = 0; i < num_vertices; i++)
		cout << "r" << i << " = " << result[i] << endl;
	cout << "p = " << result[slack_var - 1] << endl;
#endif
}


void simplex::get_retiming_vector(int *r, uint n)
{
	for (uint i = 0; i < n; i++)
		if (i < result.size())
			r[i] = result[i];
}
