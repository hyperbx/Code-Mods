#pragma once

#include <boost/preprocessor.hpp>
#include <recomputils.h>

// Extracts the type and name from a given function parameter.
#define EXTRACT_HOOK_PARAM_TYPE(PARAM) BOOST_PP_TUPLE_ELEM(0, PARAM)
#define EXTRACT_HOOK_PARAM_NAME(PARAM) BOOST_PP_TUPLE_ELEM(1, PARAM)

// Gets the global for a given function parameter.
#define GET_HOOK_PARAM_GLOBAL(FUNCTION_NAME, PARAM) \
    BOOST_PP_CAT(param_##FUNCTION_NAME##_, EXTRACT_HOOK_PARAM_NAME(PARAM))

// Declares a global for a given function parameter for use in the postfix hook.
#define DECLARE_HOOK_PARAM_GLOBAL(_, FUNCTION_NAME, PARAM) \
    static EXTRACT_HOOK_PARAM_TYPE(PARAM) GET_HOOK_PARAM_GLOBAL(FUNCTION_NAME, PARAM);

// Used for transforming globals into comma-separated values for function arguments.
#define GET_HOOK_ARG(_, FUNCTION_NAME, PARAM) \
    GET_HOOK_PARAM_GLOBAL(FUNCTION_NAME, PARAM)

// Used for transforming parameters into comma-separated values for function signatures.
#define GET_HOOK_PARAM(_A, _B, PARAM) \
    EXTRACT_HOOK_PARAM_TYPE(PARAM) EXTRACT_HOOK_PARAM_NAME(PARAM)

// Used for assigning function parameters to globals in the prefix hook.
#define ASSIGN_HOOK_PARAM_GLOBAL(_, FUNCTION_NAME, PARAM) \
    GET_HOOK_PARAM_GLOBAL(FUNCTION_NAME, PARAM) = EXTRACT_HOOK_PARAM_NAME(PARAM);

#define DECLARE_PREFIX_HOOK(RETURN_TYPE, FUNCTION_NAME, SYMBOL_NAME, PARAMS) \
    RECOMP_HOOK(SYMBOL_NAME) void prefix_##FUNCTION_NAME(BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_TRANSFORM(GET_HOOK_PARAM, FUNCTION_NAME, PARAMS)))

#define DECLARE_POSTFIX_HOOK(RETURN_TYPE, FUNCTION_NAME, SYMBOL_NAME, PARAMS)                                           \
    BOOST_PP_SEQ_FOR_EACH(DECLARE_HOOK_PARAM_GLOBAL, FUNCTION_NAME, PARAMS)                                             \
    DECLARE_PREFIX_HOOK(RETURN_TYPE, FUNCTION_NAME, SYMBOL_NAME, PARAMS)                                                \
    {                                                                                                                   \
        BOOST_PP_SEQ_FOR_EACH(ASSIGN_HOOK_PARAM_GLOBAL, FUNCTION_NAME, PARAMS)                                          \
    }                                                                                                                   \
    RETURN_TYPE impl_##FUNCTION_NAME(BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_TRANSFORM(GET_HOOK_PARAM, FUNCTION_NAME, PARAMS))); \
    RECOMP_HOOK_RETURN(SYMBOL_NAME) RETURN_TYPE postfix_##FUNCTION_NAME()                                               \
    {                                                                                                                   \
        return impl_##FUNCTION_NAME(BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_TRANSFORM(GET_HOOK_ARG, FUNCTION_NAME, PARAMS)));    \
    }                                                                                                                   \
    RETURN_TYPE impl_##FUNCTION_NAME(BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_TRANSFORM(GET_HOOK_PARAM, FUNCTION_NAME, PARAMS)))
