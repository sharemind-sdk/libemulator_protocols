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

#ifndef SHAREMIND_EMULATOR_PROTOCOLS_BINARY_H
#define SHAREMIND_EMULATOR_PROTOCOLS_BINARY_H

#include <type_traits>
#include "ShareVector.h"
#include "ValueTraits.h"
#include "VmVector.h"


namespace sharemind {

template <typename PDPI>
class __attribute__ ((visibility("internal"))) AdditionProtocol {
public: /* Methods: */

    AdditionProtocol(PDPI & pdpi) { (void) pdpi; }

    template <typename T>
    typename std::enable_if<is_any_value_tag<T>::value, bool>::type
    invoke(const share_vec<T> & param1,
           const share_vec<T> & param2,
           share_vec<T> & result)
    {
        if (param1.size() != param2.size() || param1.size() != result.size())
            return false;

        for (size_t i = 0u; i < param1.size(); ++i)
            result[i] = param1[i] + param2[i];

        return true;
    }

}; /* class AdditionProtocol { */

template <typename PDPI>
class __attribute__ ((visibility("internal"))) BitwiseAndProtocol {
public: /* Methods: */

    BitwiseAndProtocol(PDPI & pdpi) { (void) pdpi; }

    template <typename T>
    typename std::enable_if<is_any_value_tag<T>::value, bool>::type
    invoke(const share_vec<T> & param1,
           const share_vec<T> & param2,
           share_vec<T> & result)
    {
        if (param1.size() != param2.size() || param1.size() != result.size())
            return false;

        for (size_t i = 0u; i < param1.size(); ++i)
            result[i] = param1[i] & param2[i];

        return true;
    }

}; /* class BitwiseAndProtocol { */

template <typename PDPI>
class __attribute__ ((visibility("internal"))) BitwiseOrProtocol {
public: /* Methods: */

    BitwiseOrProtocol(PDPI & pdpi) { (void) pdpi; }

    template <typename T>
    typename std::enable_if<is_any_value_tag<T>::value, bool>::type
    invoke(const share_vec<T> & param1,
           const share_vec<T> & param2,
           share_vec<T> & result)
    {
        if (param1.size() != param2.size() || param1.size() != result.size())
            return false;

        for (size_t i = 0u; i < param1.size(); ++i)
            result[i] = param1[i] | param2[i];

        return true;
    }

}; /* class BitwiseOrProtocol { */

template <typename PDPI>
class __attribute__ ((visibility("internal"))) BitwiseXorProtocol {
public: /* Methods: */

    BitwiseXorProtocol(PDPI & pdpi) { (void) pdpi; }

    template <typename T>
    typename std::enable_if<is_any_value_tag<T>::value, bool>::type
    invoke(const share_vec<T> & param1,
           const share_vec<T> & param2,
           share_vec<T> & result)
    {
        if (param1.size() != param2.size() || param1.size() != result.size())
            return false;

        for (size_t i = 0u; i < param1.size(); ++i)
            result[i] = param1[i] ^ param2[i];

        return true;
    }

}; /* class BitwiseXorProtocol { */

template <typename PDPI>
class __attribute__ ((visibility("internal"))) DivisionProtocol {
public: /* Methods: */

    DivisionProtocol(PDPI & pdpi) { (void) pdpi; }

    template <typename T>
    typename std::enable_if<is_any_value_tag<T>::value, bool>::type
    invoke(const share_vec<T> & param1,
           const share_vec<T> & param2,
           share_vec<T> & result)
    {
        if (param1.size() != param2.size() || param1.size() != result.size())
            return false;

        for (size_t i = 0u; i < param2.size(); ++i) {
            if (param2[i] == 0)
                return false;
        }

        for (size_t i = 0u; i < param1.size(); ++i)
            result[i] = param1[i] / param2[i];

        return true;
    }

