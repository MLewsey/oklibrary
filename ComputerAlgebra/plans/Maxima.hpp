// Oliver Kullmann, 20.12.2007 (Swansea)
/* Copyright 2007, 2008, 2009 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file ComputerAlgebra/plans/Maxima.hpp
  \brief General plans regarding the Maxima computer algebra system

  For discussions (explanations, documentations) of Maxima-functionality see
  ComputerAlgebra/plans/MaximaTechniques.hpp.


  \todo No recursion for memoised functions
  <ul>
   <li> See "There are severe restrictions for memoised recursive functions"
   in ComputerAlgebra/plans/MaximaTechniques.hpp. </li>
   <li> It seems that ulimit doesn't help here. </li>
   <li> Then the only (general) possibility seems to write for memoised
   recursive functions a wrapper which calls the function bottom-up. </li>
   <li>
   \verbatim
_fib_mem[n] := if n <= 1 then n else _fib_mem[n-1] + _fib_mem[n-2];
fib_mem(n) := (for i : 0 thru n-1 do _fib_mem[i], _fib_mem[n])$
   \endverbatim
   </li>
   <li> It would be better if one could find out whether _fib_mem[n] is already
   defined. </li>
  </ul>


  \todo Argument-length restriction
  <ul>
   <li> In CLisp we have the very restrictive maximal argument-lenght of
   4095 (at least on 32-bit machines), which is better in ECL (2^16),
   however in CLisp "union" can be applied to arbitrarily many arguments,
   while in ECL it is restricted by the maximal argumenent-length. </li>
   <li> We need to find out about these restrictions, and its variations.
   </li>
   <li> Perhaps the cmucl is the only usable Lisp, since apparently it does
   not pose any restriction on the argument-length? </li>
  </ul>


  \todo How to use function-parameters reliably??
  <ul>
   <li> The biggest problem with Maxima is that function-parameters are
   not handled properly, not even the arguments of lambda-terms. </li>
   <li> It is unclear what actually happens, but names of parameter, which
   take functions or lambda-terms as values, must be all different!
    <ol>
     <li> On the other hand, calling test-functions from other test-functions
     doesn't cause problems. </li>
     <li> We need clear examples, where errors occur. </li>
    </ol>
   </li>
   <li> It seems that nested function calls though are not a problem (this
   would render it hopeless!). </li>
   <li> This must be discussed on the Maxima mailing list (but I (OK) fear
   nothing will happen).
    <ol>
     <li> Take as example "every_s" from
     ComputerAlgebra/DataStructures/Lisp/Lists.mac (how to write it
     properly). </li>
     <li> If the function-parameter would be called "npred", then
     "okltest_some_ndiag_scom_p" in
     ComputerAlgebra/CombinatorialMatrices/Lisp/tests/Basics.mac
     runs into an infinite loop. </li>
    </ol>
   </li>
   <li> One thing is to reserve names for the library:
    <ol>
     <li> Everything that starts with "_". </li>
     <li> Then we have "f"; likely we should rename it everywhere to "_f".
     </li>
     <li> Or perhaps "f" is an exception. </li>
     <li> Within the library, parameters naming functions must always be
     somewhat longer and specific (except of "f"); and they start with "_".
     </li>
    </ol>
   </li>
  </ul>


  \todo Problems with errcatch
  <ul>
   <li> We get an error message
   \verbatim
errcatch(map(0,[]));
Improper name or value in functional position:
0
   \endverbatim
   which shouldn't be the case. </li>
   <li> Contact the Maxima mailing list. </li>
  </ul>


  \todo What is "equalp" ?
  <ul>
   <li> It seems impossible to evaluate "equalp(0,0)" sensibly?? </li>
   <li> is(equalp(0,0)) returns "unknown" ? </li>
   <li> So then the only sensible check for being zero is
   \verbatim
is(equal(x,0))
   \endverbatim
   ?? (yielding true,false, or unknown) </li>
  </ul>


  \todo Maxima/CLisp bug for larger data-sets
  <ul>
   <li> On csltok (laptop of OK) running
   \verbatim
oklib_store : true;
set_random_state(make_random_state(0));
all_unsinghitting_mvd(8, 'all_n8);
   \endverbatim
   produced a segmentation fault after running a bit more than
   214 hours (nearly 9 full days). </li>
   <li> Apparently this just happened when writing the session file. </li>
   <li> A core-file has been produced --- how to analyse this? </li>
   <li> When by mistake printing out the repository to the screen, I
   got "string too long: desired length 6553600 exceeds the supported maximum
   length". </li>
   <li> So perhaps Maxima, when writing the file, just puts everything into a
   big string, and then the error occurred when this string was too long?
    <ol>
     <li> We had one slightly bigger file in the past; however this contained
     the annotation-strings. </li>
     <li> So perhaps each value is transformed into a string, and now a single
     value (the hash-map), was too big? </li>
     <li> Repeating the experiment with seed 10 produced after nearly the same
     running time again a segmentation fault, so the string-problem should be
     the cause. </li>
     <li> With seed 11, at nearly the same file size the segmentation
     fault happened, but this time the file was apparently correctly
     written, and the fault happened a bit after writing the file? </li>
     <li> On cs-wsok, a 64-bit machine, these errors don't happen. </li>
    </ol>
   </li>
   <li> Tell the Maxima mailing-list about that and ask for a different "save",
   call it "fsave" (fast save):
    <ol>
     <li> No list-annotations. </li>
     <li> No unnecessary spaces. </li>
     <li> Values are broken into small strings, if necessary. </li>
    </ol>
   </li>
  </ul>


  \todo General design: Lists *here* are more fundamental than sets
  <ul>
   <li> It seems that instead of clause-sets we should use clause-lists
   as the fundamental objects. </li>
   <li> In the mathematical cosmos there is no creation and destruction,
   thus no order, however in the computational cosmos there is before
   and after, construction and destruction. </li>
   <li> In this way we obtain control over enumeration aspects.
    <ol>
     <li> Typically the enumeration is controlled by ordering the
     elements of certain sets. </li>
     <li> Yet this done by applying listify, thus without control. </li>
    </ol>
    Now, when enumerating all possibilities in some function:
    <ol>
     <li> Either the given orders are used. </li>
     <li> Or random_permutation is applied. </li>
     <li> Perhaps we have a global flag "oklib_randomise_order", which
     controls this behaviour. </li>
     <li> In this way we have a simple way of random sampling. </li>
    </ol>
   </li>
   <li> But clauses should stay as sets. </li>
   <li> A formal clause-list has then also a list of variables (without
   repetition). </li>
   <li> An "ordered hypergraph" is then also given as a list of hyperedges,
   together with a list of vertices (the latter without repetition). </li>
   <li> But the hyperedges still are sets. </li>
   <li> In the same vein, "ordered graphs" are given by lists of vertices and
   lists of edges, the former without repetition, the latter with sets as
   elements. </li>
   <li> So it seems that we should rewrite all of of the Maxima-functions.
   </li>
   <li> This combined with the general clean-up. </li>
   <li> The clause-sets etc. are still available, via conversions. </li>
   <li> What about combinatorial matrices? Their point is, after all,
   the order-*independence* ?!
    <ol>
     <li> So perhaps they stay as they are, using index-sets? </li>
     <li> However, there are the same issues regarding enumerations. </li>
     <li> So we should have also "ordered combinatorial matrices", where
     indices are given by 2 lists. </li>
    </ol>
   </li>
   <li> We use the adjective "ordered" as follows:
    <ol>
     <li> Speaking of "ordered clause-sets", "ordered graphs",
     "ordered hypergraphs" etc. </li>
     <li> Different from the "list-types", here we do not have
     multiple occurrences. </li>
     <li> So an "ordered clause-set" is the same structure as a "clause-list",
     but we do not have multiple occurrences of the same clause (while an
     "clause-list" may have them). </li>
    </ol>
   </li>
   <li> Handling the multiplicity of types:
    <ol>
     <li> We do not introduce abstraction at the Maxima/Lisp level (except
     of the "mathematical abstraction" given by using terms and functions).
     </li>
     <li> Functions are implemented for the appropriate input-types (formal
     clause-sets, or just clause-sets, etc.). </li>
     <li> The user applies conversions. </li>
     <li> What about providing convenience functions, which just convert their
     argument, and then apply the main function:
      <ol>
       <li> It seems to me (OK), that this just yields confusion, since for
       some functions we have it, for some others we don't. </li>
       <li> So we should have different versions only in case they really
       implement different behaviour! </li>
      </ol>
     </li>
    </ol>
   </li>
  </ul>


  \todo Plan the redesign
  <ul>
   <li> Making lists fundamental, and introducing new and consistent naming
   conventions. </li>
   <li> See "Redesign" in
   ComputerAlgebra/Satisfiability/Lisp/plans/general.hpp. </li>
   <li> See "Redesign" in ComputerAlgebra/Hypergraphs/Lisp/plans/general.hpp.
   </li>
   <li> See "Redesign" in ComputerAlgebra/Graphs/Lisp/plans/general.hpp. </li>
   <li> See "Concepts and abbreviations" in
   ComputerAlgebra/Trees/Lisp/plans/general.hpp. </li>
  </ul>


  \todo Recovering of partial results after long (unsuccessful) computations
  <ul>
   <li> See "all_unsinghitting" in
   ComputerAlgebra/Satisfiability/Lisp/ConflictCombinatorics/HittingClauseSets.mac
   for an example how to pass variable-names as parameters, and how to store
   the elements of the result-set piecewise in this variable. </li>
   <li> And see all_hitting_DP_reductions_def in
   ComputerAlgebra/Satisfiability/Lisp/ConflictCombinatorics/HittingClauseSets.mac
   for a more advanced example how to make make these recovering-variables
   optional; here we have also a state-variable (the permutation count),
   which allows re-starting the computation from an arbitrary point. </li>
   <li> In this way we should rewrite all functions which perform long
   computations, and for which it makes sense to collect partial results. </li>
   <li> Using "oklib --maxima -g", a running computation can be interrupted by
   Ctrl-C, a variable "var" can be displayed by "$var" (using "(displa $var)"
   one gets Maxima-representation), and by "continue" (at
   break-level 1 !) the computation can be continued.
    <ol>
     <li> Does this slow down computations? Some tests seem to indicate that
     this is not the case. </li>
     <li> So perhaps this should be our default? </li>
     <li> If something goes wrong with displaying values, then suddenly
     "continue" doesn't work anymore (but is treated as variable name)?!? </li>
     <li> And also for some other reasons continuation becomes impossible??
     (Then we don't have a "Continuable Error"). </li>
     <li> This looks like a clisp compiler weakness. Perhaps with 2.44.1 this
     is solved? </li>
     <li> Perhaps the problem is that when the execution is inside a
     sub-function then continuation is not possible? </li>
     <li> Anyway, this mechanism doesn't look really reliable yet. </li>
    </ol>
   </li>
   <li> Using "oklib_save()" in a functions stores the whole state
   of Maxima to a session file, after oklib_storage_interval
   minutes have passed, given that oklib_store is true.
    <ol>
     <li> This should be applied throughout. </li>
    </ol>
   </li>
  </ul>


  \todo Debugging
  <ul>
   <li> Again and again it happens that somehow the Lisp-debugger is entered,
   and apparently there is NO ESCAPE (":top" apparently should be the escape,
   but doesn't work). </li>
   <li> How to disable the debugger ?? </li>
  </ul>

  
  \todo Documentation
  <ul>
   <li> A work-around to obtain doxygen-documentation:
    <ol>
     <li> The solution seems to be to start the .mac-files
     with the usual preamble, and then via "\htmlonly" and
     "\endhtmlonly" to suppress the extraction of code-comments
     (the source code is shown verbatim!). </li>
     <li> We should discuss this on the doxygen mailing list:
     Perhaps a dedicated doxygen-command could be introduced? </li>
     <li> Or should one use the verbatim-commands? </li>
    </ol>
   </li>
   <li> How to create function-documentation inside Maxima (usable via
   "? function-name") ? </li>
  </ul>


  \todo Handling of demos
  <ul>
   <li> The demos-files are put into demos-subdirectory, and are plain
   .mac-files (intended to be processed). </li>
   <li> How to run the maxima-demos-files?
    <ol>
     <li> Apparently, "batch" is when we want to "run through it", while
     "demo" is when we want to pause after each expression. </li>
    </ol>
   </li>
   <li> How to name the demos-files?
    <ol>
     <li> If the demonstration accompanies a file, then it has the same name.
     </li>
     <li> Otherwise any appropriate name. </li>
     <li> The suffix ".dem" is mentioned in the Maxima-manual. This or
     ".mac" ?! </li>
    </ol>
   </li>
   <li> How to create pauses?
    <ol>
     <li> On a global level one has the distinction between "oklib_batch"
     and "oklib_demo". </li>
    </ol>
   </li>
   <li> Integrate the demos into the test-system. </li>
   <li> DONE How to print out explanations?
    <ol>
     <li> The problem is that when using "batch" or "demo", where expressions
     are reported before being printed, the explanations, for which we only
     have the print-statement, are printed twice?? </li>
     <li> The solution seems to be to use just the expression
     \verbatim
"Text to be shown"$
     \endverbatim
     </li>
    </ol>
   </li>
   <li> DONE How is it integrated into the general demos-system for the
   OKlibrary? Likely nothing special is done, only we need load-capabilities,
   likely here only for single files. </li>
   <li> DONE (oklib_batch, oklib_demo)
   Extend "oklib_load" to process the maxima-demos? Perhaps better
   a dedicated function. </li>
  </ul>


  \todo Monitoring
  <ul>
   <li> We introduce a global variable "oklib_monitor",
   which our functions can use, and if set to true then they
   output progress information. </li>
   <li> Additionally we have "oklib_monitor_level":
    <ol>
     <li> The default is level 0, meaning that only basic messages
     are print. </li>
     <li> Greater values are then used at the discretion of the affected
     function. </li>
     <li> "inf" always indicates full output. </li>
    </ol>
   </li>
   <li> This output should happen in a standardised way, so that
   the source of the output is recognisable.
    <ol>
     <li> We use "M[function_name]:" to start the message. </li>
     <li> Perhaps we can offer some general services, like functions
     which print the opening and ending. Something similar to the
     Messages-system for C++ perhaps.
      <ul>
       <li> But we don't consider internationalisation. </li>
       <li> And, of course, no compile-time-issues. </li>
       <li> Is there a general facility to find out the current
       function? Otherwise perhaps we use some standard variable,
       which is then set to the name of the function. </li>
      </ul>
     </li>
    </ol>
   </li>
   <li> The monitoring code uglifies the procedure:
    <ol>
     <li> Could there be a general scheme, that certain variables are
     watched and printed if they changed value, and this happens
     non-intrusively? But we need dedicated text etc., so this doesn't
     seem to hlep.</li>
     <li> Or functions which support monitoring come in two versions?
     This would created too much code-bloat. </li>
     <li> Output should always happen via helper-functions, so the
     interruption is minimal. Standard: "monitorcheck". </li>
     <li> This procedure just inherits all variable etc. via
     dynamic binding. </li>
    </ol>
   </li>
   <li> DONE For the introduction of "oklib_monitor", apparently
   "define_variable" should be used? </li>
   <li> See first examples:
    <ol>
     <li> ComputerAlgebra/Satisfiability/Lisp/Resolution/Basics.mac </li>
     <li> ComputerAlgebra/Satisfiability/Lisp/Backtracking/DLL_solvers.mac
     </li>
    </ol>
   </li>
  </ul>


  \todo Contexts
  <ul>
   <li> There is the notion of a "context" --- what does it mean? </li>
  </ul>


  \todo Lisp integration
  <ul>
   <li> The Lisp-dialect is "CLisp" --- are there books? </li>
   <li> How to integrate CLisp with Maxima ? </li>
   <li> Shouldn't we consider our code as Lisp-code, which uses the
   maxima-library ? Perhaps we can discuss this on the Maxima mailing
   list. </li>
  </ul>
     
     
  \todo Collaboration with the Maxima community
  <ul>
   <li> On the plans for the "Google Summer of code" at
   http://maxima.sourceforge.net/wiki/index.php/Design%20Notes
   there are quite some overlaps with the OKlibrary (especially
   regarding "Boolean algebra and logic"). </li>
   <li> At some point we should contact "the Maxima community",
   and discuss possibilities for collaborations:
    <ol>
     <li> The OKlibrary uses the Maxima-level only for
     "procedural specifications". </li>
     <li> So the Maxima community can use this as a map for the whole
     field, and produce some specific more efficient implementations at
     the Lisp level. </li>
     <li> Of course, also input on the use of Maxima in the OKlibrary would
     be welcome. </li>
     <li> And doxygen support for Maxima would be great. </li>
    </ol>
   </li>
   <li> A "Logic Algebra" (title of the email) module has been submitted to the
   maxima mailing list for consideration for inclusion in share/contrib and is 
   viewable at http://beshenov.ru/maxima/logic/ . Perhaps some collaboration
   could initially occur here? </li>
  </ul>


*/

