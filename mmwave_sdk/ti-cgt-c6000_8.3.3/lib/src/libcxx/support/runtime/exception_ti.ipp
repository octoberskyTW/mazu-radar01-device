// -*- C++ -*-
//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

namespace std {

int uncaught_exceptions() _NOEXCEPT
{
    return std::uncaught_exception() ? 1 : 0;
}

#ifdef _LIBCPP_NO_EXCEPTIONS
bool uncaught_exception() _NOEXCEPT
{
    return false;
}
#endif /* defined(_LIBCPP_NO_EXCEPTIONS) */

} // namespace std
