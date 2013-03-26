#include "ufs.h"
#include "coversim.h"
#include "tautology.h"
#include "printplas.h"

/*
 * The following functions implement cubes similarity:
 *
 * common_ones: looks for intersections.
 * total_ones : sums the number of minterms covered by
 *              the cubes not taking into account that
 *              they might intersect.
 * total_ones : minterms covered by a single cube
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

int total_ones(const cube &c)
{
	int num = 1 << c.len;
	for (int i = 0; i < c.len; i++)
		if (c.vars[i] != '-')
			num >>= 1;
#ifdef DEBUG
	cout << "DEBUG: ones in this cube: " << num << endl;
#endif
	return num;
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


/*
 * The following are auxiliary functions to evaluate
 * similarity of covers when termination rules apply
 */

/* Single cover cofactor */
void single_cofactor(const cover &f, cover &pcof, cover &ncof)
{
	/* Always cofactor with respect to the first variable */
	int index = 0;

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

#ifdef DEBUG
	cout << "DEBUG: printing single cofactor" << endl;
	pcof.print();
	ncof.print();
#endif
}

/* onset returns the size of the ONset of a cover */
int onset(const cover &f)
{
	/*
	 * A simple recursion on a single cover in the
	 * most general case
	 */
	tautology t;
	if (f.empty())
		return 0;
	if (t.check(f))
		return (1 << f.lits);
	if (f.lits == 1)
		return (1 << (f.lits - 1));

	switch(f.len) {
	case 1:
		return total_ones(f.cubes[0]);
	case 2:
		return (total_ones(f.cubes[0], f.cubes[1]) -
			common_ones(f.cubes[0], f.cubes[1]));
	default:
		cover pcof(f.lits), ncof(f.lits);
		single_cofactor(f, pcof, ncof);
		return (onset(pcof) + onset(ncof));
	}
}

/* single disjoint similarity. Rule B7 */
float sdsim(const cube &c, const cover &f)
{
	int cones = 0;
	for (int i = 0; i < f.len; i++)
		cones += common_ones(c, f.cubes[i]);

	cover tmp = f;
	tmp.add_cube(c);
	int tones = onset(tmp);
	int m = 1 << c.len;
	int czeros = m - tones;
	float sim = (float) (cones + czeros) / m;

#ifdef DEBUG
	cout << "DEBUG: ";
	cout << "single disjoint similarity is  " << sim << endl;
	cout << "       CONES: " << cones << endl;
	cout << "       TONES: " << tones << endl;
	cout << "       CZEROS: " << czeros << endl;

#endif
	return sim;
}

