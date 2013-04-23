#include <algo_cp.h>

int main(int argc, char *argv[]){

        parser ip;
	cp cpobj;



        ip.parse_file(argv[1]);             //parse input file
	cpobj.func_cp(ip);
	
        return (0);


}

