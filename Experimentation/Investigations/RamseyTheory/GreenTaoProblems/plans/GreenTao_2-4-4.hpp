// Oliver Kullmann, 3.2.2009 (Swansea)
/* Copyright 2009 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Experimentation/Investigations/RamseyTheory/GreenTaoProblems/plans/GreenTao_2-4-4.hpp
  \brief Investigations on greentao_2(4)


  \todo greentao_2(4) = 512
  <ul>
   <li> greentao_2(4) > 400 (trivial for OKsolver-2002). </li>
   <li> greentao_2(4) > 420 with 6683 nodes (OKsolver-2002). </li>
   <li> greentao_2(4) > 430 with 22267 nodes (OKsolver-2002). </li>
   <li> greentao_2(4) > 440 with 77791 nodes (OKsolver-2002). </li>
   <li> greentao_2(4) > 450 with 349914 nodes (OKsolver-2002). </li>
   <li> greentao_2(4) > 460 with 12777 nodes (OKsolver-2002). </li>
   <li> greentao_2(4) > 470 with 59506 nodes (OKsolver-2002). </li>
   <li> greentao_2(4) > 471 with 58889 nodes (OKsolver-2002). </li>
   <li> greentao_2(4) > 472 with 370222 nodes (OKsolver-2002). </li>
   <li> For this n, rnovelty finds a solution quickly (~ 100000 steps).
   </li>
   <li> n = 473: stopped after 884587 nodes (OKsolver). </li>
   <li> But found satisfiable with rnovelty. </li>
   <li> And rnovelty+ is even better. </li>
   <li> n = 480: stopped after 1536394 nodes (OKsolver). </li>
   <li> n = 500: Running it with
   \verbatim
OKsolver_2002-O3-DNDEBUG -M -D18 -F GreenTao_2_4_500.cnf
   \endverbatim
   found a solution after 11 hours (38,937,288 nodes; roughly 2% of the
   search space, looking at depth 18). </li>
   <li> Found satisfiable with rnovelty+. </li>
   <li> n = 510 found satisfiable with rnovelty+. </li>
   <li> n = 511 found satisfiable with rnovelty+. </li>
   <li> n = 512: rnovelty+ yields constantly 1 falsified clause
   (also with "-runs 500 -cutoff 10000000"). </li>
   <li>
   \verbatim
OKplatform> OKsolver_2002-O3-DNDEBUG -M -D16 GreenTao_2_4_512.cnf
   \endverbatim
   finished the first branch (~ 32768 nodes at depth 16) after 9 days
   (cs-wsok) and thus
   <center> greentao_2(4) = 512. </center> </li>
   <li>  Density is 8.7734375; here always counting all variables (though
   2 variables are missing). </li>
   <li> Stopped the computation:
   \verbatim
33082:  7497, 780471.5, 765655.7

s UNKNOWN
c sat_status=2 initial_maximal_clause_length=4 initial_number_of_variables=510 initial_number_of_clauses=4492 initial_number_of_literal_occurrences=17968 running_time(s)=780475.6 number_of_nodes=765469925 number_of_single_nodes=58 number_of_quasi_single_nodes=0 number_of_2-reductions=4696146230 number_of_pure_literals=728446 number_of_autarkies=2 number_of_missed_single_nodes=11248 max_tree_depth=61 number_of_table_enlargements=0 reduced_maximal_clause_length=0 reduced_number_of_variables=0 reduced_number_of_clauses=0 reduced_number_of_literal_occurrences=0 number_of_1-autarkies=31556781 number_of_initial_unit-eliminations=0 number_of_new_2-clauses=0 maximal_number_of_added_2-clauses=0 initial_number_of_2-clauses=0 file_name=GreenTao_2_4_512.cnf
   \endverbatim
   </li>
   <li> n = 515: rnovelty+ yields constantly 1 falsified clause. </li>
   <li> n = 520: rnovelty+ yields constantly 1 falsified clause. </li>
   <li> n = 530: rnovelty+ yields constantly 1 falsified clause. </li>
   <li> n = 540: rnovelty+ yields constantly 1 falsified clause. </li>
   <li> n = 550: rnovelty+ yields constantly 2 falsified clauses. </li>
   <li> n = 600: rnovelty+ yields constantly 6 falsified clauses. </li>
   <li> Minisat looks weak on these instances. </li>
   <li> And Grasp likely doesn't work here neither. </li>
   <li> But march_pl seems stronger on the satisfiable instances than
   OKsolver-2002, though n=500 seems also difficult. </li>
  </ul>

*/
