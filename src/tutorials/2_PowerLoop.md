# [Tutorial] PowerLoop: Inheriting algorithms

Hey! This tutorial is built upon the [ForLoop tutorial](1_ForLoop.md), if you haven't followed
it yet, be sure to check it out first! Otherwise, let's dive in!

## Introduction

In this tutorial, we will be learning how algorithms can be inherited so as to modify their
behavior. The goal here is to use the ForLoop algorithm introduced in the previous tutorial
but to modify the action which is executed at each loop iteration. Indeed, we want, at each
iteration, to print out powers of the current iteration. For instance, if the power is set
to 2 and the max_iteration is set to 3, we should obtain the following output:
```cpp
0 // 0^2
1 // 1^2
4 // 2^2
```

Let's first create an empty algorithm in the next section!

## New algorithm = new builder

Just like we did in the previous tutorial, in order to create a new algorithm, even though
built upon other algorithms, we need to create a new Algorithm::Builder. This is done as
follows:
```cpp
class PowerLoop final : public Algorithm::Builder {
public:
    void build(States& states, Transitions& transitions, Layers& layers) {
        // Define our new algorithm here
    }
};
```

Up to this point, nothing new! 

Note that calling `Algorithm::sanity_check` at this point will print the following
warning message:
```shell
WARNING(EMPTY_ALGORITHM), the algorithm instance is empty
```
Indeed, our algorithm, at this statge, is empty. No states have been added and no transitions
have been defined. 

In the next section, we will be "importing" or "inheriting" all the states from the ForLoop
algorithm builder to our new builder. Let's see how it's done!

## Inheriting states and transitions

Importing the states and transitions from another algorithm is done with the template
method Algorithm::Builder::inherit<T>. See how it is easily used:
```cpp
void build(States& states, Transitions& transitions, Layers& layers) {
    inherit<ForLoop>(states, transitions, layers);
}
```

At this stage, the sanity check should not complain anymore. Why? Simply because we have
imported the ForLoop algorithm and because the ForLoop algorithm itself is well-defined. 
Thus, the obtained algorithm is well-defined. Note that you can also visualize it by using
the Algorithm::plot function like we did in the previous tutorial. Doing so trivially yields
the following image.

![my_algorithm.png](https://raw.githubusercontent.com/hlefebvr/state_machine_cpp/main/src/images/my_algorithm_tx.png)

> IMPORTANT: note that to inherit from an algorithm, we did not use C++ inheritance. The
> use of C++ inheritance is heavily discourage regarding algorithm builders.

Now let's apply our modifications!

## Applying modifications

At this stage, we are totally free to write in our build function and are free to use
the same functions as we did in the previous tutorial. For instance, we can use `states.create`
to add new states or `transitions.create_if` to create a new conditional transition! Actually, 
we can totally re-route the whole algorithm and modify its flow!

For our purpose though, we only need to change the action associated to the transition
LOOP_ITERATION -> AFTER_LOOP_ITERATION since this is where the message is being printed.
Note that we cannot use `transitions.create(LOOP_ITERATION, AFTER_LOOP_ITERATION, ...`
anymore since a transition of this kind already exists. Though it is possible to remove a
state or a transition and to re-create it in another form, it is more convenient to simply
override it. To do so, simply use the function `transitions.override`. This is done as follows:
```c++
struct PowerLoopAttributes {
    unsigned int power;
    explicit PowerLoopAttributes(unsigned int t_power) : power(t_power) {}
};

void handle_LOOP_ITERATION_with_power(Context& context) {
    auto& power_loop_attribtues = context.get<PowerLoopAttributes>();
    auto& for_loop_attributes = context.get<ForLoopAttributes>();
    std::cout << for_loop_attributes.iteration << " = " << std::pow(for_loop_attributes.iteration, power_loop_attributes.power) << std::endl;
}

class PowerLoop final : public Algorithm::Builder {
public:
    void build(States& states, Transitions& transitions, Layers& layers) {
        
        inherit<ForLoop>(states, transitions, layers);
        
        transitions.override(SHOW_COUNTER, INCREMENT_COUNTER, handle_LOOP_ITERATION_with_power);
        
    }
};
```

This code should be easy to understand. Briefly though, we create a struct containing the new attributes 
which were needed by our new algorithm. Note that we did not define "iteration" and "max_iteration" as those
are part of the "ForLoop" algorithm from which we inherit. Then, we defined the new handler for the transition
which comes from LOOP_ITERATION and goes to AFTER_LOOP_ITERATION. Finally, we used `transitions.override` to
re-write the transition behaviour.

And that's it! You have successfully modified an algorithm and created a new one!

> Note that it is possible to override a conditional transition with `transitions.override_if` as well.
> You may also change the transition type.

Now let's run our new algorithm! Once again, we have to create an algorithm instance, and to build the appropriate
context. This is done as follows (in you `main` function):
```cpp
// Building the algorithm
Algorithm::Instance algorithm;
Algorithm::build<PowerLoop>(algorithm);

// Sanity check
Algorithm::sanity_check(algorithm);

// Creating the context
ForLoopAttributes for_loop_attributes(3);
PowerLoopAttributes power_loop_attributes(2);
SimpleContext<ForLoopAttributes, PowerLoopAttributes> context(for_loop_attributes, power_loop_attributes);

// Running algorithm
Algorithm::run(algorithm, context, INITIAL_STATE, FINAL_STATE);
```

Executing the code will now print out the following:
```
0^2 = 0
1^2 = 1
2^2 = 4
```

## Advanced notions regarding inheritance

In the next tutorial, we'll be diving into the concept of layers which solves the issue of inheriting multiple
times from the same algorithm or simply inheriting from algorithms which use the same attribute class.
For now, let us simply mention two advanced notions which are virtual transitions and final transitions.

Just like in C++, within state_machine_cpp, it is possible to leave transitions intentionally empty. The goal
of such transitions are clearly to be defined later when the algorithm is being inherited to form another algorithm.
Such transitions are created with the functions `transitions.create_virtual` and `transitions.create_if_virtual`.
Visualizing an algorithm with `Algorithm::plot` will print out such transitions in blue and with the keyword
"virtual". Moreover, calling `Algorithm::sanity_check` will report the presence of virtual transitions. Finally, 
running an algorithm in which some transitions are intentionally left empty will throw an exception to report
what happened.

We've just seen how one can create a special transition which has to be defined later. Note that it is also
possible, to the contrary, to declare some transitions as "final". Final transitions are transitions which
cannot be overridden. Declaring a transition as final is done with the `transitions.declare_as_final` and 
by giving the state which starts the transition as argument.

That's it for now! In the next tutorial, we'll dive into the concept of layers!