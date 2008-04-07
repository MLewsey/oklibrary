// Matthew Gwynne, 26.3.2008 (Swansea)
/* Copyright 2008 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file ComputerAlgebra/Cryptology/Lisp/Cryptanalysis/Rijndael/plans/SboxAnalysis.hpp
  \brief Plans for the Cryptanalysis of the Rijndael Sbox in Maxima/Lisp


  \todo Provide tests for all functions
  <ul>
   <li> generate_full_aes_sbox_cnf_fcs </li>
   <li> test_CNF_aes_sbox </li>
   <li> hitting_cnf_aes_sbox </li>
   <li> generate_full_aes_sbox_dnf_fcs </li>
   <li> binary_list_to_dnf_c </li>
   <li> DONE polynomial2list </li>
  </ul>

  
  \todo Generate good CNF hitting clause-sets for the AES Sbox
  <ul> 
   <li> Different heuristics for generating hitting clause-sets
   \verbatim
length(hitting_cnf_aes_sbox(dll_heuristics_first_formal));
2048
length(hitting_cnf_aes_sbox(dll_heuristics_first_real));
2048
length(hitting_cnf_aes_sbox(dll_heuristics_first_shortest_clause));
2048
statistics_cs(hitting_cnf_aes_sbox(dll_heuristics_max_lit));
[16, 1513, 19546, 16, 6]
length(hitting_cnf_aes_sbox(dll_heuristics_max_var));
2048
statistics_cs(hitting_cnf_aes_sbox(dll_heuristics_max_lit_tb(3,3)));
[16, 1468, 18925, 16, 6]
statistics_cs(hitting_cnf_aes_sbox(dll_heuristics_max_lit_tb(4,4)));
[16, 1460, 18873, 16, 5]
   \endverbatim
   Would be interesting to understand this. See below. </li>
   <li> DONE (explained below: there are no forced assignments, so no 
   false-condensation can take place, while true-condensations can't happen
   with clause-sets) Also interesting that all the hitting trees
   produced by the SAT solvers are already condensed. </li>
   <li> Use heuristics_lookahead_distances with different lookahead-reductions
   and different distances. (MG: Looking at several combinations of the already
   defined reductions, all seem to lead to 2048. I am still trying different
   combinations) </li>
   <li> Since the AES-DNF is unique, as a correctness test we can
   just check whether we get the input back (using any heuristics):
   \verbatim
test_CNF_aes_sbox(cs_to_fcs(hitting_cnf_aes_sbox(dll_heuristics_max_lit)));
   \endverbatim
   </li>
   <li> We should also use reductions. For that we need the ability
   to translate r_k-splitting trees into hitting clause-sets, which can
   be done in a straightforward way, by just making the forced assignments
   into trees of levelled height 1 (ignoring the actual reduction).
   DONE (as explained below, here there are no forced assignments. Nevertheless,
   in general this approach should be implemented.) </li>
   <li> A general conjecture on computing dual hitting clause-sets from a
   clause-set F.
    <ol>
     <li> "For computing small dual hitting cause-sets, use as splitting literal
     one with leads to maximal probability of satisfiability." </li>
     <li> So using choose_most_sat_literal_h in
     ComputerAlgebra/Satisfiability/Lisp/Backtracking/DLL_solvers.mac
     should do a good job. </li>
     <li> Experimental results:
     \verbatim
statistics_cs(hitting_cnf_aes_sbox(johnson_heuristic));
[16, 1516, 19573, 16, 6]
statistics_cs(hitting_cnf_aes_sbox(choose_most_sat_literal_h(satprob_dll_simplest_trivial1)));
[16, 1516, 19573, 16, 6]
     \endverbatim
     <li> DONE (differences are due to ties)
     The strange thing here are these little differences "1513, 1515, 1516", where
     actually all three trees should be identical! We need to investigate this.
     (Perhaps this comes from tie-braking. But still, shouldn't be there.) </li>
     <li> Also the reductions and the look-ahead need to be considered. </li>
     <li> "The strongest approach is to use full elimination of forced 
     assignments at each node. The look-ahead then also takes all forced
     assignments into account." </li>
     <li> If the reduction misses forced assignments, then in principle this
     is not a problem for the tree, since condensing the tree will remove
     unneccesary branches at the end. However it affects the look-ahead. </li>
     <li> If F is a hitting clause-set, then computing the sat-probability
     is easy (and all other tasks), and the above heuristics is the Johnson
     heuristics. The heuristics finds also all forced assignments in the
     "combined" look-ahead, since forced assignments are identified as branches
     where the other branch has sat-probability 0; however it is cleaner to
     put this completely into the reduction. </li>
     <li> If more specially F is a full clause-set (and the class of full
     clause-sets is stable under partial assignments(!)), then the Johnson-
     heuristic just becomes the maxlit-occurrences heuristic above, choosing a
     literal occurring most often. </li>
     <li> Moreoever, in our case dll_heuristics_max_lit actually implements
     the full elimination of forced assignments and the full look-ahead(!):
      <ol>
       <li> The Sbox-function, as any other permutation, allows only satisfying
       assignments of full length --- and thus (for the CNF-perspective) there
       are no forced assignments at all! </li>
       <li> So reduction and look-ahead are so "strong" because there is simply
       nothing to be reduced (via forced assignments). </li>
      </ol>
     </li>
    </ol>
   </li>
   <li> It is likely that the SAT approximation heuristic would benefit from
   some lookahead:
    <ol>
     <li> As was presented with regards to max_lit, so as to differentiate when 
     ties occur for the maximal probability of satisfiability. </li>
     <li> We wish the same idea of maximising satisfiability to occur when we 
     make the assignment and move 1 level down in the tree, and so the literal 
     which results in the most "bias" when that literal assignment is made 
     (or potentially taking into account both branches) should be chosen. </li>
     <li> The reasoning behind maximising "bias" at each level needs to be made
     clear here (falsifying assignments occurring along the same "path" down the
     tree result in less "branch off"s for the satisfying assignments, where 
     the "branch off"s are then the clauses we take for the dual hitting clause 
     set (after comdensing?) - this is likely very imprecise and unclear). </li>
    </ol>
   </li>
  </ul>


  \todo Extracting prime implicate representations from the hitting-cls-representations
  <ul>
   <li> As explained in "Hitting clause-sets" in
   ComputerAlgebra/Satisfiability/Lisp/Resolution/plans/PrimeImplicatesImplicants.hpp,
   given a hitting clause-set representation, from it we can obtain a shorter
   representation by prime implicates. This is a better representation. </li>
   <li> This is achieved by "replace_by_prime_implicates_hitting". </li>
   <li>
   \verbatim
h_aes : hitting_cnf_aes_sbox(dll_heuristics_max_lit)$
p_aes : replace_by_prime_implicates_hitting(h_aes)$
statistics_cs(p_aes);
[16, 1359, 9430, 9, 6]
ncl_list_f(cs_to_fcs(p_aes));
[[6, 265], [7, 913], [8, 180], [9, 1]]
irredundant_bydef(cs_to_fcs(p_aes), dll_simplest_trivial1);
false
ip_aes : first_irr_fcs(cs_to_fcs(p_aes), dll_simplest_trivial2)$
statistics_cs(ip_aes[2]);
[16, 581, 4006, 8, 6]
test_CNF_aes_sbox(ip_aes);
true
h2_aes : hitting_cnf_aes_sbox(dll_heuristics_max_lit_tb(4,4))$
test_CNF_aes_sbox(cs_to_fcs(h2_aes));
true
p2_aes : replace_by_prime_implicates_hitting(h2_aes)$
statistics_cs(p2_aes);
[16, 1374, 9524, 9, 5]
ip2_aes : first_irr_fcs(cs_to_fcs(p2_aes), dll_simplest_trivial2)$
statistics_cs(ip2_aes[2]);
[16, 566, 3898, 9, 5]
test_CNF_aes_sbox(ip2_aes);
true
h0_aes : hitting_cnf_aes_sbox(dll_heuristics_first_formal)$
p0_aes : replace_by_prime_implicates_hitting(h0_aes)$
statistics_cs(p0_aes);
[16, 1722, 12118, 9, 5]
ip0_aes : first_irr_fcs(cs_to_fcs(p0_aes), dll_simplest_trivial2)$
statistics_cs(ip0_aes[2]);
[16, 680, 4784, 9, 5]
test_CNF_aes_sbox(ip0_aes);
true
   \endverbatim
   </li>
   <li> This looks very interesting! Should be close to the optimum.
   And looks much smaller than to be expected. </li>
   <li> Analysing p_aes:
   \verbatim
ir_p_aes : all_irrcl_bydef(cs_to_fcs(p_aes), dll_simplest_trivial2)$
statistics_cs(ir_p_aes);
[16, 447, 3087, 8, 6]
ncl_list_f(cs_to_fcs(ir_p_aes));
[[6, 99], [7, 291], [8, 57]]
oklib_monitor : true;
oklib_monitor_level : 1;
irrc_p_aes : all_irr_cores_bydef(cs_to_fcs(p_aes), dll_simplest_trivial2)$
   \endverbatim
   </li>
   <li> We should try random sampling of the irredundant cores. </li>
   <li> The question is how small can we get a CNF representation? We need
   also to investigate the size of a CNF obtained from the DNF via Tseitin
   translation (and optimisation); see
   ComputerAlgebra/Satisfiability/Lisp/PropositionalLogic/plans/TseitinTranslation.hpp
   </li>
  </ul>


  \todo Compute *all* prime implicates (for the purpose of analysis):
  <ul>
   <li> See
   ComputerAlgebra/Satisfiability/Lisp/Resolution/plans/PrimeImplicatesImplicants.hpp
   </li>
   <li> For a permutation of GF(2^8) we have 2 * 2^8 * 8 = 2^12 = 4096
   potential prime implicates, given by fixing 8 bit in either the inputor
   the output, and one further bit to the wrong value. As one can see by
   the identity, these are not neccessarily prime, since the identify
   just has 16 prime implicates (of length 2). </li>
   <li> One should test these. </li>
   <li> If the Maxima computation, via
   \verbatim
min_2resolution_closure_cs(generate_full_aes_sbox_cnf_fcs()[2]);
   \endverbatim
   takes too long, then we need a C++ implementation; see
   Transitional/Satisfiability/FiniteFunctions/plans/general.hpp,
   "Prime implicants and implicates". A simple implementation should
   suffice here. </li>
   <li> Brute-force approaches:
    <ol>
     <li> There are 3^16 = 43,046,721 clauses with 16 variables altogether,
     so with a C++ implementation it is even no problem to run through
     all clauses and determine in this brute-force way the prime implicates. </li>
     <li> We should write a little Maxima function which searches for prime 
     implicates (of length up to k) of a clause-set via this brute-force approach
     (using some input SAT solver). This would need as input one of the
     CNF-representations; since they are hitting clause-sets, we can then use
     a specialised SAT solver. </li>
     <li> We should also write a Maxima function for brute-force determination of
     all dual prime implicates (up to a given length), that is, the minimal 
     satisfying (partial) assignments. This is even simpler and doesn't need a 
     SAT solver. </li>
     <li> Perhaps we should write this function then also in C++ --- it's the 
     most simple function imaginable here, just run through all partial 
     assignments and check whether they satisfy the given clause-set. </li>
     <li> The only thing to think about is subsumption-elimination. But the
     simple implementation just does it at the end (since we have already a
     function for that!). As a side result, we obtain here the number of all
     satisfying partial assignments (which otherwise is actually not so easy to
     compute?!?). </li>
     <li> This would belong to module Satisfiability/Algorithms/AllSolutions;
     see Algorithms/AllSolutions/plans/MinimalAssignments.hpp. </li>
    </ol>
   </li>
   <li> However, since the S-box has a perfectly regular structure, it
   should also be possible to analytically determine all prime implicates:
    <ol>
     <li> Extract from the above results prime implicates, determine
     their structure, and generalise. </li>
     <li> See the 4096 candidates above. </li>
    </ol>
   </li>
  </ul>


  \todo Find the symmetries of the AES Sbox DNF
  <ul>
   <li> See
   ComputerAlgebra/Satisfiability/Lisp/Symmetries/plans/general.hpp. </li>
   <li> We have at least the symmetry exchanging input and output variables.
   (since x^(-1) in the field is self-inverse). </li>
   <li> Then we could simply run through all 8! * 2^8 1,032,1920
   literal substitutions on the input variables, while copying the
    values for the output variables accordingly. </li>
  </ul>


  \todo Related 8-bit bijections
  <ul>
   <li> Investigate random permutations of {0,1}^8, and compare them
   with the AES Sbox. </li>
   <li> Find representations for the multiplication with a constant in
   GF(2^8). </li>
  </ul>
     

  \todo Organisation
  <ul>
   <li> Perhaps we should provide a constant for
   generate_full_aes_sbox_cnf_fcs(). </li>
  </ul>


  \todo DONE Move functions which do not belong to this module.


  \todo DONE Sbox CNF and DNF generation functions
  <ul>
   <li> DONE Two small functions are needed which generate the CNF and DNF clause 
   sets for the AES Sbox. </li>
  </ul>

*/

