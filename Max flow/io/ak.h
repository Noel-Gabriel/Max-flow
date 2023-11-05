#ifndef AK_H
#define AK_H

/* generator of hard maxflow problems */
/* 01/09/94 - Stanford Computer Science Department */
/* Boris Cherkassky - cher@theory.stanford.edu, on.cher@zib-berlin.de */
/* Andrew V. Goldberg - goldberg@cs.stanford.edu */

// http://www.informatik.uni-trier.de/~naeher/Professur/research/generators/maxflow/ak/

// translated to C++ and to be able to write to files

#include <iostream>

/**
 * @brief Generates "hard" max flow problem using A. V. Goldberg's and
 *        B. Cherkassky's ak generator.
 * 
 * @param n 
 */
void generate_hard_problem(std::string, int n);

#endif