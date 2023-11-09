/* I/O routines for DIMACS standard format generator */
/*
   Implemented by 
   Tamas Badics, 1991, 
   Rutgers University, RUTCOR
   P.O.Box 5062
   New Brunswick, NJ, 08903
 
   e-mail: badics@rutcor.rutgers.edu
*/

// original files: http://www.informatik.uni-trier.de/~naeher/Professur/research/generators/maxflow/genrmf/
// translated to C++ and changed a few things to integrate the generator into my project


#include <fstream>
#include "../generators/genrmf/gen_maxflow_typedef.h"

namespace generators {

	namespace genrmf {


		/*===============================================================*/
		void gen_free_net(network * n)
		{
			free(n->edges);
			free(n);
		}

		/*================================================================*/
		/* prints a network heading with 
		   dim lines of comments
			no \n needs at the ends )*/
		void print_max_format (std::ofstream& file, network * n, int dim) {
			using std::to_string;
			int i, vnum, e_num;
			edge * e;

			vnum = n->vertnum;
			e_num = n->edgenum;
	
			file << "p max " + to_string(vnum) + " " + to_string(e_num) + "\n";
			file << "n " + to_string(n->source) + " s\n";
			file << "n " + to_string(n->sink) + " t\n";

			for (i = 1; i <= e_num; i++) {
				e = &n->edges[i];
				file << "a " + to_string(e->from) + " " + to_string(e->to) + " " + to_string(e->cap) + "\n";
			}
		}
	}
}

