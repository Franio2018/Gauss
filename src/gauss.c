#include "gauss.h"

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b){

    if (mat == NULL || b == NULL || mat->r != mat->c || mat->r != b->r || b->c != 1) {
        fprintf(stderr, "Invalid matrix dimensions or NULL pointers.\n");
        return 1;
    }

    int n = mat->r;

    for (int k = 0; k < n; ++k) {
        // Find the pivot element
        int maxRow = k;
        for (int i = k + 1; i < n; ++i) {
            if (fabs(mat->data[i][k]) > fabs(mat->data[maxRow][k])) {
                maxRow = i;
            }
        }

        // Swap the rows in mat and b
        if (fabs(mat->data[maxRow][k]) < 1e-10) {
            fprintf(stderr, "Matrix is singular or nearly singular.\n");
            return 1;
        }

        if (maxRow != k) {
            double *temp = mat->data[k];
            mat->data[k] = mat->data[maxRow];
            mat->data[maxRow] = temp;

            double tempB = b->data[k][0];
            b->data[k][0] = b->data[maxRow][0];
            b->data[maxRow][0] = tempB;
        }

        // Eliminate entries below the pivot
        for (int i = k + 1; i < n; ++i) {
            double factor = mat->data[i][k] / mat->data[k][k];

            mat->data[i][k] = 0.0; // Explicitly set to zero for clarity

            for (int j = k + 1; j < n; ++j) {
                mat->data[i][j] -= factor * mat->data[k][j];
            }

            b->data[i][0] -= factor * b->data[k][0];
        }
    }

    return 0; // Success
}

