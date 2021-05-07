//
// Created by henri on 07/05/21.
//

#ifndef STATE_MACHINE_CPP_TEST_TRANSITION_CREATE_H
#define STATE_MACHINE_CPP_TEST_TRANSITION_CREATE_H

TEST(transition_create, should_create_direct_transition) {

    TEST_UTIL_CREATE_ALGORITHM_BUILDER(TestAlgorithm, {
        states.create(A);
        states.create(B);

        transitions.create(A, B);
    });

    Algorithm::Instance algorithm;
    Algorithm::build<TestAlgorithm>(algorithm);

    ASSERT_TRUE(algorithm.transitions().has(A));
    const Transition::Any& transition = *algorithm.transitions().find(A);
    TEST_UTIL_ASSERT_DIRECT_TRANSITION(transition, A, B);

}

TEST(transition_create, should_create_conditional_transition) {

    TEST_UTIL_CREATE_HANDLER_IF(test, f, { return true; })

    TEST_UTIL_CREATE_ALGORITHM_BUILDER(TestAlgorithm, {
        states.create(A);
        states.create(B);
        states.create(C);

        transitions.create_if(A, B, C, test::f);
    });

    Algorithm::Instance algorithm;
    Algorithm::build<TestAlgorithm>(algorithm);

    ASSERT_TRUE(algorithm.transitions().has(A));
    const Transition::Any& transition = *algorithm.transitions().find(A);
    TEST_UTIL_ASSERT_CONDITIONAL_TRANSITION(transition, A, B, C);

}

TEST(transition_create, should_create_parallelized_transition) {

    TEST_UTIL_CREATE_ALGORITHM_BUILDER(TestAlgorithm, {
        states.create(A);
        states.create(B);
        states.create(C);
        states.create(D);

        transitions.create_parallelized(A, { B, C }, D);
        transitions.create(B, D);
        transitions.create(C, D);
    });

    Algorithm::Instance algorithm;
    Algorithm::build<TestAlgorithm>(algorithm);

    ASSERT_TRUE(algorithm.transitions().has(A));

    const Transition::Any& transition = *algorithm.transitions().find(A);
    TEST_UTIL_ASSERT_PARALLELIZED_TRANSITION_2(transition, A, B, C, D);

}

TEST(transition_create, should_throw_if_initial_state_is_non_existing) {
    TEST_UTIL_CREATE_ALGORITHM_BUILDER(TestAlgorithm, {
        states.create(B);
        transitions.create(A, B);
    });

    Algorithm::Instance algorithm;
    ASSERT_ANY_THROW(Algorithm::build<TestAlgorithm>(algorithm));
}

TEST(transition_create, should_throw_if_next_state_is_non_existing) {
    TEST_UTIL_CREATE_ALGORITHM_BUILDER(TestAlgorithm, {
        states.create(A);
        transitions.create(A, B);
    });

    Algorithm::Instance algorithm;
    ASSERT_ANY_THROW(Algorithm::build<TestAlgorithm>(algorithm));
}

#endif //STATE_MACHINE_CPP_TEST_TRANSITION_CREATE_H
