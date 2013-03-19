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



bool check_B1(const cover &f, const cover &g)
{
	if (f.empty() && g.empty())
		return true;
	else
		return false;
}

bool check_B2(const cover &f, const cover &g)
{
	if (is_tautology(f) && is_tautology(g))
		return true;
	else
		return false;
}

bool check_B3(const cover &f, const cover &g)
{
	return false;
}

bool check_B4(const cover &f, const cover &g)
{
	return false;
}

bool check_B5(const cover &f, const cover &g)
{
	return false;
}

bool check_B6(const cover &f, const cover &g)
{
	return false;
}

bool check_B7(const cover &f, const cover &g)
{
	return false;
}

bool check_B8(const cover &f, const cover &g)
{
	return false;
}

bool check_B9(const cover &f, const cover &g)
{
	return false;
}

bool check_B10(const cover &f, const cover &g)
{
	return false;
}

bool check_U11(const cover &f, const cover &g)
{
	return false;
}

bool check_U12(const cover &f, const cover &g)
{
	return false;
}

bool check_U13(const cover &f, const cover &g)
{
	return false;
}

bool check_M14(const cover &f, const cover &g)
{
	return false;
}


int coversim::check(const cover &f, const cover &g)
{
	/* TODO pick a wise ordering! */
	if (check_B1(f, g))
		return 1;
	if (check_B2(f, g))
		return 2;
	if (check_B3(f, g))
		return 3;
	if (check_B4(f, g))
		return 4;
	if (check_B5(f, g))
		return 5;
	if (check_B6(f, g))
		return 6;
	if (check_B7(f, g))
		return 7;
	if (check_B8(f, g))
		return 8;
	if (check_B9(f, g))
		return 9;
	if (check_B10(f, g))
		return 10;
	if (check_U11(f, g))
		return 11;
	if (check_U12(f, g))
		return 12;
	if (check_U13(f, g))
		return 13;
	if (check_M14(f, g))
		return 14;
	return 0;
}
