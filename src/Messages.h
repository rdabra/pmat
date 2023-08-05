

namespace pmat::messages {

constexpr const char *DATA_NOT_READ{"Error reading data"};
constexpr const char *FILE_NOT_OPEN{"Error opening file"};

constexpr const char *OPERANDS_EQUAL{"Operands must have same size"};
constexpr const char *INDEX_OUT{"Index out of bounds"};
constexpr const char *OPERANDS_MAT_PROD{"Sizes of left column and right row must be equal"};
constexpr const char *NONCOMPT_RESP{"Response object size is not compatible"};
constexpr const char *NONCOMPT_SIZE_ARG{"Argument is not compatible in size"};
constexpr const char *RHS_NOT_COMP{"Right-hand side is not compatible"};

constexpr const char *MATRIX_SINGULAR{"Matrix is singular"};
constexpr const char *ELEM_SWAPPED{"Elements cannot be swapped"};
constexpr const char *MATRIX_NOT_LU{"Matrix not LU decomposable"};
constexpr const char *MATRIX_NOT_TRANSP{"Elements cannot be transposed"};
constexpr const char *MATRIX_NOT_L{"Matrix not Cholesky decomposable"};
constexpr const char *MATRIX_NOT_RC{"Matrix is neither row nor column"};
constexpr const char *DECOMP_NOT_LU{"Calculation Mode is not Strict LU"};
} // namespace pmat::messages