    template <typename T>
    typename std::enable_if<is_any_value_tag<T>::value, bool>::type
    invoke(const share_vec<T> & param1,
           const immutable_vm_vec<T> & param2,
           share_vec<T> & result)
    {
        if (param1.size() > param2.size() || param1.size() != result.size())
            return false;

        for (size_t i = 0u; i < param2.size(); ++i) {
            if (param2[i] == 0)
                return false;
        }

        for (size_t i = 0u; i < param1.size(); ++i)
            result[i] = param1[i] / param2[i];

        return true;
    }

}; /* class DivisionProtocol { */

template <typename PDPI>
class __attribute__ ((visibility("internal"))) EqualityProtocol {
public: /* Methods: */

    EqualityProtocol(PDPI & pdpi) { (void) pdpi; }

    template <typename T, typename U>
    typename std::enable_if<is_any_value_tag<T>::value, bool>::type
    invoke(const share_vec<T> & param1,
           const share_vec<T> & param2,
           share_vec<U> & result)
    {
        if (param1.size() != param2.size() || param1.size() != result.size())
            return false;

        for (size_t i = 0u; i < param1.size(); ++i)
            result[i] = param1[i] == param2[i];

        return true;
    }

}; /* class EqualityProtocol { */

template <typename PDPI>
class __attribute__ ((visibility("internal"))) GreaterThanProtocol {
public: /* Methods: */

    GreaterThanProtocol(PDPI & pdpi) { (void) pdpi; }

    template <typename T, typename U>
    typename std::enable_if<is_any_value_tag<T>::value, bool>::type
    invoke(const share_vec<T> & param1,
           const share_vec<T> & param2,
           share_vec<U> & result)
    {
        if (param1.size() != param2.size() || param1.size() != result.size())
            return false;

        for (size_t i = 0u; i < param1.size(); ++i)
            result[i] = param1[i] > param2[i];

        return true;
    }

}; /* class GreaterThanProtocol { */

template <typename PDPI>
class __attribute__ ((visibility("internal"))) GreaterThanOrEqualProtocol {
public: /* Methods: */

    GreaterThanOrEqualProtocol(PDPI & pdpi) { (void) pdpi; }

    template <typename T, typename U>
    typename std::enable_if<is_any_value_tag<T>::value, bool>::type
    invoke(const share_vec<T> & param1,
           const share_vec<T> & param2,
           share_vec<U> & result)
    {
        if (param1.size() != param2.size() || param1.size() != result.size())
            return false;

        for (size_t i = 0u; i < param1.size(); ++i)
            result[i] = param1[i] >= param2[i];

        return true;
    }

}; /* class GreaterThanOrEqualProtocol { */

template <typename PDPI>
class __attribute__ ((visibility("internal"))) LessThanProtocol {
public: /* Methods: */

    LessThanProtocol(PDPI & pdpi) { (void) pdpi; }

    template <typename T, typename U>
    typename std::enable_if<is_any_value_tag<T>::value, bool>::type
    invoke(const share_vec<T> & param1,
           const share_vec<T> & param2,
           share_vec<U> & result)
    {
        if (param1.size() != param2.size() || param1.size() != result.size())
            return false;

        for (size_t i = 0u; i < param1.size(); ++i)
            result[i] = param1[i] < param2[i];

        return true;
    }

}; /* class LessThanProtocol { */

template <typename PDPI>
class __attribute__ ((visibility("internal"))) LessThanOrEqualProtocol {
public: /* Methods: */

    LessThanOrEqualProtocol(PDPI & pdpi) { (void) pdpi; }

    template <typename T, typename U>
    typename std::enable_if<is_any_value_tag<T>::value, bool>::type
    invoke(const share_vec<T> & param1,
           const share_vec<T> & param2,
           share_vec<U> & result)
    {
        if (param1.size() != param2.size() || param1.size() != result.size())
            return false;

        for (size_t i = 0u; i < param1.size(); ++i)
            result[i] = param1[i] <= param2[i];

        return true;
    }

}; /* class LessThanOrEqualProtocol { */

template <typename PDPI>
class __attribute__ ((visibility("internal"))) MaximumProtocol {
public: /* Methods: */

    MaximumProtocol(PDPI & pdpi) { (void) pdpi; }

