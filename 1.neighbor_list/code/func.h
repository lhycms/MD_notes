#ifndef FUNC_H
#define FUNC_H

#include <vector>
#include <initializer_list>

namespace basicfunc {
    class Particle {
    public:
        double coord[3];

        // 1. Constructor
        Particle(const std::initializer_list<double> &lst);
    };


    class VerletList {
    private:
        double cutoff;
        std::vector<Particle> particles;
        std::vector<std::vector<int>> lists;
    
    public:
        // 1. Constructor
        VerletList(double cutoff);

        // 2. add_particle
        void add_particle(const Particle &p);

        // 3. get_distance
        double get_distance(const Particle &p1, const Particle &p2) const;

        // 4. build lists
        void build_lists();

        // 5. print lists
        void print_lists();
    };

}

#endif