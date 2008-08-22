// Oliver Kullmann, 6.9.2007 (Swansea)
/* Copyright 2007, 2008 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Buildsystem/ExternalSources/SpecialBuilds/docus/Mhash.hpp
  \brief Documentation on how to build and use Mhash


  <h1> Installing and using Mhash </h1>


  <h2> On the purpose of Mhash </h2>

  Mhash is a C library with cryptographic tools XXX


  <h2> What the installation yields </h2>

  <ul>
   <li> The mhash header files and the corresponding link libraries XXX </li>
   <li> Documentation XXX </li>
  </ul>


  <h2> Usage </h2>

  <ul>
   <li> To include a mhash-header use for example
   \code
#include <mhash/XXX>
   \endcode
   together with "${mhash_include_option}" XXX (currently "$(Mhash)" XXX). </li>
   <li> To link with %Mhash, use "${mhash_link_option}" XXX for each sub-library separately XXX. </li>
  </ul>


  <h2> Current state of installation </h2>

  <ul>
   <li> Recommended version = <code>$(mhash_recommended_version_number)</code> </li>
   <li> %mhash include option = <code>$(mhash_include_option)</code> XXX </li>
   <li> %mhash link option = <code>$(mhash_link_option)</code> XXX </li>
   <li> ready: $(mhash_ready)
    <ul>
     <li> mode = <code>$(mhash_default_install)</code> </li>
     <li> version = <code>$(version_mhash)</code>
     </li>
    </ul>
   </li>
   <li> documentation: $(mhash_html_documentation_index_location_tag) </li>
   <li> list of supported versions XXX </li>
  </ul>


  <h2> How to install </h2>

  Some general remarks:
  <ul>
   <li> Currently only local installation is provided. </li>
   <li> If the required local installation of gcc is not available, then it
   needs to be built first (currently this is not handled by the build
   system). </li>
  </ul>


  <h3> Make targets </h3>
  
  <table>
   <tr>
    <td> <code> mhash </code> </td>
    <td> Build the recommended version of mhash, using the local gcc. </td>
   </tr>
   <tr>
    <td> <code> mhash-a.b.c.d </code> </td>
    <td> Build version a.b.c.d of mhash, using the local gcc (using for
    example <code>mhash-0.9.7.1</code>). </td>
   </tr>
   <tr>
    <td> <code> mhash gcc_version_okl=x.y.z </code> </td>
    <td> Build the recommended version of mhash, using the local gcc-version x.y.z (for example use <code>gcc_version_okl=4.1.2</code>). </td>
   </tr>
   <tr>
    <td> <code> mhash gcc_version_okl=all </code> </td>
    <td> Build the recommended version of mhash for all supported local gcc-versions as well as the system-gcc. </td>
   </tr>
   <tr>
    <td> <code> mhash-a.b.c.d gcc_version_okl=x.y.z </code> </td>
    <td> Build version a.b.c.d of mhash, using the local gcc-version x.y.z. </td>
   </tr>
   <tr>
    <td> <code> mhash-a.b.c.d gcc_version_okl=all </code> </td>
    <td> Build version a.b.c.d of mhash for all supported local gcc-versions as well as the system-gcc. </td>
   </tr>
   <tr>
    <td> <code> mhash_gcc_all </code> </td>
    <td> Build all supported versions of mhash for all all supported local gcc-versions as well as the system-gcc. </td>
   </tr>
  </table>


  <h3> Configuration </h3>

  <ul>
   <li> To use the system-gcc, set variable <code>gcc_version_okl</code> to the
   empty string. </li>
   <li> And to use a different version of gcc set variable
   <code>gcc_version_okl</code> accordingly.
  </ul>

*/

