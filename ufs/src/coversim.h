#include "ufs.h"
#include "tautology.h"

#ifndef __COVERSIM_H__
#define __COVERSIM_H__

/**
 * Rules for Function Similarity Evaluation
 *
 * TERMINATION RULES
 * B1:  Both covers are empty.
 * B2:  Both covers are a tautology.
 * B3:  f is empty.
 * B4:  f is a tautology.
 * B5:  f is empty and g is a tautology.
 * B6:  Both covers have a single cube.
 * B7:  f has a single cube and g has non
 *      intersecting cubes. (Requires the
 *      flag --single_disjoint or --multi_disjoint)
 * B8:  Both covers have multiple non intersecting
 *      cubes. (Requires the flag --multi_disjoint)
 * B9:  Both covers show single input dependence
 *      (same variable and same value)
 * B10: Both covers show single input dependence
 *      (same variable but different value)
 * B11: Both covers show single input dependence
 *      (different variables)
 * B12: f shows single input dependence
 *      (this rule does not terminate, but tells
 *       which is the next best slitting variable
 *       to terminate at the next step)
 *
 * UNATENESS
 * U13: Both covers are positive/negative unate
 *      on the same variable with no DCs. Prune the
 *      tree (B1 applies on a child).
 * U14: Both covers are unate on the same variable
 *      with no DCs, but one is positive, while the other
 *      is negative. This is a termination rule as well
 *      so try it first!
 * U15  f is positive/negative unate in a
 *      variable Xi with no Dcs. Pick Xi as splitting
 *      variable to einforce B3 for one child.
 *
 * Miscellaneus rules for potential speed up
 * M16: When a cover has less than X cubes, apply
 *      SCC(). (Requires flag "--scc X")
 *
 * Splitting variable choice
 * Try rules B12, U13-15 first.
 * Pick a binate variable to try to keep the tree
 * balanced, thus increasing the probability that
 * the simple rule B6 applies.
 *
 * Shannon decomposition:
 * At each level do:
 *  - sum of the similarities of children to obtain
 *    the similarity of the cofactors at the current
 *    level.
 *  - divide by two to report the similarity weight
 *    to the upper level. TODO: CHECK!!!
 */

class coversim {
public:

	coversim(bool b7, bool b8) {
		use_b7 = b7;
		use_b8 = b8;
	}
	/* Return rule to be applied or 0 */
	int check(const cover &f, const cover &g, bool b7, bool b8, int *sv);

private:
	bool use_b7, use_b8;
	int use_m14;

};

#endif /* __COVERSIM_H__ */
