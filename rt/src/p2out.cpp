#include <p2out.h>

void p2out::it0(uint area)
{
	print_item(p2_013, "#0. Initial area");
	p2_013 << area << endl << endl;
}


void p2out::it1(int *r, uint n)
{
	print_item(p2_013, "#1. Optimal retiming vector");
	p2_013  << r[0] << " ";
	for (uint i = 1; i < n; i++) {
		if (!(i % 10))
			p2_013 << endl;
		if (i == n - 1)
			/* Don't want a space after last element */
			break;
		p2_013  << r[i] << " ";
	}
	p2_013 << r[n - 1] << endl << endl;
}

void p2out::it3(uint area)
{
	print_item(p2_013, "#3. Final area");
	p2_013 << area << endl << endl;

}

struct p2_tuple {
	uint v;
	uint w;
};

bool p2_cmp_tuple(p2_tuple i, p2_tuple j)
{
	return (i.v < j.v);
}

void p2out::it2(sng *g)
{
	p2_2 << ".name " << g->get_name() << endl;
	p2_2 << ".n " << g->get_num_vertices() << endl;
	p2_2 << ".d";
	for (uint i = 1; i < g->get_num_vertices(); i++)
		p2_2 << " " << g->get_vertex_delay(i);
	p2_2 << endl;
	p2_2 << ".g" << endl;
	for (uint i = 0; i < g->get_num_vertices(); i++) {
		vertex *v = g->get_vertex(i);
		vector<p2_tuple> tmp;
		for (uint j = 0; j < v->out.size(); j++) {
			p2_tuple t;
			t.v = v->out[j]->dst->get_id();
			t.w = v->out[j]->weight;
			tmp.push_back(t);
		}
		sort(tmp.begin(), tmp.end(), p2_cmp_tuple);
		for (uint j = 0; j < tmp.size(); j++)
			p2_2 << i << " " << tmp[j].v << " " << tmp[j].w << endl;
	}
	p2_2 << ".e" << endl;

}


void p2out::it4(sng *g)
{
	uint n = g->get_num_vertices();
	print_item(p2_4, "#4. C vector");
	if (g->get_vertex_c(0) >= 0)
		p2_4 << " ";
	if (g->get_vertex_c(0) < 10 || g->get_vertex_c(0) > -10)
		p2_4 << " ";
	p2_4  << g->get_vertex_c(0) << " ";
	for (uint i = 1; i < n; i++) {
		if (!(i % 10))
			p2_4 << endl;
		if (i == n - 1)
			/* Don't want a space after last element */
			break;
		if (g->get_vertex_c(i) >= 0)
			p2_4 << " ";
		if (g->get_vertex_c(i) < 10 || g->get_vertex_c(i) > -10)
			p2_4 << " ";
		p2_4  << g->get_vertex_c(i) << " ";
	}
	if (g->get_vertex_c(n - 1) >= 0)
		p2_4 << " ";
	if (g->get_vertex_c(n - 1) < 10 || g->get_vertex_c(n - 1) > -10)
		p2_4 << " ";
	p2_4 << g->get_vertex_c(n - 1) << endl << endl;

}

bool p2_cmp_triple(p2_triple i, p2_triple j)
{
	if (i.i != j.i)
		return (i.i < j.i);
	if (i.j != j.j)
		return (i.j < j.j);
	return (i.ans <= j.ans);
}

void p2out::it5()
{
	print_item(p2_5, "#5. All constraints");

	sort(constraints.begin(), constraints.end(), p2_cmp_triple);
	for (uint i = 0; i < constraints.size(); i++) {
		if (constraints[i].ic < 0)
			p2_5 << "-v";
		else
			p2_5 << " v";
		p2_5 << constraints[i].i << " ";
		if (constraints[i].jc < 0)
			p2_5 << "- v";
		else
			p2_5 << "+ v";
		p2_5 << constraints[i].j << " ";
		if (constraints[i].leq)
			p2_5 << "<= ";
		else
			p2_5 << ">= ";
		p2_5 << constraints[i].ans << endl;
	}
}


// void p2out::it6(uint **w, uint **d, uint n, uint it)
// {
// 	/* Only in Verbose mode */
// 	if (!verb)
// 		return;


// 	p2_6 << "#6. W" << it << " and D" << it << " Matrices" << endl;
// 	p2_6 << "-------";
// 	for (uint i = 0; i < n; i++)
// 		p2_6 << "-----";
// 	p2_6 << "      ";
// 	p2_6 << "-------";
// 	for (uint i = 0; i < n; i++)
// 		p2_6 << "-----";
// 	p2_6 << endl;

// 	p2_6 << "     ";
// 	for (uint i = 0; i < n - 1; i++)
// 		if (i < 10)
// 			p2_6 << "  v" << i << " ";
// 		else
// 			p2_6 << " v" << i << " ";
// 	if (n - 1 < 10)
// 		p2_6 << "  v" << n - 1;
// 	else
// 		p2_6 << " v" << n - 1;

// 	p2_6 << "              ";
// 	for (uint i = 0; i < n - 1; i++)
// 		if (i < 10)
// 			p2_6 << "  v" << i << " ";
// 		else
// 			p2_6 << " v" << i << " ";
// 	if (n - 1 < 10)
// 		p2_6 << "  v" << n - 1;
// 	else
// 		p2_6 << " v" << n - 1;
// 	p2_6 << endl;

// 	p2_6 << "-------";
// 	for (uint i = 0; i < n; i++)
// 		p2_6 << "-----";
// 	p2_6 << "      ";
// 	p2_6 << "-------";
// 	for (uint i = 0; i < n; i++)
// 		p2_6 << "-----";
// 	p2_6 << endl;

