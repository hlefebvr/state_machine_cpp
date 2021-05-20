# Layers: handling complex import schemes  {#t3_DoubleLoop}

Hey there! This tutorial introduces somehow advanced features of the state_machine_cpp library.
Be sure to have checked out previous tutorials before reading this one. Otherwise, let's dive in!

## Introduction

In this tutorial we will be creating a double for loop based on our ForLoop algorithm. Thus,
our algorithm will use twice the same algorithm and use two different ForLoopAttributes to
manage its internal state. The objective of this tutorial is therefore to use the ForLoop
algorithm so as to get the following input:
```
0, 0
0, 1
0, 2
0, 3
0, 4
1, 0
1, 1
1, 2
1, 3
1, 4
2, 0
2, 1
2, 2
2, 3
2, 4
```

The resulting algorithm will therefore be equivalent to the following C++ code.
```cpp
for (unsigned int i = 0 ; i < 3 ; ++i) {
    for (unsigned int j = 0 ; j < 5 ; ++j) {
        std::cout << i << ", " << j << std::endl;
    }
}
```

Let's see how it's done!

## Importing twice

We have seen, in the previous tutorial, how one algorithm could import all the states and 
transitions from another. Let's start by doing this once!
```cpp
class DoubleLoop final : public Algorithm::Builder {
    void build(States& states, Transitions& transitions, Layers& layers) {
        import<ForLoop>(states, transitions, layers);
    }
};
```
Up to there, nothing new. Visualizing our algorithm yields the expected following result:

![my_algorithm.png](src/images/my_algorithm_tx.png)

Now let's try to import twice algorithm ForLoop, as follows:
```cpp
void build(States& states, Transitions& transitions, Layers& layers) {
    import<ForLoop>(states, transitions, layers);
    import<ForLoop>(states, transitions, layers);
}
```
And let's build our algorithm! 

Unfortunately, we were thrown with an exception saying "Cannot create twice the same state instance.".
Indeed, Algorithm::Builder::import<> does nothing but to import all the states from an algorithm to the current one.
The same is done for each transition. We therefore cannot import twice from the same
algorithm as this would create, indeed, twice the same states. Moreover, both ForLoop (the first)
and ForLoop (the secondly imported) use the same kind of attributes. How would one know
which attribute to consider when running the algorithm ? This situation is solved by the
concept of layers. 

So far, our algorithms were made out of only one layer since they were rather simple and
always used different attribute classes. However, it is possible to create a new layer
inside the algorithm so that two state of the same kind coexist within the same algorithm
 (but on different "levels", i.e., on different layers).

See rather the following code.
```cpp
void build(States& states, Transitions& transitions, Layers& layers) {
    
    import<ForLoop>(states, transitions, layers);
    
    layers.create();
        import<ForLoop>(states, transitions, layers);
    layers.close();
    
}
```

Now, building this algorithm works! Let's visualize it so that it becomes clear what happened.

![my_algorithm.png](src/images/my_algorithm_copied.png)

You can see that our ForLoop algorithm has been imported twice! Yet, it has been "instantiated"
on two different layers: 0 and 1. Note that, at any time, it is possible to know the current
layer by calling the `layers.current` method. 

Now that we have copied our algorithm twice, let's insert it to obtain one single algorithmic flow!

## Playing with layers

Inside the build function, every use of a State::Id, in fact, refers to the state with
the corresponding State::Id associated to the current layer id. Thus, when calling, for instance,
`states.create(INITIAL_STATE);`, we in fact created the state `INITIAL_STATE[0]`, i.e.,
`INITIAL_STATE` on layer 0. So far, we did not even mention it since it was not relevant
to our case, here, it becomes crucial to understand it.

To be even more specific, observe the following piece of code (which is independent of the
double-loop project).
```cpp
static const State::Id MY_STATE("MY_STATE");

class LayerExample final : public Algorithm::Builder {
    void build(States& states, Transitions& transitions, Layers& layers) {
        
        states.create(MY_STATE); // creates MY_STATE[0]
        
        layers.create(); // creates layer 1
            states.create(MY_STATE); // creates MY_STATE[1]
        layers.close(); // returns to layer 0
        
        states.remove(MY_STATE); // removes MY_STATE[0]
        
        layers.use(1);
            states.removes(MY_STATE); // removes MY_STATE[1]
        layers.close();
        
    }
};
```

