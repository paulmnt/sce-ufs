#include <algo_wd.h>

void wd::init_wd(sng *graph)
{
	g = graph;

	for (uint i = 0; i < n; i++)
		for (uint j = 0; j < n; j++) {
			d[i][j] = 0;
			if (i == j)
				w[i][j] = 0;
			else
				w[i][j] = UINT_MAX;
		}

	uint edges_num = graph->get_num_edges();
	for (uint k = 0; k < edges_num; k++) {
		edge *e = graph->get_edge(k);
		vertex *v = e->src;
		uint i = e->src->get_id();
		uint j = e->dst->get_id();
		uint weight = e->weight;
		w[i][j] = weight;
		d[i][j] = v->get_delay();
	}

#ifdef DEBUG
	cout << "DEBUG: W0 initial Matrix..." << endl;
	for (uint i = 0; i < n; i++) {
		cout << "       ";
		for (uint j = 0; j < n; j++) {
			if (w[i][j] < UINT_MAX)
				cout << " " << w[i][j] << " ";
			else
				cout << " - ";
		}
		cout << endl;
	}
	cout << "DEBUG: D0 initial Matrix..." << endl;
	for (uint i = 0; i < n; i++) {
		cout << "       ";
		for (uint j = 0; j < n; j++)
			if (d[i][j] < 0 || d[i][j] > 9)
				cout << d[i][j] << " ";
			else
				cout << " " << d[i][j] << " ";
		cout << endl;
	}
#endif

}


uint wd::compute_wd()
{
	cout << "INFO: STEP 1: Computing WD matrices..." << endl;

	uint phi = 0;

	for (uint k = 0; k < n; k++) {
		for (uint i = 0; i < n; i++)
			for (uint j = 0; j < n; j++) {
				if (w[i][k] < UINT_MAX && w[k][j] < UINT_MAX)
					if (w[i][j] > w[i][k] + w[k][j]) {
						w[i][j] = w[i][k] + w[k][j];
						d[i][j] = d[i][k] + d[k][j];
					}
				if (k == n - 1) {
					/* Add destination vertex delay */
					d[i][j] += g->get_vertex_delay(j);
					/* Populate sorted_d vector */
					sorted_d.push_back(d[i][j]);
					/* Update current cycle */
					if (w[i][j] == 0)
						if (phi < d[i][j])
							phi = d[i][j];
				}
			}
	}

	cout << "      W Matrix..." << endl;
	for (uint i = 0; i < n; i++) {
		cout << "      ";
		for (uint j = 0; j < n; j++) {
			if (w[i][j] < UINT_MAX)
				cout << " " << w[i][j] << " ";
			else
				cout << " - ";
		}
		cout << endl;
	}
	cout << "      D Matrix..." << endl;
	for (uint i = 0; i < n; i++) {
		cout << "      ";
		for (uint j = 0; j < n; j++)
			if (d[i][j] < 0 || d[i][j] > 9)
				cout << d[i][j] << " ";
			else
				cout << " " << d[i][j] << " ";
		cout << endl;
	}

	cout << "      Initial clock cycle is " << phi << endl;
	return phi;
}


void wd::sort_d()
{
	cout << "INFO: STEP 2: Sorting D elements..." << endl;

	/* Sort d vector and remove duplicates */
	sort(sorted_d.begin(), sorted_d.end());
	vector<uint>::iterator it;
	it = unique(sorted_d.begin(), sorted_d.end());
	sorted_d.resize(distance(sorted_d.begin(), it));


	cout << "      Sorted and Unique D elements for binary search" << endl;
	cout << "      ";
	for (uint i = 0; i < sorted_d.size(); i++)
		cout << sorted_d[i] << " ";
	cout << endl;
}
