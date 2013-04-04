#include "test_cube.hpp"

int main(int argc, char *argv[]){

	sing_cube ip;


	if(argc < 2){
		cout<<"Usage: ./run <input.txt> <optional-commands>"<<'\n';
		cout<<"Optional Commands: "<<'\n';
		cout<<"-pv : to print the list of variables to file vars_list.txt"<<'\n';
		cout<<"-pc : to print the list of cubes to file cubes_list.txt"<<'\n';
		cout<<"-pm : to print the cube-variable matrix to file matrix.txt"<<'\n';
		cout<<"-ppr : to print the list of prime rectanges to file prime_rects.txt"<<'\n';
		exit(0);
	}


	ip.parse_file(argv[1], argv[2], argv[3], argv[4], argv[5]);		//parse input file
	return (0);


}
