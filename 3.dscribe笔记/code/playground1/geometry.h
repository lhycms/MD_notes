#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cmath>
#include <vector>
#include <stdexcept>
#include <pybind11/numpy.h>
#include <Eigen/Dense>

namespace py = pybind11;
using namespace Eigen;
using namespace std;


// 1. class -- ExtendedSystem
class ExtendedSystem {
public:
    py::array_t<double> positions;
    py::array_t<int> atomic_numbers;
    py::array_t<int> indices;
}


// 2. Functions for vector
std::vector<double> cross(const std::vector<double> &a, const std::vector<double> &b);
double dot(const std::vector<double> &a, const std::vector<double> &b);
double norm(const std::vector<double> &a);


/*
    * Used to periodically extend an atomic system in order to take into account
    * periodic copies beyond the given cell.
    * 
    * @ param positions Cartesian positions of the original system
    * @ param atomic_numbers Atomic numbers of the original system
    * @ param cell Unit cell of the original system
    * @ param pbc Periodic boundary conditions (array of three booleans) of the original system
    * @ param cutoff Radial cutoff value for determining extension size
*/
// 3. 
ExtendedSystem extend_system(
            py::array_t<double> positions,
            py::array_t<int> atomic_numbers,
            py::array_t<double> cell,
            py::array_t<bool> pbc,
            double cutoff);


/*
    * Used to calculate the full distance matrix (numpy) for given positions
    *
    * @param positions Cartesian positions in a <n_atoms, 3> array.
    * 
    * @return Pairwise distances in an <n_atoms, n_atoms> array.
*/
// 4. 
py::array_t<double> distanceNumpy(py::detail::unchecked_reference<double, 2> positions_u);


/*
    * Used to calculate the full distance matrix (eigen) for given positions
    *
    * @param positions Cartesian positions in a <n_atoms, 3> array.
    * 
    * @return Pairwise distances in an <n_atoms, n_atoms> array
*/
// 5. 


#endif