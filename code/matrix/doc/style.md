Style
=====

Sean Kelleher
-------------

### About

Style guide for C code.

### Header Files

Header files are used to generate public documentation, and thus use a
doxygen-compatible, Javadoc-style, comment syntax. Every C header file must
begin with a comment describing the content of the file.

    /**
     * \file <file>.h
     * \brief A brief description of why this file exists.
     */

More details on the file can be added to this comment following the `\brief`
line.

Header files must use the standard C header inclusion trick to avoid names being
declared multiple times:

    #ifndef _<file>_H_
    #define _<file>_H_

        ...

    #endif

These are to occur right after the file description.

All other objects must be documented with at least a `\brief` description, again
using Javadoc-style comment syntax.

### C Files

C files are documented using single-line comments and must begin with a brief
comment describing why the file exists.
