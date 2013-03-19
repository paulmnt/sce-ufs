#include "tautology.h"

bool check_T1(const cover &f)
{
	for (int i = 0; i < f.len; i++) {
		bool universal = true;
		for (int j = 0; j < f.lits; j++) {
			if (f.cubes[i].vars[j] != '-') {
				universal = false;
				break;
			}
		}
		if (universal)
			return true;
	}
	return false;
}

bool check_T2(const cover &f)
{
	for (int i = 0; i < f.lits; i++) {
		if (f.ones[i] == f.len)
			//All ones
			return true;
		if (f.zeros[i] == f.len)
			//All zeros
			return true;
	}
	return false;
}

bool check_T3(const cover &f)
{
	/* This is called if T1 and T2 do not apply */
	int deps = 0;
	for (int i = 0; i < f.lits; i++) {
		if (f.dep[i])
			deps++;
		if (deps > 1)
			return false;
	}
	return true;
}

bool check_T4(const cover &f)
{
	return f.empty();
}

/*
bool check_TU1(const cover &f)
{
	for (int i = 0; i < f.lits; i++)
		if (f.ones[i] && f.zeros[i])
			return false;
	return true;
}
*/

bool tautology::check(const cover &f) {
	if (check_T4(f)) //Not tautology
		return false;
	if (check_T2(f)) //Not tautology
		return false;
	if (check_T1(f)) //Tautology
		return true;
	if (check_T3(f)) //Tautology
		return true;

	/*
	 * Skip TU1, because we return false anyway.
	 * Notice that we don't skip T2 because it is
	 * required for T3, while we don't skip T4
	 * because it is very quick
	 */
	/*
	if (check_TU1(f))
		return false;
	*/

	return false;
}
