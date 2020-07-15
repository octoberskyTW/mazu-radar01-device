               TMS320C6000 C/C++ CODE GENERATION TOOLS
                         8.3.3 Release Notes
                              February 2019


===============================================================================
Contents
===============================================================================

1) Support Information
   1.1) List of Fixed and Known Defects
   1.2) Compiler Wiki
   1.3) Compiler Documentation Errata
   1.4) TI E2E Community
   1.5) Defect Tracking Database

2) C++ 2014 Support

3) Printf Support for Vector Data Types

4) Optimizer no longer required to use Vector Data Types

5) Compiler Option --legacy

6) Linker Feature: Using memory for multiple purposes

7) Linker Option --ecc

8) New Function Inlining Control Pragmas

9) Bug related to restrict pointers fixed

-------------------------------------------------------------------------------
1) Support Information
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
1.1) List of Fixed and Known Defects
-------------------------------------------------------------------------------

The Open_defects.html and Closed_defects.html files show the open and closed
defects for the 8.3.x compiler branch. For open bugs, a status of Open or
Accepted means that the bug has not been examined yet, whereas a status of
Planned means that an evaluation or fix is in progress.

-------------------------------------------------------------------------------
1.2) Compiler Wiki
-------------------------------------------------------------------------------

A Wiki has been established to assist developers in using TI Embedded Processor
Software and Tools.  Developers are encouraged to read and contribute to the
articles.  Registered users can update missing or incorrect information.  There
is a large section of compiler-related material.  Please visit:

http://processors.wiki.ti.com/index.php?title=Category:Compiler

-------------------------------------------------------------------------------
1.3) Compiler Documentation
-------------------------------------------------------------------------------

The "TMS320C6000 Optimizing Compiler User's Guide" can be downloaded from:

http://www.ti.com/tools-software/compilers/download.html

Navigate to the C6000 Code Generation Tools section to view the user guide in
HTML or PDF format.

-------------------------------------------------------------------------------
1.4) TI E2E Community
-------------------------------------------------------------------------------

Questions concerning TI Code Generation Tools can be posted to the TI E2E
Community forums.  The "Development Tools" forum can be found at:

http://e2e.ti.com/support/development_tools/f/default.aspx

-------------------------------------------------------------------------------
1.5) Defect Tracking Database
-------------------------------------------------------------------------------

Compiler defect reports can be tracked at the Development Tools bug database,
SDOWP. The log in page for SDOWP, as well as a link to create an account with
the defect tracking database is found at:

https://cqweb.ext.ti.com/pages/SDO-Web.html

A my.ti.com account is required to access this page.  To find an issue in
SDOWP, enter your bug id in the "Find Record ID" box once logged in.  To find
tables of all compiler issues click the queries under the folder:

"Public Queries" -> "Development Tools" -> "TI C-C++ Compiler"

With your SDOWP account you can save your own queries in your "Personal
Queries" folder.

--------------------------------------------------------------------------------
2) C++ 2014 support
--------------------------------------------------------------------------------

As of v8.3, the compiler supports the C++14 version of the C++ standard.  C++03
is no longer supported. See the C++14 Standard ISO/IEC 14882:2014. For a
description of unsupported C++ features, see Section 7.2 of the "TMS320C6000
Optimizing Compiler User's Guide".

The move to C++14 will break ABI compatibility with previous C++ RTS releases.
Attempting to link old C++ object code with the new RTS will result in a
link-time error. Suppressing this error will likely result in undefined symbols
or undefined behavior during execution.

C ABI compatibility will not be affected by this change.

In most cases, recompiling old source code with the new RTS should be safe.
However, due to the changes made in the language, some constructs will result
in syntax errors. Some common issues include:
- Macro expansion immediately adjacent to string literals may fail due to the
  inclusion of new string literals and literal suffixes.
  Ex: u8"def" will fail to compile if 'u8' is a macro
      "def"_x will fail to compile if '_x' is a macro
- New keywords: alignas, alignof, char16_t, char32_t, constexpr, decltype,
  noexcept, nullptr, static_assert, and thread_local
- The auto keyword has been repurposed and is no longer a valid storage class
  specifier. Similarly, the register keyword has been deprecated and will be
  removed in the future.

A full list can be found in Appendix C, section 2 of the C++14 standard.

-------------------------------------------------------------------------------
3) Printf Support for Vector Data Types
-------------------------------------------------------------------------------

As of v8.3, the printf() function included it the RTS supports vector data
types. The convention set by OpenCL 1.2 as documented in Section 6.12.13 of the
OpenCL 1.2 standard is followed with one exception. This exception is to do
with use of ll instead of l in the format string for longlong vector
conversions.

