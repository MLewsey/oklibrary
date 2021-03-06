// Oliver Kullmann, 27.5.2009 (Swansea)
/* Copyright 2009 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file ExperimentSystem/ControllingLocalSearch/plans/PointOfUnsatisfiability.hpp
  \brief %Tools for guessing the first point of unsatisfiability in a series of problems (with one turning point)


  \todo Connections
  <ul>
   <li> See
   Experimentation/Investigations/RamseyTheory/VanderWaerdenProblems/plans/general.hpp
   for a case study. </li>
  </ul>


  \todo Finding the n where a problem series changes from SAT to UNSAT
  <ul>
   <li> For problems coming from %Ramsey theory we have given a CNF-generator
   G(n), where n is a natural number and where for some (unknown) n_0 it is
   known that G(n') is unsatisfiable iff n' >= n_0. </li>
   <li> We assume computation of G(n) is fast (a few seconds, say); so
   typically a C++ program is needed. </li>
   <li> Now via local search an "educated guess" for n_0 is sought (that
   is a lower bound n_0' <= n_0 (where the problem is known to be satisfiable),
   where n_0'+1 seems unsatisfiable. </li>
   <li> The algorithm alg from the ubcsat-suite is given (has been selected
   before). </li>
   <li> We always use option "-solve" to stop once a solution was found. </li>
   <li> A reasonable strategy seems to be the following ("big steps,
   followed by scanning with small steps, followed by systematic
   exploration (minimum steps)"):
    <ol>
     <li> Start with some n for which n <= n_0 is known.
      <ol>
       <li> For establishing n the algorithm starts with a, b, where
       a is a known lower bound, while b is assumed to be an upper bound. </li>
       <li> Then via bisection we find n, where not too much effort is
       spent for upper bounds. </li>
       <li> Alternatively we compute s = (b-a) / G ("G" like "groups"),
       and consider a+s, a+2s, ... . Perhaps this is better, since so
       we don't have to deal with possibly hard unsatisfiable problems. </li>
       <li> One starts with cutoff=10^4, and uses runs=10, increasing cutoff
       using a factor of 2 if necessary, until an upper bound for cutoff
       is reached, say, 10^7 (of course, all these numbers are parameters
       to the algorithm, with these default values). </li>
       <li> Perhaps G=100 is a reasonable default value. </li>
       <li> For the upper bound b one assumes that 10 runs with cutoff=10^8
       only reaches a minimum of, say, 10. </li>
       <li> Also for establishing b we should use some algorithm, which uses
       bigger steps, say here s=1000, and a fixed cutoff=10^8. </li>
      </ol>
     </li>
     <li> The procedure will now increase n in steps of 1: Given that
     unsatisfiable problems in this area are very hard, and via local search
     we don't have a reasonable grasp on that, this seems best (avoiding to
     jump into unknown areas). </li>
     <li> First an appropriate cutoff is computed:
      <ol>
       <li> The start cutoff is cutoff_start as given by the above
       computation. </li>
       <li> t runs of ubcsat::alg are performed:
        <ul>
         <li> If a solution was found, then we go to the next n. </li>
         <li> If the frequency of runs with min=1 is less then p, then cutoff
         is multiplied by cfactor, and again t runs are performed. </li>
         <li> Otherwise the current cutoff is considered appropriate. </li>
        </ul>
       </li>
       <li> For t a value t=10 seems reasonable. </li>
       <li> For p a value p=0.2 (i.e., 20%) seems alright. </li>
       <li> For cfactor currently I (OK) use cfactor=10; cfactor=2 seems
       ineffective, but perhaps cfactor=5 is a good compromise. </li>
       <li> If cutoff becomes larger than cbound, the whole process is
       stopped (and the current n is taken as a guess for n_0). </li>
       <li> Requiring that min=1 must occur, and this with a certain
       frequency, is based on the experiences with adaptnovelty+, which
       has a quite small volatility; we could generalise this to ask
       for runs with min <= min_required, where for more volatily algorithms
       one could use up to min_required = 5. </li>
      </ol>
     </li>
     <li> Now the main search is performed:
      <ol>
       <li> M "meta"-runs of ubcsat with M' runs each are performed. </li>
       <li> If a solution was found then n is increased. </li>
       <li> Otherwise cutoff is multiplied with cfactor, and we repeat. </li>
      </ol>
     </li>
     <li> The devision of the M*M' ubcsat-runs into M packages is there so that
     for data evaluation one doesn't need to wait until the end of the
     ubcsat-run; but M shouldn't be too small, since reading the formula
     takes time. </li>
     <li> But in order to make this happen, actually the ubcsat-runs have to
     happen in the background, only informing R about completion of one
     package --- is this possible? </li>
     <li> M=10 and M'=100 seems reasonable. </li>
     <li> Instead of increasing the cutoff, one could also increase M:
     perhaps if the average of osteps for the runs achieving the minimum is
     less then q*cutoff, then multiplying M by rfactor is sensible, where
     q = 0.4, and rfactor = 2. </li>
     <li> The upper bound for M should perhaps be 80: If this is reached,
     then M is reset to the start value, cutoff is multiplied by cfactor,
     and the main search is continued. </li>
    </ol>
   </li>
   <li> Everything is logged to files. </li>
   <li> What is a suitable programming language here?
    <ol>
     <li> Since here a lot of variation and further development is needed,
     perhaps we already start with a C++ program in object-oriented style
     (mainly). </li>
     <li> But all external calls are handled by wrapper scripts, which
     make handling of the various inputs and outputs very easy for the
     C++ program. </li>
     <li> On the other hand, perhaps R would be easier? </li>
     <li> Maxima is also possible; but we have only "system" available,
     without getting at the return value, and we also have (big) problems
     with the initialisation, while with R we can set HOME appropriately,
     so either R or C++. </li>
     <li> Perhaps R is most suitable here; also for later developments
     we might use more sophisticated statistical evaluations. </li>
     <li> Though C++ feels better, and at this time there are no complicated
     statistics envolved. </li>
    </ol>
   </li>
  </ul>


  \todo Simpler strategies
  <ul>
   <li> Motivated by
   Experimentation/Investigations/RamseyTheory/HindmanProblems/plans/Hindman_2^a(2).hpp
   where ubcsat::rsaps behaves very predictibly, we should allow for several
   strategies. </li>
   <li> Here the strategy would be just to use a fixed cutoff, and 10 rounds,
   and to determine the transition point. </li>
   <li> If mixed cases occur (sat and unsat), then the program simply stops.
   </li>
   <li> So here perhaps we do not stop once a solution was found. </li>
   <li> One could then just use some start value, and from there use bisection,
   and if necessary (yet no "unsat" case found), multiply the old n-value
   by some constant; say 1.2. </li>
  </ul>

*/

