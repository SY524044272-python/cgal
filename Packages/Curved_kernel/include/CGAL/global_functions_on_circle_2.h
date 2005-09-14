#ifndef CGAL_CURVED_KERNEL_GLOBAL_FUNCTIONS_ON_CIRCLE_2_H
#define CGAL_CURVED_KERNEL_GLOBAL_FUNCTIONS_ON_CIRCLE_2_H

namespace CGAL {

template< class CK >
inline
typename CK::Polynomial_for_circles_2_2
get_equation(const typename CK::Circle_2 & c)
{
  return CK().get_equation_object()(c);
}

template< class CK >
inline
typename CK::Circle_2
construct_circle_2(const typename CK::Polynomial_for_circles_2_2 & eq)
{
  return CK().construct_circle_2_object()(eq);
}

template< class CK, class OutputIterator>
inline
OutputIterator
intersect_2( const typename CK::Circle_2 & c1,
			   const typename CK::Circle_2 & c2,
			   OutputIterator res )
{
  return CK().intersect_2_object()(c1,c2,res);
}

template< class CK >
inline
bool
has_on_2(const typename CK::Circle_2 &c, const typename CK::Circular_arc_point_2 &p)
{
  return CK().has_on_2_object()(c, p);
}

} // namespace CGAL
#endif // CGAL_CURVED_KERNEL_GLOBAL_FUNCTIONS_ON_CIRCLE_2_H