Things should be more clear now. However, two important remarks should be made at this point.
- First, note that every time `layers.create` or `layers.use` is being called, a corresponding
`layers.close` should be called. If this fails to be done then an exception will be thrown.
- Then, `layers.create` in fact returns the id of the layer and it is better - in the sense
of "more modular" to act upon layers using variables rather than explicit values. Why? 
  Simply because your algorithm may further be imported by another algorithm and that layer 1
  may well be something else. Using a variable allows your code to be more general and context
  independent.
  
## Routing between layers

Back to our double for loop example! We now want to insert one algorithm inside the other.
In other words, we want to override the transition from `BEGIN_OF_ITERATION[0]` to `INITIAL_STATE[1]`
and to override the transition from `FINAL_STATE[1]` to `END_OF_ITERATION[1]`.

This can be done as follows.
```cpp
void build(States& states, Transitions& transitions, Layers& layers) {
    
    import<ForLoop>(states, transitions, layers);
    
    auto A = layers.create();
        import<ForLoop>(states, transitions, layers);
    layers.close();

    transitions.override(BEGIN_OF_ITERATION, INITIAL_STATE[A]);
    transitions.override(FINAL_STATE[A], END_OF_ITERATION);
    
}
```

Visualizing the resulting algorithm, one obtains the following.

![my_algorithm.png](src/images/my_algorithm_merged.png)

We therefore have successfully inserted our copied version of ForLoop inside another copied version of ForLoop.

To run our algorithm though, we need to define a new context called `LayeredContext`. The following piece of
code speaks for iteself.
```cpp
ForLoopAttributes for_loop_attributes_1(3);
ForLoopAttributes for_loop_attributes_2(5);
SimpleContext<ForLoopAttributes> context(for_loop_attributes_1);
SimpleContext<ForLoopAttributes> context_2(for_loop_attributes_2);
LayeredContext<2> layered_context(context, context_2);

Algorithm::run(algorithm, layered_context);
```

Running our resulting algorithm outputs the following.
```
0
1
2
3
4
0
1
2
3
4
0
1
2
3
4
```
We can see here that the algorithm does, indeed, perform a double for loop! However, the goal of this tutorial
was to print `i, j` at each iteration, and not only `i` or `j`. In the following section, we will see how
it is possible to access the attributes of another layer throughout the context object.

## Accessing layered context

In this last section, we will override the transition between `BEGIN_OF_ITERATION[A]` and `END_OF_ITERATION[A]`
in order to print `i, j`. To do this, we need to access the context's attribute of a different layer than
the one which triggered the transition. This can be done by using the `context.get_relative<T>` template function.
This function takes an argument which is the offset from which to access the attributes. Thus, we have
`context.get<T>()` which is equivalent to `context.get_relative<T>(0)`. And `context.get_relative<T>(-1)` which
accesses the attribute of type `T` as used by the previous layer. See rather how we
can write our new handler.
```cpp
void show_double_counter(Context& context) {
    std::cout << context.get_relative<ForLoopAttributes>(-1).iteration
              << ", "
              << context.get<ForLoopAttributes>().iteration
              << std::endl;
}
```
Here, we are printing the iteration counter of the previous layer, then, print out the iteration counter of
the current layer. 

We can then override our transition as follows.
```cpp
void build(States &states, Transitions &transitions, Layers &layers) override {
    import<Counter>(states, transitions, layers);

    unsigned int A = layers.create();
        import<Counter>(states, transitions, layers);
        
        transitions.override(BEGIN_OF_ITERATION, END_OF_ITERATION, show_double_counter);
        
    layers.close();

    transitions.override(BEGIN_OF_ITERATION, INITIAL_STATE[A]);
    transitions.override(FINAL_STATE[A], END_OF_ITERATION);

}
```

Running our algorithm now prints out the following result.
```
0, 0
0, 1
0, 2
0, 3
0, 4
1, 0
1, 1
1, 2
1, 3
1, 4
2, 0
2, 1
2, 2
2, 3
2, 4
```

And voilà! We have successfully built an algorithm as the combination of the same algorithm with itself!
As an exercise, try to implement a template algorithm `MultipleLoop<unsigne int N>` which creates an `N`-loop.
Enjoy!