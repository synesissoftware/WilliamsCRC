/* /////////////////////////////////////////////////////////////////////////
 * File:        WilliamsCRC/implicit_link.h
 *
 * Purpose:     Implicit linking for the WilliamsCRC API
 *
 * Created:     6th January 2021
 * Updated:     31st December 2023
 *
 * Copyright (c) 2021-2023, Matthew Wilson and Synesis Information Systems
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * - Neither the name(s) of Matthew Wilson and Synesis Information Systems
 *   nor the names of any contributors may be used to endorse or promote
 *   products derived from this software without specific prior written
 *   permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ////////////////////////////////////////////////////////////////////// */


/** \file WilliamsCRC/implicit_link.h
 *
 * \brief [C, C++] Implicit linking for the WilliamsCRC API.
 */

#ifndef WILLIAMSCRC_INCL_WILLIAMSCRC_H_IMPLICIT_LINK
#define WILLIAMSCRC_INCL_WILLIAMSCRC_H_IMPLICIT_LINK

/* /////////////////////////////////////////////////////////////////////////
 * version information
 */

#ifndef WILLIAMSCRC_DOCUMENTATION_SKIP_SECTION
# define WILLIAMSCRC_VER_WILLIAMSCRC_H_IMPLICIT_LINK_MAJOR      1
# define WILLIAMSCRC_VER_WILLIAMSCRC_H_IMPLICIT_LINK_MINOR      0
# define WILLIAMSCRC_VER_WILLIAMSCRC_H_IMPLICIT_LINK_REVISION   3
# define WILLIAMSCRC_VER_WILLIAMSCRC_H_IMPLICIT_LINK_EDIT       3
#endif /* !WILLIAMSCRC_DOCUMENTATION_SKIP_SECTION */

/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#ifndef SYNSOFT_INCL_WILLIAMSCRC_H_WILLIAMSCRC
# include <WilliamsCRC/WilliamsCRC.h>
#endif /* !SYNSOFT_INCL_WILLIAMSCRC_H_WILLIAMSCRC */

/* /////////////////////////////////////////////////////////////////////////
 * macros and definitions
 */

#define WILLIAMSCRC_STRINGIZE_(x)                           #x
#define WILLIAMSCRC_STRINGIZE(x)                            WILLIAMSCRC_STRINGIZE_(x)

/* /////////////////////////////////////////////////////////////////////////
 * architecture discrimination
 */

#if defined(__amd64__) || \
    defined(__amd64) || \
    defined(_AMD64_) || \
    defined(_M_AMD64) || \
    defined(_M_X64)
# define WILLIAMSCRC_ARCH_IS_X64
#elif defined(__ia64__) || \
      defined(__ia64) || \
      defined(_IA64_) || \
      defined(_M_IA64)
# define WILLIAMSCRC_ARCH_IS_IA64
#elif defined(__i386__) || \
      defined(__i386) || \
      defined(_X86_) || \
      defined(_M_IX86)
# define WILLIAMSCRC_ARCH_IS_X86
#endif /* _M_?? */

/* /////////////////////////////////////////////////////////////////////////
 * implicit linking
 */

#if defined(_WIN32) || \
    defined(_WIN64)

# if defined(__BORLANDC__) || \
     /* defined(__DMC__) || */ \
     defined(__INTEL_COMPILER) || \
     defined(__MWERKS__) || \
     defined(_MSC_VER)
#  if !defined(__COMO__)
#   define WILLIAMSCRC_IMPLICIT_LINK_SUPPORT
#  endif /* compiler */
# endif /* compiler */

# if defined(WILLIAMSCRC_IMPLICIT_LINK_SUPPORT) && \
     defined(WILLIAMSCRC_NO_IMPLICIT_LINK)
#  undef WILLIAMSCRC_IMPLICIT_LINK_SUPPORT
# endif /* WILLIAMSCRC_IMPLICIT_LINK_SUPPORT && WILLIAMSCRC_NO_IMPLICIT_LINK */

# if defined(WILLIAMSCRC_IMPLICIT_LINK_SUPPORT)

  /* prefix */

#  define WILLIAMSCRC_IMPL_LINK_PREFIX

  /* library basename */

#  define WILLIAMSCRC_IMPL_LINK_LIBRARY_BASENAME            "SynesisSoftware.WilliamsCRC"

  /* major version */

#  define WILLIAMSCRC_IMPL_LINK_MAJOR_VERSION               "." WILLIAMSCRC_STRINGIZE(SYNSOFT_WILLIAMSCRC_VER_MAJOR)

  /* library module */

#  define WILLIAMSCRC_IMPL_LINK_LIBRARY_MODULE              "core"

  /* module name */

#  define WILLIAMSCRC_IMPL_LINK_MODULE_NAME                 ""

  /* compiler tag */

