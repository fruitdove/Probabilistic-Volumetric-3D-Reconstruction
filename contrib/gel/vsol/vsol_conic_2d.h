#ifndef VSOL_CONIC_2D_H
#define VSOL_CONIC_2D_H
//*****************************************************************************
//
// .NAME vsol_conic_2d - Section of a conic curve in a 2D space
// .LIBRARY vsol
// .INCLUDE vsol/vsol_conic_2d.h
// .FILE    vsol/vsol_conic_2d.cxx

//:
// \file
// The conic is defined by its cartesian equation
// a x^2 +b xy +c y^2 +d x +e y +f
//
// .SECTION Author
// Fran�ois BERTEL
//
// .SECTION Modifications
// 2000/06/17 Peter Vanroose  Implemented all operator==()s and type info
// 2000/04/28 Fran�ois BERTEL Creation
//*****************************************************************************

class vsol_conic_2d;

//*****************************************************************************
// External declarations for values
//*****************************************************************************
#include <vsol/vsol_conic_2d_sptr.h>

#include <vsol/vsol_curve_2d.h>
#include <vsol/vsol_point_2d_sptr.h>
#include <vnl/vnl_double_3x3.h>
#include <vnl/vnl_math.h>

class vsol_conic_2d
  :public vsol_curve_2d
{
public:
  //---------------------------------------------------------------------------
  //: the different kinds of conic
  //---------------------------------------------------------------------------
  enum vsol_conic_type
  {
    degenerate=0,
    real_ellipse,
    real_circle,
    complex_ellipse,
    complex_circle,
    hyperbola,
    parabola,
    real_intersecting_lines,
    complex_intersecting_lines,
    real_parallel_lines,
    complex_parallel_lines,
    coincident_lines
  };

  //---------------------------------------------------------------------------
  //: Return the curve type
  //---------------------------------------------------------------------------
  virtual vsol_curve_2d_type curve_type(void) const { return vsol_curve_2d::CONIC; }

  //***************************************************************************
  // Initialization
  //***************************************************************************

  //---------------------------------------------------------------------------
  //: Constructor from coefficient of the cartesian equation
  //  `new_a'x^2+`new_b'xy+`new_c'y^2+`new_d'x+`new_e'y+`new_f'
  //---------------------------------------------------------------------------
  explicit vsol_conic_2d(double new_a,
                         double new_b,
                         double new_c,
                         double new_d,
                         double new_e,
                         double new_f);

  //---------------------------------------------------------------------------
  //: Copy constructor
  //---------------------------------------------------------------------------
  vsol_conic_2d(const vsol_conic_2d &other);

  //---------------------------------------------------------------------------
  //: Destructor
  //---------------------------------------------------------------------------
  virtual ~vsol_conic_2d();

  //---------------------------------------------------------------------------
  //: Clone `this': creation of a new object and initialization
  // See Prototype pattern
  //---------------------------------------------------------------------------
  virtual vsol_spatial_object_2d_sptr clone(void) const;

  //***************************************************************************
  // Access
  //***************************************************************************

  //---------------------------------------------------------------------------
  //: Coefficient of x^2
  //---------------------------------------------------------------------------
  inline double a(void) const { return a_; }

  //---------------------------------------------------------------------------
  //: Coefficient of xy
  //---------------------------------------------------------------------------
  inline double b(void) const { return b_; }

  //---------------------------------------------------------------------------
  //: Coefficient of y^2
  //---------------------------------------------------------------------------
  inline double c(void) const { return c_; }

  //---------------------------------------------------------------------------
  //: Coefficient of x
  //---------------------------------------------------------------------------
  inline double d(void) const { return d_; }

  //---------------------------------------------------------------------------
  //: Coefficient of y
  //---------------------------------------------------------------------------
  inline double e(void) const { return e_; }

  //---------------------------------------------------------------------------
  //: Constant coefficient
  //---------------------------------------------------------------------------
  inline double f(void) const { return f_; }

  //---------------------------------------------------------------------------
  //: Return the first point of `this'
  //---------------------------------------------------------------------------
  virtual vsol_point_2d_sptr p0(void) const;

  //---------------------------------------------------------------------------
  //: Return the last point of `this'
  //---------------------------------------------------------------------------
  virtual vsol_point_2d_sptr p1(void) const;

  //***************************************************************************
  // Comparison
  //***************************************************************************

  //---------------------------------------------------------------------------
  //: Has `this' the same coefficients than `other' ?
  //---------------------------------------------------------------------------
  virtual bool operator==(const vsol_conic_2d &other) const;
  virtual bool operator==(const vsol_spatial_object_2d& obj) const; // virtual of vsol_spatial_object_2d

  //---------------------------------------------------------------------------
  //: Has `this' not the same coefficients than `other' ?
  //---------------------------------------------------------------------------
  virtual bool operator!=(const vsol_conic_2d &other) const;

  //***************************************************************************
  // Status report
  //***************************************************************************

  //---------------------------------------------------------------------------
  //: Return the real type of a line. It is a CURVE
  //---------------------------------------------------------------------------
  vsol_spatial_object_2d_type spatial_type(void) const;

  //---------------------------------------------------------------------------
  //: Return the real type of the conic from its coefficients
  //---------------------------------------------------------------------------
  virtual vsol_conic_type real_type(void) const;

  //---------------------------------------------------------------------------
  //: Is `this' an real ellipse ?
  //---------------------------------------------------------------------------
  virtual bool is_real_ellipse(void) const;

  //---------------------------------------------------------------------------
  //: Is `this' a real circle ?
  //---------------------------------------------------------------------------
  virtual bool is_real_circle(void) const;

  //---------------------------------------------------------------------------
  //: Is `this' a complex ellipse ?
  //---------------------------------------------------------------------------
  virtual bool is_complex_ellipse(void) const;

  //---------------------------------------------------------------------------
  //: Is `this' a complex circle ?
  //---------------------------------------------------------------------------
  virtual bool is_complex_circle(void) const;

  //---------------------------------------------------------------------------
  //: Is `this' a parabola ?
  //---------------------------------------------------------------------------
  virtual bool is_parabola(void) const;

  //---------------------------------------------------------------------------
  //: Is `this' a hyperbola ?
  //---------------------------------------------------------------------------
  virtual bool is_hyperbola(void) const;

  //---------------------------------------------------------------------------
  //: Is `this' an real intersecting lines ?
  //---------------------------------------------------------------------------
  virtual bool is_real_intersecting_lines(void) const;

  //---------------------------------------------------------------------------
  //: Is `this' an complex intersecting lines ?
  //---------------------------------------------------------------------------
  virtual bool is_complex_intersecting_lines(void) const;

  //---------------------------------------------------------------------------
  //: Is `this' an coincident lines ?
  //---------------------------------------------------------------------------
  virtual bool is_coincident_lines(void) const;

  //---------------------------------------------------------------------------
  //: Return 3 ellipse parameters:
  //  -                            centre (`cx',`cy'),
  //  -                            orientation `phi',
  //  -                            size (`width',`height')
  //  REQUIRE: is_real_ellipse()
  //---------------------------------------------------------------------------
  virtual void ellipse_parameters(double &cx,
                                  double &cy,
                                  double &phi,
                                  double &width,
                                  double &height) const;

  //---------------------------------------------------------------------------
  //: Return 2 parabola parameters:
  //  -                             top (`cx',`cy'),
  //  -                             orientation (`cosphi',`sinphi')
  //  REQUIRE: is_parabola()
  //---------------------------------------------------------------------------
  virtual void parabola_parameters(double &cx,
                                   double &cy,
                                   double &cosphi,
                                   double &sinphi) const;

  //---------------------------------------------------------------------------
  //: Return the length of `this'
  //---------------------------------------------------------------------------
  virtual double length(void) const;

  //---------------------------------------------------------------------------
  //: Return the matrix associated to the coefficients.
  //  Has to be deleted manually
  //---------------------------------------------------------------------------
  virtual vnl_double_3x3 *matrix(void) const;

  //***************************************************************************
  // Status setting
  //***************************************************************************

  //---------------------------------------------------------------------------
  //: Set the first point of the curve
  //  REQUIRE: in(new_p0)
  //---------------------------------------------------------------------------
  virtual void set_p0(const vsol_point_2d_sptr &new_p0);

  //---------------------------------------------------------------------------
  //: Set the last point of the curve
  //  REQUIRE: in(new_p1)
  //---------------------------------------------------------------------------
  virtual void set_p1(const vsol_point_2d_sptr &new_p1);

  //***************************************************************************
  // Basic operations
  //***************************************************************************

  //---------------------------------------------------------------------------
  //: Is `p' in `this' ? (ie `p' verifies the equation)
  //---------------------------------------------------------------------------
  virtual bool in(const vsol_point_2d_sptr &p) const;

private:
  //***************************************************************************
  // Internals
  //***************************************************************************

  //---------------------------------------------------------------------------
  //: Are `x' and `y' almost equal ?
  //  the comparison uses an adaptative epsilon
  //---------------------------------------------------------------------------
  inline static bool are_equal(double x, double y) {
    // epsilon is a fixed fraction of the absolute average of x and y
    const double epsilon=1e-6*(vnl_math_abs(x)+vnl_math_abs(y));
    // <=epsilon but not <epsilon, to compare to null values
    return vnl_math_abs(x-y)<=epsilon;
  }

  //---------------------------------------------------------------------------
  //: Is `x' almost zero ?
  //  the comparison uses a fixed epsilon, as the adaptive one from
  //  are_equal() makes no sense here.
  //---------------------------------------------------------------------------
  static bool is_zero(double x) { return vnl_math_abs(x)<=1e-6; }

private:
  //***************************************************************************
  // Implementation
  //***************************************************************************

  //---------------------------------------------------------------------------
  //: Coefficient of x^2
  //---------------------------------------------------------------------------
  double a_;

  //---------------------------------------------------------------------------
  //: Coefficient of xy
  //---------------------------------------------------------------------------
  double b_;

  //---------------------------------------------------------------------------
  //: Coefficient of y^2
  //---------------------------------------------------------------------------
  double c_;

  //---------------------------------------------------------------------------
  //: Coefficient of x
  //---------------------------------------------------------------------------
  double d_;

  //---------------------------------------------------------------------------
  //: Coefficient of y
  //---------------------------------------------------------------------------
  double e_;

  //---------------------------------------------------------------------------
  //: Constant coefficient
  //---------------------------------------------------------------------------
  double f_;

  //---------------------------------------------------------------------------
  //: First point of the curve
  //---------------------------------------------------------------------------
  vsol_point_2d_sptr p0_;

  //---------------------------------------------------------------------------
  //: Last point of the curve
  //---------------------------------------------------------------------------
  vsol_point_2d_sptr p1_;
};

#endif // #ifndef VSOL_CONIC_2D_H
