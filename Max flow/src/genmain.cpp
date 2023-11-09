/* genrmf maxflow input generator */

// original files: http://www.informatik.uni-trier.de/~naeher/Professur/research/generators/maxflow/genrmf/
// translated to C++ and changed a few things to integrate the generator into my project

#include "../generators/genrmf/gen_maxflow_typedef.h"
#include "../algorithms/random.h"

#include <iostream>
#include <string>
#include <fstream>


namespace generators {

	namespace genrmf {

		void gen_free_net(network * n);
		void print_max_format (std::ofstream& path, network * n, int dim);
		network * gen_rmf(int a, int b, int c1, int c2, algorithms::utils::Random& rand);


		/**
         * @brief Generate a max flow problem using the genrmf generator.
         * 
         * @param a Frame size.
         * @param b Depth.
         * @param c1 min capacity.
         * @param c2 max capacity.
         * @param seed Seed for the random capacities.
         */
		void generate(int a, int b, int c1, int c2, int seed) {
			using std::to_string;
  			network * n;
			// Initialize random number generator
			algorithms::utils::Random rand;
			if(seed <= -1) {
				rand = algorithms::utils::Random();
			} else {
				rand = algorithms::utils::Random(seed);
			}
			// where to save the graph
			std::string path{"test graphs/genrmf/"};
  			std::ofstream file(path + "genrmf" + to_string(a) + "x" + to_string(b) + "-" + to_string(c1) + "-" 
				+ to_string(c2) + "-s" + to_string(rand.get_seed()) + ".dimacs");

			// generate network
  			n = gen_rmf(a, b, c1, c2, rand);

  			file << "c This file was generated by genrmf.\n";
  			file << "c params: a: " + to_string(a) + " b: " + to_string(b) + " c1: " + to_string(c1) 
				+ " c2: " + to_string(c2) + " seed: " + to_string(rand.get_seed()) + "\n";
  
			// write to file in .dimacs format
  			print_max_format(file, n, 1);

			// delete network
  			gen_free_net(n);

			file.close();
		}
	}
}
