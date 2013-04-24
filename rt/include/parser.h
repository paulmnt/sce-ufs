#ifndef __PARSER_H__
#define __PARSER_H__

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <utility>
#include <sstream>
#include <sng.h>

using namespace std;

class parser{

public:
	sng *parse_file(char* file);

};


#endif /* __PARSER_H__ */
