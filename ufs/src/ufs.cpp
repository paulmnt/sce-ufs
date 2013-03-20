#include "ufs.h"
#include "coversim.h"

/*
 * The following functions implement cubes similarity:
 *
 * common_ones: looks for intersections.
 * total_ones : sums the number of minterms covered by
 *              the cubes not taking into account that
 *              they might intersect.
 * cubesim    : calculates similarity between the cubes 
 */
int common_ones(const cube &c1, const cube &c2)
{
	/* Cubes length is always the same */
	int num = 1 << c1.len;
	int den = 1;
	for (int i = 0; i < c1.len; i++) {
		if (c1.vars[i] != c2.vars[i]) {
			if ((c1.vars[i] != '-') && (c2.vars[i] != '-')) {
				// cubes do not intersect
				num = 0;
				break;
			} else {
				// match on half of the remained products
				den <<= 1;
				continue;
			}
		} else {
			if (c1.vars[i] == '-') {
				// this variable has no effects
				continue;
			} else {
				// products to compare are halved
				num >>= 1;
				continue;
			}
		}
	}

#ifdef DEBUG
	assert(!(num % den));
	cout << "DEBUG: ";
	cout << "Cubes intersect on " << num / den << " minterms" << endl;
#endif
	return num / den;
}

int total_ones(const cube &c1, const cube &c2)
{
	/* Does not consider intersection! */
	int num1 = 1 << c1.len;
	int num2 = 1 << c2.len;

	for (int i = 0; i < c1.len; i++) {
		if (c1.vars[i] != '-')
			num1 >>= 1;
		if (c2.vars[i] != '-')
			num2 >>= 1;
	}

#ifdef DEBUG
	cout << "DEBUG: ";
	cout << "Cube 1 covers " << num1 << " minterms" << endl;
	cout << "       Cube 2 covers " << num2 << " minterms" << endl;
#endif
	return num1 + num2;
}

/* Similarity between two cubes. Called if B6 applies */
float cubesim(const cube &c1, const cube &c2)
{
	/* Assumes covers are non empty! */
	int cones = common_ones(c1, c2);
	int tones = total_ones(c1, c2);
	int m = 1 << c1.len;
	int czeros = m - (tones - cones);
	float sim = (float) (cones + czeros) / m;

#ifdef DEBUG
	cout << "DEBUG: ";
	cout << "Cubes similarity is  " << sim << endl;
#endif

	return sim;
}


void ufs::cofactor(const cover &f, const cover &g,
		cover &pcof, cover &pcog,
		cover &ncof, cover &ncog, int sv)
{
	int index = -1;
	/* Index is the same for every cover */
	for (int i = 0; i < f.lits; i++)
		if (f.varid[i] == sv) {
			index = i;
			break;
		}
#ifdef DEBUG
	if (index < 0) {
		cout << "ERROR: cofactoring w.r.t. missing variable" << endl;
		return;
	} else
		cout << "DEBUG: Splittin on variable x" << sv << " @ index " << index << endl;
#endif

	/* Fsv */
	for (int i = 0; i < f.len; i++) {
		if (f.cubes[i].vars[index] != '0')
			pcof.add_cube(f.cubes[i]);
	}
	pcof.del_column(index);
	/* Fsv' */
	for (int i = 0; i < f.len; i++) {
		if (f.cubes[i].vars[index] != '1')
			ncof.add_cube(f.cubes[i]);
	}
	ncof.del_column(index);
	/* Gsv */
	for (int i = 0; i < g.len; i++) {
		if (g.cubes[i].vars[index] != '0')
			pcog.add_cube(g.cubes[i]);
	}
	pcog.del_column(index);
	/* Gsv' */
	for (int i = 0; i < g.len; i++) {
		if (g.cubes[i].vars[index] != '1')
			ncog.add_cube(g.cubes[i]);
	}
	ncog.del_column(index);

#ifdef DEBUG
	cout << "Splitting variable: x" << sv << endl;
	cout << "DEBUG: printing positive cofactor of F" << endl;
	pcof.print();
	cout << "DEBUG: printing negative cofactor of F" << endl;
	ncof.print();
	cout << "DEBUG: printing positive cofactor of G" << endl;
	pcog.print();
	cout << "DEBUG: printing negative cofactor of G" << endl;
	ncog.print();
#endif
}

int ufs::check_rules(const cover &f, const cover &g, int *sv)
{
	int rule;
	coversim csim(use_b7, use_b8);
	rule = csim.check(f, g, use_b7, use_b8, sv);

#ifdef DEBUG
	cout << "DEBUG: matching rule " << rule << endl;
	if (*sv >= 0)
		cout << "Suggested splitting var: " << *sv << endl;
#endif

	return rule;
}

/* Pick a variable, which is binate for both or pick the first var */
static int pick_binate(const cover &f, const cover &g)
{
	for (int i = 0; i < f.lits; i++) {
		if (f.ones[i] && f.zeros[i] &&
		    g.ones[i] && g.zeros[i])
			return i;
	}
	return 0;
}


float ufs::similarity(const cover &f, const cover &g, int levelid)
{
	/* Recursive function */

	// Increase number of levels if necessary
	level l;
	if (levelid >= len)
		add_level(l);

	int sv;
	node cur;
	out[levelid].add_node(cur);
	int cur_lits = f.lits;
	cover pcof(cur_lits), pcog(cur_lits), ncof(cur_lits), ncog(cur_lits);
	int rule = check_rules(f, g, &sv);
	int sim;

	switch (rule) {
	case 1: break;
	case 2: break;
	case 3: break;
	case -3: break;
	case 4: break;
	case -4: break;
	case 5: break;
	case -5: break;
	case 6: break;
	case 7: break;
	case -7: break;
	case 8: break;
	case 9: break;
	case 10: break;
	case 11: break;
	case 12: break;
	case -12: break;
	case 13: break;
	case 14: break;
	case 15: break;
	case -15: break;
	default:
		sv = pick_binate(f, g);
		cur.splitvar = sv;
		cur.rule = "split";
		cofactor(f, g, pcof, pcog, ncof, ncog, sv);
		sim = 0.5 * (similarity(pcof, pcog, levelid + 1) +
			     similarity(ncof, ncog, levelid + 1));
		cur.sim = sim;
		break;
	}

	return sim;
}


float ufs::simeval(const cover &f, const cover &g)
{
	/* Recursive function */
	level lev;
	add_level(lev);

	return similarity(f, g, 0);
}
