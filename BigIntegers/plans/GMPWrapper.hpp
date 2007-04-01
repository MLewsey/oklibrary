// Oliver Kullmann, 19.10.2005 (Swansea)

/*!
  \file BigIntegers/plans/GMPWrapper.hpp
  \brief Plans for the sub-module for wrapping the GMP-C-approach into a class according to the basic concept.

  \todo Design the concept of a wrapper.

  The main first "client" is the OKgenerator (see
  RandomGenerator/plans/RandomGenerator.hpp)

  \todo Write tests for the concepts

  \todo Implementation of the basic wrappers:
  I guess, best based on the C-interface.
  <ul>
   <li> constructor uses mpz_init </li>
   <li> destructor uses mpz_clear </li>
  </ul>
*/

