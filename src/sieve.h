/*!
  \file sieve.h Definition of a primes factorization class using
  Eratosthenes sieve.

  \author Mircea Neacsu
  \copyright MIT License
*/

#pragma once
#include <vector>

/// An array of bits packed in 64-bit integers
class bitset
{
public:
  bitset (size_t n);
  ~bitset ();
  bool operator [](size_t i) const;
  void set (size_t i, bool on = true);
  void reset (size_t i);
  size_t size () const;

private:
  std::uint64_t* v;
  size_t sz;
};

/// Simple Eratosthenes sieve for number factoring
class sieve
{
public:
  typedef std::vector<unsigned int> nvec;

  /// Constructor
  sieve (size_t sz);

  /// Return `true` if a number is prime
  bool prime (unsigned int n);

  /// Factorize a number
  int factor (unsigned int n, nvec& factors);

  const nvec primes;    ///< Vector of prime numbers

private:
  bitset arr;
};

/// Return bitset size
inline
size_t bitset::size () const
{
  return sz;
}