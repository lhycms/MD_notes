#include <stdio.h>
#include <cmath>
#include <vector>


struct Particle {
    double x, y;
};


class LinkedCellList {
public:
    double boxSizeX, boxSizeY;
    double cellSize;
    int numCellX, numCellY;
    std::vector<Particle> particles;
    std::vector<int> head_lst;  // Store the max index of particle inside the cell
    std::vector<int> next_lst;  // Store the smaller index for the particle

    // 1. Constructor
    LinkedCellList(double box_size_x, double box_size_y, double cell_size) 
        : boxSizeX(box_size_x), boxSizeY(box_size_y), cellSize(cell_size) 
    {
        this->numCellX = std::ceil(this->boxSizeX / this->cellSize);
        this->numCellY = std::ceil(this->boxSizeY / this->cellSize);
    }


    // 2. add particle
    void addParticle(Particle &particle) {
        this->particles.push_back(particle);
    }


    // 3. wrap around for central cell
    void wrap_cell_index(int &cell_ix, int &cell_iy) {
        cell_ix = std::fmod(cell_ix+this->numCellX, this->numCellX);
        cell_iy = std::fmod(cell_iy+this->numCellY, this->numCellY);
    }


    // 4. getNbrCellIndices
    const std::vector<int> getNbrCellIndices(int cell_index) {
        std::vector<int> nbr_cell_indices;

        int cell_ix = std::fmod(cell_index, this->numCellX);
        int cell_iy = cell_index / this->numCellY;

        for (int dy=-1; dy<=1; dy++) {
            for (int dx=-1; dx<=1; dx++) {
                int cell_nx = cell_ix + dx;
                int cell_ny = cell_iy + dy;
                this->wrap_cell_index(cell_nx, cell_ny);

                int nbrCellIndex = cell_nx + cell_ny*this->numCellX;
                nbr_cell_indices.push_back(nbrCellIndex);
            }
        }
        return nbr_cell_indices;
    }


    // 5. Get cell index for given particle
    const int getCellIndex(Particle &particle) const {
        int cell_ix = std::floor(particle.x / this->cellSize);
        int cell_iy = std::floor(particle.y / this->cellSize);
        return cell_ix + cell_iy*this->numCellX;
    }


    // 6. build list
    void buildList() {
        // Step 1. Initilizer arrays
        int num_cells = this->numCellX * this->numCellY;
        this->head_lst.resize(num_cells, -1);
        this->next_lst.resize(this->particles.size(), -1);

        // Step 2. populate the arrays
        for (int i=0; i<this->particles.size(); i++) {
            int cell_index = this->getCellIndex(this->particles[i]);
            this->next_lst[i] = this->head_lst[cell_index];
            this->head_lst[cell_index] = i;
        }
    }

    // 7. Get particles inside specific cell
    const std::vector<int> getParticlesInsideCell(int cell_index) {
        std::vector<int> particleIncides;

        int start = this->head_lst[cell_index];
        while (start != -1) {   // Starting search inside cell
            particleIncides.push_back(start);
            start = this->next_lst[start];
        }

        return particleIncides;
    }


    // 8. Find neighbor particles for specific central particle
    

};


int main() {
    double box_size_x = 10;
    double box_size_y = 10;
    double cell_size = 5;

    Particle p0 = {6., 9.};
    Particle p1 = {4.4, 3};
    Particle p2 = {7.5, 6};
    Particle p3 = {3.5, 2};
    Particle p4 = {6, 3.7};
    Particle p5 = {8.5, 2};
    Particle p6 = {9, 9};
    Particle p7 = {1, 4};

    LinkedCellList lcl(box_size_x, box_size_y, cell_size);
    lcl.addParticle(p0);
    lcl.addParticle(p1);    
    lcl.addParticle(p2);
    lcl.addParticle(p3);
    lcl.addParticle(p4);
    lcl.addParticle(p5);
    lcl.addParticle(p6);
    lcl.addParticle(p7);
    lcl.buildList();

    std::vector<int> particles_inside_cell = lcl.getParticlesInsideCell(3);
    for (int i: particles_inside_cell) {
        printf("%d, ", i);
    }
    printf("\n");


    return 0;
}