Example:

 float4 f = (float4)(1.0f, 2.0f, 3.0f, 4.0f);
 uchar4 uc = (uchar4)(0xFA, 0xFB, 0xFC, 0xFD);

 printf("f4 = %2.2v4hlf\n", f);
 printf("uc = %#v4hhx\n", uc);

 /* Output: */
 f4 = 1.00,2.00,3.00,4.00
 uc = 0xfa,0xfb,0xfc,0xfd

-------------------------------------------------------------------------------
4) Use of Vector Data Types no longer requires optimizer
-------------------------------------------------------------------------------

Usage of vector data types previously required the optimizer. As of v8.3, use
of the optimizer is no longer required i.e. the --vectypes option can be used
without specifying a -o[0-3] option.

-------------------------------------------------------------------------------
5) Compiler Option --legacy
-------------------------------------------------------------------------------

As of the 8.2.2 release, a compiler option, --legacy, has been added.  When
legacy code bases tuned for C6000 CGT v7.4.x or older exhibit performance
degradations (cycles or code size) with later compiler versions, this option
may help. Do not use this option in new applications. Any new features added to
newer tool chains will not be available when the --legacy option is used.

-------------------------------------------------------------------------------
6) New Linker Feature: Using memory for multiple purposes
-------------------------------------------------------------------------------

As of v8.3, this feature enables overlaying an initialized section with the
same load and run address with other sections that have separate load and run
addresses.

One way to reduce memory required is to use the same range of memory for
multiple purposes. It is possible to use a range of memory at first for system
initialization and startup. Once that phase is complete, the same memory can
then be repurposed as a collection of uninitialized data variables, or a heap.
To implement this scheme, use the variation of UNION which allows one section
to be initialized, and the remaining sections to be uninitialized.

Generally, an initialized section (one with raw data, such as .text) in a union
must have its load allocation separately specified. However, one and only one
initialized section in a union can be allocated at the union's run address. By
listing it in the union with no load allocation at all, it will use the union's
run address as its own load address.

For example:

 UNION run = FAST_MEM

 { .cinit .bss }

.cinit is an initialized section. It will be loaded into FAST_MEM at the run
address of the union. .bss is an uninitialized section. Its run address will
also be that of the union.

-------------------------------------------------------------------------------
7) New Linker Option --ecc
-------------------------------------------------------------------------------

In previous versions, linker generated ECC has been enabled via an ECC
specifier on memory ranges in the linker command file. This makes it difficult
for TI to provide linker command files with ECC specified because users need
the ability to enable/disable the support.

Starting with v8.3, users can enable/disable ecc support via the --ecc=[on|off]
linker option. Existing users of ECC will need to specify --ecc=on

-------------------------------------------------------------------------------
8) New Function Inlining Control Pragmas
-------------------------------------------------------------------------------

Three new pragmas to control function inlining were added in this version:

a) The FORCEINLINE pragma will force functions to be inlined in the annotated
statement i.e., it has no effect on those functions in general, only on
function calls in a single statement.

b) The FORCEINLINE_RECURSIVE pragma will force inlining not only of calls
visible in the statement, but also in the inlined bodies of calls from that
statement.

c) The NOINLINE pragma prevents calls within a single statement from being
inlined. (NOINLINE is the inverse of the FORCEINLINE pragma.)

-------------------------------------------------------------------------------
9) Bug related to restrict pointers fixed
-------------------------------------------------------------------------------

A bug that could propagate a restrict pointer into a disjoint scope (e.g., an
inlined function) and make a wrong decision about memory disambiguation was
fixed.

The fix may cause performance degradations when a restrict pointer is passed
into an inlined function.

Based on the definition of 'restrict', 'restrict' means within the scope of the
declaration of a pointer P. Only P or expressions based on P will be used to
access the object or sub-object pointed to by P. A pointer copy of another
restrict pointer can inherit the restrictness only when they are in the same
scope or nested scopes.

For example:

 int x[100];
 void test()
 {
   int *restrict p1;
   int *restrict p2;

   p1 = x;
   p2 = x+1;

   foo(p1);
   bar(p2);
 }


 void foo(int* r1)
 {
   *(r1+1) = 0;
   return;
 }

 void bar(int* r2)
 {
   *r2 = 1;
   return;
 }

After inlining foo() and bar(), we have:

 void test()
 {
   int *restrict p1;
   int *restrict p2;

   p1 = x;
   p2 = x+1;

   {// inlined function f00()
     int *r1 = p1;
     *(r1+1) = 0;
   }

   {// inlined function bar()
     int *r2=p2;
     *r2 = 1;
   }
 }

Previous versions of the compiler might propagate p1 and p2 for r1 and r2, and
incorrectly determine that *(r1+1) and *r2 do not alias.

This fix may cause performance degradations when pointers in disjoint scopes
actually do not access the same memory locations, because the compiler has to
assume that alias exists.

-- End Of File --
