# az-vcv
vcv rack plugins by az


# modulo
## usage
- Patch a clock or trigger to clock input.
- Pick some notes by clicking the keys.
- Pick your favorite prime (or non-prime) numbers for length and step.
- Patch out to the v/oct input of a sound source.

## notes
- The sequence of notes played will be more "interesting" (fewer repeats) if length, step and the number of selected notes are different primes.
- Length and step have CV inputs with attenuverters next to them.
- shift shifts the starting note of the sequence.
- Reset resets the sequence back the the starting note.


## idea
The modulo module is based on the idea of [cyclic group](https://en.wikipedia.org/wiki/Cyclic_group) generators.

Pick two numbers (say 2 and 5) and call them step and length respectively. 

Add step to itself repeatedly and then divide by length and find the remainder, i.e. the modulo operation.

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
Notice that the result repeats every 5 additions and contains all the numbers 0 to 4 exactly once.

i.e. 2 generates {2, 4, 1, 3, 0}.  if step and length are coprime, all numbers {0, 1, 2, ... length} are generated. 

The order (2, 4, 1, 3, 0) is used to step through the selected notes.


# LoFiTV

## usage
- Patch a clock or trigger to clock input:  ⧗.
- Wiggle the knobs on the bottom:  ✢ ▒ ∠ ↥.
- Patch a divided clock to jitter:  ↯.
- Adjust the amount of jitter:  !.
- Patch a divided clock to the reset input:  ↻.
- Any changes to the number knob:  #, or the color knobs:  red, blue or green will only take effect after a reset is triggered.
- Use the modulation output from the three unlabeled outputs at the bottom.

## idea
The LoFiTV module is a slime mold simulation.  It was inspired by the work of [Sage Jenson](https://sagejenson.com/physarum) and [Jeff Jones](https://uwe-repository.worktribe.com/output/980579).  The basic idea is that there are a number of agents that move forward each step (each tick of the clock ⧗ results in a single step) and after moving, they leave behind a slime trail.  Then, each agent senses in front, to left and to the right and turns towards the direction with the highest concentration of the slime trail.  The sensor distance and angle are controlled via ∠ and ↥.  Finally, the slime trail diffuses into the 8 adjacent pixels based on the diffusion factor ✢ and each pixel fades based on the retainment factor ▒.

Note that if any of the CV inputs are patched, the corresponding knobs are simply ignored.  Thus, the signals used for modulation may need to be scaled, inverted, offset, etc.

## parameters
- ⧗ clock : advances the simulation one tick per clock pulse.
- ↯ jitter : moves each agent a random amount determined by:
- ! force : maximum distance that an agent moves when jitter receives a pulse.  
  
- ↻ reset : resets the simulation.  Randomly generates agents, their position and color.  
  
  The following parameters only affect the simulation when it is reset:  
- \# number of agents : How many agents spawn when the simulation is reset.
- red knob : maximum amount of red in each agent.
- blue knob : maximum amount of blue in each agent.
- green knob : maximum amount of green in each agent.  
  
- ✢ diffusion factor : amount of slime in the current pixel that spreads to the adjacent 8 pixels.
- ▒ retainment factor : how fast the slime in the current pixel fades.
- ∠ sensor angle : angle (left / right) that the agent senses.
- ↥ sensor distance : distance that the agent senses.  
  
- 3 unlabeled outputs : modulation output (-10v to +10v) based on the averages of select pixels.  This is "random" stepped voltage as it is only updated once per step (once per clock pulse).
