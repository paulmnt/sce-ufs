#include "test_cube.hpp"

void sing_cube::parse_file(char* file, const char* pcub, const char* pvar, const char* pmat, const char* pprime){

	fstream f0;
	
	int count_fns = 0;

	char rem_dot;
	string temp;
	string file_read = "0";

	string spcub;
	spcub = pcub?pcub:"";
	string spvar;
	spvar = pvar?pvar:"";
	string spmat;
	spmat = pmat?pmat:"";
	string spprime;
	spprime = pprime?pprime:"";

	string cub = "-pc";				//Trying to match the commands listed in the README file
	string var = "-pv";
	string mat = "-pm";
	string prime = "-ppr";


	int pc = 0;
	int pv = 0;
	int pm = 0;
	int pp = 0;
	
	if((spcub == cub) or (spvar == cub) or (spmat == cub) or (spprime == cub))		//match commands
		pc = 1;
	if((var == spcub) or (var == spvar) or (var == spmat) or (spprime == var))
		pv = 1;
	if((mat == spcub) or (mat == spvar) or (mat == spmat) or (spprime == mat))
		pm = 1;
	if((prime == spcub) or (prime == spvar) or (prime == spmat) or (spprime == prime))
		pp = 1;



	f0.open(file);					//open the input file

	f0>>rem_dot;
	f0>>num_fns;
	f0>>rem_dot;
	f0>>num_vars;

	cube_ord.push_back("NULL");
	cube_id.push_back(0);

	while (file_read != ".e"){				//read file
	
		f0>>file_read;
		if(file_read == "="){
			count_fns++;
			f0>>file_read;
			cube_ord.push_back(file_read);
			cube_id.push_back(count_fns);
			f0>>file_read;
			while(file_read == "+"){
				f0>>file_read;
				cube_ord.push_back(file_read);		//read cubes and put them in order
				cube_id.push_back(count_fns);		//read cubes and IDs
				f0>>file_read;
			}	
			

		}

	}

	int var_strt = 96;
	var_ord.push_back('A');
	for(int i = 1; i <= num_vars; i++){
		var_ord.push_back((char)(var_strt+i));			//read variables
	}


	ofstream of0;

	if(pc == 1){

	of0.open("cubes_list.txt");					//output list of cubes to file
	of0<<"row#"<<'\t'<<"ID"<<'\t'<<"product"<<'\n';
	for(int i = 1; i < cube_ord.size(); i++){
		of0<<i<<'\t'<<cube_id[i]<<'\t'<<cube_ord[i]<<'\n';
		
	}
	of0<<'\n';							
	of0<<"Total number of Cubes: "<<cube_ord.size()-1<<'\n';
	of0.close();

	}

	if(pv == 1){

	of0.open("vars_list.txt");					//output list of variables to file
	of0<<"variable"<<'\t'<<"column#"<<'\n';
	
	for(int i = 1; i < var_ord.size(); i++){
		of0<<var_ord[i]<<'\t'<<'\t'<<i<<'\n';
	}
	of0<<'\n';
	of0<<"Total number of variables: "<<var_ord.size()-1<<'\n';
	of0.close();

	}
	


	if(pm == 1){
	of0.open("matrix.txt");					//output cube-variable matrix to file
	of0<<'\t'<<'\t'<<"var"<<'\t';
	for(int i = 1; i < var_ord.size(); i++){
		of0<<var_ord[i]<<'\t';
	}
	of0<<'\n';
	of0<<"Cube"<<'\t'<<"ID"<<'\t'<<"RC"<<'\t';
	for(int i = 1; i < var_ord.size(); i++){
		of0<<i<<'\t';
	}
	of0<<'\n';
	}
	
	for (int i = 1; i < cube_ord.size(); i++){				//find points (R,C) in the matrix where the value is 1
		if(pm == 1){							// save those points in vector pts_vec
			of0<<cube_ord[i]<<'\t'<<cube_id[i]<<'\t'<<i<<'\t';
		}
		for (int j = 1; j < var_ord.size(); j++){
			string string_inter;
			string s;
			stringstream ss;
			ss << var_ord[j];
			ss >> s;
			string cube_str = cube_ord[i];
			sort(cube_str.begin(), cube_str.end());
			//cout<<"string s is: "<<s<<" and cube after sort is: "<<cube_str<<'\n';
			set_intersection(cube_str.begin(), cube_str.end(), s.begin(), s.end(), back_inserter(string_inter));
			//cout<<"string inter is: "<<string_inter<<'\n';
			if(string_inter == s){
				if(pm == 1){
					of0<<"1"<<'\t';
				}
				points pts_temp;
				pts_temp.r = i;
				pts_temp.c = j;
				pts_vec.push_back(pts_temp);
			}
			else
				if(pm == 1)
					of0<<"0"<<'\t';

		}
		if(pm == 1){
			of0<<'\n';
		}
	}
	if(pm == 1){
		of0.close();
	}

	
	print_rectangles(pp);						//compute and print prime rectangles
	

}


