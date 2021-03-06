// Oliver Kullmann, 23.5.2009 (Swansea)
/* Copyright 2009 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Experimentation/Investigations/RamseyTheory/GreenTaoProblems/plans/GreenTao_3-3-4-k.hpp
  \brief On investigations into Green-Tao numbers greentao_3(3,4,k)
  

  \todo greentao_3(3,4,4) > 1537
  <ul>
   <li> Creating problems via output_greentao_stdname([3,4,4],n). </li>
   <li> n=500 trivially satisfiable (adaptnovelty+). </li>
   <li> n=600 trivially satisfiable. </li>
   <li> n=700 trivially satisfiable. </li>
   <li> n=900 trivially satisfiable. </li>
   <li> n=1000 trivially satisfiable. </li>
   <li> n=1100 still easy to solve (cutoff=100*10^3). </li>
   <li> n=1200 still easy to solve (cutoff=10^6). </li>
   <li> n=1300 rather easy to solve (cutoff=10^6). </li>
   <li> n=1400: one solution in 10 runs with cutoff=10^6. </li>
   <li> n=1500: only min=3 for 10 runs with cutoff=10*10^6; cutoff=100*10^6
   found a solution in the third run (osteps=39412430, seed=1928236138). </li>
   <li> n=1512: one run in 10 with cutoff=100*10^6 found a solution
   (osteps=37551993, seed=4046775428). While another 100 runs with this
   cutoff actually found no solution. </li>
   <li> n=1518
    <ol>
     <li> 9 runs with cutoff=100*10^6 yield only a minimum of 2. </li>
     <li> cutoff=500*10^6: run 18 found a solution (osteps=309459026,
     seed=3122222825). </li>
    </ol>
   </li>
   <li> n=1525
    <ol>
     <li> 10 runs with cutoff=100*10^6 yield only min=2. </li>
     <li> cutoff=500*10^6: run 16 yields a solution (msteps=375313903,
     seed=2274305602). </li>
    </ol>
   </li>
   <li> n=1531: cutoff=5*10^8 yields a solution (seed=1692755539) in
   run 12. </li>
   <li> n=1532
    <ol>
     <li> cutoff=5*10^8 yields in 10 runs only once min=1. </li>
     <li> cutoff=10^9 yields in run 15 a solution (seed=1453937791). </li>
    </ol>
   </li>
   <li> n=1534
    <ol>
     <li> cutoff=5*10^8 yields in 23 runs only 4 times min=1. </li>
     <li> cutoff=10^9 yields in run 6 a solution (seed=1913394293). </li>
    </ol>
   </li>
   <li> n=1535
    <ol>
     <li> cutoff=10^9 yields in 9 runs only min=2. </li>
     <li> cutoff=2*10^9 yields in run 18 a solution (seed=238771004,
     osteps=47373687). </li>
    </ol>
   </li>
   <li> n=1537
    <ol>
     <li> 16 runs with cutoff=5*10^8 only yield min=1 twice. </li>
     <li> cutoff=10^9 yields in 12 runs min=1 twice, so a cutoff of
     2*10^9 would be needed. </li>
     <li> cutoff=10^8, 1000 runs: In run 213 a solution was found
     (seed=2884500780, osteps=42486702). </li> </li>
    </ol>
   </li>
   <li> n=1538 </li>
   <li> n=1550
    <ol>
     <li> Looks (at first sight) unsatisfiable: 10 runs with
     cutoff=10^8 yield min=3 (twice; so cutoff=10^9 would be needed). </li>
     <li> cutoff=5*10^8: 13 runs only yield min=2, so a cutoff of 2.5*10^9
     would be needed. </li>
     <li> cutoff=10^8, 1000 runs yields
     \verbatim
> E = read_ubcsat("GreenTao_3-3-4-4_1550.cnf_OUT")
  1   2   3   4   5   6   7   8   9
  1  17  75 123 166 241 232 133  12
1000
     \endverbatim
     so perhaps 100 * 1000 runs would be needed to find a solution. </li>
     <li> cutoff = 10^9 yields
     \verbatim
 1  2  3  4  5  6
 5 46 35  6  6  2
100
     \endverbatim
     </li>
    </ol>
   </li>
  </ul>


  \todo greentao_3(3,4,5) > 7000
  <ul>
   <li> n=1000 trivial for adaptnovelty+. </li>
   <li> n=2000 trivial for adaptnovelty+ (70% success with cutoff=10^4). </li>
   <li> n=2200 trivial for adaptnovelty+ (70% success with cutoff=10^4). </li>
   <li> n=3000 trivial for adaptnovelty+ (90% success with cutoff=10^5). </li>
   <li> n=4000 simple for adaptnovelty+ (100% success with cutoff=10^6). </li>
   <li> n=5000 simple for adaptnovelty+ (40% success with cutoff=10^6). </li>
   <li> n=6000 simple for adaptnovelty+ (100% success with cutoff=10^7). </li>
   <li> n=7000
    <ol>
     <li> cutoff=10^7 yields min=4 in 10 runs. </li>
     <li> cutoff=10^8: 100% success. </li>
    </ol>
   </li>
   <li> n=8000 </li>
  </ul>
  
*/

