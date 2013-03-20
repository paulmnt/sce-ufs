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
 *      (same varible)
 * B10: Both covers show single input dependence
 *      (different variables)
 *
 * UNATENESS
 * U11: Both covers are positive/negative unate
 *      on the same variable with no DCs. Prune the
 *      tree.
 * U12: Both covers are unate on the same variable
 *      with no DCs, but one is positive, while the
 *      other is negative. Prune the tree.
 * U13  f is positive/negative unate in a
 *      variable Xi. Pick Xi as splitting variable
 *      to einforce B3 for one child.
 *
 * Miscellaneus rules for potential speed up
 * M14: When a cover has less than X cubes, apply
 *      SCC(). (Requires flag "--scc X")
 *
 * Splitting variable choice
 * Try rule U3 first.
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
	int check(const cover &f, const cover &g, bool b7, bool b8);

private:
	bool use_b7, use_b8;
	int use_m14;

};

#endif /* __COVERSIM_H__ */
