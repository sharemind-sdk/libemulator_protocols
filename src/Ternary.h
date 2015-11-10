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

#ifndef SHAREMIND_EMULATOR_PROTOCOLS_TERNARY_H
#define SHAREMIND_EMULATOR_PROTOCOLS_TERNARY_H

#include <type_traits>
#include "ShareVector.h"
#include "ValueTraits.h"


namespace sharemind {

template <typename PDPI>
class __attribute__ ((visibility("internal"))) ObliviousChoiceProtocol {
public: /* Methods: */

    ObliviousChoiceProtocol(PDPI & pdpi) { (void) pdpi; }

    template <typename T, typename U>
    typename std::enable_if<is_any_value_tag<T>::value, bool>::type
    invoke(const share_vec<U> & param1,
           const share_vec<T> & param2,
           const share_vec<T> & param3,
           share_vec<T> & result)
    {
        if (param1.size() != param2.size() ||
                param1.size() != param3.size() ||
                param1.size() != result.size())
        {
            return false;
        }

        for (size_t i = 0u; i < param1.size(); ++i)
            result[i] = param1[i] ? param2[i] : param3[i];

        return true;
    }

}; /* class ObliviousChoiceProtocol { */

} /* namespace sharemind { */

#endif /* SHAREMIND_EMULATOR_PROTOCOLS_TERNARY_H */
