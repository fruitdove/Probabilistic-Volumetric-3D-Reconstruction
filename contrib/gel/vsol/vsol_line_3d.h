#ifndef vsol_line_3d_h
#define vsol_line_3d_h
//*****************************************************************************
//
// .NAME vsol_line_3d - Straight line segment in a 3D space.
// .LIBRARY vsol
// .INCLUDE vsol/vsol_line_3d.h
// .FILE    vsol/vsol_line_3d.cxx
//
// .SECTION Description
// The direction gives the orientation and the length of the segment
//
// .SECTION Author
// Fran�ois BERTEL
//
// .SECTION Modifications
// 2000/06/17 Peter Vanroose  Implemented all operator==()s and type info
// 2000/05/03 Fran�ois BERTEL Creation
//*****************************************************************************

class vsol_line_3d;

//*****************************************************************************
// External declarations for values
//*****************************************************************************
#include <vsol/vsol_line_3d_sptr.h>

#include <vsol/vsol_curve_3d.h>
#include <vsol/vsol_point_3d_sptr.h>

#include <vnl/vnl_vector_fixed.h>
#include <vgl/vgl_homg_line_3d_2_points.h>

class vsol_line_3d
  :public vsol_curve_3d
{
  //***************************************************************************
  // Initialization
  //***************************************************************************
public:
  //---------------------------------------------------------------------------
  //: Constructor from the direction and the middle point
  //---------------------------------------------------------------------------
  explicit vsol_line_3d(const vnl_vector_fixed<double,3> &new_direction,
                        const vsol_point_3d_sptr &new_middle);

  //---------------------------------------------------------------------------
  //: Constructor from the first and the last point of the straight line
  //---------------------------------------------------------------------------
  explicit vsol_line_3d(const vsol_point_3d_sptr &new_p0,
                        const vsol_point_3d_sptr &new_p1);

  //---------------------------------------------------------------------------
  //: Copy constructor
  //  no duplication of the points
  //---------------------------------------------------------------------------
  vsol_line_3d(const vsol_line_3d &other);

  //---------------------------------------------------------------------------
  //: Destructor
  //---------------------------------------------------------------------------
  virtual ~vsol_line_3d();

  //---------------------------------------------------------------------------
  //: Return the curve type
  //---------------------------------------------------------------------------
  virtual vsol_curve_3d_type curve_type(void) const { return vsol_curve_3d::LINE; }

  //---------------------------------------------------------------------------
  //: Clone `this': creation of a new object and initialization
  //  See Prototype pattern
  //---------------------------------------------------------------------------
  virtual vsol_spatial_object_3d_sptr clone(void) const;

  //***************************************************************************
  // Access
  //***************************************************************************

  //---------------------------------------------------------------------------
  //: Middle point of the straight line segment
  //---------------------------------------------------------------------------
  virtual vsol_point_3d_sptr middle(void) const;

  //---------------------------------------------------------------------------
  //: direction of the straight line segment. Has to be deleted manually
  //---------------------------------------------------------------------------
  virtual vnl_vector_fixed<double,3> *direction(void) const;

  //---------------------------------------------------------------------------
  //: First point of the straight line segment
  //---------------------------------------------------------------------------
  virtual vsol_point_3d_sptr p0(void) const;

  //---------------------------------------------------------------------------
  //: Last point of the straight line segment
  //---------------------------------------------------------------------------
  virtual vsol_point_3d_sptr p1(void) const;

  //***************************************************************************
  // Comparison
  //***************************************************************************

  //---------------------------------------------------------------------------
  //: Has `this' the same points than `other' ?
  //---------------------------------------------------------------------------
  virtual bool operator==(const vsol_line_3d &other) const;
  virtual bool operator==(const vsol_spatial_object_3d& obj) const; // virtual of vsol_spatial_object_3d

  //---------------------------------------------------------------------------
  //: Has `this' not the same points than `other' ?
  //---------------------------------------------------------------------------
  virtual bool operator!=(const vsol_line_3d &other) const;

  //***************************************************************************
  // Status report
  //***************************************************************************

  //---------------------------------------------------------------------------
  //: Return the real type of a line. It is a CURVE
  //---------------------------------------------------------------------------
  virtual vsol_spatial_object_3d_type spatial_type(void) const;

  //---------------------------------------------------------------------------
  //: Compute the bounding box of `this'
  //---------------------------------------------------------------------------
  virtual void compute_bounding_box(void);

  //---------------------------------------------------------------------------
  //: Return the length of `this'
  //---------------------------------------------------------------------------
  virtual double length(void) const;

  //***************************************************************************
  // Status setting
  //***************************************************************************

  //---------------------------------------------------------------------------
  //: Set the first point of the straight line segment
  //---------------------------------------------------------------------------
  virtual void set_p0(const vsol_point_3d_sptr &new_p0);

  //---------------------------------------------------------------------------
  //: Set the last point of the straight line segment
  //---------------------------------------------------------------------------
  virtual void set_p1(const vsol_point_3d_sptr &new_p1);

  //---------------------------------------------------------------------------
  //: Set the length of `this'. Doesn't change middle point and orientation.
  //  If p0 and p1 are equal then the direction is set to (1,0,0)
  //  REQUIRE: new_length>=0
  //---------------------------------------------------------------------------
  virtual void set_length(const double new_length);

  //***************************************************************************
  // Basic operations
  //***************************************************************************

  //---------------------------------------------------------------------------
  //: Is `p' in `this' ?
  //---------------------------------------------------------------------------
  virtual bool in(const vsol_point_3d_sptr &p) const;

  //---------------------------------------------------------------------------
  //: Return the tangent to `this' at `p'. Has to be deleted manually
  //  REQUIRE: in(p)
  //---------------------------------------------------------------------------
  virtual vgl_homg_line_3d_2_points<double> *
  tangent_at_point(const vsol_point_3d_sptr &p) const;

  //***************************************************************************
  // Implementation
  //***************************************************************************
private:

  //---------------------------------------------------------------------------
  // Description: First point of the straight line segment
  //---------------------------------------------------------------------------
  vsol_point_3d_sptr p0_;

  //---------------------------------------------------------------------------
  // Description: Last point of the straight line segment
  //---------------------------------------------------------------------------
  vsol_point_3d_sptr p1_;
};

#endif // vsol_line_3d_h
