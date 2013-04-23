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
	vertex(int i) {
		id = i;
	}

	int id;
	int delay;
	vector<edge *> in;
	vector<edge *> out;
};


class edge {
public:
	edge(int i, uint w, vertex *u, vertex *v) {
		id = i;
		weight = w;
		src = u;
		dst = v;
	}

	int id;
	uint weight;
	/* Directed edge */
	vertex *src;
	vertex *dst;
};


class sng {

public:
	sng(string s, int n) {
		name = s;
		num_vertices = n + 1;

		vertex v0(0);
		v0.delay = 0;
		vertices.push_back(v0);

		for (int i = 1; i < num_vertices; i ++) {
			vertex vi(i);
			vertices.push_back(vi);
		}
	}

	string name;
	int num_vertices;		// total number of vertices, including v_0
	vector<vertex> vertices;
	vector<edge> edges;
};


#endif /* __SNG_H__ */