// 	for (uint i = 0; i < n; i++) {
// 		if (i < 10)
// 			p2_6 << "   v" << i << " ";
// 		else
// 			p2_6 << "  v" << i << " ";
// 		for (uint j = 0; j < n; j++) {
// 			if (w[i][j] < UINT_MAX)
// 				p2_6 << "  " << w[i][j] << "  ";
// 			else
// 				p2_6 << "  -  ";
// 		}
// 		p2_6 << "       ";
// 		if (i < 10)
// 			p2_6 << "   v" << i << " ";
// 		else
// 			p2_6 << "  v" << i << " ";
// 		for (uint j = 0; j < n; j++)
// 			if (d[i][j] < 0 || d[i][j] > 9)
// 				p2_6 << " " << d[i][j] << "  ";
// 			else
// 				p2_6 << "  " << d[i][j] << "  ";
// 		p2_6 << endl;
// 	}
// 	p2_6 << "-------";
// 	for (uint i = 0; i < n; i++)
// 		p2_6 << "-----";
// 	p2_6 << "      ";
// 	p2_6 << "-------";
// 	for (uint i = 0; i < n; i++)
// 		p2_6 << "-----";
// 	p2_6 << endl;


// 	p2_6 << endl;

// }

// void p2out::it7(vector<uint> &r, uint n)
// {
// 	print_item(p2_457, "#7. Sorted and unique elements of Matrix D");
// 	if (r[0] < 10)
// 		p2_457 << " ";
// 	p2_457  << r[0] << " ";
// 	for (uint i = 1; i < n; i++) {
// 		if (!(i % 10))
// 			p2_457 << endl;
// 		if (i == n - 1)
// 			/* Don't want a space after last element */
// 			break;
// 		if (r[i] < 10)
// 			p2_457 << " ";
// 		p2_457  << r[i] << " ";
// 	}
// 	p2_457 << r[n - 1] << endl << endl;
// }


// void p2out::it8a(sng *g, uint it, uint phi)
// {
// 	/* Only in Verbose mode */
// 	if (!verb)
// 		return;

// 	stringstream ss;
// 	ss << "#8a. FEAS combinational component graph" << endl;
// 	ss << "     Target cycle: " << phi << "; Iteration: " << it;
// 	print_item(p2_8, ss.str());

// 	p2_8 << ".name " << g->get_name() << endl;
// 	p2_8 << ".n " << g->get_num_vertices() << endl;
// 	p2_8 << ".d";
// 	for (uint i = 1; i < g->get_num_vertices(); i++)
// 		p2_8 << " " << g->get_vertex_delay(i);
// 	p2_8 << endl;
// 	p2_8 << ".g" << endl;
// 	for (uint i = 0; i < g->get_num_vertices(); i++) {
// 		vertex *v = g->get_vertex(i);
// 		vector<p2_tuple> tmp;
// 		for (uint j = 0; j < v->out.size(); j++) {
// 			p2_tuple t;
// 			t.v = v->out[j]->dst->get_id();
// 			t.w = v->out[j]->weight;
// 			if (t.w)
// 				continue;
// 			tmp.push_back(t);
// 		}
// 		sort(tmp.begin(), tmp.end(), p2_cmp_tuple);
// 		for (uint j = 0; j < tmp.size(); j++)
// 			p2_8 << i << " " << tmp[j].v << " " << tmp[j].w << endl;
// 	}
// 	p2_8 << ".e" << endl << endl << endl;

// }

// void p2out::it8b(sng *g, uint it, uint phi)
// {
// 	/* Only in Verbose mode */
// 	if (!verb)
// 		return;

// 	stringstream ss;
// 	ss << "#8b. FEAS vertices data-ready time" << endl;
// 	ss << "     Target cycle: " << phi << "; Iteration: " << it;
// 	print_item(p2_8, ss.str());

// 	if (g->get_vertex_delta(0) < 10)
// 		p2_8 << " ";
// 	p2_8  << g->get_vertex_delta(0) << " ";
// 	for (uint i = 1; i < g->get_num_vertices(); i++) {
// 		if (!(i % 10))
// 			p2_8 << endl;
// 		if (i == g->get_num_vertices() - 1)
// 			/* Don't want a space after last element */
// 			break;
// 		if (g->get_vertex_delta(i) < 10)
// 			p2_8 << " ";
// 		p2_8 << g->get_vertex_delta(i) << " ";
// 	}
// 	if (g->get_vertex_delta(g->get_num_vertices() - 1) < 10)
// 		p2_8 << " ";
// 	p2_8 << g->get_vertex_delta(g->get_num_vertices() - 1) << endl << endl;

// 	p2_8 << endl;

// }


// void p2out::it8c(sng *g, uint it, uint phi)
// {
// 	/* Only in Verbose mode */
// 	if (!verb)
// 		return;

// 	stringstream ss;
// 	ss << "#8c. FEAS late vertices" << endl;
// 	ss << "     Target cycle: " << phi << "; Iteration: " << it;
// 	print_item(p2_8, ss.str());

// 	uint count = 0;

// 	for (uint i = 0; i < g->get_num_vertices(); i++) {
// 		if (!(count % 10) && count)
// 			p2_8 << endl;
// 		if (g->get_vertex_delta(i) > phi) {
// 			if (i < 10)
// 				p2_8 << " ";
// 			p2_8 << i << " ";
// 			count++;
// 		}
// 	}
// 	p2_8 << endl << endl << endl;


// }
