//
// Created by henri on 07/05/21.
//

#ifndef STATE_MACHINE_CPP_TEST_STATE_REMOVE_H
#define STATE_MACHINE_CPP_TEST_STATE_REMOVE_H

TEST(state_create, should_remove_state) {
    TEST_UTIL_CREATE_ALGORITHM_BUILDER(TestAlgorithm, {
        states.create(B);
        states.create(C);

        states.create(A);
        states.remove(A);

        transitions.create(B, C);
    });

    Algorithm::Instance algorithm;
    Algorithm::build<TestAlgorithm>(algorithm);

    ASSERT_FALSE(algorithm.transitions().has(A));
}

TEST(state_create, should_throw_if_remove_non_existing_state) {
    TEST_UTIL_CREATE_ALGORITHM_BUILDER(TestAlgorithm, {
        states.remove(A);
    });

    Algorithm::Instance algorithm;
    ASSERT_ANY_THROW(Algorithm::build<TestAlgorithm>(algorithm));
}

TEST(state_create, should_throw_if_remove_state_used_in_transition_as_initial_state) {
    TEST_UTIL_CREATE_ALGORITHM_BUILDER(TestAlgorithm, {
        states.create(A);
        states.create(B);

        transitions.create(A, B);

        states.remove(A);
    });

    Algorithm::Instance algorithm;
    ASSERT_ANY_THROW(Algorithm::build<TestAlgorithm>(algorithm));
}

TEST(state_create, should_throw_if_remove_state_used_in_transition_as_next_state) {
    TEST_UTIL_CREATE_ALGORITHM_BUILDER(TestAlgorithm, {
        states.create(A);
        states.create(B);

        transitions.create(B, A);

        states.remove(A);
    });

    Algorithm::Instance algorithm;
    ASSERT_ANY_THROW(Algorithm::build<TestAlgorithm>(algorithm));
}

#endif //STATE_MACHINE_CPP_TEST_STATE_REMOVE_H
