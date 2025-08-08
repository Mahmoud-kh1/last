 // to calc mst number mat[i][i] = number of degree , mat[i][j] = -1 if there is edge between i, j else it's 0

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
 
using namespace std;

double determinant(vector<vector<double>> matrix) {
    int n = matrix.size();
    double det = 1.0;
    int sign = 1;
    const double EPS = 1e-12;  // Tolerance for floating-point comparison

    // Create a copy of the matrix to avoid modifying original
    vector<vector<double>> mat = matrix;

    // Check if matrix is square
    for (const auto& row : mat) {
        if (row.size() != n) {
            throw invalid_argument("Matrix must be square");
        }
    }

    // Perform Gaussian elimination with partial pivoting
    for (int col = 0; col < n; ++col) {
        // Find pivot row (row with largest element in current column)
        int pivot_row = col;
        for (int i = col + 1; i < n; ++i) {
            if (abs(mat[i][col]) > abs(mat[pivot_row][col])) {
                pivot_row = i;
            }
        }

        // Swap rows if necessary
        if (pivot_row != col) {
            swap(mat[col], mat[pivot_row]);
            sign *= -1;  // Each row swap changes the sign of determinant
        }

        // Check for singular matrix
        if (abs(mat[col][col]) < EPS) {
            return 0.0;
        }

        // Elimination step
        for (int i = col + 1; i < n; ++i) {
            double factor = mat[i][col] / mat[col][col];
            for (int j = col + 1; j < n; ++j) {
                mat[i][j] -= factor * mat[col][j];
            }
        }
    }

    // Calculate determinant from diagonal elements
    for (int i = 0; i < n; ++i) {
        det *= mat[i][i];
    }

    return sign * det;
}

int main() {
    // Test matrix (determinant = -240)
    vector<vector<double>> matrix = {
        {4, 3, 2, 2},
        {0, 1, -3, 3},
        {0, -1, 3, 3},
        {0, 3, 1, 1}
    };

    try {
        double det = determinant(matrix);
        cout << "Determinant: " << det << endl;  // Output: -240
    } catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
