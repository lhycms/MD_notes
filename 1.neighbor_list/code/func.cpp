#include <initializer_list>
#include <vector>
#include <cmath>
#include <stdio.h>

#include "func.h"


// 1. Constructor
mdutils::Particle::Particle(std::initializer_list<double> lst) {
    this->x = *(lst.begin());
    this->y = *(lst.begin() + 1);
}


// 1. Constructor
mdutils::LinkedCellList::LinkedCellList(double box_size_x, double box_size_y, double cell_size)
    : box_size_x(box_size_x), box_size_y(box_size_y), cell_size(cell_size)
{
    this->num_cell_x = std::ceil(this->box_size_x / this->cell_size);
    this->num_cell_y = std::ceil(this->box_size_y / this->cell_size);
}


// 2. add_particle()
void mdutils::LinkedCellList::add_particle(const Particle &p) {
    this->particles.push_back(p);
}


// 3. get_cell_index()
int mdutils::LinkedCellList::get_cell_index(const Particle &p) const {
    int cell_ix = std::floor(p.x / this->cell_size);
    int cell_iy = std::floor(p.y / this->cell_size);

    return cell_ix + cell_iy * this->num_cell_x;
}


// 4. wrap_cell_index()
void mdutils::LinkedCellList::wrap_cell_index(int &cell_ix, int &cell_iy) {
    cell_ix = std::fmod(cell_ix + this->num_cell_x, this->num_cell_x);
    cell_iy = std::fmod(cell_iy + this->num_cell_y, this->num_cell_y);
}


// 5. get_nbr_cell_indices()
std::vector<int> mdutils::LinkedCellList::get_nbr_cell_indices(int cell_index) {
    std::vector<int> nbr_cell_indices;
    int cell_ix = std::fmod(cell_index, this->num_cell_x);
    int cell_iy = cell_index / this->num_cell_x;

    for (int dy=-1; dy<=1; dy++) {
        for (int dx=-1; dx<=1; dx++) {
            int cell_nx = cell_ix + dx;
            int cell_ny = cell_iy + dy;

            this->wrap_cell_index(cell_nx, cell_ny);
            int nbr_cell_index = cell_nx + cell_ny * this->num_cell_x;
            nbr_cell_indices.push_back(nbr_cell_index);
        }
    }
    return nbr_cell_indices;
}


// 6. build_list()
void mdutils::LinkedCellList::build_list() {
    int num_cell = this->num_cell_x * this->num_cell_y;
    this->head_lst.resize(num_cell, -1);
    this->next_lst.resize(this->particles.size(), -1);

    for (int i=0; i<this->particles.size(); i++) {
        int cell_index = this->get_cell_index(this->particles[i]);
        this->next_lst[i] = this->head_lst[cell_index];
        this->head_lst[cell_index] = i;
    }
}


// 7. get_particles_inside_cell()
std::vector<int> mdutils::LinkedCellList::get_particles_inside_cell(int cell_index) {
    std::vector<int> particles_inside_cell;

    int start = this->head_lst[cell_index];
    while (start != -1) {
        particles_inside_cell.push_back(start);
        start = this->next_lst[start];
    }

    return particles_inside_cell;
}