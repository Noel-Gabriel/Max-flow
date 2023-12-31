/* gen_maxflow_typedef.h == Type definitions for a directed graph 
                            for generators */
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
#ifndef GEN_MAXFLOW_TYPE_H
#define GEN_MAXFLOW_TYPE_H


namespace generators {
	
	namespace genrmf {
		/*==================================================================*/
		typedef struct VERTEX{
	
			struct EDGE ** edgelist;  /* Pointer to the list of pointers to 
								 		the adjacent edges. 
								 		(No matter that to or from edges) */

			struct EDGE ** current;   /* Pointer to the current edge */

			int degree;        /* Number of adjacent edges (both direction) */
			int index;
		}vertex;

		/*==================================================================*/
		typedef struct EDGE{
			int from;
			int to;
			int cap;        /* Capacity */
		}edge;

		/*==================================================================*/
		typedef struct NETWORK{

			struct NETWORK	* next, * prev;

			int vertnum;
			int edgenum;

			vertex	* verts; /* Vertex array[1..vertnum] */
			edge    * edges; /* Edge array[1..edgenum] */

			int source; /* Pointer to the source */
			int sink;   /* Pointer to the sink */
		}network;
	}
}

#endif 

