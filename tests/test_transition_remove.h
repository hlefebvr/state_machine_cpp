//
// Created by henri on 07/05/21.
//

#ifndef STATE_MACHINE_CPP_TEST_TRANSITION_REMOVE_H
#define STATE_MACHINE_CPP_TEST_TRANSITION_REMOVE_H

TEST(transition_remove, should_remove_transition) {
    TEST_UTIL_CREATE_ALGORITHM_BUILDER(TestAlgorithm, {
        states.create(A);
        states.create(B);

        transitions.create(A, B);
        transitions.remove(A);
    });

    Algorithm::Instance algorithm;
    Algorithm::build<TestAlgorithm>(algorithm);

    ASSERT_TRUE(algorithm.transitions().has(A));
    ASSERT_FALSE(algorithm.transitions()[A].has_handler());
    ASSERT_EQ(algorithm.transitions()[A].type(), Transition::Type::Undefined);
}

TEST(transition_remove, should_throw_if_remove_final_transition) {
    TEST_UTIL_CREATE_ALGORITHM_BUILDER(TestAlgorithm, {
        states.create(A);
        states.create(B);

        transitions.create(A, B);
        transitions.declare_as_final(A);
        transitions.remove(A);
    });

    Algorithm::Instance algorithm;
    ASSERT_ANY_THROW(Algorithm::build<TestAlgorithm>(algorithm));
}

#endif //STATE_MACHINE_CPP_TEST_TRANSITION_REMOVE_H
