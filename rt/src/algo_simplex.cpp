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
#ifdef INFO
	cout << "INFO: Printing current tableau..." << endl;
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
#endif
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
		if (row.ans * row.coeff[slack_var] < 0) {
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
			if (row.ans * row.coeff[slack_var] < 0) {
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
	if (row.ans * row.coeff[slack_var] < 0) {
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
	print_tableau();
}





void simplex::func_clear_col(int pivot_col, int pivot_row, int width)
{
	int flag = 0;
	int c1;

	for (int i = 0; i < (int) matrix.size(); i++) {
		if (i != pivot_row) {
			c1 = matrix[i].coeff[pivot_col];

			if ((abs(c1) % matrix[pivot_row].coeff[pivot_col] != 0 ) and (matrix[pivot_row].coeff[pivot_col] % abs(c1) != 0))
				flag = 5;
			else if (matrix[i].coeff[pivot_col] < 0) {
				flag = 1;
				if (abs(c1) > matrix[pivot_row].coeff[pivot_col])
					flag = 4;
			}
			else if (matrix[i].coeff[pivot_col] > (matrix[pivot_row].coeff[pivot_col]))
				flag = 3;
			else if (matrix[i].coeff[pivot_col] == 0)
				flag = 2;

			for (int j = 0; j < width; j++) {
				if (flag == 0)
					matrix[i].coeff[j] = ((matrix[pivot_row].coeff[pivot_col]) / (c1)) * matrix[i].coeff[j] - matrix[pivot_row].coeff[j];
				if (flag == 1)
					matrix[i].coeff[j] = ((matrix[pivot_row].coeff[pivot_col]) / (c1)) * matrix[i].coeff[j] * (-1) + matrix[pivot_row].coeff[j];
				if (flag == 3)
					matrix[i].coeff[j] = matrix[i].coeff[j] - (c1 / (matrix[pivot_row].coeff[pivot_col])) * matrix[pivot_row].coeff[j];
				if (flag == 4)
					matrix[i].coeff[j] = matrix[i].coeff[j] + (c1 / (matrix[pivot_row].coeff[pivot_col])) * matrix[pivot_row].coeff[j] * (-1);
				if (flag == 5)
					matrix[i].coeff[j] = (matrix[i].coeff[j] * matrix[pivot_row].coeff[pivot_col]) - (matrix[pivot_row].coeff[j] * c1);
                        }
                }
                flag = 0;
        }

        matrix[pivot_row].label = pivot_col;

	for (uint i = 0; i < matrix.size(); i++)
		if (matrix[i].ans * matrix[i].coeff[matrix[i].label] < 0)
			matrix[i].star = true;
		else {
			if (matrix[i].star)
				for (uint k = 0; k < stars.size(); k++)
					if (stars[k] == i)
						stars.erase(stars.begin() + k);
			matrix[i].star = false;
		}
}


int simplex::func_pivot_col(int first_starred_row, int width_matrix)
{

        int max = -1;
        int pivot_column = 0;

        for (int i = 0; i < width_matrix; i++){
		if (matrix[first_starred_row].coeff[i] > max){
			max = matrix[first_starred_row].coeff[i];
			pivot_column = i;
		}
	}
	return pivot_column;
}


int simplex::func_test_ratio(int pivot_col, int width)
{
	int pivot_row;
	vector<double> test_ratios;
	vector<int> rows_test_ratios;
	for (int i = 0; i < (int) matrix.size() - 1; i++)
		if (matrix[i].coeff[pivot_col] > 0) {
			test_ratios.push_back((double)matrix[i].ans/(double)matrix[i].coeff[pivot_col]);
			rows_test_ratios.push_back(i);
		}

	double min = DBL_MAX;

	for (uint i = 0; i < test_ratios.size(); i++) {
		if (test_ratios[i] < min) {
			min = test_ratios[i];
			pivot_row = rows_test_ratios[i];
		}
	}

	for (uint i = 0; i < rows_test_ratios.size(); i++)
		if (test_ratios[i] == min)
			if (matrix[rows_test_ratios[i]].star) {
				pivot_row = rows_test_ratios[i];
				break;
			}

	return pivot_row;
}

void simplex::phase1()
{
	while (stars.size() > 0) {
		/* Pick first starred row and remove it form starred list */
		uint first_starred_row = stars[0];

		int pivot_column;
		int pivot_row;
		int width_matrix = slack_var;

		pivot_column = func_pivot_col(first_starred_row, width_matrix);
#ifdef INFO
		cout << "pivot column is: " << pivot_column << endl;
#endif
		pivot_row = func_test_ratio(pivot_column, width_matrix);
#ifdef INFO
		cout << "pivot row is: " << pivot_row << endl;
#endif
		func_clear_col(pivot_column, pivot_row, width_matrix);

		print_tableau();
	}
}
