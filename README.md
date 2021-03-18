# SternBrocot
Rational approximation using Stern-Brocot tree

Nodes of the [Stern-Brocot tree](https://en.wikipedia.org/wiki/Stern%E2%80%93Brocot_tree)
offer the best possible rational (`p/q`) approximation for any real number in
the sense that any other rational approximation `p'/q'` of the same precision has `p' >= p` and `q' >= q`.

Finding small rational approximations can be important for programs designed
to run on small microprocessors where floating point support may be missing
or too expensive. For instance, floating point value of &#x03C0; can be replaced
by the fraction 355/113 that is accurate to 6 decimal places (see
https://en.wikipedia.org/wiki/Approximations_of_%CF%80)

Also Stern-Brocot trees are important when trying to find solutions to gear train problems.
A recent example is [the work](https://www.nature.com/articles/s41598-021-84310-w) of a team
at the University College of London on the Antikythera mechanism. The authors describe a process
they call *Parmenides Proposition* which in fact represents a search in the Stern-Brocot tree.
Using it, they generate the spectacular set of gears shown below:
![Exploded model of Cosmos gearing. From right to left: b1, mean Sun, Nodes, Mercury, Venus;
true Sun and superior planets gearing; CP and shared gears; Ring Display; Dragon Hand; Moon position and phase
mechanism.](img/Antikythera-fig6.png)

The `sba` utility finds the Stern-Brocot approximation of a number with
any number of decimal places. It also tries to generate factorizations for each number in the search path. 

Usage:
````
  sba <number> <decimals>
````