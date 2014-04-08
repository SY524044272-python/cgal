// Copyright (c) 2011-2013 GeometryFactory
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL:$
// $Id:$
//
// Author(s)     : Ilker O. Yaz

#ifndef CGAL_SURFACE_MODELING_SPOKES_AND_RIMS_ITERATOR_H
#define CGAL_SURFACE_MODELING_SPOKES_AND_RIMS_ITERATOR_H
/// @cond CGAL_DOCUMENT_INTERNAL

namespace CGAL {
namespace internal {
/** 
 * Currently this class is not used by surface modeling package, just leave it for possible future need.
 * Provide simple functionality for iterating over spoke and rim edges
 *   - use get_descriptor() to obtain active edge
 *   - get_iterator() always holds spoke edges */
 /// \code
 /// // how to use Spokes_and_rims_iterator
 /// boost::tie(e_begin, e_end) = boost::out_edges(vertex, halfedge_graph);
 /// Spokes_and_rims_iterator<HalfedgeGraph> rims_it(e_begin, halfedge_graph);
 /// 
 /// for ( ; rims_it.get_iterator() != e_end; ++rims_it )
 /// {
 ///   edge_descriptor active_edge = rims_it.get_descriptor();
 ///   // use active_edge as you like
 /// }
 /// \endcode
template<class HalfedgeGraph>
class Spokes_and_rims_iterator
{
public:
  typedef typename boost::graph_traits<HalfedgeGraph>::out_edge_iterator	out_edge_iterator;
  typedef typename boost::graph_traits<HalfedgeGraph>::edge_descriptor		edge_descriptor; 

  Spokes_and_rims_iterator(out_edge_iterator edge_iterator, HalfedgeGraph& halfedge_graph)
    : is_current_rim(false), iterator(edge_iterator), descriptor(*edge_iterator), halfedge_graph(halfedge_graph)
  { }

  /// descriptor will be assigned to next valid edge, note that iterator might not change
  Spokes_and_rims_iterator<HalfedgeGraph>&
  operator++() 
  {
    // loop through one spoke then one rim edge
    if(!is_current_rim && !boost::get(CGAL::edge_is_border, halfedge_graph, descriptor)) // it is rim edge's turn
    {
	    is_current_rim = true;
	    descriptor = CGAL::next_edge(descriptor, halfedge_graph);
    }
    else // if current edge is rim OR there is no rim edge (current spoke edge is boudary)
    {    // then iterate to next spoke edge
	    is_current_rim = false;
	    descriptor = *(++iterator);
    }
    return *this;
  }

  out_edge_iterator get_iterator()   { return iterator; }
  edge_descriptor   get_descriptor() { return descriptor; }

private:
  bool is_current_rim;        ///< current descriptor is rim or spoke
  out_edge_iterator iterator; ///< holds spoke edges (i.e. descriptor is not always = *iterator)
  edge_descriptor descriptor; ///< current active edge descriptor for looping
  HalfedgeGraph& halfedge_graph;
};

}//namespace internal
/// @endcond
}//namespace CGAL
#endif //CGAL_SURFACE_MODELING_SPOKES_AND_RIMS_ITERATOR_H
