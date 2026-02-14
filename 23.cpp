// Use Eigen3 to perform SVD on a dense matrix and reconstruct it. 

// A Dense Matrix is one where most of the entries are non-zero, or at least, the    computer is instructed to store a value for every single coordinate (i,j).
// SVD: Singular Value Decomposition ::It factorizes any matrix A (even non-square ones!) into three specific parts:
// A=UΣV^T
// U: Left singular vectors (Unitary/Orthogonal).
// Σ: A diagonal matrix of Singular Values (non-negative real numbers). In physics   , these represent the "strength" or "importance" of specific modes.
// V^T: Right singular vectors (Unitary/Orthogonal).
// Reconstruction is the act of multiplying those three pieces (U,Σ,VT) back toget   her to see if you get the original matrix A again.

#include <iostream>
#include <Eigen/Dense>

int main() {
    // Define a 3x2 Dense Matrix (Physics example: maybe 3 coordinates, 2 time steps)
    Eigen::MatrixXd A(3, 2);
    A << 1, 2,
         3, 4,
         5, 6;
    // MatrixXd --> Matrix is a 2D grid, X -> dynaminc(not fixed size). d-> double. Other types are -- Matrix3f, Matrix4d, VectorXd . Matrix3d is strored on a stack. MatrixXd is stored on the heap.Used malloc to grab a block of memory.
    // 1. Perform SVD
    // ComputeThinU and ComputeThinV are faster and sufficient for reconstruction
    Eigen::JacobiSVD<Eigen::MatrixXd> svd(A, Eigen::ComputeThinU | Eigen::ComputeThinV);

    Eigen::MatrixXd U = svd.matrixU();
    Eigen::VectorXd s = svd.singularValues();
    Eigen::MatrixXd V = svd.matrixV();

    // 2. Reconstruction: A_rect = U * Sigma * V^T
    // We must turn the vector 's' into a diagonal matrix first
    Eigen::MatrixXd A_rect = U * s.asDiagonal() * V.transpose();

    std::cout << "Original Matrix:\n" << A << "\n\n";
    std::cout << "Reconstructed Matrix:\n" << A_rect << "\n";

    return 0;
}

// I don't understand this properly, nor do I know the the use case of this. Got to get back to it.

