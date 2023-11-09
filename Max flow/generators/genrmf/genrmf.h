#ifndef GENRMF_H
#define GENRMF_H

/*

    Implemented in genmain.cpp, not genrmf.cpp (I kept the original file names)

    original files: http://www.informatik.uni-trier.de/~naeher/Professur/research/generators/maxflow/genrmf/
    translated to C++ and changed a few things to integrate the generator into my project

*/
namespace generators {
    
    namespace genrmf {

        /**
         * @brief Generate a max flow problem using the genrmf generator.
         * 
         * @param a Frame size.
         * @param b Depth.
         * @param c1 min capacity.
         * @param c2 max capacity.
         * @param seed Seed for the random capacities.
         */
        void generate(int a, int b, int c1, int c2, int seed=-1);

    }
}

#endif