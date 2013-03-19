#include "coversim.h"

/*
 * Simple tatutology checking: this check does not
 * go through a complete tautology checking, because
 * it would be as expensive as making more splitting
 * steps. This function just checks for quick rules
 * for termination, taken from "Tautology Checking"
 * but does not go through recursion.
 * Called by rule B2 and B4 and B5
 */
bool is_tautology(const cover &f)
{
	tautology t;
	return t.check(f);
}



int coversim::check(const cover &f, const cover &g)
{
	return 0;
}
