// Oliver Kullmann, 10.11.2006 (Swansea)
/* Copyright 2006 - 2007 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Programming/Utilities/OrderRelations/plans/general.hpp
  \brief Plans for the module on order relations


  \todo Update namespaces.


  \todo Update namespace usage.


  \todo Write doxygen documentation


  \todo Write docus
  <ul>
   <li> Clarify the relations to similar facilities in the standard library
   and in Boost. </li>
  </ul>


  \todo Write demos.


  \todo Write tests (in the new system).


  \todo String comparison
  <ul>
   <li> Lexicographical comparison of C-strings via
   \code
#include <functional>
#include <cstdlib>
struct string_compare : std::binary_function<const char*, const char*, bool> {
  bool operator() (const char* const a, const char* const b) {
    return std::strcmp(a,b) < 0;
  }
};
   \endcode
   </li>
   <li> Isn't there a standard implementation?! </li>
  </ul>

*/

/*!
  \namespace OKlib::OrderRelations
  \brief Components for handling order relations
*/

namespace OKlib {
  namespace OrderRelations {
  }
}

