#include "algo_feas.h"

bool feas::func_feas(int c, int *r) {

/*

	vector<int> retime_vert;
	vector<int> re_wts_edges = wts_edges;

	vector<int> deltav_feas;

	cp cpobj2;	

	for (int i = 0; i < num_vert; i++){
		retime_vert.push_back(0);
	}	

	for (int i = 0; i < num_vert-1; i++){
		
		for (int j = 0; j < re_wts_edges.size(); j++){
			re_wts_edges[j] = wts_edges[j] + retime_vert[edges[j][1]] - retime_vert[edges[j][0]];
		}
		deltav_feas = cpobj2.func_cp(num_vert, delay_vert, edges, re_wts_edges);
	
		for (int j = 0; j < num_vert; j++){
			if(deltav_feas[j] > c){
				cout<<"HERE"<<endl;
				retime_vert[j]++;
			}
		}	
			
	}

	deltav_feas = cpobj2.func_cp(num_vert, delay_vert, edges, re_wts_edges);

	int phiGr = cpobj2.get_clock_period();

	cout<<"clock period of Gr here in feas is: "<<phiGr<<endl;

	if (phiGr > c){
		return false;
	}
	else{
		return true;
	}

*/

	return false;
}