void sing_cube::print_rectangles(int pp){



	for(int i = 1; i < cube_ord.size(); i++){
		col_set cset;
		cset.row = i;
		for(int j = 0; j < pts_vec.size(); j++){		//For each row generate a set of columns: step 1 of algorithm 1
			if (pts_vec[j].r == i){
				cset.set_cols.push_back(pts_vec[j].c);
			}
		}
		sort(cset.set_cols.begin(), cset.set_cols.end());
		vec_col_set.push_back(cset);
	}	

	/*for(int i = 0; i < vec_col_set.size(); i++){			//For debugging
		cout<<"row is: "<<vec_col_set[i].row<<" column set is: "<<"(";
		for(int j = 0; j < vec_col_set[i].set_cols.size(); j++){
			cout<<vec_col_set[i].set_cols[j];
			if (j < vec_col_set[i].set_cols.size()-1){
				cout<<",";
			}
		}
		cout<<")"<<'\n';
	}*/

	vector< vector<int> > vec_vec_inter;		//store intersected columns of prime rectangles
	vector< vector<int> > vec_vec_rows;		// store rows of the prime rectangles
	typedef map<vector<int>, int> mymaptype;
        map<vector<int>, int> mymap;
        map<vector<int>, int> mymap2;
	pair<mymaptype::iterator, bool> result;

	int flag_vec_present;
	int same_inter_cols = 0;
	int flag_test = 0;
	int set_found_flag = 0;
	int key_count = 1;

	for (int i = 0; i < vec_col_set.size(); i++){

                for(int j = 0; j < vec_col_set.size(); j++){				//step 2 of algorithm 1: find intersections of set of columns
			if(vec_col_set[j].row > vec_col_set[i].row){
			vector<int> intersect;
                        vector<int> vec_rows;
                        vector<int> vec_subset;
                        vector<int> vec_save_m;
                        vector<int> vec_big_subset;

                        set_intersection(vec_col_set[i].set_cols.begin(), vec_col_set[i].set_cols.end(),vec_col_set[j].set_cols.begin(), vec_col_set[j].set_cols.end(), back_inserter(intersect));
                                if(intersect.size() != 0){
					vec_rows.push_back(vec_col_set[i].row);			
                                        vec_rows.push_back(vec_col_set[j].row);
                                        vec_vec_rows.push_back(vec_rows);		//push set of rows for the rectangle
                                        vec_vec_inter.push_back(intersect);		//push set of columns for the rectangle
	
				}
	
		}

	}

	}
	for(int i = 0; i < vec_vec_rows.size(); i++){
        	sort( vec_vec_rows[i].begin(), vec_vec_rows[i].end() );
                vec_vec_rows[i].erase( unique( vec_vec_rows[i].begin(), vec_vec_rows[i].end() ), vec_vec_rows[i].end() );
        }

	int n = vec_vec_inter.size();
	vector<vector<int> > vec_vec_rows_dum;
	vector<vector<int> > vec_vec_rows_new;
	vector<vector<int> > vec_vec_inter_dum;

	vector<int> vec_zero;
	vec_zero.push_back(0);

	vector<int> erase_from_rows;

	for (int i = 0; i < vec_vec_inter.size(); i++){				// remove duplicate set of columns: step 3 of algorithm 1
		for (int j = 0; j < vec_vec_inter.size(); j++){
			vector<int> vec_rows;
			if (i != j){
				if((vec_vec_inter[i] == vec_vec_inter[j]) and (vec_vec_inter[i] != vec_zero)){
					vec_vec_inter[j] = vec_zero;
					for(int k = 0; k < vec_vec_rows[j].size(); k++){
						vec_vec_rows[i].push_back(vec_vec_rows[j][k]);
					}
					vec_vec_rows[j] = vec_zero;


				}	
			}
		}
	
	}


	for (int i = 0; i < vec_vec_inter.size(); i++){			// step 3 of algorithm 1: push the rows of the removed columns
		if (vec_vec_inter[i] != vec_zero){
			vec_vec_inter_dum.push_back(vec_vec_inter[i]);
			vec_vec_rows_dum.push_back(vec_vec_rows[i]);
		}
	}

	vec_vec_rows = vec_vec_rows_dum;
	vec_vec_inter = vec_vec_inter_dum;

	
	vector<vector<int> > vec_vec_not_in;

	for(int i = 0; i < vec_vec_rows.size(); i++){			//sort and remove duplicates within each set of rows
        	sort( vec_vec_rows[i].begin(), vec_vec_rows[i].end() );
                vec_vec_rows[i].erase( unique( vec_vec_rows[i].begin(), vec_vec_rows[i].end() ), vec_vec_rows[i].end() );
        }

	int flag_found_not_in = 0;

	for (int i = 0; i < vec_vec_inter.size(); i++){			//step 4 of algorithm 1: find complete set of rows
		for (int j = 0; j < vec_vec_inter.size(); j++){
			vector<int> vec_rows;
			vector<int> intersect;
			if (i != j){
                        	set_intersection(vec_vec_inter[i].begin(), vec_vec_inter[i].end(),vec_vec_inter[j].begin(), vec_vec_inter[j].end(), back_inserter(intersect));
				flag_found_not_in = 0;
				if (intersect == vec_vec_inter[i]) {			// Case 1 of step 4
					vec_rows = vec_vec_rows[j];
					for(int k = 0; k < vec_rows.size(); k++){
						vec_vec_rows[i].push_back(vec_rows[k]);
					}
					
				}
				else{
					if(intersect.size() != 0)			//Case 2 of step 4
							vec_vec_not_in.push_back(intersect);
				}				

			}
		}
	}

	int set_flag_present = 0;
	int erase_pos = 0;
	vector<int> vec_erase;
	
	for (int i = 0; i < vec_vec_inter.size(); i++){			//subcase 2 of step 4 of algorithm 1
		for (int j = 0; j < vec_vec_not_in.size(); j++){
			if(vec_vec_inter[i] == vec_vec_not_in[j]){
				vec_erase.push_back(j);
			}
		}
	}



	vector< vector<int> > vec_vec_add;
	for(int i = 0; i < vec_erase.size(); i++){
		vec_vec_not_in[vec_erase[i]] = vec_zero;
	
	}

	int flag_found_add = 0;



	for (int i = 0; i < vec_vec_not_in.size(); i++){
		flag_found_add = 0;
		for (int j = 0; j < vec_vec_add.size(); j++){
			if (vec_vec_not_in[i] == vec_vec_add[j]){
				flag_found_add = 1;
			}
		}
		if((flag_found_add == 0) and (vec_vec_not_in[i] != vec_zero)){
			vec_vec_add.push_back(vec_vec_not_in[i]);
		}

	}

	
	vector<int> vec_rows1;
	vector<int> vec_rows2;

	//cout<<"vec_vec_add.size: "<<vec_vec_add.size()<<'\n';		//for debugging

	for (int j = 0; j < vec_vec_add.size(); j++){			//add the set of rows under subcase 2 of step 4
		for (int i = 0; i < vec_vec_inter.size(); i++){
			vector<int> intersect;
                        set_intersection(vec_vec_inter[i].begin(), vec_vec_inter[i].end(),vec_vec_add[j].begin(), vec_vec_add[j].end(), back_inserter(intersect));
			if(intersect == vec_vec_add[j]){
				vec_rows2 = vec_vec_rows[i];
				vec_rows1.insert(vec_rows1.end(), vec_rows2.begin(), vec_rows2.end());
				
			}
		}
		vec_vec_rows.push_back(vec_rows1);
		vec_rows1.clear();
		vec_rows2.clear();
		
	}


	for (int i = 0; i < vec_vec_add.size(); i++){			// add set of columns under subcase 2 of step 4
		vec_vec_inter.push_back(vec_vec_add[i]);
	}

	/*for (int i = 0; i < vec_vec_add.size(); i++){			//for debugging
		for (int j = 0; j < vec_vec_add[i].size(); j++){
			cout<<"vec_vec_add is: "<<vec_vec_add[i][j]<<'\n';
		}
	}*/


	for(int i = 0; i < vec_vec_rows.size(); i++){
        	sort( vec_vec_rows[i].begin(), vec_vec_rows[i].end() );
                vec_vec_rows[i].erase( unique( vec_vec_rows[i].begin(), vec_vec_rows[i].end() ), vec_vec_rows[i].end() );
        }

	vector<int> swap_temp_vec;

	for (int i = 1; i < vec_vec_rows.size(); i++){				//Bubble sort the set of rows and set of columns
		for (int j = 0; j < vec_vec_rows.size()-i; j++){
			if (vec_vec_rows[j][0] > vec_vec_rows[j+1][0]){
				swap_temp_vec = vec_vec_rows[j];
				vec_vec_rows[j] = vec_vec_rows[j+1];
				vec_vec_rows[j+1] = swap_temp_vec;
				swap_temp_vec = vec_vec_inter[j];
				vec_vec_inter[j] = vec_vec_inter[j+1];
				vec_vec_inter[j+1] = swap_temp_vec;
			}
			else if (vec_vec_rows[j][0] == vec_vec_rows[j+1][0]){
				if (vec_vec_rows[j][1] > vec_vec_rows[j+1][1]){
                                swap_temp_vec = vec_vec_rows[j];
                                vec_vec_rows[j] = vec_vec_rows[j+1];
                                vec_vec_rows[j+1] = swap_temp_vec;
                                swap_temp_vec = vec_vec_inter[j];
                                vec_vec_inter[j] = vec_vec_inter[j+1];
                                vec_vec_inter[j+1] = swap_temp_vec;
                        }

			}
		}
	}

	ofstream of0;

	if (pp == 1){
	of0.open("prime_rects.txt");				//output the prime rectangles to a file

	
	for(int i = 0; i < vec_vec_rows.size(); i++){



		of0<<"(";
		of0<<"{";
		for(int j = 0; j < vec_vec_rows[i].size(); j++){
			of0<<vec_vec_rows[i][j];				
			if (j < vec_vec_rows[i].size()-1){
				of0<<",";
			}
		}
		of0<<"}"<<","<<"{";
		for(int j = 0; j < vec_vec_inter[i].size(); j++){
			of0<<vec_vec_inter[i][j];				
			if (j < vec_vec_inter[i].size()-1){
				of0<<",";
			}
		}
		of0<<"}"<<")"<<'\n';
			
	}
	of0<<'\n';
	of0<<"Total number of rectangles: "<<vec_vec_rows.size()<<'\n';
	of0.close(); }




	
	int literals_bef_ext = 0;

	for (int i = 1; i < cube_ord.size(); i++){			// Calculate no. of literals before extraction
			literals_bef_ext = literals_bef_ext + cube_ord[i].size();
	}

	int literals_after_ext = 0;

	int max_value_prime = 0;

	of0.open("restricted.txt");					//open restricted.txt for candidate prime rectangles
	int func_id;							// and optimal prime rectangles
	int flag_same_funcs;
	int count_restricted_rects = 0;
	
	for(int i = 0; i < vec_vec_rows.size(); i++){
		flag_same_funcs = 1;
		func_id = cube_id[vec_vec_rows[i][0]];
		for(int l = 1; l < vec_vec_rows[i].size(); l++){
			if(cube_id[vec_vec_rows[i][l]] != func_id){
				flag_same_funcs = 0;
				break;
			}
				 	
		}
		if((vec_vec_inter[i].size() > 1) and (flag_same_funcs == 0)){		//Remove prime rectangles which belong to same function
			of0<<"(";							// or have only one column
			of0<<"{";
			for(int j = 0; j < vec_vec_rows[i].size(); j++){
				of0<<vec_vec_rows[i][j];				
				if (j < vec_vec_rows[i].size()-1){
					of0<<",";
				}
			}
			of0<<"}"<<","<<"{";
			for(int j = 0; j < vec_vec_inter[i].size(); j++){
				of0<<vec_vec_inter[i][j];				
				if (j < vec_vec_inter[i].size()-1){
					of0<<",";
				}
			}
			of0<<"}"<<")";
			of0<<'\t';
			for(int j = 0; j < vec_vec_inter[i].size(); j++){
				of0<<var_ord[vec_vec_inter[i][j]];
			}
			of0<<'\t';
			vector<int> vec_func_id;
			for(int p = 0; p < vec_vec_rows[i].size(); p++){
				vec_func_id.push_back(cube_id[vec_vec_rows[i][p]]);
			}
	
			for(int q = 0; q < vec_func_id.size(); q++){
				sort( vec_func_id.begin(), vec_func_id.end() );
				vec_func_id.erase( unique( vec_func_id.begin(), vec_func_id.end() ), vec_func_id.end() );
			}
			literals_after_ext = get_literals_after_ext(vec_vec_rows[i], vec_vec_inter[i], vec_func_id);	//calculate no. of literals
															//after extraction of this prime rectangle
				
			of0<<literals_bef_ext - literals_after_ext;					//value of the candidate prime rectangle
			if(max_value_prime < (literals_bef_ext - literals_after_ext)){
				max_value_prime = (literals_bef_ext - literals_after_ext);
			}
			of0<<'\n';				

			count_restricted_rects++;
		}
			
	}
	of0<<'\n';
	of0<<"Total number of candidate prime rectangles: "<<count_restricted_rects<<'\n'<<'\n';

	of0<<"Optimal single-cube extraction choice(s): "<<'\n';
		
	for(int i = 0; i < vec_vec_rows.size(); i++){
		flag_same_funcs = 1;
		func_id = cube_id[vec_vec_rows[i][0]];
		for(int l = 1; l < vec_vec_rows[i].size(); l++){
			if(cube_id[vec_vec_rows[i][l]] != func_id){
				flag_same_funcs = 0;
				break;
			}
				 	
		}
	
	
		if((vec_vec_inter[i].size() > 1) and (flag_same_funcs == 0)){				//choose the candidate prime rectangle with maximum value
			vector<int> vec_func_id;
			for(int p = 0; p < vec_vec_rows[i].size(); p++){
				vec_func_id.push_back(cube_id[vec_vec_rows[i][p]]);
			}
	
			for(int q = 0; q < vec_func_id.size(); q++){
				sort( vec_func_id.begin(), vec_func_id.end() );
				vec_func_id.erase( unique( vec_func_id.begin(), vec_func_id.end() ), vec_func_id.end() );
			}
			literals_after_ext = get_literals_after_ext(vec_vec_rows[i], vec_vec_inter[i], vec_func_id);
			if((max_value_prime == (literals_bef_ext - literals_after_ext))){
			
			of0<<"(";
			of0<<"{";
			for(int j = 0; j < vec_vec_rows[i].size(); j++){
				of0<<vec_vec_rows[i][j];				
				if (j < vec_vec_rows[i].size()-1){
					of0<<",";
				}
			}
			of0<<"}"<<","<<"{";
			for(int j = 0; j < vec_vec_inter[i].size(); j++){
				of0<<vec_vec_inter[i][j];				
				if (j < vec_vec_inter[i].size()-1){
					of0<<",";
				}
			}
			of0<<"}"<<")";
			of0<<'\t';
			for(int j = 0; j < vec_vec_inter[i].size(); j++){
				of0<<var_ord[vec_vec_inter[i][j]];
			}
			of0<<'\t';
			of0<<max_value_prime;

			of0<<'\t'<<"{";
			for(int r = 0; r < vec_func_id.size(); r++){
				of0<<"f"<<vec_func_id[r];
				if (r < vec_func_id.size()-1){
					of0<<",";
				}	
			}
			of0<<"}";

			of0<<'\n';				
			}
		}
			
	}

	of0.close();
	
		

}

