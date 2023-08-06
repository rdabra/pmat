#ifndef MESSAGES_H
#define MESSAGES_H
#pragma once

namespace pmat::messages {

constexpr const char *DATA_NOT_READ{"Error reading file data"};
constexpr const char *FILE_NOT_OPEN{"Error opening file"};

constexpr const char *INDEX_OUT{"Index out of bounds"};
constexpr const char *NONCOMPT_SIZE_ARG{"Argument is not compatible in size"};

constexpr const char *MATRIX_SINGULAR{"Matrix is singular"};
constexpr const char *MATRIX_NOT_LU{"Matrix not LU decomposable"};
constexpr const char *MATRIX_NOT_L{"Matrix not positive definite"};
constexpr const char *DECOMP_NOT_LU{"Calculation mode was not set to Strict LU"};

} // namespace pmat::messages

#endif