    template <typename T>
    typename std::enable_if<is_any_value_tag<T>::value, bool>::type
    invoke(const share_vec<T> & param1,
           const share_vec<T> & param2,
           share_vec<T> & result)
    {
        if (param1.size() != param2.size() || param1.size() != result.size())
            return false;

        for (size_t i = 0u; i < param1.size(); ++i)
            result[i] = param1[i] > param2[i] ? param1[i] : param2[i];

        return true;
    }

}; /* class MaximumProtocol { */

template <typename PDPI>
class __attribute__ ((visibility("internal"))) MinimumProtocol {
public: /* Methods: */

    MinimumProtocol(PDPI & pdpi) { (void) pdpi; }

    template <typename T>
    typename std::enable_if<is_any_value_tag<T>::value, bool>::type
    invoke(const share_vec<T> & param1,
           const share_vec<T> & param2,
           share_vec<T> & result)
    {
        if (param1.size() != param2.size() || param1.size() != result.size())
            return false;

        for (size_t i = 0u; i < param1.size(); ++i)
            result[i] = param1[i] < param2[i] ? param1[i] : param2[i];

        return true;
    }

}; /* class MinimumProtocol { */

template <typename PDPI>
class __attribute__ ((visibility("internal"))) MultiplicationProtocol {
public: /* Methods: */

    MultiplicationProtocol(PDPI & pdpi) { (void) pdpi; }

    template <typename T>
    typename std::enable_if<is_any_value_tag<T>::value, bool>::type
    invoke(const share_vec<T> & param1,
           const share_vec<T> & param2,
           share_vec<T> & result)
    {
        if (param1.size() != param2.size() || param1.size() != result.size())
            return false;

        for (size_t i = 0u; i < param1.size(); ++i)
            result[i] = param1[i] * param2[i];

        return true;
    }

    template <typename T>
    typename std::enable_if<is_any_value_tag<T>::value, bool>::type
    invoke(const share_vec<T> & param1,
           const immutable_vm_vec<T> & param2,
           share_vec<T> & result)
    {
        if (param1.size() > param2.size() || param1.size() != result.size())
            return false;

        for (size_t i = 0u; i < param1.size(); ++i)
            result[i] = param1[i] * param2[i];

        return true;
    }

}; /* class MultiplicationProtocol { */

template <typename PDPI>
class __attribute__ ((visibility("internal"))) RemainderProtocol {
public: /* Methods: */

    RemainderProtocol(PDPI & pdpi) { (void) pdpi; }

    template <typename T>
    typename std::enable_if<is_any_value_tag<T>::value, bool>::type
    invoke(const share_vec<T> & param1,
           const share_vec<T> & param2,
           share_vec<T> & result)
    {
        if (param1.size() != param2.size() || param1.size() != result.size())
            return false;

        for (size_t i = 0u; i < param2.size(); ++i) {
            if (param2[i] == 0)
                return false;
        }

        for (size_t i = 0u; i < param1.size(); ++i)
            result[i] = param1[i] % param2[i];

        return true;
    }

    template <typename T>
    typename std::enable_if<is_any_value_tag<T>::value, bool>::type
    invoke(const share_vec<T> & param1,
           const immutable_vm_vec<T> & param2,
           share_vec<T> & result)
    {
        if (param1.size() > param2.size() || param1.size() != result.size())
            return false;

        for (size_t i = 0u; i < param2.size(); ++i) {
            if (param2[i] == 0)
                return false;
        }

        for (size_t i = 0u; i < param1.size(); ++i)
            result[i] = param1[i] % param2[i];

        return true;
    }

}; /* class RemainderProtocol { */

template <typename PDPI>
class __attribute__ ((visibility("internal"))) SubtractionProtocol {
public: /* Methods: */

    SubtractionProtocol(PDPI & pdpi) { (void) pdpi; }

    template <typename T>
    typename std::enable_if<is_any_value_tag<T>::value, bool>::type
    invoke(const share_vec<T> & param1,
           const share_vec<T> & param2,
           share_vec<T> & result)
    {
        if (param1.size() != param2.size() || param1.size() != result.size())
            return false;

        for (size_t i = 0u; i < param1.size(); ++i)
            result[i] = param1[i] - param2[i];

        return true;
    }

}; /* class SubtractionProtocol { */

} /* namespace sharemind { */

#endif /* SHAREMIND_EMULATOR_PROTOCOLS_BINARY_H */
