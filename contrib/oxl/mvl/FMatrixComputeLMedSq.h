#ifndef FMatrixComputeLMedSq_h_
#define FMatrixComputeLMedSq_h_
// .NAME    FMatrixComputeLMedSq - Robust FMatrix computation
// .LIBRARY MViewCompute
// .HEADER  MultiView Package
// .INCLUDE mvl/FMatrixComputeLMedSq.h
// .FILE    FMatrixComputeLMedSq.cxx
// .EXAMPLE
//
// .SECTION Description
//    FMatrixComputeLMedSq implements
//    Zhengyou Zhang's LMedSq (Least Medium of Squares Estimation) of the fundamental matrix.
//
//    Points are preconditioned as described in [Hartley, ``In defence of
//    the 8-point algorithm'', ICCV95], and the resulting F matrix is rank-2
//    truncated.  The conditioning and truncation are optional and may be
//    omitted.
//
// .SECTION Author
//     David N. McKinnon, UQ I.R.I.S., 02.12.2000
//
// .SECTION Modifications:
//     <none yet>
//
//-----------------------------------------------------------------------------

#include <mvl/FMatrixComputeRobust.h>
#include <vcl/vcl_vector.h>

class FMatrixComputeLMedSq : public FMatrixComputeRobust {
public :
  // -- Initialize FMatrixComputeRobust object.
  // If rank2_truncate = false, the resulting solution is not forced to rank 2
  // using the vnl_svd<double>.
  FMatrixComputeLMedSq(bool rank2_truncate, int size);
  virtual ~FMatrixComputeLMedSq();

  virtual double calculate_term(vcl_vector<double>& residuals, vcl_vector<bool>& inlier_list, int& count);
  virtual double calculate_residual(HomgPoint2D& one, HomgPoint2D& two, FMatrix* F);
private :
  // Helper Functions
  // Return the median vaule for a vector of residuals
  double median(vcl_vector<double> residuals);
};

#endif // FMatrixComputeLMedSq_h_
