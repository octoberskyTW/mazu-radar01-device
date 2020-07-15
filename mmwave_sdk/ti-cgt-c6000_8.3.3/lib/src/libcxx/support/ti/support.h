// -*- C++ -*-
//===----------------------- support/ibm/support.h ----------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP_SUPPORT_TI___SUPPORT_H
#define _LIBCPP_SUPPORT_TI___SUPPORT_H

template <typename T, int TBits = sizeof(T) * __CHAR_BIT__>
struct __ti_support;

template <typename T>
struct __ti_support<T, 16> {
    static int popcount(T input) {
        T mask1 = 0x5555;
        input -= ((input >> 1) & mask1);
        T mask2 = 0x3333;
        input = ((input & mask2) + ((input >> 2) & mask2));
        T mask3 = 0x0f0f;
        input = ((input + (input >> 4)) & mask3);
        input += (input >> 8);
        return (input & 0x1f);
    }
    static int clz(T input) {
        unsigned int pos = 0;

        if ((input & 0xff00) != 0) { pos += 8; input >>= 8; }
        if ((input & 0x00f0) != 0) { pos += 4; input >>= 4; }
        if      (input >= 8) pos += 4;
        else if (input >= 4) pos += 3;
        else if (input >= 2) pos += 2;
        else if (input >= 1) pos += 1;

        return (16 - pos);
    }
    static int ctz(T input) {
        int pos = 0;

        if ((input & 0x000000ff) == 0) { pos +=  8; input >>=  8; }
        if ((input & 0x0000000f) == 0) { pos +=  4; input >>=  4; }
        if ((input & 0x00000003) == 0) { pos +=  2; input >>=  2; }
        if ((input & 0x00000001) == 0) { pos +=  1;               }

        return pos;
    }
};

template <typename T>
struct __ti_support<T, 32> {
    static int popcount(T input) {
        T mask1 = 0x55555555;
        input -= ((input >> 1) & mask1);
        T mask2 = 0x33333333;
        input = ((input & mask2) + ((input >> 2) & mask2));
        T mask3 = 0x0f0f0f0f;
        input = ((input + (input >> 4)) & mask3);
        input += (input >> 8);
        input += (input >> 16);
        return (input & 0x3f);
    }

    static int clz(T input) {
        unsigned int pos = 0;
        if ((input & 0xffff0000) != 0) { pos += 16; input >>= 16; }
        return (16 + __ti_support<T, 16>::clz(input) - pos);
    }

    static int ctz(T input) {
        int pos = 0;
        if ((input & 0x0000ffff) == 0) { pos += 16; input >>= 16; }
        return pos + __ti_support<T, 16>::ctz(input);
    }
};

template <typename T>
struct __ti_support<T, 64> {
    static int popcount(T input) {
        T mask1 = 0x5555555555555555;
        input -= ((input >> 1) & mask1);
        T mask2 = 0x3333333333333333;
        input = ((input & mask2) + ((input >> 2) & mask2));
        T mask3 = 0x0f0f0f0f0f0f0f0f;
        input = ((input + (input >> 4)) & mask3);
        input += (input >> 8);
        input += (input >> 16);
        input += (input >> 32);
        return (input & 0x7f);
    }

    static int clz(T input) {
        T p1 = (input >> 32);
        T p2 = (input & 0x00000000ffffffff);
        unsigned int pos = 0;

        if ((p1 & 0xffffffff) != 0)
        {
            pos += 32;
            p2 = p1;
        }
        return (32 + __ti_support<T, 32>::clz(p2) - pos);
    }

    static int ctz(T input) {
        T p1 = (input >> 32);
        T p2 = (input & 0x00000000ffffffff);
        unsigned int pos = 0;

        if ((p2 & 0xffffffff) == 0)
        {
            pos += 32;
            p2 = p1;
        }
        return pos + __ti_support<T, 32>::ctz(p2);
    }
};

#define __builtin_popcount(x) (__ti_support<unsigned int>::popcount(x))
#define __builtin_popcountl(x) (__ti_support<unsigned long>::popcount(x))
#define __builtin_popcountll(x) (__ti_support<unsigned long long>::popcount(x))

#define __builtin_ctz(x) (__ti_support<unsigned int>::ctz(x))
#define __builtin_ctzl(x) (__ti_support<unsigned long>::ctz(x))
#define __builtin_ctzll(x) (__ti_support<unsigned long long>::ctz(x))

#define __builtin_clz(x) (__ti_support<unsigned int>::clz(x))
#define __builtin_clzl(x) (__ti_support<unsigned long>::clz(x))
#define __builtin_clzll(x) (__ti_support<unsigned long long>::clz(x))

#endif /* !defined(_LIBCPP_SUPPORT_TI___SUPPORT_H) */
