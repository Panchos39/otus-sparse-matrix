#ifndef OTUS_SPARSE_MATRIX_SPARSE_MATRIX_H
#define OTUS_SPARSE_MATRIX_SPARSE_MATRIX_H

#include <map>
#include <memory>
#include <indexer.h>

/*!
@file
@brief Заголовочный файл, содержащий шаблон класса SparseMatrix,
*/
namespace otus_sparse_matrix {

    /**
        * @class SparseMatrix
        * @brief Класс proxy для std::map, обеспечивающий функциональность
            разреженной матрицы
        * @tparam T тип данных, хранящийся в разряженной матрице
        * @tparam EmptyValue значение типа T, которое будет считаться не заполненным
             для разреженной матрицы
        * @tparam Dims количество измерений в матрице. По умолчанию 2 измерения.
    */
    template <typename T, T EmptyValue, int Dims=2>
    class SparseMatrix {
    private:
        std::map<std::array<int, Dims>, T> m_Container;/**<
        контейнер std::map для хранения значений разреженной матрицы */
        const T m_Default = EmptyValue;/**<
        константа с значением по умолчанию */
    public:
        using map_iterator = typename std::map<std::array<T, Dims>, T>::iterator;

        /**
            * @brief Перегрузка оператора [].
            * @param i индекс, который передается в оператор [].
            * @returns объект помощник Indexer, расширяющий возможности индексирования
            для многомерной разреженной матрицы.
        */
        Indexer<SparseMatrix, T, Dims> operator[](size_t i);

        /**
            * @brief Перегрузка оператора (), для возможности передачи сложного ключа подряд,
                через запятую
            * @tparam Args последовательность индексов для разреженной матрицы
            * @returns объект помощник Indexer, расширяющий возможности индексирования
            для многомерной разреженной матрицы.
        */
        template <typename ...Args>
        Indexer<SparseMatrix, T, Dims> operator()(Args... args);

        /**
            * @brief метод, предоставлюящий возможность установить значение элемента матрицы по ключу
                в явном виде
            * @param key массив размера Dims, содержащий в себе индексы по каждому измерению для
                конкретного элемента разреженной матрицы.
            * @param value значение типа T, которое нужно установить по ключу key
            * @returns итератор на объект внутреннего контейнера, которому было присвоено новое значение
        */
        map_iterator set(const std::array<T, Dims>& key, T value);

        /**
           * @brief метод, возвращающий значение элемента матрицы по ключу
               в явном виде
           * @param key массив размера Dims, содержащий в себе индексы по каждому измерению для
               конкретного элемента разреженной матрицы.
           * @returns возвращает ссылку на найденный элемент
       */
        const T& get(const std::array<T, Dims>& key);

        /**
           * @brief метод, возвращающий количество занятых ячеек матрицы
           * @returns количество занятых ячеек в матрицы
       */
        size_t size();

        /**
           * @brief метод, возвращающий итератор на начало внутреннего контейнера std::map
           * @returns итератор на начальный элемент внутреннего контейнера std::map
       */
        map_iterator begin();

        /**
           * @brief метод, возвращающий итератор на конец внутреннего контейнера std::map
           * @returns итератор на конец внутреннего контейнера std::map
       */
        map_iterator end();
    };


} // otus_sparse_matrix
#include "sparse_matrix.tpp"
#endif //OTUS_SPARSE_MATRIX_SPARSE_MATRIX_H
