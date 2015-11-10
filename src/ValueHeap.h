/*
 * Copyright (C) 2015 Cybernetica
 *
 * Research/Commercial License Usage
 * Licensees holding a valid Research License or Commercial License
 * for the Software may use this file according to the written
 * agreement between you and Cybernetica.
 *
 * GNU General Public License Usage
 * Alternatively, this file may be used under the terms of the GNU
 * General Public License version 3.0 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU General Public License version 3.0 requirements will be
 * met: http://www.gnu.org/copyleft/gpl-3.0.html.
 *
 * For further information, please contact us at sharemind@cyber.ee.
 */

#ifndef SHAREMIND_EMULATOR_PROTOCOLS_VALUEHEAP_H
#define SHAREMIND_EMULATOR_PROTOCOLS_VALUEHEAP_H

#include <cstdint>
#include <unordered_map>
#include "ShareVector.h"
#include "ValueTraits.h"


namespace sharemind {

/**
 * \brief Heap of share vectors.
 * This class tracks in a type safe manner all of the allocated share vectors.
 */
class __attribute__ ((visibility("internal"))) value_heap {

private: /* Types: */

    typedef std::unordered_map<share_vec_base *, uint8_t> impl_t;

public: /* Methods: */

    value_heap() = default;
    value_heap(const value_heap &) = delete;
    value_heap & operator=(const value_heap &) = delete;

    /**
     * Frees all stored share vectors.
     */
    ~value_heap() {
        for (impl_t::value_type & pair : m_pointers)
            delete pair.first;
    }

    /**
     * Insert vector share vector of type T into the heap.
     * \param[in] vec Vector to be inserted into the heap.
     * \retval true If vector was inserted into the heap successfully, and it wasn't stored in the heap before.
     * \retval false If vec was null pointer, or if the vector was already stored in the heap.
     */
    template <typename T>
    bool insert(share_vec<T>* vec) {
        uint8_t heap_type_id = value_traits<T>::heap_type_id;
        if (vec != 0)
            return m_pointers.emplace(static_cast<share_vec_base *>(vec), heap_type_id).second;

        return false;
    }

    /**
     * Erases a share vector of given type from the heap.
     * \param[in] vec The vector to be erased.
     * \retval true If vector was successfully freed from the heap.
     * \retval false If the vector was not stored, or was stored with incorrect type.
     */
    template <typename T>
    bool erase(share_vec<T>* vec) {
        impl_t::iterator i = m_pointers.find(vec);
        if (i != m_pointers.end()) {
            if (i->second == value_traits<T>::heap_type_id) {
                delete i->first;
                m_pointers.erase(i);
                return true;
            }
        }

        return false;
    }

    /**
     * Checks if given handle is stored in the heap with given type.
     * \param[in] hndl A handle to a share vector.
     * \retval true If the \a hndl was stored in the heap with type \a T.
     * \retval false If the handle is not stored in the heap, or is stored with incorrect type.
     */
    template <typename T>
    bool check(void* hndl) const {
        impl_t::const_iterator i = m_pointers.find(static_cast<share_vec_base*>(hndl));
        if (i != m_pointers.end())
            return (i->second == value_traits<T>::heap_type_id);

        return false;
    }

private: /* Fields: */

    impl_t m_pointers;

}; /* class value_heap { */

} /* namespace sharemind */

#endif /* SHAREMIND_EMULATOR_PROTOCOLS_VALUEHEAP_H */
