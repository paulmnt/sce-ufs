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


 /* Cubes intersection evaluation */
bool intersect(const cube &c1, const cube &c2)
{
	/* Cubes length is always the same */
	for (int i = 0; i < c1.len; i++) {
		if (c1.vars[i] == c2.vars[i])
			continue;
		if ((c1.vars[i] == '-') || (c2.vars[i] == '-'))
			continue;
		return false;
	}
	return true;
}
/* Disjoint cubes in a cover */
bool disjoint_cubes(const cover &f)
{
	for (int i = 0; i < f.len; i++) {
		for (int j = i + 1; j < f.len; j++)
			if (intersect(f.cubes[i], f.cubes[j]))
				return false;
	}
	return true;
}


int check_B1_5(const cover &f, const cover &g)
{
	if (f.empty()) {
		if (g.empty())
			return 1;
		if (is_tautology(g))
			return 5;
		return 3;
	}
	if (g.empty()) {
		if (is_tautology(f))
			return -5;
		return -3;
	}
	if (is_tautology(f)) {
		if (is_tautology(g))
			return 2;
		return 4;
	}
	if (is_tautology(g))
		return -4;
	return 0;
}

int check_B6_8(const cover &f, const cover &g, bool b7, bool b8)
{
	/* Notice that if b8 is true, then b7 is true as well! */
	if (f.len == 1) {
		if (g.len ==1)
			return 6;
		if (!b7)
			return 0;
		if (disjoint_cubes(g))
			return 7;
		return 0;
	}
	if (!b7)
		return 0;
	if (g.len == 1)
		if (disjoint_cubes(f))
			return -7;
	if (!b8)
		return 0;
	if (disjoint_cubes(f) && disjoint_cubes(g))
		return 8;
	return 0;
}

int check_B9_10(const cover &f, const cover &g)
{
	return 0;
}


int check_U11_13(const cover &f, const cover &g)
{
	return 0;
}


/*
 * We return negative rule number if the covers f, g
 * are swapped with respect to the rules listed in
 * coversim.h
 */
int coversim::check(const cover &f, const cover &g,
		    bool b7, bool b8)
{
	/* TODO pick a wise ordering! */
	int tmp = check_B1_5(f, g);
	if (tmp)
		return tmp;

	tmp = check_B9_10(f, g);
	if (tmp)
		return tmp;

	tmp = check_B6_8(f, g, b7, b8);
	if (tmp)
		return tmp;

	tmp = check_U11_13(f, g);
	if (tmp)
		return tmp;

	return 0;
}
