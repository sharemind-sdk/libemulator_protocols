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

#ifndef SHAREMIND_EMULATOR_PROTOCOLS_NULLARY_H
#define SHAREMIND_EMULATOR_PROTOCOLS_NULLARY_H

#include <type_traits>
#include <sharemind/ShareVector.h>
#include <sharemind/ValueTraits.h>


namespace sharemind {

template <typename PDPI>
class __attribute__ ((visibility("internal"))) RandomizeProtocol {
public: /* Methods: */

    RandomizeProtocol(PDPI &pdpi)
        : m_pdpi(pdpi)
    { }

    template <typename T>
    typename std::enable_if<is_any_value_tag<T>::value, bool>::type
    invoke(ShareVec<T>& result) {
        result.randomize(m_pdpi.rng());
        return true;
    }

private: /* Fields: */

    PDPI & m_pdpi;

}; /* class RandomizeProtocol { */

} /* namespace sharemind { */

#endif /* SHAREMIND_EMULATOR_PROTOCOLS_NULLARY_H */
