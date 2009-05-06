// Oliver Kullmann, 6.5.2009 (Swansea)
/* Copyright 2009 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Applications/RamseyTheory/plans/GreenTaoProblems.hpp
  \brief Plans on the module on computing Green-Tao numbers (and related quantities)


  \todo Connections
  <ul>
   <li> See
   ComputerAlgebra/Satisfiability/Lisp/Generators/plans/VanderWaerdenProblems.hpp
   and
   ComputerAlgebra/Satisfiability/Lisp/Generators/VanderWaerdenProblems.mac.
   </li>
   <li> See
   Experimentation/Investigations/RamseyTheory/GreenTaoProblems/plans/general.hpp.
   </li>
   <li> See the various generators in Satisfiability/Transformers/Generators/
   (they should all be moved to here). </li>
  </ul>


  \todo Generator for Green-Tao problems
  <ul>
   <li> We need to write a program with functionality like arithprog_primes_hg
   from the Maxima/Lisp level (and all the other functions there in
   ComputerAlgebra/Satisfiability/Lisp/Generators/VanderWaerdenProblems.mac).
   </li>
   <li> See
   Experimentation/Investigations/RamseyTheory/plans/GreenTaoProblems.hpp
   for experiments. </li>
   <li> Best we provide this functionality as Unix tools as well as at
   library level. </li>
   <li> Perhaps this hypergraph creation happens in
   OKlib/Combinatorics/Hypergraphs, while here we plug these
   hypergraphs together to get a clause-set. </li>
   <li> The hypergraph can be output as a positive clause-set,
   in DIMACS format, into a file. </li>
   <li> From OKlib/Satisfiability/Transformers we get the tools
   for standardising the names. </li>
   <li> Perhaps the number-theoretical tools should go to
   OKlib/Structures/NumberTheory.
    <ol>
     <li> Enumerating the primes:
      <ol>
       <li> Gmp has a "mpz_nextprime" function, by which we first create the
       complete list of primes and the corresponding boolean array (for the
       primality predicate). </li>
       <li> Optionally, if one of the randomised tests is not secure, then the
       whole computation is checked via a simple sieve of Erathostenes. </li>
      </ol>
     </li>
    </ol>
   </li>
   <li> Also important to be able to compute the various statistics on
   arithmetical progressions of primes (without creating hypergraphs or
   clause-sets). </li>
  </ul>

*/