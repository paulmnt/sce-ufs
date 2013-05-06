#include <parser.h>

sng *parser::parse_file(char* file)
{

#ifdef DEBUG
	cout << "DEBUG: PARSING..." << endl;
#endif

	fstream f0;
	f0.open(file);

	if (!f0.good()) {
		cout << "ERROR: cannot read input file " << file << endl;
		return NULL;
	}

	string file_read = ".name";
	string name;
	uint num_vertices;

	while (file_read != ".d") {
		f0 >> file_read;
		if (file_read == ".name")
			f0 >> name;
		if(file_read == ".n")
			f0 >> num_vertices;
	}
	num_vertices++;

	sng *graph = new sng(name, num_vertices);

#ifdef DEBUG
	cout << "DEBUG: " << name << "has " << num_vertices << " vertices" << endl;
#endif

	uint delay;
	for (uint i = 1; i < num_vertices; i++) {
		f0 >> delay;
		graph->set_vertex_delay(i, delay);
	}

	string line;
	uint edge_id = 0;

	while (file_read != ".g")
		f0 >> file_read;

	/* Skip comment if any */
	getline(f0, line);
#ifdef DEBUG
	cout << "DEBUG: " << "comment after .g if present is: " << line << endl;
#endif


	while (line.find(".e") == string::npos) {
		getline(f0, line);

		if (line.find(".e") != string::npos)
			break;

		istringstream iss(line);
		uint a, b, c;
		iss >> a;
		iss >> b;
		iss >> c;
		graph->add_edge(edge_id, c, a, b);

		edge_id++;
	}

#ifdef DEBUG
	for (uint i = 0; i < edge_id; i++) {
		cout << "DEBUG: ";
		graph->print_edge(i);
	}
	for (uint i = 0; i < num_vertices; i++) {
		cout << "DEBUG: ";
		graph->print_vertex(i);
	}
#endif

	f0.close();
	return graph;
}
