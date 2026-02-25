#pragma once

#ifndef offsetof
#define offsetof(s, m) ((size_t)&(((s*)0)->m))
#endif

#define _CONCAT2(X, Y) X##Y
#define CONCAT2(X, Y) _CONCAT(X, Y)

#define INSERT_PADDING(LENGTH) \
    uint8_t CONCAT2(pad, __LINE__)[LENGTH]

#define ASSERT_OFFSETOF(TYPE, FIELD, OFFSET) \
    static_assert(offsetof(TYPE, FIELD) == OFFSET, "offsetof assertion failed")

#define ASSERT_SIZEOF(TYPE, SIZE) \
    static_assert(sizeof(TYPE) == SIZE, "sizeof assertion failed")

#include "StringHelper.h"

#ifdef WIN32
#include "UtilitiesWin32.h"
#endif