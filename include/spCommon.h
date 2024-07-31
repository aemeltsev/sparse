#ifndef SPARSE_COMMON_H
#define SPARSE_COMMON_H

#if defined(_MSC_VER)
#  ifdef SPARSE_STATIC
#    define SPARSE_EXPORT
#  elif defined(SPARSE_EXPORTS)
#    define SPARSE_EXPORT __declspec(dllexport)
#  else
#    define SPARSE_EXPORT __declspec(dllimport)
#  endif
#  define SPARSE_INLINE __forceinline
#else
#  define SPARSE_EXPORT __attribute__((visibility("default")))
#  define SPARSE_INLINE static inline __attribute((always_inline))
#endif

#include <stdio.h>
#include "spConfig.h"
#include "spMatrix.h"
#include "spDefs.h"



SPARSE_EXPORT int SparseMatrixAddElement(spMatrix Matrix, int Row, int Col, double Value);
SPARSE_EXPORT double* SparseMatrixMakeElement(spMatrix Matrix, int Row, int Col);
SPARSE_EXPORT void SparseMatrixClear(spMatrix Matrix);
SPARSE_EXPORT int SparseMatrixComplexLUFactor(spMatrix Matrix);
SPARSE_EXPORT int SparseMatrixLUFactor(spMatrix Matrix, double Gmin);
SPARSE_EXPORT int SparseMatrixComplexReorder(spMatrix Matrix, double PivTol, double PivRel, int* NumSwaps);
SPARSE_EXPORT void SparseMatrixTransposedSolve(spMatrix Matrix, double RHS[], double iRHS[], double Spare[], double iSpare[]);
SPARSE_EXPORT void SparseMatrixComplexSolve(spMatrix Matrix, double RHS[], double iRHS[], double Spare[], double iSpare[]);
SPARSE_EXPORT void SparseMatrixSolve(spMatrix Matrix, double RHS[], double Spare[]);
SPARSE_EXPORT int SparseMatrixSize(spMatrix Matrix);
SPARSE_EXPORT int SparseMatrixCreate(spMatrix* pMatrix, int Size, int Complex);
SPARSE_EXPORT void SparseMatrixDestroy(spMatrix pMatrix);
SPARSE_EXPORT int SparseMatrixPpeOrder(spMatrix pMatrix);
SPARSE_EXPORT void SparseMatrixPrint(spMatrix pMatrix, FILE* file);
SPARSE_EXPORT void SparseMatrixGetError(spMatrix pMatrix, int* Row, int* Col);
SPARSE_EXPORT int SparseMatrixComplexProdDiag(spMatrix pMatrix, int *pExponent, double* pDeterminant, double* piDeterminant);
void SparseMatrixLoadGmin(spMatrix pMatrix, double Gmin);
ElementPtr *SparseMatrixFindElement(spMatrix pMatrix, int Row, int Col, int CreateIfMissing);
SPARSE_EXPORT int SparseMatrixError(spMatrix pMatrix);


#endif //SPARSE_COMMON_H
