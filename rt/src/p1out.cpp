#include <p1out.h>

void p1out::it0(uint area)
{
	print_item(p1_013, "#0. Initial area");
	p1_013 << area << endl << endl;
}


void p1out::it1(int *r, uint n)
{
	print_item(p1_013, "#1. Optimal retiming vector");
	p1_013  << r[0] << " ";
	for (uint i = 1; i < n; i++) {
		if (!(i % 10))
			p1_013 << endl;
		if (i == n - 1)
			/* Don't want a space after last element */
			break;
		p1_013  << r[i] << " ";
	}
	p1_013 << r[n - 1] << endl << endl;
}

void p1out::it3(uint phi)
{
	print_item(p1_013, "#3. Optimal clock cycle");
	p1_013 << phi << endl << endl;

}


struct tuple {
	uint v;
	uint w;
};

bool cmp_tuple(tuple i, tuple j)
{
	return (i.v < j.v);
}

void p1out::it2(sng *g)
{
	p1_2 << ".name " << g->get_name() << endl;
	p1_2 << ".n " << g->get_num_vertices() << endl;
	p1_2 << ".d";
	for (uint i = 1; i < g->get_num_vertices(); i++)
		p1_2 << " " << g->get_vertex_delay(i);
	p1_2 << endl;
	p1_2 << ".g" << endl;
	for (uint i = 0; i < g->get_num_vertices(); i++) {
		vertex *v = g->get_vertex(i);
		vector<tuple> tmp;
		for (uint j = 0; j < v->out.size(); j++) {
			tuple t;
			t.v = v->out[j]->dst->get_id();
			t.w = v->out[j]->weight;
			tmp.push_back(t);
		}
		sort(tmp.begin(), tmp.end(), cmp_tuple);
		for (uint j = 0; j < tmp.size(); j++)
			p1_2 << i << " " << tmp[j].v << " " << tmp[j].w << endl;
	}
	p1_2 << ".e" << endl;

}


void p1out::it4(uint **w, uint **d, uint n)
{
	p1_457 << "#4. W and D Matrices" << endl;
	p1_457 << "-------";
	for (uint i = 0; i < n; i++)
		p1_457 << "-----";
	p1_457 << "      ";
	p1_457 << "-------";
	for (uint i = 0; i < n; i++)
		p1_457 << "-----";
	p1_457 << endl;

	p1_457 << "     ";
	for (uint i = 0; i < n - 1; i++)
		if (i < 10)
			p1_457 << "  v" << i << " ";
		else
			p1_457 << " v" << i << " ";
	if (n - 1 < 10)
		p1_457 << "  v" << n - 1;
	else
		p1_457 << " v" << n - 1;

	p1_457 << "              ";
	for (uint i = 0; i < n - 1; i++)
		if (i < 10)
			p1_457 << "  v" << i << " ";
		else
			p1_457 << " v" << i << " ";
	if (n - 1 < 10)
		p1_457 << "  v" << n - 1;
	else
		p1_457 << " v" << n - 1;
	p1_457 << endl;

	p1_457 << "-------";
	for (uint i = 0; i < n; i++)
		p1_457 << "-----";
	p1_457 << "      ";
	p1_457 << "-------";
	for (uint i = 0; i < n; i++)
		p1_457 << "-----";
	p1_457 << endl;

	for (uint i = 0; i < n; i++) {
		if (i < 10)
			p1_457 << "   v" << i << " ";
		else
			p1_457 << "  v" << i << " ";
		for (uint j = 0; j < n; j++) {
			if (w[i][j] < UINT_MAX)
				p1_457 << "  " << w[i][j] << "  ";
			else
				p1_457 << "  -  ";
		}
		p1_457 << "       ";
		if (i < 10)
			p1_457 << "   v" << i << " ";
		else
			p1_457 << "  v" << i << " ";
		for (uint j = 0; j < n; j++)
			if (d[i][j] < 0 || d[i][j] > 9)
				p1_457 << " " << d[i][j] << "  ";
			else
				p1_457 << "  " << d[i][j] << "  ";
		p1_457 << endl;
	}
	p1_457 << "-------";
	for (uint i = 0; i < n; i++)
		p1_457 << "-----";
	p1_457 << "      ";
	p1_457 << "-------";
	for (uint i = 0; i < n; i++)
		p1_457 << "-----";
	p1_457 << endl;
	p1_457 << endl;

}

void p1out::it5(uint phi)
{
	print_item(p1_457, "#5. Initial clock cycle");
	p1_457 << phi << endl << endl;
}


