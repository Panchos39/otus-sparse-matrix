#include <gtest/gtest.h>

#include "sparse_matrix.h"

TEST(SparseMatrix, start_size) {
    otus_sparse_matrix::SparseMatrix<int, -1, 2> matrix;
    ASSERT_EQ(matrix.size(), 0);
}

TEST(SparseMatrix, getting_missed_element) {
    otus_sparse_matrix::SparseMatrix<int, -1, 2> matrix;
    auto a = matrix[0][0];
    ASSERT_EQ(a, -1);
}

TEST(SparseMatrix, assign_element) {
    otus_sparse_matrix::SparseMatrix<int, -1, 2> matrix;
    matrix[100][100] = 314;
    ASSERT_EQ(matrix[100][100], 314);
}

TEST(SparseMatrix, matrix_size_after_adding) {
    otus_sparse_matrix::SparseMatrix<int, -1, 2> matrix;
    matrix[100][100] = 314;
    ASSERT_EQ(matrix.size(), 1);
}

TEST(SparseMatrix, canonical_assign_element) {
    otus_sparse_matrix::SparseMatrix<int, -1, 2> matrix;
    ((matrix[100][100] = 314) = 0) = 217;
    ASSERT_EQ(matrix[100][100], 217);
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
