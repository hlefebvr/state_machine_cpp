# Organize your code! {#t4_Organize}

Hi there! I hope you enjoyed the first three tutorials! Now is time to give you some guidelines on how to structure
your code when using state_machine_cpp. Let's dive in with our list of guidelines and good practise!

## #1 Define your states as static attributes of your builder

As a first guideline, it is highly suggested defining everything which is related to your algorithm inside
your algorithm builder. This applies for states, in particular. Thus, rather than having the following code:
```cpp
static const State::Id INITIAL_STATE("ExampleAlgorithm::INITIAL_STATE");

class ExampleAlgorithm final : public Algorithm::Builder {
public:
    void build(States& states, Transitions& transitions, Layers& layers) {
        states.create(INITIAL_STATE);
    }
};
```
You should prefer having the following:
```cpp
class ExampleAlgorithm final : public Algorithm::Builder {
public:
    static const State::Id INITIAL_STATE;
    
    void build(States& states, Transitions& transitions, Layers& layers) {
        states.create(INITIAL_STATE);
    }
};

const State::Id ExampleAlgorithm::INITIAL_STATE = State::Id("ExampleAlgorithm::INITIAL_STATE");
```
Why ? Simply because it is more natural to relate to the INITIAL_STATE of the ExampleAlgorithm algorithm by
calling `ExampleAlgorithm::INITIAL_STATE` rather than `INITIAL_STATE`. Moreover, you therefore prevent other
developers to name their state C++ variable `INITIAL_STATE`. Finally, this also allows for auto-detection of
states as described in point #7 of this page.

## #2 Use namespaces for your State::Id

Using namespaces for State::Id names is also a good idea. Why? Imagine having two algorithms having an `INITIAL_STATE`
whose name are defined as `INITIAL_STATE` and ``INITIAL_STATE` as shown in the following code:
```cpp
class A final : public Algorithm::Builder {
public:
    
    static const State::Id INITIAL_STATE; 
    
    void build(States& states, Transitions& transitions, Layers& layers) {
        // ...
    }
};

class B final : public Algorithm::Builder {
public:
    
    static const State::Id INITIAL_STATE;
    
    void build(States& states, Transitions& transitions, Layers& layers) {
        // ...
    }
};

const State::Id A::INITIAL_STATE = State::Id("INITIAL_STATE");
const State::Id B::INITIAL_STATE = State::Id("INITIAL_STATE");
```
If this situation happens, then other developers cannot directly import their algorithm from both `A` and `B`.
Rather, they need to use two different layers. Why? Because when adding `A::INITIAL_STATE` and `B::INITIAL_STATE`
ont the same layer, an exception will be throw saying that a state is being added twice. Indeed, they both
have the same name! It would be possible to import from both algorithms by doing the following:
```cpp
class C final : public Algorithm::Builder {
public:
    void build(States& states, Transitions& transitions, Layers& layers) {
        import<A>(states, transitions, layers);
        
        auto layer_id = layers.create();
            import<B>(states, transitions, layers);        
        layers.close();
    }
};
```
However, this code has a sort of useless complexity. Consider using namespaces for state names, i.e., having,
```cpp
const State::Id A::INITIAL_STATE = State::Id("A::INITIAL_STATE");
const State::Id B::INITIAL_STATE = State::Id("B::INITIAL_STATE");
```
And the previous code can be conceptually simplified as follows:
```cpp
class C final : public Algorithm::Builder {
public:
    void build(States& states, Transitions& transitions, Layers& layers) {
        import<A>(states, transitions, layers);
        import<B>(states, transitions, layers);
    }
};
```

## #3 Define your transitions handlers as static methods

In the same spirit as #1, you should also define your transitions handlers as static methods of your
algorithm builder. Again, this is done for clarity and maintainability reasons. This also provides symbols
to being overridden. 

## #4 Define your attributes as nested class

Defining your attributes as nested class, again, improves readability. For instance, think back again about*
our ForLoop algorithm. To make this algorithm work, we created a `ForLoopAttributes` class. Defining it
inside the ForLoop class allows us to use the more readable `ForLoop::Attributes` expression! Moreover,
our handlers can now embed the following code:
```cpp
void some_example_handler(Context& context) {
    auto& attributes = context.get<Attributes>();
    // ...
}
```
which is much more clear! Moreover, you end up with multiple imports which would result in codes like
the following one:
```cpp
void some_other_example_handler(Context& context) {
    auto& a_attributes = context.get<A::Attributes>();
    auto& b_attributes = context.get<B::Attributes>();
    auto& c_attributes = context.get<C::Attributes>();
    // ...
}
```
This way of managing attributes is therefore generic!

Moreover, we encourage you to always define an `Attribute` nested class, even in cases where you are reusing
an existing class! See the following:
```cpp
class B final : public Algorithm::Builder {
public:
    using Attributes = A::Attributes;
    
