'''
Let's define a *smooth* number as a natural number with prime factors that are single-digit (less than 10).
An example of such a number is 1560674304, which is related (how?) to the 108th birthday of IBM.

This month's challenge is to find two sets of smooth numbers whose square root sums are close to each other.
For example, the sets {2,6} and {15} yield a distance between their square root sums of less than 0.01 since sqrt{2}+sqrt{6} = 3.86 ... ~  3.87 ... = sqrt{15} .

Two sets that meet our criterion even better are {2,10,15} and {6,36} , which yield an even smaller distance between their square root sums: sqrt{2}+sqrt{10}+sqrt{15} = 8.44947 ... ~ 8.44948 ... = sqrt{6}+sqrt{36} .

Find two sets of smooth numbers that produce a distance d where 0 < d < 10^{-15} .
'''

from decimal import *
getcontext().prec = 100;
sq2 = Decimal(2).sqrt()
epsilon = 1e-16

numer = 1
denom = 1

#Newtons Method xn~sqrt2, xn= n/d, n~d*sqrt(2)
while abs(numer - denom*sq2) > epsilon:
    numer, denom = numer**2 + 2*denom**2, 2*numer*denom

delta = abs(numer - denom*sq2)
print('Difference')
print(delta)
print

bin_numer = bin(numer)[::-1]
bin_denom = bin(denom)[::-1]


# sqrt(2^2k) == 2^k
even_set = [2**(2*k) for k, b in enumerate(bin_numer) if b == '1']
# sqrt(2^(2k+1)) == 2^k*sqrt(2)
odd_set = [2**(2*k+1) for k, b in enumerate(bin_denom) if b == '1']

print('Set 1')
print(even_set)
print
print('Set 2')
print(odd_set)
print

#Validate

even_sum = sum([Decimal(x).sqrt() for x in even_set])
odd_sum = sum([Decimal(x).sqrt() for x in odd_set])

delta2 = abs(even_sum - odd_sum)
assert(abs(delta - delta2) < epsilon/1e5)
