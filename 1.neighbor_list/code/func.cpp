#include <vector>
#include <initializer_list>
#include <cmath>
#include <stdio.h>

#include "func.h"


// 1. Constructor
basicfunc::Particle::Particle(const std::initializer_list<double> &lst) {
    this->coord[0] = *(lst.begin());
    this->coord[1] = *(lst.begin() + 1);
    this->coord[2] = *(lst.begin() + 2);
}


// 1. Constructor
basicfunc::VerletList::VerletList(double cutoff) : cutoff(cutoff) {}


// 2. add_particle
void basicfunc::VerletList::add_particle(const Particle &p) {
    this->particles.push_back(p);
}


// 3. get_distances
double basicfunc::VerletList::get_distance(const Particle &p1, const Particle &p2) const {
    double dx = p2.coord[0] - p1.coord[0];
    double dy = p2.coord[1] - p2.coord[1];
    double dz = p2.coord[2] - p2.coord[2];

    return std::sqrt(dx*dx + dy*dy + dz*dz);
}


// 4. build lists
void basicfunc::VerletList::build_lists() {
    // Step 1. Initialize
    int num_particles = this->particles.size();
    this->lists.resize(num_particles);
    for (int i=0; i<num_particles; i++) {
        this->lists[i].clear();
    }

    // Step 2. Populate the lists
    for (int i=0; i<num_particles; i++) {
        for (int j=i+1; j<num_particles; j++) {
            if ( this->get_distance(this->particles[i], this->particles[j]) < this->cutoff ) {
                this->lists[i].push_back(j);
                this->lists[j].push_back(i);

            }
        }
    }
}


// 5. print_lists
void basicfunc::VerletList::print_lists() {
    for (int i=0; i<this->lists.size(); i++) {
        printf("%d: ", i);
        for (int j=0; j<this->lists[i].size(); j++) {
            printf("%d, ", this->lists[i][j]);
        }
        printf("\n");
    }
}