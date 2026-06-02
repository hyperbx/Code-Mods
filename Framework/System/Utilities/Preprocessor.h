#pragma once

#include <boost/preprocessor.hpp>

#ifndef offsetof
#define offsetof(s, m) ((size_t)&(((s*)0)->m))
#endif

#define INSERT_PADDING(LENGTH) \
    uint8_t BOOST_PP_CAT(pad, __LINE__)[LENGTH]

#define ASSERT_OFFSETOF(TYPE, FIELD, OFFSET) \
    static_assert(offsetof(TYPE, FIELD) == OFFSET, "offsetof assertion failed")

#define ASSERT_SIZEOF(TYPE, SIZE) \
    static_assert(sizeof(TYPE) == SIZE, "sizeof assertion failed")

#define IS_TYPE_void

#define IS_VOID(TYPE) \
    BOOST_PP_IS_EMPTY(BOOST_PP_CAT(IS_TYPE_, TYPE))

#define GET_RETURN(RETURN_TYPE) \
    BOOST_PP_IF(IS_VOID(RETURN_TYPE), BOOST_PP_EMPTY(), return)

#ifdef WIN32
#include "PreprocessorWin32.h"
#endif
