#ifndef __TAUTOLOGY_H__
#define __TAUTOLOGY_H__

#include "ufs.h"

/**
 * Simple termination rules for
 * Tatutology Checking
 *
 * Notice that we do recursion for
 * similarity checking, but not for
 * tautology.
 *
 * TERMINATION RULES
 * T1:  Universal cube.
 * T2:  Input column all ones/zeros.
 * T3:  Single input dependence.
 * T4:  Empty cover.
 * TU1: Unateness of the cover.
 */

class tautology {
public:
	static bool check(const cover &f);

};

#endif /* __TAUTOLOGY_H__ */