#  if defined(__BORLANDC__)
#   if 0
#   elif __BORLANDC__ == 0x0550
#    define WILLIAMSCRC_IMPL_LINK_COMPILER_NAME             "bc55"
#   elif (__BORLANDC__ == 0x0551)
#    define WILLIAMSCRC_IMPL_LINK_COMPILER_NAME             "bc551"
#   elif (__BORLANDC__ == 0x0560)
#    define WILLIAMSCRC_IMPL_LINK_COMPILER_NAME             "bc56"
#   elif (__BORLANDC__ == 0x0564)
#    define WILLIAMSCRC_IMPL_LINK_COMPILER_NAME             "bc564"
#   elif (__BORLANDC__ == 0x0582)
#    define WILLIAMSCRC_IMPL_LINK_COMPILER_NAME             "bc582"
#   elif (0x0590 == (__BORLANDC__ & 0xfff0))
#    define WILLIAMSCRC_IMPL_LINK_COMPILER_NAME             "bc59x"
#   elif (0x0610 == (__BORLANDC__ & 0xfff0))
#    define WILLIAMSCRC_IMPL_LINK_COMPILER_NAME             "bc61x"
#   else /* ? __BORLANDC__ */
#    error Unrecognised value of __BORLANDC__
#   endif /* __BORLANDC__ */

/*
#  elif defined(__DMC__)
#   define WILLIAMSCRC_IMPL_LINK_COMPILER_NAME              "dm"
 */

#  elif defined(__INTEL_COMPILER)
#   if 0
#   elif __INTEL_COMPILER == 600
#    define   WILLIAMSCRC_IMPL_LINK_COMPILER_NAME           "icl6"
#   elif __INTEL_COMPILER == 700
#    define   WILLIAMSCRC_IMPL_LINK_COMPILER_NAME           "icl7"
#   elif __INTEL_COMPILER == 800
#    define   WILLIAMSCRC_IMPL_LINK_COMPILER_NAME           "icl8"
#   elif __INTEL_COMPILER == 900
#    define   WILLIAMSCRC_IMPL_LINK_COMPILER_NAME           "icl9"
#   elif __INTEL_COMPILER == 1000
#    define   WILLIAMSCRC_IMPL_LINK_COMPILER_NAME           "icl10"
#   elif __INTEL_COMPILER == 1100
#    define   WILLIAMSCRC_IMPL_LINK_COMPILER_NAME           "icl11"
#   else /* ? __INTEL_COMPILER */
#    error Intel C/C++ version not supported
#   endif /* __INTEL_COMPILER */

#  elif defined(__MWERKS__)
#   if 0
#   elif ((__MWERKS__ & 0xFF00) == 0x2400)
#    define WILLIAMSCRC_IMPL_LINK_COMPILER_NAME             "cw7"
#   elif ((__MWERKS__ & 0xFF00) == 0x3000)
#    define WILLIAMSCRC_IMPL_LINK_COMPILER_NAME             "cw8"
#   elif ((__MWERKS__ & 0xFF00) == 0x3200)
#    define WILLIAMSCRC_IMPL_LINK_COMPILER_NAME             "cw9"
#   else /* ? __MWERKS__ */
#    error CodeWarrior version not supported
#   endif /* __MWERKS__ */

#  elif defined(_MSC_VER)
#   if 0
#   elif _MSC_VER < 1200
#    error WilliamsCRC is not supported for Visual C++ compilers prior to version 6 (Visual Studio 1998)
#   elif _MSC_VER == 1200
#    define WILLIAMSCRC_IMPL_LINK_COMPILER_NAME             "vc6"
#   elif _MSC_VER == 1300
#    define WILLIAMSCRC_IMPL_LINK_COMPILER_NAME             "vc7"
#   elif _MSC_VER == 1310
#    define WILLIAMSCRC_IMPL_LINK_COMPILER_NAME             "vc71"
#   elif _MSC_VER == 1400
#    define WILLIAMSCRC_IMPL_LINK_COMPILER_NAME             "vc8"
#   elif _MSC_VER == 1500
#    define WILLIAMSCRC_IMPL_LINK_COMPILER_NAME             "vc9"
#   elif _MSC_VER == 1600
#    define WILLIAMSCRC_IMPL_LINK_COMPILER_NAME             "vc10"
#   elif _MSC_VER == 1700
#    define WILLIAMSCRC_IMPL_LINK_COMPILER_NAME             "vc11"
#   elif _MSC_VER == 1800
#    define WILLIAMSCRC_IMPL_LINK_COMPILER_NAME             "vc12"
#   elif _MSC_VER == 1900
#    define WILLIAMSCRC_IMPL_LINK_COMPILER_NAME             "vc14"
#   elif _MSC_VER >= 1910
#    if 0
#    elif _MSC_VER < 1920
#     define WILLIAMSCRC_IMPL_LINK_COMPILER_NAME            "vc15"
#    elif _MSC_VER <= 1929
#     define WILLIAMSCRC_IMPL_LINK_COMPILER_NAME            "vc16"
#    else
#     error Visual C++ version that is >= vc16 is not recognised
#    endif
#   else /* ? _MSC_VER */
#    error Visual C++ version not supported
#   endif /* _MSC_VER */

