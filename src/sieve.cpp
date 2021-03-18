/*!
  \file sieve.cpp Implementation of a prime factorization class.
  \author Mircea Neacsu
  \copyright MIT License
*/
#include "sieve.h"
#include <assert.h>
#include <stdexcept>
#include <ctgmath>

///  Constructs an array of bits with `n` bits all set to 0.
bitset::bitset (size_t n)
  : sz (n)
{
  size_t nb = (n + 63) / 64 * 8;
  v = (std::uint64_t*)malloc (nb);
  if (!v)
    throw std::runtime_error ("Out of memory");
  memset (v, 0, nb);
}

/// Frees allocated memory
bitset::~bitset ()
{
  free (v);
}

/// Return the state of the `i` bit 
bool bitset::operator[](size_t i) const
{
  assert (i < sz);
  size_t n = i >> 6;
  size_t b = i & 0x3f;
  return (v[n] & (1ull << b));
}

/// Set a bit on or off
void bitset::set (size_t i, bool on)
{
  assert (i < sz);
  size_t n = i >> 6;
  size_t b = i & 0x3f;
  if (on)
    v[n] |= 1ull << b;
  else
    v[n] &= ~(1ull << b);
}

/// Turn off a bit
void bitset::reset (size_t i)
{
  assert (i < sz);
  size_t n = i >> 6;
  size_t b = i & 0x3f;
  v[n] &= ~(1ull << b);
}

//////////////////////////////////////////////////////////////////////////////

sieve::sieve (size_t sz)
  : arr (sz)
{
  int lim = (int)sqrt (sz);
  int i;
  for (i = 2; i <= lim; i++)
  {
    if (!arr[i])
    {
      const_cast<nvec&>(primes).push_back (i);
      for (size_t k = i * i; k < sz; k += i)
        arr.set (k);
    }
  }
  for (; i < sz; i++)
  {
    if (!arr[i])
      const_cast<nvec&>(primes).push_back (i);
  }
}

// Return true if number is prime
bool sieve::prime (unsigned int n)
{
  return (n < arr.size()) && !arr[n];
}

/*!
  Find prime factors of a number

  \param   n        number to factor
  \param   factors  vector of prime factors

  \retval  1  number is prime
  \retval  0  number was decomposed in primes
  \retval -1  number is larger than the size of table of primes and 
              could not find prime factors
*/
int sieve::factor (unsigned int n, nvec& factors)
{
  factors.clear ();
  if (prime (n))
    return 1;
  for (auto i : primes)
  {
    while (n % i == 0)
    {
      factors.push_back (i);
      n /= i;
    }
    if (i >= n)
      break;
  }
  return factors.size()? 0 : -1;
}
