// Oliver Kullmann, 4.8.2009 (Swansea)
/* Copyright 2009 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file ExperimentSystem/SolverMonitoring/plans/OKsolver.hpp
  \brief General plans monitoring OKsolver_2002


  \todo Object-oriented syntax
  <ul>
   <li> It would be good if one could just say "plot(E)", "summary(E)" or
   "hist(E)", and the corresponding function "plot_oksolver" etc. would be
   chosen. </li>
   <li>  For this the data frames needed to be "marked". </li>
  </ul>


  \todo Function plot_oksolver_mon_nodes
  <ul>
   <li> Currently it is hardly visible that one observation node might
   have associated 100 nodes, and another observation might have this
   as well, while the former really advances only one observation level,
   while the latter advances more observation levels, say 10, and thus
   in effect the number of associated nodes for it is closer to
   100 / 10 = 10. </li>
  </ul>


  \todo Function summary_oksolver
  <ul>
   <li> The R-standard is to have "summary" just outputting text, while by
   "plot" one gets plots; now we have it combined? </li>
  </ul>


  \todo Function hist_oksolver_mon_nodes
  <ul>
   <li> The current breakpoints don't reflect the value-structure well for
   low node-counts, say up to 8 nodes:
   \verbatim
> log2(seq(0,8))
[1]     -Inf 0.000000 1.000000 1.584963 2.000000 2.321928 2.584963 2.807355
[9] 3.000000
   \endverbatim
   </li>
   <li> Is it possible to adjust the standard setting of breakpoints just for
   these initial values? </li>
   <li> Perhaps one bar for each of the values 0, ..., 8. </li>
   <li> But if there are no values in this range, then no breakpoints are
   needed. </li>
   <li> It would be good if one could first compute the proposed setting of
   breakpoints, and then just adjust them, if necessary. </li>
   <li> However one problem is the grouping (so that one gets to see a
   distribution)?! Somehow the bars should collect "equal" amounts of counts
   --- however should this relate to the original node-counts or to their
   logarithms?? Perhaps the logarithms (as it is now) is fine in principle,
   but the discretisation effects for small node-counts should be repaired.
   </li>
   <li> A fine-grained histogram is created by breaks="Freedman-Diaconis"
   (just "f" is sufficient). For the examples considered, "Scott" (just "sc"
   has the same effect. </li>
   <li> breaks="Sturges" (just "st" is sufficient) uses less bars; this might
   be actually more appropriate, since we need to consider here a
   distribution? The single counts can be viewed by plot(table(E$nodes)) or
   plot(table(log2(E$nodes))). </li>
   <li> If only the first n values and their counts are of interest, use
   table(E$nodes)[1:n] (or the usual other variations). This information can
   also be plotted (just using "plot"). </li>
   <li> We need also more tick-marks. </li>
  </ul>

*/

