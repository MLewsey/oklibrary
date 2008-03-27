// Oliver Kullmann, 27.3.2008 (Swansea)
/* Copyright 2008 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file ComputerAlgebra/Satisfiability/Lisp/Resolution/plans/PrimeImplicatesImplicants.hpp
  \brief Plans for Maxima-components regarding computation of prime implicates/implicants of boolean functions and clause-sets
  
  
  \todo min_2resolution_closure_cs
  <ul>
   <li> Currently the name likely is not corrected, since if the input is not
   a full clause-set, then likely we do not compute the min-closure under
   2-subsumption resolution (example?). </li>
  </ul>


  \todo Dualisation
  <ul>
   <li> Implement the algorithm given by "dual_cs" in
   ComputerAlgebra/Satisfiability/Lisp/ClauseSets/Constructions.mac
   </li>
   <li> Or sh0uld this go somewhere else?? </li>
  </ul>


  \todo Connections
  <ul>
   <li> The above dualisation yields a representation of all
   satisfying assignments:
    <ol>
     <li> See
     ComputerAlgebra/Satisfiability/Lisp/Counting/plans/general.hpp
     </li>
     <li> See AllSolutions/plans/general.hpp, and especially
     AllSolutions/plans/MinimalAssignments.hpp. </li>
    </ol>
   </li>
  </ul>


  \todo Hitting clause-sets
  <ul>
   <li> The input of Quine/McCluskey is a (special) hitting clause-set
   (namely a full clause-set) --- can we somehow generalise the algorithm
   to work with arbitrary hitting clause-sets? </li>
   <li> Given a hitting clause-set F, we can easily compute for each
   clause C in F a prime implicate C' <= C of F, by greedily removing
   literals from C and checking whether still F implies C' holds.
    <ol>
     <li> Can all prime implicates of F be obtained in this way (for
     fixed F)? Likely not (examples?). </li>
     <li> Likely there can be exponentially many prime implicates
     C' <= C ? </li>
     <li> And likely it is hard to find some C' of minimal length? </li>
     <li> Once we know phi_C' * F is unsatisfiable, it should be possible
     to read off directly from this computation which literals from C'
     can be further dropped. </li>
    </ol>
   </li>
   <li> In this way we obtain F' <= F consisting of some prime implicates
   of F such that F' is equivalent to F. By removing redundant clauses
   from F' we can further go into the direction of a shortest CNF
   representation of the underlying boolean function.
    <ol>
     <li> Since SAT solvers can be used to obtain F, in this way we can
     harness the power of SAT solvers (w.r.t. computing small splitting
     trees) for computing small CNF/DNF representations. </li>
    </ol>
   </li>
   <li> It should be possible to compute with polynomial delay
   all prime implicates which are subsuming some clause from F.
  </ul>

*/
