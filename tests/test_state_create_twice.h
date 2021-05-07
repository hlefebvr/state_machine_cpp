//
// Created by henri on 07/05/21.
//

#ifndef STATE_MACHINE_CPP_TEST_STATE_CREATE_TWICE_H
#define STATE_MACHINE_CPP_TEST_STATE_CREATE_TWICE_H

TEST(state_create_twice, should_throw_if_create_twice) {
    TEST_UTIL_CREATE_ALGORITHM_BUILDER(TestAlgorithm, {
        states.create(A);
        states.create(A);
    });

    Algorithm::Instance algorithm;
    ASSERT_ANY_THROW(Algorithm::build<TestAlgorithm>(algorithm));
}


#endif //STATE_MACHINE_CPP_TEST_STATE_CREATE_TWICE_H
