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

#ifndef SHAREMIND_EMULATOR_PROTOCOLS_UNARY_H
#define SHAREMIND_EMULATOR_PROTOCOLS_UNARY_H

#include <algorithm>
#include <type_traits>
#include <sharemind/ShareVector.h>
#include <sharemind/ValueTraits.h>


namespace sharemind {

template <typename PDPI>
class __attribute__ ((visibility("internal"))) BitwiseInvProtocol {
public: /* Methods: */

    BitwiseInvProtocol(PDPI & pdpi) { (void) pdpi; }

    template <typename T>
    typename std::enable_if<is_any_value_tag<T>::value, bool>::type
    invoke(const ShareVec<T> & param,
           ShareVec<T> & result)
    {
        if (param.size() != result.size())
            return false;

        for (size_t i = 0u; i < param.size(); ++i)
            result[i] = ~param[i];

        return true;
    }

}; /* BitwiseInvProtocol { */

template <typename PDPI>
class __attribute__ ((visibility("internal"))) ConversionProtocol {
public: /* Methods: */

    ConversionProtocol(PDPI & pdpi) { (void) pdpi; }

    template <typename T, typename U>
    typename std::enable_if<is_any_value_tag<T>::value, bool>::type
    invoke(const ShareVec<T> & param,
           ShareVec<U> & result)
    {
        if (param.size() != result.size())
            return false;

        for (size_t i = 0u; i < param.size(); ++i)
            result[i] = param[i];

        return true;
    }

}; /* class ConversionProtocol { */

enum MinimumMaximumMode { /// \todo
    ModeMin,
    ModeMax
};

template <typename PDPI, MinimumMaximumMode mode>
class __attribute__ ((visibility("internal"))) MinimumMaximumProtocol {
public: /* Methods: */

    MinimumMaximumProtocol(PDPI & pdpi) { (void) pdpi; }

    template <typename T>
    typename std::enable_if<is_any_value_tag<T>::value, bool>::type
    invoke(const ShareVec<T> & param,
           ShareVec<T> & result)
    {
        const size_t result_size = result.size();
        const size_t param_size = param.size();

        if (result_size == 0u)
            return false;

        if (param_size % result_size != 0u)
            return false;

        const size_t subarr_len = param_size / result_size;

        auto offset = param.cbegin();
        for (size_t i = 0u; i < result_size; ++i) {
            if (mode == ModeMin) {
                result[i] = *std::min_element(offset, offset + subarr_len);
            } else {
                result[i] = *std::max_element(offset, offset + subarr_len);
            }

            offset += subarr_len;
        }

        return true;
    }

}; /* class MinimumMaximumProtocol { */

template <typename PDPI>
class __attribute__ ((visibility("internal"))) NegProtocol {
public: /* Methods: */

    NegProtocol(PDPI & pdpi) { (void) pdpi; }

    template <typename T, typename U>
    typename std::enable_if<is_any_value_tag<T>::value, bool>::type
    invoke(const ShareVec<T> & param,
           ShareVec<U> & result)
    {
        if (param.size() != result.size())
            return false;

        for (size_t i = 0u; i < param.size(); ++i)
            result[i] = -param[i];

        return true;
    }

}; /* class NegProtocol { */

template <typename PDPI>
class __attribute__ ((visibility("internal"))) NotProtocol {
public: /* Methods: */

    NotProtocol(PDPI & pdpi) { (void) pdpi; }

    template <typename T>
    typename std::enable_if<is_any_value_tag<T>::value, bool>::type
    invoke(const ShareVec<T> & param,
           ShareVec<T> & result)
    {
        if (param.size() != result.size())
            return false;

        for (size_t i = 0u; i < param.size(); ++i)
            result[i] = !param[i];

        return true;
    }

}; /* NotProtocol { */

template <typename PDPI>
class __attribute__ ((visibility("internal"))) ProductProtocol {
public: /* Methods: */

    ProductProtocol(PDPI & pdpi) { (void) pdpi; }

    template <typename T, typename U>
    typename std::enable_if<is_any_value_tag<T>::value, bool>::type
    invoke(const ShareVec<T> & param,
           ShareVec<U> & result)
    {
        const size_t param_size = param.size ();
        const size_t result_size = result.size ();
        if (result_size == 0u)
            return false;

        if (param_size == 0u) {
            if (result_size != 1)
                return false;
            result[0] = 0;
            return true;
        }

        if (param_size % result_size != 0u)
            return false;

        for (size_t i = 0u; i < result_size; ++i) {
            result[i] = 1;
        }

        const size_t subarr_len = param_size / result_size;
        for (size_t i = 0u; i < param_size; ++i) {
            result[i / subarr_len] *= param[i];
        }

        return true;
    }

}; /* class ProductProtocol { */

template <typename PDPI>
class __attribute__ ((visibility("internal"))) SignProtocol {
public: /* Methods: */

    SignProtocol(PDPI & pdpi) { (void) pdpi; }

    template <typename T>
    typename std::enable_if<is_any_value_tag<T>::value, bool>::type
    invoke(const ShareVec<T> & param,
           ShareVec<T> & result)
    {
        if (param.size() != result.size())
            return false;

        for (size_t i = 0u; i < param.size(); ++i)
            result[i] = (param[i] > 0) ? 1 : ((param[i] < 0) ? -1 : 0);

        return true;
    }

}; /* class SignProtocol { */

template <typename PDPI>
class __attribute__ ((visibility("internal"))) SumProtocol {
public: /* Methods: */

    SumProtocol(PDPI & pdpi) { (void) pdpi; }

    template <typename T, typename U>
    typename std::enable_if<is_any_value_tag<T>::value, bool>::type
    invoke(const ShareVec<T> & param,
           ShareVec<U> & result)
    {
        const size_t param_size = param.size ();
        const size_t result_size = result.size ();
        if (result_size == 0u)
            return false;

        if (param_size % result_size != 0u)
            return false;

        for (size_t i = 0u; i < result_size; ++i) {
            result[i] = 0;
        }

        const size_t subarr_len = param_size / result_size;
        for (size_t i = 0u; i < param_size; ++i) {
            result[i / subarr_len] += param[i];
        }

        return true;
    }

}; /* class SumProtocol { */

} /* namespace sharemind { */

#endif /* SHAREMIND_EMULATOR_PROTOCOLS_UNARY_H */
