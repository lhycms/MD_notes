#include <stdio.h>
#include "func.h"


int main() {
    double box_size_x = 10;
    double box_size_y = 10;
    double cell_size = 5;

    mdutils::Particle p0 = {6., 9.};
    mdutils::Particle p1 = {4.4, 3};
    mdutils::Particle p2 = {7.5, 6};
    mdutils::Particle p3 = {3.5, 2};
    mdutils::Particle p4 = {6, 3.7};
    mdutils::Particle p5 = {8.5, 2};
    mdutils::Particle p6 = {9, 9};
    mdutils::Particle p7 = {1, 4};

    mdutils::LinkedCellList lcl(box_size_x, box_size_y, cell_size);
    lcl.add_particle(p0);
    lcl.add_particle(p1);    
    lcl.add_particle(p2);
    lcl.add_particle(p3);
    lcl.add_particle(p4);
    lcl.add_particle(p5);
    lcl.add_particle(p6);
    lcl.add_particle(p7);
    lcl.build_list();

    std::vector<int> particles_inside_cell = lcl.get_particles_inside_cell(3);
    for (int i: particles_inside_cell) {
        printf("%d, ", i);
    }
    printf("\n");

}