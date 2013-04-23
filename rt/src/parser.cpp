#include <parser.h>

void parser::parse_file(char* file)
{
	fstream f0;
	f0.open(file);

	string file_read = ".name";
	int read_delay_vert = 0;

	delay_vert_vec.push_back(0);

	while (file_read != ".e") {
		f0 >> file_read;
		if(file_read == ".n")
			f0 >> num_vertices;
	}
	num_vertices++;

#ifdef DEBUG
	cout << "DEBUG: " << "num_vertices: " << num_vertices<<endl;
#endif

	file_read = ".name";
	f0.close();

	f0.open(file);

	while (file_read != ".e") {
		f0>>file_read;
		if (file_read == ".d")
			for (int i = 0; i < num_vertices - 1; i++) {
				f0 >> read_delay_vert;
				delay_vert_vec.push_back(read_delay_vert);
			}
	}
	file_read = ".name";
	f0.close();

#ifdef DEBUG
	for (uint i = 0; i < delay_vert_vec.size(); i++) {
		cout << "DEBUG: " << "vertex is: " << i << " delay is: ";
		cout << delay_vert_vec[i] << endl;
	}
#endif

	f0.open(file);

	string line;

	while (file_read != ".e") {
		f0>>file_read;
		if (file_read == ".g")
			break;
	}

	int num_lines = 0;
	string vert_str;

	getline(f0, line);

#ifdef DEBUG
	cout << "DEBUG: " << "comment if present is: " << line << endl;
#endif

	while (line != ".e"){
		getline(f0, line);

		if (line == ".e")
			break;

		istringstream iss(line);
		int a, b, c;

		iss >> a;
		iss >> b;
		iss >> c;

		vector<int> edge;
		edge.push_back(a);
		edge.push_back(b);

		edges_vec.push_back(edge);
		edge_wts_vec.push_back(c);

		num_lines++;
	}

#ifdef DEBUG
	for (uint i = 0; i < edge_wts_vec.size(); i++) {
		cout << "DEBUG: first vertex: " << edges_vec[i][0];
		cout << "       second vertex: " << edges_vec[i][1];
		cout << "       edge weight: " << edge_wts_vec[i] << endl;
	}
#endif

}

int parser::get_num_vertices()
{
	return num_vertices;
}

vector<int> parser::get_delay_vert_vec()
{
	return delay_vert_vec;
}

vector<vector<int> > parser::get_edges_vec()
{
	return edges_vec;
}

vector<int> parser::get_edge_wts_vec()
{
	return edge_wts_vec;
}