    void build(// ...
};
```
This simplifies and generalizes the approach to every algorithm.

## #5 Create final builders

As a general guideline, importing algorithms should be done through the `Algorithm::Builder::import`
template method. To ensure that, we recommend that every algorithm builder be declared as a `final` class.

## #6 Define a handle_standard_argument static method

Creating algorithm's context may become complex. See, for instance, the following code used to create our
DoubleLoop's context:
```cpp
ForLoopAttributes for_loop_attributes_1(3);
ForLoopAttributes for_loop_attributes_2(5);
SimpleContext<ForLoopAttributes> context(for_loop_attributes_1);
SimpleContext<ForLoopAttributes> context_2(for_loop_attributes_2);
LayeredContext<2> layered_context(context, context_2);
```
Quite embarrassing right? Also, note that each ForLoopAttributes are given to a `SimpleContext<ForLoopAttributes>`
by non-const reference! Which means that each `ForLoopAttributes` has to be kept alive as long as each corresponding
`SimpleContext<ForLoopAttributes>` is being used. And the same is true for each `SimpleContext<ForLoopAttributes>`
and `LayeredContext<2>`. 

To ease the creation of algorithmic context, we recommend to developers to define a static method called
`handle_standard_arguments` returning an object of the class `AutoContext`. An `AutoContext` object simply
is a type of `Context` which holds its arguments as `std::unique_ptr`. In that sense, the attributes and
other contexts used to create the final context will be kept alive as long as the `AutoContext` lives.
See how it can be create:
```cpp
auto* for_loop_attributes_1 = new ForLoop::Attributes(3);
auto* for_loop_attributes_2 = new ForLoop::Attributes(5);
auto* context = new SimpleContext<ForLoop::Attributes>(*for_loop_attributes_1);
auto* context_2 = new SimpleContext<ForLoop::Attributes>(*for_loop_attributes_2);
auto* layered_context = new LayeredContext<2>(*context, *context_2);

auto context = AutoContext(layered_context, context, context_2, for_loop_attributes_1, for_loop_attributes_2);
```
Note that the first argument IS the real context designed to be used in the algorithm. Here, it is therefore
`layered_context`. 

The recommendation is as follows: declare a static method returning an `AutoContext` inside your algorithm
builder. See, for instance, the following piece of code:
```cpp
class DoubleLoop final : public Algorithm::Builder {
public:
    void build(States &states, Transitions &transitions, Layers &layers) override {
        // ...
    }

    static AutoContext handle_standard_arguments(int n, int m) {
        auto* for_loop_attributes_1 = new ForLoop::Attributes(n);
        auto* for_loop_attributes_2 = new ForLoop::Attributes(m);
        auto* context = new SimpleContext<ForLoop::Attributes>(*for_loop_attributes_1);
        auto* context_2 = new SimpleContext<ForLoop::Attributes>(*for_loop_attributes_2);
        auto* layered_context = new LayeredContext<2>(*context, *context_2);

        return AutoContext(layered_context, context, context_2, for_loop_attributes_1, for_loop_attributes_2);
    }
};
```
This allows us to run our algorithm as follows:
```cpp
Algorithm::Instance algorithm;
Algorithm::build<DoubleLoop>(algorithm);

auto context = DoubleLoop::handle_standard_arguments(3, 5);

Algorithm::run(algorithm, context);
```

## #7 Define an INITIAL_STATE and a FINAL_STATE

You probably noticed from our previous tutorial the necessity of the following lines before running an
algorithm:
```cpp
algorithm.set_initial_state(MY_INITIAL_STATE);
algorithm.set_final_state(MY_FINAL_STATE);
```
Note that these lines can be made optional by defining a static attribute inside your algorithm builder with
the C++ symbol names `INITIAL_STATE` and `FINAL_STATE` as follows:
```cpp
class ExampleAlgorithm final : public Algorithm::Builder {
public:
    static const State::Id INITIAL_STATE;
    static const State::Id FINAL_STATE;
    
    void build(States& states, Transitions& transitions, Layers& layers) {
        states.create(INITIAL_STATE);
    }
};

const State::Id ExampleAlgorithm::INITIAL_STATE = State::Id("ExampleAlgorithm::INITIAL_STATE");
const State::Id ExampleAlgorithm::FINAL_STATE = State::Id("ExampleAlgorithm::FINAL_STATE");
```
By doing so, state_machine_cpp will automatically set the initial state and final state for you! You, therefore,
won't have to define your initial and final state manually each time you want to run your algorithm. For
genericity reasons, we advise doing so for every algorithm you create.

Note that when algorithm do not define their own `INITIAL_STATE` because they use another algorithm's state
as initial state, it is still possible to apply this guideline as follows:
```cpp
class B final : public Algorithm::Builder {
public:
    static const State::Id& INITIAL_STATE;
    static const State::Id& FINAL_STATE;
    // ...
};

const State::Id& B::INITIAL_STATE = A::INITIAL_STATE;
const State::Id& B::FINAL_STATE = A::FINAL_STATE;
```

That's it for our guidelines! You know now how to organize a clean code using state_machine_cpp!