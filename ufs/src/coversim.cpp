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


/* Single input dependence: return variable index or -1*/
int single_dep(const cover &f)
{
	int dep = 0;
	int index = -1;
	for (int i = 0; i < f.lits; i++) {
		if (f.dep[i]) {
			dep++;
			index = i;
		}
		if (dep > 1)
			return -1;
	}
	return index;
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

int check_B9_12(const cover &f, const cover &g, int *sv)
{
	int ind1, ind2;
	ind1 = single_dep(f);
	if (ind1 >= 0) {
		ind2 = single_dep(g);
		if (ind2 < 0) {
			*sv = ind1;
			return 12;
		}
		if (ind2 == ind1) {
			if (f.ones[ind1] == g.ones[ind2])
				return 9;
			else
				return 10;
		}
		return 11;
	}
	ind2 = single_dep(g);
	if (ind2 >= 0) {
		*sv = ind2;
		return -12;
	}
	return 0;
}



/* Positive or negative unateness on a variable */
int posunate_nodc(const cover &f)
{
	/*
	 * TODO: for now we take the first. Cross checking
	 * all possibilities with the other cover could be
	 * expensive
	 */
	for (int i = 0; i < f.lits; i++)
		if (f.ones[i] == f.len)
			return i;
	return -1;

}
int negunate_nodc(const cover &f)
{
	for (int i = 0; i < f.lits; i++)
		if (f.zeros[i] == f.len)
			return i;
	return -1;

}
bool posunate_nodc(const cover &f, int index)
{
	if (f.ones[index] == f.len)
		return true;
	return false;
}
bool negunate_nodc(const cover &f, int index)
{
	if (f.zeros[index] == f.len)
		return true;
	return false;
}

int check_U13_15(const cover &f, const cover &g, int *sv)
{
	int ind1p, ind1n, ind2p, ind2n;
	ind1p = posunate_nodc(f);
	ind2p = posunate_nodc(g);
	ind1n = negunate_nodc(f);
	ind2n = negunate_nodc(g);
	if ((ind1p >= 0) && (ind2n >= 0)) {
		if (ind1p == ind2n)
			return 14;
		if (negunate_nodc(g, ind1p))
			return 14;
		if (posunate_nodc(f, ind2n))
			return 14;
	}
	if ((ind1n >= 0) && (ind2p >= 0)) {
		if (ind1n == ind2p)
			return 14;
		if (posunate_nodc(g, ind1n))
			return 14;
		if (negunate_nodc(f, ind2p))
			return 14;
	}

	if ((ind1p >= 0) && (ind2p >= 0)) {
		if (ind1p == ind2p) {
			*sv = ind1p;
			return 13;
		}
		if (posunate_nodc(g, ind1p)) {
			*sv = ind1p;
			return 13;
		}
		if (posunate_nodc(f, ind2p)) {
			*sv = ind2p;
			return 13;
		}
	}

	if ((ind1n >= 0) && (ind2n >= 0)) {
		if (ind1n == ind2n) {
			*sv = ind1n;
			return 13;
		}
		if (negunate_nodc(g, ind1n)) {
			*sv = ind1n;
			return 13;
		}
		if (negunate_nodc(f, ind2n)) {
			*sv = ind2n;
			return 13;
		}
	}

	/* Else favour f. Might not be optimal */
	if (f.len > 1) {
		// Not single cube
		if ((ind1p >= 0)) {
			*sv = ind1p;
			return 15;
		}
		if ((ind1n >= 0)) {
			*sv = ind1n;
			return 15;
		}
	}
	if (g.len > 1) {
		// Not single cube
		if ((ind2p >= 0)) {
			*sv = ind2p;
			return -15;
		}
		if ((ind2n >= 0)) {
			*sv = ind2n;
			return -15;
		}
	}
	return 0;
}


/*
 * We return negative rule number if the covers f, g
 * are swapped with respect to the rules listed in
 * coversim.h
 * Sometimes sv is used to store suggested splitting
 * variable. If no optimal sv can be derived from
 * the rules, then sv is set to -1
 */
int coversim::check(const cover &f, const cover &g,
		    bool b7, bool b8, int *sv)
{
	/* TODO pick a wise ordering! */
	*sv = -1;
	int tmp = check_B1_5(f, g);
	if (tmp)
		return tmp;

	tmp = check_B9_12(f, g, sv);
	if (tmp)
		return tmp;

	tmp = check_B6_8(f, g, b7, b8);
	if (tmp)
		return tmp;

	tmp = check_U13_15(f, g, sv);
	if (tmp)
		return tmp;

	return 0;
}
