Asserts
=======

Sean Kelleher
-------------

### About

This document justifies the use of `assert` statements in this project.

### The Problem

`assert` statements are a special kind of error detection that can be disabled
by a compiler flag. There is a difference between

    ASSERT(0 <= row && row < num_rows);

and

    if (0 <= row && row < num_rows) {
        return index_err("'row' is out of range");
    }

where `index_err` creates a special error structure that is returned by the
enclosing function. I'll refer to assertions of the first form as invariants and
assertions of the second form as constraints. The two differ in who the target
of the error is - if an invariant is violated, that is an error in the code,
with the target of the error being the developer of the API. A violated
constraint, however, is a condition required of the API user that was not
upheld, such as the boundary condition (that an index may not be out of range,
as in the code snippet above). In languages with unchecked exceptions, it is
common for an API to provide an auxiliary function to check if parameters are
safe to pass to another function, such as a function to check if a dictionary
contains a certain key before trying to retrieve the associated value.

Another difference between what we have denoted as invariants and constraints is
that constraints will usually provide a description of what went wrong, because
a developer may not have access to, or want to investigate, the code at the
location where the error occurred. Invariants, however, are (or should be)
self-descriptive, and will require that the source code at that location be
examined.

The key difference between invariants and constraints is the fact that
invariants can be disabled. Once confidence has been built that the invariants
of a piece of code indeed hold, those assertions can be disabled to speed up the
overall performance of the containing functions. This should only be done,
however, for code that will never be public - invariants that provide assertions
about information from the outside world should never be disabled, and thus,
should be replaced by constraints.

### The Solution

There is no solution provided because there is no problem with using `assert`
statements in this project since the code is not public. Making the code public,
however, would require that the invariants be replaced with constraints.
