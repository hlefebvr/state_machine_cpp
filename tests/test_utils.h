//
// Created by henri on 07/05/21.
//

#ifndef STATE_MACHINE_CPP_TEST_UTILS_H
#define STATE_MACHINE_CPP_TEST_UTILS_H


#define TEST_UTIL_CREATE_ALGORITHM_BUILDER(name, build_function) \
class name final : public Algorithm::Builder { \
public: \
void build(Algorithm::Builder::States &states, \
           Algorithm::Builder::Transitions &transitions, \
           Algorithm::Builder::Layers &layers) override \
build_function \
};

# define TEST_UTIL_CREATE_HANDLER(scope, name, impl) \
struct scope { \
static bool name(Context2& context) impl \
};

# define TEST_UTIL_CREATE_HANDLER_IF(scope, name, impl) \
struct scope { \
static bool name(const Context2& context) impl \
};

#define TEST_UTIL_ASSERT_DIRECT_TRANSITION(transition, from, to) \
ASSERT_TRUE(transition.has_handler()); \
ASSERT_EQ(transition.type(), Transition::Type::Direct); \
ASSERT_EQ(transition.initial_state(), from); \
ASSERT_EQ(transition.next_states().size(), 1); \
ASSERT_EQ(transition.next_states().front(), to); \
ASSERT_FALSE(transition.is_final()); \
ASSERT_FALSE(transition.is_virtual()); \

#define TEST_UTIL_ASSERT_CONDITIONAL_TRANSITION(transition, from, if_true, if_false) \
ASSERT_TRUE(transition.has_handler()); \
ASSERT_EQ(transition.type(), Transition::Type::Conditional); \
ASSERT_EQ(transition.initial_state(), from); \
ASSERT_EQ(transition.next_states().size(), 2); \
ASSERT_EQ(transition.next_states()[true], if_true); \
ASSERT_EQ(transition.next_states()[false], if_false); \
ASSERT_FALSE(transition.is_final()); \
ASSERT_FALSE(transition.is_virtual());

#define TEST_UTIL_ASSERT_PARALLELIZED_TRANSITION_2(transition, from, then_1, then_2, to) \
ASSERT_TRUE(transition.has_handler()); \
ASSERT_EQ(transition.type(), Transition::Type::Parallelized); \
ASSERT_EQ(transition.initial_state(), from);    \
ASSERT_EQ(transition.next_states().size(), 3); \
ASSERT_EQ(transition.next_states()[0], then_1); \
ASSERT_EQ(transition.next_states()[1], then_2); \
ASSERT_EQ(transition.next_states()[2], to); \
ASSERT_FALSE(transition.is_final()); \
ASSERT_FALSE(transition.is_virtual()); \

#endif //STATE_MACHINE_CPP_TEST_UTILS_H
