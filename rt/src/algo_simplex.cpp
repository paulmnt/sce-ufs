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
	for (uint i = 0; i < matrix.size(); i++)
		matrix[i].print();
#endif
}

void simplex::make_tableau(sng *g, uint **w, uint **d)
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
		row.star = false;
		slack_var++;

		/* Add row to tableau */
		matrix.push_back(row);
	}
	print_tableau();
}
