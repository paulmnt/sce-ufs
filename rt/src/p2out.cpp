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
	sort(constraints.begin(), constraints.end(), p2_cmp_triple);
	for (uint i = 0; i < constraints.size(); i++) {
		if (constraints[i].ic < 0)
			p2_5 << "-v";
		else
			p2_5 << "v";
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

void p2out::it6()
{
	/* Constraints sorted already while printing item 5 */
	for (uint i = 0; i < constraints.size(); i++) {
		if (!constraints[i].opt)
			continue;
		if (constraints[i].ic < 0)
			p2_6 << "-v";
		else
			p2_6 << "v";
		p2_6 << constraints[i].i << " ";
		if (constraints[i].jc < 0)
			p2_6 << "- v";
		else
			p2_6 << "+ v";
		p2_6 << constraints[i].j << " ";
		if (constraints[i].leq)
			p2_6 << "<= ";
		else
			p2_6 << ">= ";
		p2_6 << constraints[i].ans << endl;
	}
}

void p2out::it7a()
{
	print_item(p2_7, "#7a. Initial tableau (sorted by vi, vj, ans)");
}
void p2out::it7b(int it)
{
 	stringstream ss;
	ss << "#7bcd. Iteration # " << it;;
	print_item(p2_7, ss.str());
}

void p2out::it7b()
{
 	stringstream ss;
	ss << "#7bcd. Final tableau ";;
	print_item(p2_7, ss.str());
}
