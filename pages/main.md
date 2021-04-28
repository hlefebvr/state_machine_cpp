The state_machine_cpp library is a library written in C++17 which permits the development
of algorithms by means of state-machines-like behaviors.
It aims to be used when, among others, one wants to achieve the following goals:
- have excessive control over the execution of an algorithm (i.e., step-by-step implementation)
- make available and highly customizable an algorithmic work to a larger community

To achieve these goals, algorithms are decomposed in a succession of states while the algorithmic flow
is enforced by so-called transitions from one state to another. This decomposition of algorithms makes it 
possible to insert new states and new transitions to an existing algorithm without breaking the original
algorithm and to be able to rewrite any part of the algorithm which comprises: state or transition removal, 
transition action overriding, transition flow overriding, algorithmic combination (i.e., sub-routines), etc.

![for_loop](ForLoop.png)