int sing_cube::get_literals_after_ext(vector<int>& rows_vec, vector<int>& inter_vec, vector<int>& vec_func_id){	    //Uses algorithm 2

	vector< vector<string> > quotient;	//store quotient for each function
	vector< vector<string> > rem;		//store remainder for each function
						//CAUTION: vectors start from 0, but functions
						//are numbered from 1
	vector<string> vec_qt;
	vector<string> vec_rem;


	string a = "abcd";
	string b = "c";
	int pos = a.find(b);
	string orig_cube;
	string temp_cube;

	int flag_cube_rem = 0;

	for (int i = 0; i < vec_func_id.size(); i++){	//find quotient and remainder for all the functions from which cube 
							//needs to be extracted							
		vec_rem.clear();
		vec_qt.clear();
		for(int j = 1; j < cube_id.size(); j++){
			if (cube_id[j] == vec_func_id[i]){
				flag_cube_rem = 0;
				orig_cube = cube_ord[j];
				temp_cube = orig_cube;
				for(int k = 0; k < inter_vec.size(); k++){
					stringstream ss;
					string s;
					ss << var_ord[inter_vec[k]];
					ss >> s;
					pos = temp_cube.find(s);	
					if(pos != -1){
						temp_cube.erase(pos,1);
						
					}
					if(pos == -1){
						flag_cube_rem = 1;
						break;	
					}		
				}
				if(flag_cube_rem == 1){
					vec_rem.push_back(orig_cube);
				}
				else{
					if (temp_cube.empty()){
						vec_qt.push_back("1");
					}
					else
						vec_qt.push_back(temp_cube);
				}
			}
		}
		quotient.push_back(vec_qt);
		rem.push_back(vec_rem);
	}

	

	int num_literals = 0;
	int num_ands = 0;
	string one = "1";
	string two;

	int num_ors = 0;

	vector<string> vec_com;
	int flag_com_found = 0;


	int K = inter_vec.size();		//K is the new function created in Logic network, equal to the prime rectangle to
						//be extracted
	num_literals = 	K;

	int count = 0;

	for (int i = 0; i < quotient.size(); i++){
		for (int j = 0; j < quotient[i].size(); j++){
			if((quotient[i].size() == 1) && (quotient[i][j] == one)){	//if the quotient is one then increment the literal
				num_literals = num_literals + 1;
				count++;
			}
			else if((quotient[i].size() != 1) && (quotient[i][j] == one)){
				num_literals = num_literals + 1;
			}
			else{
						num_literals = num_literals + quotient[i][j].size();	//add the size of the cube in quotient + 1
						num_literals = num_literals + 1;
			}
		}
		for (int j = 0; j < rem[i].size(); j++){
					num_literals = num_literals + rem[i][j].size();
		}
	}


	vector<int> vec_fns;
	vector<int> vec_fns_not_inter;

	for (int i = 1; i <= num_fns; i++){
		vec_fns.push_back(i);
	}

	int count_fns_uneq = 0;
	for (int i = 0; i < vec_fns.size(); i++){				//the functions from which the cube is not being extracted
		count_fns_uneq = 0;
		for (int j = 0; j < vec_func_id.size(); j++){
			if(vec_fns[i] != vec_func_id[j]){
				count_fns_uneq++;
			}	
		}
		if(count_fns_uneq == vec_func_id.size()){
			vec_fns_not_inter.push_back(vec_fns[i]);
		}
	}

	for (int i = 0; i < vec_fns_not_inter.size(); i++){
				for (int k = 1; k < cube_id.size(); k++){
					if (cube_id[k] == vec_fns_not_inter[i]){
							num_literals = num_literals + cube_ord[k].size();	//just add the sie of the cube to num_literals
					}
				}
			
		
	}

	
	return num_literals;	

}



