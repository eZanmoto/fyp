Plot Format
===========

Sean Kelleher
-------------

### About

This document defines a format for representing plot data.

### Format

The data for a plot is stored in a JSON file. While XML is a (objectively)
stronger format for data interchange, JSON was chosen because it has everything
that is (currently) needed for representing the data for plots. Another benefit
to using JSON to represent this data is that the data model matches the data (as
noted in [http://stackoverflow.com/a/3537499/497142]). Also, using a data
interchange format as distinct from a simple record or binary format means that
the layout of the file is extensible.

The actual format of a plot file is as follows:

    {
        "title": string,
        "x-title": string,
        "y-title": string,
        "share-x": bool,
        "share-y": bool,
        "share-lines": bool,
        "subplots": [ {
            "title": string,
            "lines": { /* label */ string: {
                "colour": string,
                "points": [ {
                    "x": int,
                    "y": int
                } ]
            } }
        } ]
    }

This structure uses the notation presented at [json.org] with an additional
"type specifier" for the expected content of arrays, using a Haskell-style
notation. All other fields are free-form according to their type, except for
`colour`, which must be either `null` (a distinct colour will be chosen at
random) or a string with the HTML colour code for that colour, such as
`"#BEEF42"`.