/* multi disjoint similarity. Rule B8 */
float mdsim(const cover &f, const cover &g)
{
	int cones = 0;
	for (int i = 0; i < f.len; i++)
		for (int j = 0; j < g.len; j++)
			cones += common_ones(f.cubes[i], g.cubes[j]);

	int m = 1 << f.lits;
	cover tmp = f;
	for (int i = 0; i < g.len; i++)
		tmp.add_cube(g.cubes[i]);
	int tones = onset(tmp);
	int czeros = m - tones;
	float sim = (float) (cones + czeros) / m;

#ifdef DEBUG
	cout << "DEBUG: ";
	cout << "single disjoint similarity is  " << sim << endl;
	cout << "       CONES: " << cones << endl;
	cout << "       TONES: " << tones << endl;
	cout << "       CZEROS: " << czeros << endl;

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

int ufs::check_rules(const cover &f, const cover &g, int *sv, int *prune)
{
	int rule;
	coversim csim(use_b7, use_b8);
	rule = csim.check(f, g, use_b7, use_b8, sv, prune);

#ifdef DEBUG
	cout << "DEBUG: matching rule " << rule << endl;
	if (*sv >= 0)
		cout << "       Suggested splitting var: " << *sv << endl;
#endif

	return rule;
}

/* Pick a variable, which is binate for both or pick the first var */
static int pick_binate(const cover &f, const cover &g)
{
	for (int i = 0; i < f.lits; i++) {
		if ((f.ones[i] > 0) && (f.zeros[i] > 0) &&
		    (g.ones[i] > 0) && (g.zeros[i] > 0))
			return i;
	}
#ifdef DEBUG
	cout << "DEBUG: pick_binate found no common binate variables";
#endif
	return 0;
}


float ufs::similarity(const cover &f, const cover &g, int levelid, int nodeid)
{
	/* Recursive function */

	// Increase number of levels if necessary
	level l;
	l.levelid = levelid;
	if (levelid >= len)
		add_level(l);

	int sv;
	int prune;
	node cur;
	cur.nodeid = nodeid;
	int cur_lits = f.lits;
	cover pcof(cur_lits), pcog(cur_lits), ncof(cur_lits), ncog(cur_lits);
	/* Import variable ids for splitting */
	pcof.varid = f.varid;
	pcog.varid = f.varid;
	ncof.varid = f.varid;
	ncog.varid = f.varid;

	int rule = check_rules(f, g, &sv, &prune);
	float sim;

	switch (rule) {
	case 1: //B1
		cur.splitvar = sv;
		cur.rule = "B1";
		sim = 1;
		cur.sim = sim;
		break;

	case 2: //B2
		cur.splitvar = sv;
		cur.rule = "B2";
		sim = 1;
		cur.sim = sim;
		break;

	case 3: //B3
		cur.splitvar = sv;
		cur.rule = "B3";
		sim = 1 - ((float) onset(g) / (1 << g.lits));
		cur.sim = sim;
		break;

	case -3: //B3
		cur.splitvar = sv;
		cur.rule = "B3";
		sim = 1 - ((float) onset(f) / (1 << g.lits));
		cur.sim = sim;
		break;

	case 4: //B4
		cur.splitvar = sv;
		cur.rule = "B4";
		sim = (float) onset(g) / (1 << g.lits);
		cur.sim = sim;
		break;

	case -4: //B4
		cur.splitvar = sv;
		cur.rule = "B4";
		sim = (float) onset(f) / (1 << g.lits);
		cur.sim = sim;
		break;

	case 5: //B5
		cur.splitvar = sv;
		cur.rule = "B5";
		sim = 0;
		cur.sim = sim;
		break;

	case 6: //B6
		cur.splitvar = sv;
		cur.rule = "B6";
		sim = cubesim(f.cubes[0], g.cubes[0]);
		cur.sim = sim;
		break;

	case 7: //B7
		cur.splitvar = sv;
		cur.rule = "B7";
		sim = sdsim(f.cubes[0], g);
		cur.sim = sim;
		break;

	case -7: //B7
		cur.splitvar = sv;
		cur.rule = "B7";
		sim = sdsim(g.cubes[0], f);
		cur.sim = sim;
		break;

	case 8: //B8
		cur.splitvar = sv;
		cur.rule = "B8";
		sim = mdsim(f, g);
		cur.sim = sim;
		break;

	case 9: //B9
		cur.splitvar = sv;
		cur.rule = "B9";
		sim = 1;
		cur.sim = sim;
		break;

	case 10: //B10
		cur.splitvar = sv;
		cur.rule = "B10";
		sim = 0;
		cur.sim = sim;
		break;

	case 11: //B11
		cur.splitvar = sv;
		cur.rule = "B11";
		sim = 0.5;
		cur.sim = sim;
		break;

	case 14://B14
		cur.splitvar = sv;
		cur.rule = "B14";
		sim = 1 - ((float) (onset(f) + onset(g)) / (1 << f.lits));
		cur.sim = sim;
		break;


	case 12:  //B12: we apply B3 on a child and B4 on the other
		sv = f.varid[sv];
		cofactor(f, g, pcof, pcog, ncof, ncog, sv);
		if (pcof.empty()) {
			sim = 1 - ((float) onset(pcog) / (1 << pcog.lits));
			sim += (float) onset(ncog) / (1 << ncog.lits);
		} else {
			sim = 1 - ((float) onset(ncog) / (1 << ncog.lits));
			sim += (float) onset(pcog) / (1 << pcog.lits);
		}
		sim *= 0.5;
		cur.splitvar = -1;
		cur.rule = "B12";
		cur.sim = sim;
		break;

	case -12: //B12: we apply B3 on a child and B4 on the other
		sv = f.varid[sv];
		cofactor(f, g, pcof, pcog, ncof, ncog, sv);
		if (pcog.empty()) {
			sim = 1 - ((float) onset(pcof) / (1 << pcof.lits));
			sim += (float) onset(ncof) / (1 << ncof.lits);
		} else {
			sim = 1 - ((float) onset(ncof) / (1 << ncof.lits));
			sim += (float) onset(pcof) / (1 << pcog.lits);
		}
		sim *= 0.5;
		cur.splitvar = -1;
		cur.rule = "B12";
		cur.sim = sim;
		break;

	case 13: //U13: prune one kid by applying B1
		sv = f.varid[sv];
		cur.splitvar = sv;
		cur.rule = "split";
		cofactor(f, g, pcof, pcog, ncof, ncog, sv);
		if (prune == 2)
			// Covers are positive unate no DCs on sv. Prune right kid
			sim = similarity(pcof, pcog, levelid + 1, 2 * nodeid -1);
		else
			// Covers are negative unate no DCs on sc. Prune left kig
			sim = similarity(ncof, ncog, levelid + 1, 2 * nodeid);
		sim = 0.5 * (1 + sim);
		cur.sim = sim;
		break;

	case 15:  //U15: prune one kid by applying B3
		sv = f.varid[sv];
		cofactor(f, g, pcof, pcog, ncof, ncog, sv);
		if (prune == 2) {
			// Cover f is positive unate no DCs on sv. Prune right kid
			sim = similarity(pcof, pcog, levelid + 1, 2 * nodeid -1);
			sim += 1 - ((float) onset(ncog) / (1 << ncog.lits));
		} else {
			// Cover f is negative unate no DCs on sc. Prune left kid
			sim = similarity(ncof, ncog, levelid + 1, 2 * nodeid);
			sim += 1 - ((float) onset(pcog) / (1 << pcog.lits));
		}
		sim *= 0.5;
		cur.splitvar = sv;
		cur.rule = "split";
		cur.sim = sim;
		break;

	case -15: //U15: prune one kid by applying B3
		sv = f.varid[sv];
		cofactor(f, g, pcof, pcog, ncof, ncog, sv);
		if (prune == 2) {
			// Cover g is positive unate no DCs on sv. Prune right kid
			sim = similarity(pcof, pcog, levelid + 1, 2 * nodeid -1);
			sim += 1 - ((float) onset(ncof) / (1 << ncof.lits));
		} else {
			// Cover f is negative unate no DCs on sc. Prune left kid
			sim = similarity(ncof, ncog, levelid + 1, 2 * nodeid);
			sim += 1 - ((float) onset(pcof) / (1 << pcof.lits));
		}
		sim *= 0.5;
		cur.splitvar = sv;
		cur.rule = "split";
		cur.sim = sim;
		break;

	default:
		sv = pick_binate(f, g);
		sv = f.varid[sv];
		cur.splitvar = sv;
		cur.rule = "split";
		cofactor(f, g, pcof, pcog, ncof, ncog, sv);
		sim = 0.5 * (similarity(pcof, pcog, levelid + 1, 2 * nodeid -1) +
			     similarity(ncof, ncog, levelid + 1, 2 * nodeid));
		cur.sim = sim;
		break;
	}

	out[levelid].add_node(cur);

	if (use_verb) {
		printplas p;
		p.print(levelid + 1, nodeid, f, g);
	}

	return sim;
}


float ufs::simeval(const cover &f, const cover &g)
{
	/* Recursive function */
	level lev;
	add_level(lev);

	return similarity(f, g, 0, 1);
}
