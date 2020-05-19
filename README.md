# az-vcv
vcv rack plugins by az


# modulo
## usage
- patch a clock or trigger to clock input
- pick some notes by clicking the keys
- pick your favorite prime (or non-prime) numbers for length and step
- patch out to the v/oct input of a sound source

## notes
- the sequence of notes played will be more "interesting" (fewer repeats) if length, step and the number of selected notes are different primes
- length and step have CV inputs with attenuverters next to them
- shift shifts the starting note of the sequence
- reset resets the sequence back the the starting note


## idea
the modulo module is based on the idea of [cyclic group](https://en.wikipedia.org/wiki/Cyclic_group) generators.

pick two numbers (say 2 and 5) and call them step and length respectively. 

add step to itself repeatedly and then divide by length and find the remainder, i.e. the modulo operation.

```
(step + step + step + ...) % length


step = 2 and length = 5:

2                   =  2 % 5 = 2
2+2                 =  4 % 5 = 4
2+2+2               =  6 % 5 = 1
2+2+2+2             =  8 % 5 = 3
2+2+2+2+2           = 10 % 5 = 0

2+2+2+2+2+2         = 12 % 5 = 2 
2+2+2+2+2+2+2       = 14 % 5 = 4
2+2+2+2+2+2+2+2     = 16 % 5 = 1
2+2+2+2+2+2+2+2+2   = 18 % 5 = 3
2+2+2+2+2+2+2+2+2+2 = 20 % 5 = 0

...
```
notice that the result repeats every 5 additions and contains all the numbers 0 to 4 exactly once.

i.e. 2 generates {2, 4, 1, 3, 0}.  if step and length are coprime, all numbers {0, 1, 2, ... length} are generated. 

the order (2, 4, 1, 3, 0) is used to step through the selected notes.
