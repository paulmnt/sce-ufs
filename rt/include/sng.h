#ifndef __SNG_H__
#define __SNG_H__

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

/**
 * Synchronous Network Graph header defines all data structures used within
 * the implementation of the retiming tool
 */

class edge;

class vertex {

public:
	vertex(uint i) {
		id = i;
	}

	void set_delay(uint d)
	{
		delay = d;
	}
	uint get_delay()
	{
		return delay;
	}
	uint get_id()
	{
		return id;
	}

	void add_in_edge(edge *e)
	{
		in.push_back(e);
	}

	void add_out_edge(edge *e)
	{
		out.push_back(e);
	}

	vector<edge *> in;
	vector<edge *> out;

private:
	uint id;
	uint delay;
};


class edge {
public:
	edge(uint i, uint w, vertex *u, vertex *v) {
		id = i;
		weight = w;
		src = u;
		dst = v;
	}

	void print()
	{
		cout << "Edge " << id << ": ";
		cout << src->get_id() << "->" << dst->get_id();
		cout << "; w=" << weight << endl;
	}

	uint id;
	uint weight;
	/* Directed edge */
	vertex *src;
	vertex *dst;
};


class sng {

public:
	sng(string s, uint n)
	{
		name = s;

		vertex *v0 = new vertex(0);
		v0->set_delay(0);
		vertices.push_back(v0);

		for (uint i = 1; i < n; i ++) {
			vertex *vi = new vertex(i);
			vertices.push_back(vi);
		}
	}

	void set_vertex_delay(uint vind, uint delay)
	{
		if (vind < vertices.size())
			vertices[vind]->set_delay(delay);
		else
			cout << "ERROR: vertex index out of bound" << endl;
	}
	uint get_vertex_delay(uint vind)
	{
		if (vind < vertices.size())
			return vertices[vind]->get_delay();
		else {
			cout << "ERROR: vertex index out of bound" << endl;
			return -1;
		}
	}

	void add_edge(uint edge_id, uint c, uint u, uint v)
	{
		edge *e = new edge(edge_id, c, vertices[u], vertices[v]);
		edges.push_back(e);
		vertices[u]->add_out_edge(e);
		vertices[v]->add_in_edge(e);
		edges[edge_id]->print();
	}

	void print_vertex(uint vind)
	{
		if (vind < vertices.size()) {
			cout << "Vertex " << vertices[vind]->get_id();
			cout << ": " << "Delay is " << vertices[vind]->get_delay();
			cout << endl;

			cout << "In edges " << endl;
			for (uint i = 0; i < vertices[vind]->in.size(); i++)
				vertices[vind]->in[i]->print();
			cout << "Out edges " << endl;
			for (uint i = 0; i < vertices[vind]->out.size(); i++)
				vertices[vind]->out[i]->print();

		} else
			cout << "ERROR: vertex index out of bound" << endl;
	}

	void print_edge(uint eind)
	{
		if (eind < edges.size())
			edges[eind]->print();
		else
			cout << "ERROR: edge index out of bound" << endl;
	}

private:
	string name;
	vector<vertex *> vertices;
	vector<edge *> edges;
};


#endif /* __SNG_H__ */