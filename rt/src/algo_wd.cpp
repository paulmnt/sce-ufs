#include <algo_wd.h>

void wd::init_wd(sng *graph)
{
	g = graph;

	for (uint i = 0; i < n; i++)
		for (uint j = 0; j < n; j++) {
			if (i == j)
				w[i][j] = 0;
			else
				w[i][j] = UINT_MAX;
		}

	uint edges_num = graph->get_num_edges();
	for (uint k = 0; k < edges_num; k++) {
		edge *e = graph->get_edge(k);
		uint i = e->src->get_id();
		uint j = e->dst->get_id();
		uint weight = e->weight;
		w[i][j] = weight;
	}

#ifdef DEBUG
	cout << "DEBUG: W0 initial Matrix..." << endl;
	for (uint i = 0; i < n; i++) {
		cout << "       ";
		for (uint j = 0; j < n; j++) {
			if (w[i][j] < UINT_MAX)
				cout << w[i][j] << " ";
			else
				cout << "-" << " ";
		}
		cout << endl;
	}
#endif

}


void wd::copy_wd()
{
	for (uint i = 0; i < n; i++)
		for (uint j = 0; j < n; j++) {
			w[i][j] = w1[i][j];
			d[i][j] = d1[i][j];
		}
}

void wd::compute_wd()
{
	for (uint k = 0; k < n; k++) {
		for (uint i = 0; i < n; i++)
			for (uint j = 0; j < n; j++)
				if (w[i][k] < UINT_MAX && w[k][j] < UINT_MAX)
					w1[i][j] = min(w[i][j], w[i][k] + w[k][j]);
				else
					w1[i][j] = w[i][j];
		copy_wd();
	}

#ifdef DEBUG
	cout << "DEBUG: W Matrix..." << endl;
	for (uint i = 0; i < n; i++) {
		cout << "       ";
		for (uint j = 0; j < n; j++) {
			if (w[i][j] < UINT_MAX)
				cout << w[i][j] << " ";
			else
				cout << "-" << " ";
		}
		cout << endl;
	}
#endif

}
