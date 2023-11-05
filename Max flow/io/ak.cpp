/* generator of hard maxflow problems */
/* 01/09/94 - Stanford Computer Science Department */
/* Boris Cherkassky - cher@theory.stanford.edu, on.cher@zib-berlin.de */
/* Andrew V. Goldberg - goldberg@cs.stanford.edu */

// translated to C++ and to be able to write to files

#include <iostream>
#include <fstream>

void generate_hard_problem(std::string path, int n) {
   using std::to_string;
   if(n < 2) { return; }
   std::ofstream file(path);
   file << "c very bad maxflow problem\n";
   file << "p max " + to_string(4*n+6) + " " + to_string(6*n+7) + "\n";
   file << "n 1 s\n";
   file << "n 2 t\n";
   // first horrible graph
   for (int i{0}; i < n; ++i)
   {
     file << "a "+to_string(i+3)+" "+to_string(i+4)+" "+to_string(n-i+1)+"\n";
     file << "a "+to_string(i+3)+" "+to_string(n+4)+" 1\n";
   }
   file << "a "+to_string(n+3)+" "+to_string(2*n+4)+" 1\n";
   file << "a "+to_string(n+3)+" "+to_string(n+4)+" 1\n";
   // second horrible graph
   for(int i{n+3}; i <= 2*n+2; ++i) {
      file << "a "+to_string(i+1)+" "+to_string(i+2)+" "+to_string(n+1)+"\n";
   }
   int d{2*n+4};
   for(int i{d}; i <= 2*n+d; ++i) {
      file << "a "+to_string(i+1)+" "+to_string(i+2)+" "+to_string(n)+"\n";
   }
   for(int i{0}; i < n; ++i) {
      file << "a "+to_string(i+d+1)+" "+to_string(2*n+2-i+d)+" 1\n";
   }
   // edges from source to sink
   file << "a 1 3 1000000\n";
   file << "a 1 "+to_string(d+1)+" 1000000\n";
   file << "a "+to_string(d)+" 2 1000000\n";
   file << "a "+to_string(4*n+6)+" 2 1000000";
}
