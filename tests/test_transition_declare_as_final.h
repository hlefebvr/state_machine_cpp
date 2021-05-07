//
// Created by henri on 07/05/21.
//

#ifndef STATE_MACHINE_CPP_TEST_TRANSITION_DECLARE_AS_FINAL_H
#define STATE_MACHINE_CPP_TEST_TRANSITION_DECLARE_AS_FINAL_H

TEST(transition_declare_as_final, should_declare_final_transition) {
    TEST_UTIL_CREATE_ALGORITHM_BUILDER(TestAlgorithm, {
        states.create(A);
        states.create(B);
        transitions.create(A, B);
        transitions.declare_as_final(A);
    });

    Algorithm::Instance algorithm;
    Algorithm::build<TestAlgorithm>(algorithm);
    ASSERT_TRUE(algorithm.transitions()[A].is_final());
}

TEST(transition_declare_as_final, should_throw_if_declaring_final_a_virtual_transition) {
    TEST_UTIL_CREATE_ALGORITHM_BUILDER(TestAlgorithm, {
        states.create(A);
        states.create(B);
        transitions.create_virtual(A, B);
        transitions.declare_as_final(A);
    });

    Algorithm::Instance algorithm;
    ASSERT_ANY_THROW(Algorithm::build<TestAlgorithm>(algorithm));
}

TEST(transition_declare_as_final, should_throw_if_declaring_final_a_non_existing_transition) {
    TEST_UTIL_CREATE_ALGORITHM_BUILDER(TestAlgorithm, {
        states.create(A);
        states.create(B);
        transitions.declare_as_final(A);
    });

    Algorithm::Instance algorithm;
    ASSERT_ANY_THROW(Algorithm::build<TestAlgorithm>(algorithm));
}

TEST(transition_declare_as_final, should_throw_if_declaring_final_from_a_non_existing_state) {
    TEST_UTIL_CREATE_ALGORITHM_BUILDER(TestAlgorithm, {
        transitions.declare_as_final(A);
    });

    Algorithm::Instance algorithm;
    ASSERT_ANY_THROW(Algorithm::build<TestAlgorithm>(algorithm));
}

#endif //STATE_MACHINE_CPP_TEST_TRANSITION_DECLARE_AS_FINAL_H
