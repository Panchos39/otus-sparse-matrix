#include "indexer.h"
#include <cassert>
namespace otus_sparse_matrix {

    template <typename Matrix, typename T, size_t Dims >
    Indexer<Matrix, T, Dims>::Indexer(Matrix* mat,
                                      std::array<T, Dims> key) {
        static_assert(Dims > 0, "Empty depth");
        m_SparseMat = mat;
        m_Key = key;
        m_Index = Dims;
    }

    template <typename Matrix, typename T, size_t Dims >
    Indexer<Matrix, T, Dims>::Indexer(Matrix* mat,
                                      size_t index) {
        static_assert(Dims > 0, "Empty dimension");
        m_SparseMat = mat;
        m_Key = {index};
        m_Index = 1;
    }

    template <typename Matrix, typename T, size_t Dims >
    Indexer<Matrix, T, Dims>& Indexer<Matrix, T, Dims>::operator[](size_t i) {
        assert(m_Index < Dims && "Out of dimension");
        m_Key[m_Index] = i;
        ++m_Index;
        return *this;
    }

    template <typename Matrix, typename T, size_t Dims >
    const auto& Indexer<Matrix, T, Dims>::get() const {
        assert(m_Index == Dims && "not enough indices to get value");
        return m_SparseMat->get(m_Key);
    }

    template <typename Matrix, typename T, size_t Dims >
    Indexer<Matrix, T, Dims>& Indexer<Matrix, T, Dims>::operator=(T value) {
        assert(m_Index == Dims && "Wrong dimensions");
        m_SparseMat->set(m_Key, value);
        return *this;
    }

    template <typename Matrix, typename T, size_t Dims >
    bool Indexer<Matrix, T, Dims>::operator==(const T& value) const {
        return this->get()==value;
    }



} // otus_sparse_matrix