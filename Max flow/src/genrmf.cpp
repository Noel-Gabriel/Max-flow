/************************* Original comment ************************/
			
/* maxflow generator in DIMACS format */
/*
   Implemented by 
   Tamas Badics, 1991, 
   Rutgers University, RUTCOR
   P.O.Box 5062
   New Brunswick, NJ, 08903
 
   e-mail: badics@rutcor.rutgers.edu
*/
/*
GENRMF -- Maxflow generator in DIMACS format.

Files: genio.c genrmf.c genmain.c  genio.h 
	   gen_maxflow_typedef.h  math_to_gcc.h
	   makefile

Compilation: Simply type make.

Usage: genrmf [-out out_file]
              -a frame_size -b depth
              -c1 cap_range1 -c2 cap_range2

		Here without the -out option the generator will
		write to stdout.

		The generated network is as follows:
			It has b pieces of frames of size (a x a).
			(So alltogether the number of vertices is a*a*b)
			
			In each frame all the vertices are connected with 
			their neighbours. (forth and back)
			In addition the vertices of a frame are connected
			one to one with the vertices of next frame using 
			a random permutation of those vertices.

			The source is the lower left vertex of the first frame,
			the sink is the upper right vertex of the b'th frame. 
                         t
				+-------+
				|	   .|
				|	  .	|
             /  |    /  |
			+-------+/ -+ b
			|    |  |/.
		  a |   -v- |/
            |    |  |/
		    +-------+ 1
           s    a

			The capacities are randomly chosen integers
			from the range of (c1, c2) in the case of interconnecting
			edges, and c2 * a * a for the in-frame edges.
 
This generator was used by U. Derigs & W. Meier (1989)
in the article "Implementing Goldberg's Max-Flow-Algorithm
				A Computational Investigation"
ZOR - Methods & Models of OR (1989) 33:383-403
*/

/*********************************************/


// original files: http://www.informatik.uni-trier.de/~naeher/Professur/research/generators/maxflow/genrmf/
// translated to C++ and changed a few things to integrate the generator into my project

#include "../generators/genrmf/gen_maxflow_typedef.h"
#include "../algorithms/random.h"

#include <vector>
#include <iostream>

namespace generators {

	namespace genrmf {

		/*==================================================================*/
		void make_edge(int from, int to, int c1, int c2, int& Ec, network* N, algorithms::utils::Random& rand) {
			Ec++;
			N->edges[Ec].from = from;
			N->edges[Ec].to = to;
			N->edges[Ec].cap = rand.random_num_in_range(c1, c2);
		}

		/*==================================================================*/
		void permute(int AA, std::vector<int>& Parr, algorithms::utils::Random& rand) {
			int i, j, tmp;
	
			for (i = 1; i < AA; i++){
				j = rand.random_num_in_range(i, AA);
				tmp = Parr[i];
				Parr[i] = Parr[j];
				Parr[j] = tmp;
			} 
		}

		/*==================================================================*/
		void connect(int offset, int cv, int x1, int y1, int C2AA, int& Ec, int A, network* N){
			int cv1;
			cv1 = offset + (x1 - 1) * A + y1;
			Ec++;
			N->edges[Ec].from = cv;
			N->edges[Ec].to = cv1;
			N->edges[Ec].cap = C2AA;
		}

		/*==================================================================*/
		/* generates a network with 
								 a*a*b nodes and 6a*a*b-4ab-2a*a edges
								 random_frame network:
								 Derigs & Meier
								 Methods & Models of OR (1989) 
								 33:383-403 */
		network * gen_rmf(int a, int b, int c1, int c2, algorithms::utils::Random& rand) {
			int x, y, z, offset, cv;
	
			int A = a;
			int AA = a*a;
			int C2AA = c2*AA;
			int Ec = 0;
	
			network* N = (network *)malloc(sizeof(network));
			N->vertnum = AA * b;
			N->edgenum = 5*AA*b-4*A*b-AA; 
			N->edges =(edge *)calloc(N->edgenum + 1, sizeof(edge));
			N->source = 1;
			N->sink   = N->vertnum;

			std::vector<int> Parr(AA+1);
	
			for (x = 1; x <= AA; x++) {
	  			Parr[x] = x;
			}
	
			for( z = 1; z <= b; z++) {
				offset = AA * (z-1);
				if (z != b) {
		  			permute(AA, Parr, rand);
				}
	
				for( x = 1; x <= A; x++){ 
					for( y = 1; y <= A; y++){
						cv = offset + (x - 1) * A + y;
						if (z != b) {
				  			make_edge(cv, offset + AA + Parr[cv - offset]  
							,c1, c2, Ec, N, rand);   /* the intermediate edges */
						}
				
						if (y < A) connect(offset, cv, x, y + 1, C2AA, Ec, A, N);
						if (y > 1) connect(offset, cv, x, y - 1, C2AA, Ec, A, N);
						if (x < A) connect(offset, cv, x + 1, y, C2AA, Ec, A, N);
						if (x > 1) connect(offset, cv, x - 1, y, C2AA, Ec, A, N);
					}
				}
			}
			return N;
		}		
	}
}


