# SternBrocot
Rational approximation using Stern-Brocot tree

Nodes of the [Stern-Brocot tree](https://en.wikipedia.org/wiki/Stern%E2%80%93Brocot_tree)
offer the best possible rational (`p/q`) approximation for any real number in
the sense that any other rational approximation `p'/q'` of the same precision has `p' >= p` and `q' >= q`.

Finding small rational approximations can be important for programs designed
to run on small microprocessors where floating point support may be missing
or too expensive. For instance floating point value of &#x03C0; can be replaced
by the fraction 355/113 that is accurate to 6 decimal places (see
https://en.wikipedia.org/wiki/Approximations_of_%CF%80)

The `sba` utility finds the Stern-Brocot approximation of a number with
any number of decimal places. 

Usage:
````
  sba <number> <decimals>
````