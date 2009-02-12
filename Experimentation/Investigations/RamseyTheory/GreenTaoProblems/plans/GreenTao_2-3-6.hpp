// Oliver Kullmann, 4.2.2009 (Swansea)
/* Copyright 2009 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Experimentation/Investigations/RamseyTheory/GreenTaoProblems/plans/GreenTao_2-3-6.hpp
  \brief Investigations on greentao_2(3,6)


  \todo Establishing the target
  <ul>
   <li> Analysing the sequence 4,7,23,79,528 by linear regressions seems to
   suggest it is linear in the log-log, and a linear model then is
   exp(exp(-0.05899 + i * 0.38269)), which would yield 11691 as the
   next term. </li>
   <li> I would guess that this is too big (more like 6000). </li>
   <li> n = 5000 looks actually highly unsatisfiable:
   \verbatim
> ubcsat-okl -alg rnovelty+ -runs 10 -cutoff 100000 -i GreenTao_2_3_6_5000.cnf
       sat  min     osteps     msteps       seed
      1 0   762      95596     100000 1800420164
      2 0   757      87106     100000 1703561105
> ubcsat-okl -alg rnovelty+ -runs 10 -cutoff 1000000 -i GreenTao_2_3_6_5000.cnf
       sat  min     osteps     msteps       seed
      1 0   728     346940    1000000 1829692653
      2 0   723     924133    1000000 4140965461
      3 0   724     835749    1000000  415080732
      4 0   705     843568    1000000 1307725777
      5 0   727     209350    1000000 2801750750
      6 0   726     652002    1000000 3411586467
> ubcsat-okl -alg rnovelty+ -runs 10 -cutoff 10000000 -i GreenTao_2_3_6_5000.cnf
       sat  min     osteps     msteps       seed
      1 0   714    7083923   10000000  621767107
   \endverbatim
   </li>
   <li> Of course, one needs to investigate again which ubcsat-algorithm
   works best here --- these problems are highly constrained. </li>
   <li> n = 4000 still loks unsatisfiable:
   \verbatim
> ubcsat-okl -alg rnovelty+ -runs 10 -cutoff 100000 -i GreenTao_2_3_6_4000.cnf
Clauses = 547577
Variables = 4000
TotalLiterals = 1648107
FlipsPerSecond = 8108
BestStep_Mean = 54674.900000
Steps_Mean = 100000.000000
Steps_Max = 100000.000000
PercentSuccess = 0.00
BestSolution_Mean = 393.700000
BestSolution_Median = 392.500000
BestSolution_Min = 376.000000
BestSolution_Max = 411.000000
> ubcsat-okl -alg rnovelty+ -runs 10 -cutoff 1000000 -i GreenTao_2_3_6_4000.cnf
       sat  min     osteps     msteps       seed
      1 0   378     131403    1000000  549915421
   \endverbatim
   </li>
   <li> n = 2000 is satisfiable: ubcsat-rnovelty+ found a solution
   with msteps=419656 and seed=1409958555 (cutoff = 10^6). </li>
   <li> So we assume 2000 < greentao_2(3,6) < 4000. </li>
  </ul>


  \todo Finding the best algorithm from ubcsat
  <ul>
   <li> adaptnovelty+ seems best:
   \verbatim
> ubcsat-okl -alg adaptnovelty+ -runs 10 -i GreenTao_2-3-6_2250.cnf
Clauses = 185490
Variables = 2250
TotalLiterals = 558633
FlipsPerSecond = 18008
BestStep_Mean = 88748.500000
Steps_Mean = 100000.000000
Steps_Max = 100000.000000
PercentSuccess = 0.00
BestSolution_Mean = 20.200000
BestSolution_Median = 20.000000
BestSolution_Min = 18.000000
BestSolution_Max = 22.000000
> ubcsat-okl -alg adaptnovelty+ -runs 10 -cutoff 1000000 -i GreenTao_2-3-6_2250.cnf
Clauses = 185490
Variables = 2250
TotalLiterals = 558633
FlipsPerSecond = 33208
BestStep_Mean = 695169.500000
Steps_Mean = 1000000.000000
Steps_Max = 1000000.000000
PercentSuccess = 0.00
BestSolution_Mean = 9.700000
BestSolution_Median = 9.500000
BestSolution_Min = 7.000000
BestSolution_Max = 12.000000
> ubcsat-okl -alg adaptnovelty+ -runs 10 -cutoff 10000000 -i GreenTao_2-3-6_2250.cnf
Clauses = 185490
Variables = 2250
TotalLiterals = 558633
FlipsPerSecond = 42551
BestStep_Mean = 3400237.000000
Steps_Mean = 10000000.000000
Steps_Max = 10000000.000000
PercentSuccess = 0.00
BestSolution_Mean = 7.700000
BestSolution_Median = 7.500000
BestSolution_Min = 7.000000
BestSolution_Max = 9.000000
> ubcsat-okl -alg adaptnovelty+ -runs 10 -cutoff 100000000 -i GreenTao_2-3-6_2250.cnf
Clauses = 185490
Variables = 2250
TotalLiterals = 558633
FlipsPerSecond = 49276
BestStep_Mean = 25508521.900000
Steps_Mean = 100000000.000000
Steps_Max = 100000000.000000
PercentSuccess = 0.00
BestSolution_Mean = 6.100000
BestSolution_Median = 6.000000
BestSolution_Min = 5.000000
BestSolution_Max = 7.000000
> ubcsat-okl -alg adaptnovelty+ -runs 10 -cutoff 1000000000 -i GreenTao_2-3-6_2250.cnfClauses = 185490
Variables = 2250
TotalLiterals = 558633
FlipsPerSecond = 72631
BestStep_Mean = 172037848.800000
Steps_Mean = 1000000000.000000
Steps_Max = 1000000000.000000
PercentSuccess = 0.00
BestSolution_Mean = 5.000000
BestSolution_Median = 5.000000
BestSolution_Min = 5.000000
BestSolution_Max = 5.000000
   \endverbatim
   (Seems that 5 falsified clauses is the minimum.)
   </li>
   <li> Also "walksat-tabu -v nonull" seems better than rnovelty+ (but not as
   good as adaptnovelty+):
   \verbatim
> ubcsat-okl -alg  walksat-tabu -v nonull -runs 10 -i GreenTao_2-3-6_2250.cnf
Clauses = 185490
Variables = 2250
TotalLiterals = 558633
FlipsPerSecond = 24728
BestStep_Mean = 66136.100000
Steps_Mean = 100000.000000
Steps_Max = 100000.000000
PercentSuccess = 0.00
BestSolution_Mean = 21.300000
BestSolution_Median = 22.000000
BestSolution_Min = 13.000000
BestSolution_Max = 25.000000
> ubcsat-okl -alg  walksat-tabu -v nonull -runs 10 -cutoff 1000000 -i GreenTao_2-3-6_2250.cnf
Clauses = 185490
Variables = 2250
TotalLiterals = 558633
FlipsPerSecond = 32283
BestStep_Mean = 642215.000000
Steps_Mean = 1000000.000000
Steps_Max = 1000000.000000
PercentSuccess = 0.00
BestSolution_Mean = 14.500000
BestSolution_Median = 14.500000
BestSolution_Min = 11.000000
BestSolution_Max = 16.000000
   \endverbatim
   </li>
   <li> rnovelty+ seems third from the ubcsat-range (version 1.0.0):
   \verbatim
> ubcsat-okl -alg rnovelty+ -runs 10 -cutoff 100000 -i GreenTao_2-3-6_2250.cnf
Clauses = 185490
Variables = 2250
TotalLiterals = 558633
FlipsPerSecond = 22267
BestStep_Mean = 51646.200000
Steps_Mean = 100000.000000
Steps_Max = 100000.000000
PercentSuccess = 0.00
BestSolution_Mean = 24.600000
BestSolution_Median = 24.000000
BestSolution_Min = 21.000000
BestSolution_Max = 28.000000
> ubcsat-okl -alg rnovelty+ -runs 10 -cutoff 1000000 -i GreenTao_2-3-6_2250.cnf
Clauses = 185490
Variables = 2250
TotalLiterals = 558633
FlipsPerSecond = 43269
BestStep_Mean = 495302.000000
Steps_Mean = 1000000.000000
Steps_Max = 1000000.000000
PercentSuccess = 0.00
BestSolution_Mean = 18.200000
BestSolution_Median = 19.500000
BestSolution_Min = 11.000000
BestSolution_Max = 23.000000
> ubcsat-okl -alg rnovelty+ -runs 10 -cutoff 10000000 -i GreenTao_2-3-6_2250.cnf
Clauses = 185490
Variables = 2250
TotalLiterals = 558633
FlipsPerSecond = 42383
BestStep_Mean = 4779885.400000
Steps_Mean = 10000000.000000
Steps_Max = 10000000.000000
PercentSuccess = 0.00
BestSolution_Mean = 11.500000
BestSolution_Median = 12.000000
BestSolution_Min = 10.000000
BestSolution_Max = 13.000000
> ubcsat-okl -alg rnovelty+ -runs 10 -cutoff 100000000 -i GreenTao_2-3-6_2250.cnf
Clauses = 185490
Variables = 2250
TotalLiterals = 558633
FlipsPerSecond = 39750
BestStep_Mean = 51162593.300000
Steps_Mean = 100000000.000000
Steps_Max = 100000000.000000
PercentSuccess = 0.00
BestSolution_Mean = 7.300000
BestSolution_Median = 7.000000
BestSolution_Min = 6.000000
BestSolution_Max = 9.000000
   \endverbatim
   </li>
   <li> Preprocessing:
    <ol>
     <li> Due to the highly constraint character of these problems, the
     minisat2 preprocessor achieves a considerable reduction in the number
     of variables. </li>
     <li> While for example for greentao_2(4,5) no variable was eliminated.
     </li>
     <li> However, actually these "simplified" problems seem to be harder (at
     least for adaptnovelty+):
     \verbatim
> ubcsat-okl -alg adaptnovelty+ -runs 10 -cutoff 10000000 -i GreenTao_2-3-6_2071_pre.cnf
Clauses = 88303
Variables = 2071
TotalLiterals = 465266
FlipsPerSecond = 89232
BestStep_Mean = 4078732.700000
Steps_Mean = 10000000.000000
Steps_Max = 10000000.000000
PercentSuccess = 0.00
BestSolution_Mean = 1.100000
BestSolution_Median = 1.000000
BestSolution_Min = 1.000000
BestSolution_Max = 2.000000
> ubcsat-okl -alg adaptnovelty+ -runs 10 -cutoff 100000000 -i GreenTao_2-3-6_2071_pre.cnf
Clauses = 88303
Variables = 2071
TotalLiterals = 465266
FlipsPerSecond = 83669
BestStep_Mean = 9849960.900000
Steps_Mean = 94840863.900000
Steps_Max = 100000000.000000
PercentSuccess = 10.00
BestSolution_Mean = 0.900000
BestSolution_Median = 1.000000
BestSolution_Min = 0.000000
BestSolution_Max = 1.000000
> ubcsat-okl -alg adaptnovelty+ -runs 10 -cutoff 10000000 -i GreenTao_2-3-6_2071.cnf
Clauses = 158884
Variables = 2071
TotalLiterals = 478584
FlipsPerSecond = 78718
BestStep_Mean = 4601845.300000
Steps_Mean = 9364095.600000
Steps_Max = 10000000.000000
PercentSuccess = 30.00
BestSolution_Mean = 1.000000
BestSolution_Median = 1.000000
BestSolution_Min = 0.000000
BestSolution_Max = 2.000000
> ubcsat-okl -alg adaptnovelty+ -runs 10 -cutoff 100000000 -i GreenTao_2-3-6_2071.cnf
Clauses = 158884
Variables = 2071
TotalLiterals = 478584
FlipsPerSecond = 101111
BestStep_Mean = 42545701.800000
Steps_Mean = 52277744.000000
Steps_Max = 100000000.000000
PercentSuccess = 90.00
BestSolution_Mean = 0.100000
BestSolution_Median = 0.000000
BestSolution_Min = 0.000000
BestSolution_Max = 1.000000
     \endverbatim
     (Perhaps there is a problem with the gaps regarding the variable indices?
     The preprocessed file kept the old variable names. Hopefully not.) </li>
    </ol>
   </li>
  </ul>


  \todo greentao_2(3,6) >= 2072
  <ul>
   <li> Conjecture: greentao_2(3,6) = 2072.
    <ol>
     <li> While with a cutoff of 100*10^6 n=2071 is easily
     handled, no success with n=2072, </li>
     <li> See "Upper bounds" below. </li>
    </ol>
   </li>
   <li> n = 2062 found satisfiable by ubcsat-adaptnovelty+ with
   msteps = 24408280 and seed = 1309685658 (cutoff = 100*10^6). </li>
   <li> n = 2070 found satisfiable by ubcsat-adaptnovelty+ with
   msteps = 17943201 and seed = 2009708202 (cutoff = 100*10^6). </li>
   <li> n = 2071 found satisfiable by ubcsat-adaptnovelty+ with
   msteps = 11332054 and seed = 1169059362 (cutoff = 100*10^6). </li>
   <li> n = 2072 looks unsatisfiable:
   \verbatim
> ubcsat-okl -alg adaptnovelty+ -runs 10 -cutoff 100000000 -i GreenTao_2-3-6_2072.cnf
Clauses = 159039
Variables = 2072
TotalLiterals = 479052
FlipsPerSecond = 119377
BestStep_Mean = 15846549.300000
Steps_Mean = 100000000.000000
Steps_Max = 100000000.000000
PercentSuccess = 0.00
BestSolution_Mean = 1.000000
BestSolution_Median = 1.000000
BestSolution_Min = 1.000000
BestSolution_Max = 1.000000
   \endverbatim
   </li>
   <li> Further 57 runs yield all min=1. </li>
   <li> And also after preprocessing with Minisat2 (see below) no satisfying
   assignment is found:
   \verbatim
> ubcsat-okl -alg adaptnovelty+ -runs 10 -cutoff 10000000 -i GreenTao_2-3-6_2072_pre.cnf
Clauses = 88791
Variables = 2072
TotalLiterals = 467889
FlipsPerSecond = 78648
BestStep_Mean = 2783465.900000
Steps_Mean = 10000000.000000
Steps_Max = 10000000.000000
PercentSuccess = 0.00
BestSolution_Mean = 1.600000
BestSolution_Median = 2.000000
BestSolution_Min = 1.000000
BestSolution_Max = 2.000000
   \endverbatim
   </li>
   <li> n = 2074 looks unsatisfiable:
   \verbatim
> ubcsat-okl -alg adaptnovelty+ -runs 10 -cutoff 100000000 -i GreenTao_2-3-6_2074.cnf
Clauses = 159321
Variables = 2074
TotalLiterals = 479898
FlipsPerSecond = 117038
BestStep_Mean = 11611872.900000
Steps_Mean = 100000000.000000
Steps_Max = 100000000.000000
PercentSuccess = 0.00
BestSolution_Mean = 1.000000
BestSolution_Median = 1.000000
BestSolution_Min = 1.000000
BestSolution_Max = 1.000000
   \endverbatim
   </li>
   <li> n = 2078 seems unsatisfiable:
   \verbatim
> ubcsat-okl -alg adaptnovelty+ -runs 10 -cutoff 100000000 -i GreenTao_2-3-6_2078.cnf
Clauses = 159895
Variables = 2078
TotalLiterals = 481629
FlipsPerSecond = 110868
BestStep_Mean = 19625287.200000
Steps_Mean = 100000000.000000
Steps_Max = 100000000.000000
PercentSuccess = 0.00
BestSolution_Mean = 1.000000
BestSolution_Median = 1.000000
BestSolution_Min = 1.000000
BestSolution_Max = 1.000000
   \endverbatim
   </li>
   <li> n = 2094 seems unsatisfiable
   \verbatim
> ubcsat-okl -alg adaptnovelty+ -runs 100 -cutoff 100000000 -i GreenTao_2_3_6_2094.cnf
Clauses = 162248
Variables = 2094
TotalLiterals = 488703
FlipsPerSecond = 93403
BestStep_Mean = 10185143.160000
Steps_Mean = 100000000.000000
Steps_Max = 100000000.000000
PercentSuccess = 0.00
BestSolution_Mean = 1.890000
BestSolution_Median = 2.000000
BestSolution_Min = 1.000000
BestSolution_Max = 2.000000
   \endverbatim
   </li>
   <li> n = 2125 might be unsatisfiable:
   \verbatim
> ubcsat-okl -alg adaptnovelty+ -runs 100 -cutoff 10000000 -i GreenTao_2_3_6_2125.cnf
Clauses = 166757
Variables = 2125
TotalLiterals = 502284
FlipsPerSecond = 84973
BestStep_Mean = 4796045.770000
Steps_Mean = 10000000.000000
Steps_Max = 10000000.000000
PercentSuccess = 0.00
BestSolution_Mean = 2.740000
BestSolution_Median = 3.000000
BestSolution_Min = 2.000000
BestSolution_Max = 4.000000
> ubcsat-okl -alg adaptnovelty+ -runs 10 -cutoff 100000000 -i GreenTao_2_3_6_2125.cnf
Clauses = 166757
Variables = 2125
TotalLiterals = 502284
FlipsPerSecond = 89403
BestStep_Mean = 13475345.800000
Steps_Mean = 100000000.000000
Steps_Max = 100000000.000000
PercentSuccess = 0.00
BestSolution_Mean = 2.000000
BestSolution_Median = 2.000000
BestSolution_Min = 2.000000
BestSolution_Max = 2.000000
   \endverbatim
   </li>
   <li> n = 2250 looks unsatisfiable: see above. </li>
   <li> n = 2500 looks unsatisfiable:
   \verbatim
> ubcsat-okl -alg rnovelty+ -runs 10 -cutoff 100000 -i GreenTao_2_3_6_2500.cnf
Clauses = 226059
Variables = 2500
TotalLiterals = 680712
FlipsPerSecond = 13038
BestStep_Mean = 68629.200000
Steps_Mean = 100000.000000
Steps_Max = 100000.000000
PercentSuccess = 0.00
BestSolution_Mean = 61.900000
BestSolution_Median = 62.500000
BestSolution_Min = 57.000000
BestSolution_Max = 64.000000
> ubcsat-okl -alg rnovelty+ -runs 10 -cutoff 1000000 -i GreenTao_2_3_6_2500.cnf
Clauses = 226059
Variables = 2500
TotalLiterals = 680712
FlipsPerSecond = 13062
BestStep_Mean = 495738.100000
Steps_Mean = 1000000.000000
Steps_Max = 1000000.000000
PercentSuccess = 0.00
BestSolution_Mean = 54.000000
BestSolution_Median = 55.000000
BestSolution_Min = 47.000000
BestSolution_Max = 57.000000
> ubcsat-okl -alg rnovelty+ -runs 10 -cutoff 10000000 -i GreenTao_2_3_6_2500.cnf
Clauses = 226059
Variables = 2500
TotalLiterals = 680712
FlipsPerSecond = 12799
BestStep_Mean = 4374264.300000
Steps_Mean = 10000000.000000
Steps_Max = 10000000.000000
PercentSuccess = 0.00
BestSolution_Mean = 50.300000
BestSolution_Median = 50.500000
BestSolution_Min = 46.000000
BestSolution_Max = 53.000000
   \endverbatim
   <li> n = 3000 looks unsatisfiable:
   \verbatim
> ubcsat-okl -alg rnovelty+ -runs 10 -cutoff 100000 -i GreenTao_2_3_6_3000.cnf
Clauses = 318899
Variables = 3000
TotalLiterals = 960054
FlipsPerSecond = 7081
BestStep_Mean = 52997.600000
Steps_Mean = 100000.000000
Steps_Max = 100000.000000
PercentSuccess = 0.00
BestSolution_Mean = 137.300000
BestSolution_Median = 137.500000
BestSolution_Min = 126.000000
BestSolution_Max = 146.000000
> ubcsat-okl -alg rnovelty+ -runs 10 -cutoff 1000000 -i GreenTao_2_3_6_3000.cnf
       sat  min     osteps     msteps       seed
      1 0   132     899782    1000000  257061986
      2 0   133     533282    1000000 3225188000
   \endverbatim
   </li>
  </ul>


  \todo Upper bounds
  <ul>
   <li> It appears that OKsolver would need, say, 50 years for n=5000 on the
   laptop. </li>
   <li> With a cluster, this would be feasible; and perhaps optimising the
   heuristics yields something. </li>
   <li> We need to investigate march_pl and minisat (problematic that progress
   is hard to judge). </li>
   <li> Also higher n could be tried. </li>
   <li> n=2072
    <ol>
     <li> OKsolver-2002
     \verbatim
> OKsolver_2002-O3-DNDEBUG -M -D30 GreenTao_2-3-6_2072.cnf
 GreenTao_2-3-6_2072.cnf, 1073741824
  8:    28,   15.1, 2024003323.2
s UNKNOWN
c sat_status=2 initial_maximal_clause_length=6 initial_number_of_variables=2071 initial_number_of_clauses=159039 initial_number_of_literal_occurrences=479052 running_time(s)=-653.2 number_of_nodes=16842 number_of_single_nodes=0 number_of_quasi_single_nodes=0 number_of_2-reductions=338046 number_of_pure_literals=11941 number_of_autarkies=0 number_of_missed_single_nodes=0 max_tree_depth=92 number_of_table_enlargements=0 reduced_maximal_clause_length=0 reduced_number_of_variables=0 reduced_number_of_clauses=0 reduced_number_of_literal_occurrences=0 number_of_1-autarkies=3398799 number_of_initial_unit-eliminations=0number_of_new_2-clauses=0 maximal_number_of_added_2-clauses=0 initial_number_of_2-clauses=0 file_name=GreenTao_2-3-6_2072.cnf
     \endverbatim
     looks hopeless
     </li>
     <li> minisat2 seems to achieve quite some good initial reduction; using
     just the preprocessed file:
     \verbatim
> minisat2 -dimacs=GreenTao_2-3-6_2072_pre.cnf GreenTao_2-3-6_2072.cnf
> OKsolver_2002-O3-DNDEBUG -M -D30 GreenTao_2-3-6_2072_pre.cnf
s UNKNOWN
c sat_status=2 initial_maximal_clause_length=15 initial_number_of_variables=1316 initial_number_of_clauses=88791 initial_number_of_literal_occurrences=467889 running_time(s)=-1489.3 number_of_nodes=6440 number_of_single_nodes=0 number_of_quasi_single_nodes=0 number_of_2-reductions=113298 number_of_pure_literals=1639 number_of_autarkies=0 number_of_missed_single_nodes=0max_tree_depth=101 number_of_table_enlargements=0 reduced_maximal_clause_length=0 reduced_number_of_variables=0 reduced_number_of_clauses=0 reduced_number_of_literal_occurrences=0 number_of_1-autarkies=28917 number_of_initial_unit-eliminations=0 number_of_new_2-clauses=0 maximal_number_of_added_2-clauses=0 initial_number_of_2-clauses=0 file_name=GreenTao_2-3-6_2072_pre.cnf
     \endverbatim
     Actually, nearly no reduction in formula size, but quite some variables
     where eliminated (at the expense of longer clauses). Doesn't seem to
     make the problem (observable) easier (and for local search algorithms
     it makes it even harder --- see above). </li>
     <li> minisat2 seems also not achieving something:
     \verbatim
> minisat2 GreenTao_2-3-6_2072.cnf
...
|  57525118 |    1316    88791   467889 |   568094   272657     40 |  0.000 % |

*** INTERRUPTED ***
restarts              : 32
conflicts             : 57658225       (229 /sec)
decisions             : 63767800       (1.80 % random) (253 /sec)
propagations          : 4376843220     (17368 /sec)
conflict literals     : 2291143690     (40.74 % deleted)
Memory used           : 203.70 MB
CPU time              : 252005 s
     \endverbatim
     </li>
     <li> march_pl
      <ol>
       <li> It seems in phase 1 of the preprocessing 68553 clauses and 397
       variables are removed, while in phase 2 65386 clauses are added. </li>
       <li> Apparently the maximal clause-length has not been increased in
       this process (so perhaps march_pl is less aggressive than minisat2).
       </li>
      </ol>
     </li>
    </ol>
   </li>
  </ul>

*/
