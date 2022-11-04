#include <iostream>

#include "sparse_matrix.h"

int main() {

    otus_sparse_matrix::SparseMatrix<int, 0, 2> target_matrix;

    // Заполнение матрицы диагональными элементами
    for (int i = 0; i < 10; ++i) {
        target_matrix[i][i] = i;
        target_matrix[i][10 - (i + 1)] = 10 - (i + 1);
    }

    // Вывод участка матрицы от [1, 1]  до  [8, 8]
    for (int i = 1; i < 9; ++i) {
        for (int j = 1; j < 9; ++j) std::cout << target_matrix[i][j] << ' ';
        std::cout << std::endl;
    }
    // Вывести количество занятых ячеек
    std::cout << target_matrix.size() << std::endl;

    // Вывести все занятые ячейки
    for(auto [key, value]: target_matrix) {
        auto [x, y] = key;
        std::cout << '[' << x << ',' << y << "] ->" << value << std::endl;
    }
    return 0;

}