void p1out::it6(uint **w, uint **d, uint n, uint it)
{
	/* Only in Verbose mode */
	if (!verb)
		return;


	p1_6 << "#6. W" << it << " and D" << it << " Matrices" << endl;
	p1_6 << "-------";
	for (uint i = 0; i < n; i++)
		p1_6 << "-----";
	p1_6 << "      ";
	p1_6 << "-------";
	for (uint i = 0; i < n; i++)
		p1_6 << "-----";
	p1_6 << endl;

	p1_6 << "     ";
	for (uint i = 0; i < n - 1; i++)
		if (i < 10)
			p1_6 << "  v" << i << " ";
		else
			p1_6 << " v" << i << " ";
	if (n - 1 < 10)
		p1_6 << "  v" << n - 1;
	else
		p1_6 << " v" << n - 1;

	p1_6 << "              ";
	for (uint i = 0; i < n - 1; i++)
		if (i < 10)
			p1_6 << "  v" << i << " ";
		else
			p1_6 << " v" << i << " ";
	if (n - 1 < 10)
		p1_6 << "  v" << n - 1;
	else
		p1_6 << " v" << n - 1;
	p1_6 << endl;

	p1_6 << "-------";
	for (uint i = 0; i < n; i++)
		p1_6 << "-----";
	p1_6 << "      ";
	p1_6 << "-------";
	for (uint i = 0; i < n; i++)
		p1_6 << "-----";
	p1_6 << endl;

	for (uint i = 0; i < n; i++) {
		if (i < 10)
			p1_6 << "   v" << i << " ";
		else
			p1_6 << "  v" << i << " ";
		for (uint j = 0; j < n; j++) {
			if (w[i][j] < UINT_MAX)
				p1_6 << "  " << w[i][j] << "  ";
			else
				p1_6 << "  -  ";
		}
		p1_6 << "       ";
		if (i < 10)
			p1_6 << "   v" << i << " ";
		else
			p1_6 << "  v" << i << " ";
		for (uint j = 0; j < n; j++)
			if (d[i][j] < 0 || d[i][j] > 9)
				p1_6 << " " << d[i][j] << "  ";
			else
				p1_6 << "  " << d[i][j] << "  ";
		p1_6 << endl;
	}
	p1_6 << "-------";
	for (uint i = 0; i < n; i++)
		p1_6 << "-----";
	p1_6 << "      ";
	p1_6 << "-------";
	for (uint i = 0; i < n; i++)
		p1_6 << "-----";
	p1_6 << endl;


	p1_6 << endl;

}

void p1out::it7(vector<uint> &r, uint n)
{
	print_item(p1_457, "#7. Sorted and unique elements of Matrix D");
	if (r[0] < 10)
		p1_457 << " ";
	p1_457  << r[0] << " ";
	for (uint i = 1; i < n; i++) {
		if (!(i % 10))
			p1_457 << endl;
		if (i == n - 1)
			/* Don't want a space after last element */
			break;
		if (r[i] < 10)
			p1_457 << " ";
		p1_457  << r[i] << " ";
	}
	p1_457 << r[n - 1] << endl << endl;
}


void p1out::it8a(sng *g, uint it, uint phi)
{
	/* Only in Verbose mode */
	if (!verb)
		return;

	stringstream ss;
	ss << "#8a. FEAS combinational component graph" << endl;
	ss << "     Target cycle: " << phi << "; Iteration: " << it;
	print_item(p1_8, ss.str());

	p1_8 << ".name " << g->get_name() << endl;
	p1_8 << ".n " << g->get_num_vertices() << endl;
	p1_8 << ".d";
	for (uint i = 1; i < g->get_num_vertices(); i++)
		p1_8 << " " << g->get_vertex_delay(i);
	p1_8 << endl;
	p1_8 << ".g" << endl;
	for (uint i = 0; i < g->get_num_vertices(); i++) {
		vertex *v = g->get_vertex(i);
		vector<tuple> tmp;
		for (uint j = 0; j < v->out.size(); j++) {
			tuple t;
			t.v = v->out[j]->dst->get_id();
			t.w = v->out[j]->weight;
			if (t.w)
				continue;
			tmp.push_back(t);
		}
		sort(tmp.begin(), tmp.end(), cmp_tuple);
		for (uint j = 0; j < tmp.size(); j++)
			p1_8 << i << " " << tmp[j].v << " " << tmp[j].w << endl;
	}
	p1_8 << ".e" << endl << endl << endl;

}