#  else /* ? compiler */
#   error Unrecognised compiler
#  endif /* compiler */


  /* operating system tag */

#  if defined(_STLSOFT_FORCE_ANY_COMPILER) && \
      defined(WILLIAMSCRC_PLATFORM_IS_UNIX) && \
      defined(_WIN32)
#   define WILLIAMSCRC_IMPL_LINK_OS_TAG                     ".unix"
#  endif /* pseudo UNIX */

#  if !defined(WILLIAMSCRC_IMPL_LINK_OS_TAG)
#   define WILLIAMSCRC_IMPL_LINK_OS_TAG                     ""
#  endif /* !WILLIAMSCRC_IMPL_LINK_OS_TAG */


  /* architecture tag */

#  if defined(WILLIAMSCRC_ARCH_IS_X86)
#   define WILLIAMSCRC_IMPL_LINK_ARCH_TAG                   ""
#  elif defined(WILLIAMSCRC_ARCH_IS_X64)
#   define WILLIAMSCRC_IMPL_LINK_ARCH_TAG                   ".x64"
#  elif defined(WILLIAMSCRC_ARCH_IS_IA64)
#   define WILLIAMSCRC_IMPL_LINK_ARCH_TAG                   ".ia64"
#  endif /* arch */

#  if !defined(WILLIAMSCRC_IMPL_LINK_ARCH_TAG)
#   define WILLIAMSCRC_IMPL_LINK_ARCH_TAG                   ""
#  endif /* !WILLIAMSCRC_IMPL_LINK_ARCH_TAG */


  /* encoding tag */

#  if defined(WILLIAMSCRC_CHAR_TYPE_IS_WCHAR)
#   define WILLIAMSCRC_IMPL_LINK_ENCODING_TAG               ".widestring"
#  else /* ? WILLIAMSCRC_CHAR_TYPE_IS_WCHAR */
#   define WILLIAMSCRC_IMPL_LINK_ENCODING_TAG               ""
#  endif /* WILLIAMSCRC_CHAR_TYPE_IS_WCHAR */


  /* threading tag */

#  if defined(__MT__) || \
      defined(_REENTRANT) || \
      defined(_MT)
#   if 0
#   elif defined(_DLL) || \
       defined(__DLL)
#    define WILLIAMSCRC_IMPL_LINK_THREADING_TAG             ".dll"
#   else /* ? dll */
#    define WILLIAMSCRC_IMPL_LINK_THREADING_TAG             ".mt"
#   endif /* dll */
#  else /* ? mt */
#    define WILLIAMSCRC_IMPL_LINK_THREADING_TAG             ""
#  endif /* mt */


  /* debug tag */

#  if !defined(NDEBUG) && \
      defined(_DEBUG)
#   define WILLIAMSCRC_IMPL_LINK_DEBUG_TAG                  ".debug"
#  else /* ? debug */
#   define WILLIAMSCRC_IMPL_LINK_DEBUG_TAG                  ""
#  endif /* debug */


  /* suffix */

#  define WILLIAMSCRC_IMPL_LINK_SUFFIX                      ".lib"


   /* Library name is:
    *
    * [lib]<library-basename>.<major-version>.<module-name>.<compiler-name>[.<os-arch-tag>][.<char-encoding-tag>][.<threading-tag>][.<nox-tag>][.<debug-tag>].{a|lib}
    */

#  define WILLIAMSCRC_IMPL_LINK_LIBRARY_NAME                WILLIAMSCRC_IMPL_LINK_PREFIX \
                                                            WILLIAMSCRC_IMPL_LINK_LIBRARY_BASENAME \
                                                            WILLIAMSCRC_IMPL_LINK_MAJOR_VERSION \
                                                            "." WILLIAMSCRC_IMPL_LINK_LIBRARY_MODULE \
                                                            WILLIAMSCRC_IMPL_LINK_MODULE_NAME \
                                                            "." WILLIAMSCRC_IMPL_LINK_COMPILER_NAME \
                                                            WILLIAMSCRC_IMPL_LINK_OS_TAG \
                                                            WILLIAMSCRC_IMPL_LINK_ARCH_TAG \
                                                            WILLIAMSCRC_IMPL_LINK_ENCODING_TAG \
                                                            WILLIAMSCRC_IMPL_LINK_THREADING_TAG \
                                                            WILLIAMSCRC_IMPL_LINK_DEBUG_TAG \
                                                            WILLIAMSCRC_IMPL_LINK_SUFFIX


#  pragma message("lib: " WILLIAMSCRC_IMPL_LINK_LIBRARY_NAME)

#  pragma comment(lib, WILLIAMSCRC_IMPL_LINK_LIBRARY_NAME)

# endif /* WILLIAMSCRC_IMPLICIT_LINK_SUPPORT */

#endif /* Win-32 || Win-64 */

/* ////////////////////////////////////////////////////////////////////// */

#endif /* !WILLIAMSCRC_INCL_WILLIAMSCRC_H_IMPLICIT_LINK */

/* ///////////////////////////// end of file //////////////////////////// */

