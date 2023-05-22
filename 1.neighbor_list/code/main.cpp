#include <stdio.h>
#include <vector>
#include <initializer_list>
#include <cmath>


struct Particle {
    double coord[3];

    Particle(std::initializer_list<double> lst) {
        this->coord[0] = *(lst.begin());
        this->coord[1] = *(lst.begin()+1);
        this->coord[2] = *(lst.begin()+2);
    }
};


class VerletList {
private:
    double cutoff;
    std::vector<Particle> particles;
    std::vector<std::vector<int>> lists;

public:
    // 1. Constructor
    VerletList(double cutoff) : cutoff(cutoff) {}

    // 2. add particle
    void add_particle(const Particle &p) {
        this->particles.push_back(p);
    }

    // 3. get distance
    const double get_distance(const Particle &p1, const Particle &p2) const {
        double dx = p2.coord[0] - p1.coord[0];
        double dy = p2.coord[1] - p1.coord[1];
        double dz = p2.coord[2] - p2.coord[2];

        return std::sqrt(dx*dx + dy*dy + dz*dz);
    }

    // 4. build lists
    void build_lists() {
        int num_particles = this->particles.size();
        this->lists.resize(num_particles);
        for (int i=0; i<num_particles; i++) {
            this->lists[i].clear();
        }

        for (int i=0; i<num_particles; i++) {
            for (int j=i+1; j<num_particles; j++) {
                if ( this->get_distance(this->particles[i], this->particles[j]) < this->cutoff ) {
                    this->lists[i].push_back(j);
                    this->lists[j].push_back(i);
                }
            }
        }
    }

    // 5. print lists
    void print_lists() {
        for (int i=0; i<this->particles.size(); i++) {
            printf("%d: ", i);
            for (int j=0; j<this->lists[i].size(); j++) {
                printf("%d, ", this->lists[i][j]);
            }
            printf("\n");
        }
    }

};



int main() {
    Particle p1 = {0., 0., 0.};
    Particle p2 = {1., 1., 1.};
    Particle p3 = {2., 2., 2.};

    VerletList vl(2.);
    vl.add_particle(p1);
    vl.add_particle(p2);
    vl.add_particle(p3);

    vl.build_lists();
    vl.print_lists();

    return 0;
}