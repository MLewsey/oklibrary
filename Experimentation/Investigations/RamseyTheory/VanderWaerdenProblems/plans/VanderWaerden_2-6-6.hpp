// Oliver Kullmann, 16.2.2009 (Swansea)
/* Copyright 2009 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Experimentation/Investigations/RamseyTheory/VanderWaerdenProblems/plans/VanderWaerden_2-6-6.hpp
  \brief On investigations into vanderwaerden_2(6) = 1132


  \todo Basic statistics for n=1132
  <ul>
   <li> Density = 225.6 </li>
  </ul>


  \todo Local search solvers
  <ul>
   <li> n = 1000
    <ul>
     <li> ubcsat-irots seems best. </li>
     <li> But finding a solution seems hopeless; less than 1400 falsified
     clauses seems to require billions of steps --- the difference between
     100,000 and 10,000,000 steps is very small. </li>
     <li> We need to look into the Heule-et-al article. </li>
    </ul>
   </li>
  </ul>


  \todo Upper bounds
  <ul>
   <li> n = 1132
    <ol>
     <li> OKsolver-2002
     \verbatim
> OKsolver_2002-O3-DNDEBUG -M -D30 VanderWaerden_2_6_1132.cnf
     \endverbatim
     looks hopeless (no node of depth 30 solved in one hour). </li>
    </ol>
   </li>
  </ul>

*/

