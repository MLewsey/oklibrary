// Matthew Gwynne, 8.12.2007 (Swansea)
/* Copyright 2007, 2008 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file ComputerAlgebra/Cryptology/Lisp/plans/AdvancedEncryptionStandard.hpp
  \brief Plans for cryptological tools regarding the Rijndael cipher using Maxima


  \todo New design and implementation
  <ul>
   <li> Move items from below to here, if appropriate. </li>
   <li> Regarding generalisations (AES -> Rijndael -> small-scale variations):
   If they come natural then they are done now, otherwise later (after we have
   more experience). </li>
   <li> Finite field operations
    <ol>
     <li> Move the interface to the gf-package into a seperate module / .mac file. </li>
     <li> The gf_set operation in the finite field package takes a considerable
     amount of time to complete and doesn't seem to cache 
     any of the results in any way and so each call takes the same amount of 
     time and so simply calling gf_set inside wrappers, as has been done, 
     causes issues where these functions are called often (such as in the case 
     of egf_add).
      <ol>
       <li> Perhaps a potential solution would be to keep track of which field
       is currently being used, and only if the field being used is different 
       to the last call would gf_set be called? (although in general, this 
       concept of keeping global state in such a way seems like it will cause 
       problems) .</li>
      </ol>
     </li>
     <li> Create an interface to the gf-package. DONE </li>
     <li> Create field-identification list [p, n, poly]. DONE </li>
     <li> Field-operation-functions take such an "object" as additional argument,
     to specify the field. DONE </li>
    </ol>
   </li>
   <li> Basic aes-functions:
    <ol>
     <li> S-box </li>
     <li> round-function </li>
     <li> key-schedule </li>
    </ol>
   </li>
  </ul>

  
  \todo Split "Maxima: design" into subtopics (and update)


  \todo Maxima: design
  <ul>
   <li> The following points need review --- the more general discussions belong
   to Axiom/Aldor(see below), and should be moved there, while here we have 
   to decide what is the "right" level of abstraction. </li>
   <li> What specifically is needed from the maxima implementation?
    <ul>
     <li> A function F_AES(p,k) = c and F_AES'(c,k) = p . </li>
     <li> How to generalise this to Rijndael? Perhaps F_Rijndael(p,k,r) where 
     the size of p and k is implicit based on the structures used for p and k,
     and r is given? Is r really needed as it seems this is a function of the 
     size of p and k? 
     </li>
     <li> A separate round function to allow greater flexibility 
     when investigating reduced round variants. </li>
     <li> What sort of generalisations are needed?
      <ol>
       <li> Should the elements of the round such as ShiftRows be interchangable
       to some arbitrary permutation (perhaps just across rows?)? </li>
       <li> Should MixColumns be generalised to an arbitrary 4-Byte value
       multiplication, should it even be viewed in this way? See ??? </li>
      </ol>
     </li>
    </ul>
   </li>
   <li> Should it be split up into each of the individual round functions
   ("MixColumns" etc) or should these be combined?
    <ol>
     <li> Combining them might make certain relationships/conditions more obvious,
     but it also makes things much less flexible and depending on how it is done,
     could make generalising to Rijndael harder. </li>
     <li> It seems a better understanding of the nature of the cipher might yield
     a different perspective that isn't as focused on these functions? </li>
    </ol>
    Further reading of Algebraic Aspects of the AES may yield some insight but this also 
    appears to consider such functions (although generalised to produce a larger number
    of AES variants), perhaps this is most natural?
   </li>
   <li> How to approach key scheduling?
    <ol>
     <li> AES and symmetric plaintext-key sizes provide a fairly elegant recursive
     key generation where each round key is just the result of the key generation
     on the last round key, whereas asymetric sizes such as 192bit plaintext and a
     128bit key means you will have to use parts of the previous two round keys. </li>
     <li>  This seems to be done with an expanded key which is a large array/list of round keys in Design of
     Rijndael. </li>
    </ol>
   </li> 
   <li> How to pass data around and represent field elements ?
    <ol>
     <li> It seems the simplest way to pass data around would be as a list of 
     bits, given that this is one of the simplest representations, it translates
     nicely when considering translation to SAT and translation from this to 
     finite field elements and elements within the 4-Byte PID seems trivial. </li>
    </ol>
   </li>
   <li> How should the implementation of the individual round operations be approached?
    <ul>
     <li> 3/4 conversion functions (OK: ???) with suitable inverses working on lists
     of the appropriate elements :
     <ol>
      <li> hexToGF2 (with binToHex) for conversion of a hexidecimal string
      in the same format as in the Design of Rijndael (discuss here). 
      </li>
      <li> GF2ToGF2t4 (with GF2t4ToGF2) for conversion of a list of binary bit 
      values representing GF(2) elements to a list of GF(2^4) elements.
      </li>
      <li> GF4ToGF2t8 (with GF2t8ToGF2t4)) for a conversion from a list of 
      elements in GF(2^4) to elements in GF(2^8).
      </li>
      <li> GF2t8ToPID (with PIDToGF2t8) for a conversion of a list of binary
      bit values representing GF(2) elements to a list of 4-Byte PID column elements.
      </li>
     </ol>
     </li>
     <li> The MixColumn operation, which would then take a list of GF(2) 
     elements or bits and convert it to a list of elements in the 4-Byte PID, 
     would simply be a mapping of the multiplication by the constant polynomial
     (2x^3 + 3x^2 + x + 1) across the list. </li>
     <li> There may be a way to represent this
     multiplication by simple operations over polynomials and so on, or it may 
     have to be represented via a matrix multiplication over GF(2^8). </li>
     <li> The list would then be converted back to GF(2) using the appropriate
     helper function. </li>
     <li> Such a  mapping would be general across AES and Rijndael. </li>
     <li> Generalising this based on parameter n_R discussed in [Algebraic
     Aspects of the AES}, seems possible by use of a lookup function for the
     constant to multiply based on n_R, as well as looking up the field to
     multiply over. </li>
     <li> Generalising over n_C should be trivial as given a function on elements
     in the QR/PID of size n_R (columns), the result of MixColumns is just a
     mapping over n_C of these elements and so the n_C parameter seems irrelevant
     here. </li>
     <li> Generalising over e, seems to tie in closely with generalising over n_R,
     as the polynomial the elements in columns of the block form, are over elements
     of size e. </li>
     <li> The SubBytes operation would take a list of GF(2) elements, convert this
     list to a list of GF(2^8) elements, and then map the S_rd operation across it. 
     The resultant list would then be converted back to a list of GF(2)/bit elements.
     Such a mapping would be general across AES and Rijndael. Discussion is needed 
     on potential generalisation to ???
     </li>
     <li> The ShiftRows operation is simply the shift operation applied to each row
     in the block seperately depending on the size of the input. This can be achieved 
     by taking the list of GF(2) elements, and partitioning it into a list of 4 lists of
     GF(2) elements, which can then simply be shifted by the appropriate amounts, perhaps
     determining the amount to shift/rotate by for each list/row by looking at the length
     of the input list.
     </li>
     <li> The Key Scheduling operation could simply take a list of GF(2) elements convert this
     to a list of GF(2^8) elements and perform the key schedule repeatedly in an iterative or
     recursive manner to produce the expanded key, for which the algorithm is relatively 
     simple and described in Design of Rijndael and in various other places, returning an 
     expanded key (list of GF(2) elements) of size of r+1 times the block size, which the 
     individual round keys can then be extracted from using a helper function. </li>
     <li> It seems that defining such operations as operations on matrices provides the 
     most clear representation of each round function. The question of how to 
     parameterise such an implementation, may be addressed by parameterising
     the round functions or at least their basic operations themselves. </li>
    </ul>
   </li>
  </ul>


  \todo Split "Maxima: implementation issues" into subtopics (and update)


  \todo Maxima: implementation issues
  <ul>
   <li> The main point is to have a very neat implementation of AES/Rijndael. </li>
   <li> Some initial/example code for this has been added in
   ComputerAlgebra/Cryptology/AES.mac. </li>
   <li> OK : where does the suffix ".mac" come from? looks unmotivated to me?
   is this the standard ending for maxima-files, or for special ones? </li>
   <li> MG - Looking through the maxima documentation and at
   the Finite Fields package and others, it seemed to be the common file extension,
   and due to a misunderstanding on my part, I believed that it was required, however
   I simply misunderstood the use of the load function and a more explicit file
   extension of .maxima following the TauMachinery example seems sensible. OK : one
   could ask this question on the (main) maxima mailing list. </li>
   <li> Most important: Follow the standard coding practice!
    <ol>
     <li> Use named constants. </li>
     <li> Do not use abbreviated names except of well-established cases. </li>
     <li> Add code documentation for the specification of functions. </li>
    </ol>
    Furthermore declarations of local variables are needed.
   </li>
   <li> The finite field packages function names, along with maximas syntax make
   things a little verbose and perhaps a little longer than is really necessary a
   lthough this is more of a nuisance than a real problem.
   OK : Why is there a nuisance? In general in the OKlibrary "full" names are appreciated; is this
   somewhat special here?
   MG : It only arose as an issue due to my wish to keep the code relatively
   short and concise and so while trying to keep to a fixed line length of say
   80 characters, this meant that the code become much longer. The syntax when
   dealing with the binary operations as well doesn't seem to immediately make
   clear things such as associativity when reading, in my mind, potentially making
   simplification more difficult. I imagine that this is more my unfamiliarity 
   with the language and more importantly problems occuring due to lack of design.
   as suggested below.</li>
   <li> Since we need the package, and it doesn't come with Maxima, we need to
   handle it as an ExternalSource. 
    <ul>
     <li> What is the procedure for this?
      <ol>
       <li> At least make the package (pyhsically) available. </li>
       <li> Installation will at least unpack it, and put it to a right place. </li>
       <li> There should be configuration variables which help us using the package. </li>
      </ol>
     </li>
     <li> When doing this, it might be beneficial to add some basic functionality
     such as a gf_matadd (matrix addition within the set field) and so on which
     isn't currently offered but seems trivial to implement using the functions 
     defined in gf.mac, although whether this is useful would depend on the design. </li>
    </ul>
   </li>
   <li> How best to implement multiplication by the 4-byte constant in the 
    MixColumns step (or it's equivalent), as it is not a field element?
     <ol>
      <li> It seems Maxima has functions regarding various operations on
      polynomials (multiplication, quotient/modulus etc) but is this general
      enough in terms of the field it works over or is it specific to the reals? </li>
      <li> It appears you can override the functions used for multiplication etc and
      so generalising the field used, even if not easily possible, seems at
      least possible? </li>
      <li> Is there a great deal of benefit from representing the
      multiplication by this fixed constant in the 4-Byte PID/QR (or variants)
      or is it better to simply represent this as matrix operation, does this
      lose anything? </li>
     </ol>
   </li>
   <li> Right form of abstraction : DONE (these problems will go away through proper design)
    <ol>
     <li> Approaching the implementation from the perspective of the 4-byte block
     using this package (and with sage's finite fields) seems to be a little harder
     as the 4-byte block only forms a ring and it needs to be looked into
     how to form rings that behave in the same way (with a given polynomial modulus etc).
     Trying to create a field object without checking if the modulus is irreducible and then
     somehow casting that to a Ring doesn't seem to work although I'm not sure why it would. </li>
     <li> It seems easier to me to express the system in terms of the byte field
     elements (GF(2^8)) as most of the operations  are easily expressed as operations
     on these elements although it doesn't appear that many others have looked at the 
     problem from the perspectives other than GF(2^8) and GF(2) so other perspectives
     (4-byte block, considering things as operations on integers etc) might yield
     something different. </li>
     <li> OK: The problem I see here is that there is no proper design --- design
     (in the plans) must come first! (Implementations come later!!) </li>
    </ol>
   </li>
   <li> Finite fields? Possibly through a third party package. (see
   http://www.math.utexas.edu/pipermail/maxima/2006/003255.html), 
   although this looks untested. DONE (started using it) </li>
  </ul>

*/