/* vim: set expandtab shiftwidth=2 softtabstop=2 tw=70: */

#include <Rcpp.h>
using namespace Rcpp;

// Cross-reference work:
// 1. update ../src/registerDynamicSymbol.c with an item for this
// 2. main code should use the autogenerated wrapper in ../R/RcppExports.R
//
// [[Rcpp::export]]

NumericMatrix do_matrix_smooth(NumericMatrix mat)
{
    int ni = mat.nrow(), nj=mat.ncol();
    NumericMatrix res(ni, nj);
    // copy edges (FIXME: could use 1D smoother here)
    for (int j = 0; j < nj; j++) {
        res(0, j) = mat(0, j);
        res(ni-1, j) = mat(ni-1, j);
    }
    for (int i = 0; i < ni; i++) {
        res(i, 0) = mat(i, 0);
        res(i, nj-1) = mat(i, nj-1);
    }
    // smooth middle 
    for (int i = 1; i < ni - 1; i++)
        for (int j = 1; j < nj - 1; j++)
            res(i, j) = (2.0*mat(i, j) +
                    mat(i-1, j) + mat(i+1, j) + mat(i, j-1) + mat(i, j+1)) / 6.0;
    return(res);
}
