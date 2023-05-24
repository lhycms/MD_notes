#include "func.h"


int main() {
    basicfunc::VerletList vl(2.);
    basicfunc::Particle p1 = {0., 0., 0.};
    basicfunc::Particle p2 = {1., 1., 1.};
    basicfunc::Particle p3 = {2., 2., 2.};

    vl.add_particle(p1);
    vl.add_particle(p2);
    vl.add_particle(p3);

    vl.build_lists();
    vl.print_lists();

    return 0;
}