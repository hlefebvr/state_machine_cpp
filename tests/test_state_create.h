//
// Created by henri on 07/05/21.
//

#ifndef STATE_MACHINE_CPP_TEST_STATE_CREATE_H
#define STATE_MACHINE_CPP_TEST_STATE_CREATE_H

TEST(state_create, should_create_state) {
    TEST_UTIL_CREATE_ALGORITHM_BUILDER(TestAlgorithm, {
        states.create(A);
    });

    Algorithm::Instance algorithm;
    Algorithm::build<TestAlgorithm>(algorithm);

    ASSERT_TRUE(algorithm.transitions().has(A));
    ASSERT_FALSE(algorithm.transitions()[A].has_handler());
    ASSERT_EQ(algorithm.transitions()[A].type(), Transition::Type::Undefined);
}

#endif //STATE_MACHINE_CPP_TEST_STATE_CREATE_H
