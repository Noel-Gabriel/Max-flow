#ifndef RANDOM_H
#define RANDOM_H

#include <random>

namespace algorithms {

    namespace utils {

        /**
         * @brief Class to generate random numbers using the
         *        Marsenne Twister.
         */
        class Random {
            public:
                // uses std::random_device to set the seed
                Random();
                Random(unsigned int seed);

                /**
                 * @brief Generate a random number in [l, h].
                 * 
                 * @param l Lower bound.
                 * @param h Upper bound.
                 * @return int The random number generated.
                 */
                int random_num_in_range(int l, int h);
                unsigned int get_seed() { return m_seed; };

            private:
                std::mt19937 m_generator{};
                unsigned int m_seed{};
        };
    }
}

#endif