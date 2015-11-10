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

#ifndef SHAREMIND_EMULATOR_PROTOCOLS_VMVECTOR_H
#define SHAREMIND_EMULATOR_PROTOCOLS_VMVECTOR_H

#include <cstddef>
#include <sharemind/libmodapi/api_0x1.h>
#include <vector>

#include "ValueTraits.h"


namespace sharemind {

/**
 * Base class to represent VM references and memory.
 * As the data is owned by the VM we don't need to manage it.
 */
template <typename T>
class __attribute__ ((visibility("internal"))) vm_vec_base {

public: /* Types: */

    typedef T value_type;
    typedef const value_type* const_iterator;

public: /* Methods: */

    vm_vec_base ()
        : m_begin (0)
        , m_end (0)
    { }

    vm_vec_base (T* begin, size_t size)
        : m_begin((assert(begin), begin))
        , m_end (begin + size)
    { }

    inline size_t size () const { return (m_end - m_begin); }
    inline const value_type& operator [] (size_t i) const { return *(m_begin + i); }
    inline bool empty () const { return m_end <= m_begin; }
    inline const_iterator begin () const { return m_begin; }
    inline const_iterator end () const { return m_end; }

protected: /* Fields: */

    T*  m_begin;
    T*  m_end;

}; /* class vm_vec_base { */

/**
 * Mutable vector of VM data, can be constructed from VM references.
 */
template <typename T>
class __attribute__ ((visibility("internal"))) mutable_vm_vec : vm_vec_base<typename T::public_type> {

private: /* Types: */

    typedef vm_vec_base<typename T::public_type> Base;

public: /* Types: */

    typedef typename Base::value_type value_type;
    typedef typename Base::const_iterator const_iterator;
    typedef value_type* iterator;

public: /* Methods: */

    explicit
    mutable_vm_vec (const SharemindModuleApi0x1Reference& ref)
        : Base (static_cast<value_type*>(ref.pData), ref.size / sizeof (value_type))
    { }

    /* For debugging only! */
    explicit
    mutable_vm_vec (std::vector<value_type>& vec)
        : Base ((assert (!vec.empty ()), &vec[0]), vec.size ())
    { }

    iterator begin () { return this->m_begin; }
    iterator end () { return this->m_end; }
    value_type& operator [] (size_t i) { return *(this->m_begin + i); }

    using Base::empty;
    using Base::size;
    using Base::operator [];
    using Base::begin;
    using Base::end;

}; /* class mutable_vm_vec { */

/**
 * Immutable vector of VM data, can be constructed from VM constant references.
 */
template <typename T>
class __attribute__ ((visibility("internal"))) immutable_vm_vec : vm_vec_base<const typename T::public_type> {

private: /* Types: */

    typedef vm_vec_base<const typename T::public_type> Base;

public: /* Types: */

    typedef typename Base::value_type value_type;
    typedef typename Base::const_iterator const_iterator;

public: /* Methods: */

    explicit
    immutable_vm_vec (const SharemindModuleApi0x1CReference& cref)
        : Base (static_cast<value_type*>(cref.pData), cref.size / sizeof (value_type))
    { }

    explicit
    immutable_vm_vec (const mutable_vm_vec<T>& immvec)
        : Base (immvec)
    { }

    using Base::empty;
    using Base::size;
    using Base::operator [];
    using Base::begin;
    using Base::end;

}; /* class immutable_vm_vec { */

} /* namespace sharemind */

#endif /* SHAREMIND_EMULATOR_PROTOCOLS_VMVECTOR_H */
