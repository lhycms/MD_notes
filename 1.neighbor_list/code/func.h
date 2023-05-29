#pragma once
#include <initializer_list>
#include <vector>

namespace mdutils {
    class Particle {
    public:
        double x, y;

    // 1. Constructor
    Particle(std::initializer_list<double> lst);
    };


    class LinkedCellList {
    private:
        double box_size_x, box_size_y;
        double cell_size;
        int num_cell_x, num_cell_y;
        std::vector<Particle> particles;
        std::vector<int> head_lst;
        std::vector<int> next_lst;

    public:
        // 1. Constructor
        LinkedCellList(double box_size_x, double box_size_y, double cell_size);

        // 2. add_particle()
        void add_particle(const Particle &p);

        // 3. get_cell_index()
        int get_cell_index(const Particle &p) const;

        // 4. wrap_cell_index()
        void wrap_cell_index(int &cell_ix, int &cell_iy);

        // 5. build_list()
        void build_list();

        // 6. get_nbr_cells(int cell_index);
        std::vector<int> get_nbr_cells(int cell_index);

        // 7. get_particles_inside_cell()
        std::vector<int> get_particles_inside_cell(int cell_index);
    };

}
