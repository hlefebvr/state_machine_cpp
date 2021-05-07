//
// Created by henri on 07/05/21.
//

#include <gtest/gtest.h>
#include <iostream>

#include "basics.h"

using namespace state_machine_cpp;

static const State::Id A("A");
static const State::Id B("B");
static const State::Id C("C");
static const State::Id D("D");

#include "./test_utils.h"
#include "./test_state_create.h"
#include "./test_transition_create.h"
#include "./test_state_remove.h"
#include "./test_state_create_twice.h"
#include "./test_transition_declare_as_final.h"
#include "./test_transition_create_twice.h"
#include "./test_transition_override.h"
#include "./test_transition_remove.h"
#include "./test_auto_detect.h"

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
