#include "../algorithms/random.h"

#include <random>

namespace algorithms {
    
    namespace utils {

        Random::Random(unsigned int seed) 
            : m_generator(seed)
            , m_seed{seed} {}

        Random::Random() {
            std::random_device rd;
            m_seed = rd();
            m_generator.seed(m_seed);
        }

        int Random::random_num_in_range(int l, int h) {
            std::uniform_int_distribution<> distr(l, h);
            return distr(m_generator);
        }
    }
}