#ifndef __PRINTPLAS_H__
#define __PRINTPLAS_H__

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>

#include "ufs.h"


class printplas {
public:
	void print(int levelid, int nodeid, const cover &f, const cover &g);

};

#endif /*  __PRINTPLAS_H__ */
