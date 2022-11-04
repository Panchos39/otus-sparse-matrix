#include "sparse_matrix.h"

namespace otus_sparse_matrix {

    template <typename T, T EmptyValue, int Dims>
    Indexer<SparseMatrix<T, EmptyValue, Dims>, T, Dims>
    SparseMatrix<T, EmptyValue, Dims>::operator[](size_t i) {
        return Indexer<SparseMatrix, T, Dims>(this, i);
    }

    template <typename T, T EmptyValue, int Dims>
    template <typename ...Args>
    Indexer<SparseMatrix<T, EmptyValue, Dims>, T, Dims>
    SparseMatrix<T, EmptyValue, Dims>::operator()(Args ...args) {
        return Indexer<SparseMatrix, T, Dims>(this, {size_t{args}...});
    }

    template <typename T, T EmptyValue, int Dims>
    typename SparseMatrix<T, EmptyValue, Dims>::map_iterator
    SparseMatrix<T, EmptyValue, Dims>::set(const std::array<T, Dims> &key, T value) {
        auto elem = m_Container.find(key);
        if (elem == m_Container.end()) {
            if (value != EmptyValue) {
                auto [elem, flag] = m_Container.emplace(key, value);
            }
            return elem;
        }

        if (value == EmptyValue) {
            m_Container.erase(elem);
            return elem;
        }
        elem->second = value;
        return elem;
    }

    template <typename T, T EmptyValue, int Dims>
    const T& SparseMatrix<T, EmptyValue, Dims>::get(const std::array<T, Dims> &key) {
        auto elem = m_Container.find(key);
        if (elem == m_Container.end()) {
            return m_Default;
        }
        return elem->second;

    }

    template <typename T, T EmptyValue, int Dims>
    size_t SparseMatrix<T, EmptyValue, Dims>::size() {
        return m_Container.size();
    }

    template <typename T, T EmptyValue, int Dims>
    typename SparseMatrix<T, EmptyValue, Dims>::map_iterator
    SparseMatrix<T, EmptyValue, Dims>::begin() {
        return m_Container.begin();
    }

    template <typename T, T EmptyValue, int Dims>
    typename SparseMatrix<T, EmptyValue, Dims>::map_iterator
    SparseMatrix<T, EmptyValue, Dims>::end() {
        return m_Container.end();
    }

    template<typename Matrix, typename T, size_t Depth = 2>
    std::ostream &operator<<(std::ostream &out, const Indexer<Matrix, T, Depth>& value) {
        return out << value.get();
    }

} // otus_sparse_matrix