#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "../worldcup23a2.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>

std::string str(const permutation_t &perm1)
{
    std::stringstream p1;
    p1 << perm1;
    return p1.str();
}

TEST_CASE("check add, remove team")
{
    SECTION("add_team error check")
    {
        world_cup_t *obj = new world_cup_t();
        REQUIRE(obj->add_team(0) == StatusType::INVALID_INPUT);
        REQUIRE(obj->add_team(-1) == StatusType::INVALID_INPUT);
        REQUIRE(obj->add_team(-100) == StatusType::INVALID_INPUT);

        REQUIRE(obj->add_team(1) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(1) == StatusType::FAILURE);
        REQUIRE(obj->add_team(2) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(2) == StatusType::FAILURE);

        delete obj;
    }

    SECTION("remove team error check")
    {
        world_cup_t *obj = new world_cup_t();
        REQUIRE(obj->remove_team(0) == StatusType::INVALID_INPUT);
        REQUIRE(obj->remove_team(-1) == StatusType::INVALID_INPUT);
        REQUIRE(obj->remove_team(-100) == StatusType::INVALID_INPUT);

        REQUIRE(obj->remove_team(1) == StatusType::FAILURE);
        REQUIRE(obj->remove_team(2) == StatusType::FAILURE);
        delete obj;
    }
    SECTION("add and remove team")
    {
        world_cup_t *obj = new world_cup_t();

        REQUIRE(obj->add_team(1) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(2) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(3) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(4) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(5) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(6) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(7) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(8) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(9) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(10) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(11) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(12) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(13) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(14) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(15) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(16) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(17) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(18) == StatusType::SUCCESS);
        REQUIRE(obj->remove_team(1) == StatusType::SUCCESS);
        REQUIRE(obj->remove_team(2) == StatusType::SUCCESS);
        REQUIRE(obj->remove_team(3) == StatusType::SUCCESS);
        REQUIRE(obj->remove_team(4) == StatusType::SUCCESS);
        REQUIRE(obj->remove_team(5) == StatusType::SUCCESS);
        REQUIRE(obj->remove_team(6) == StatusType::SUCCESS);
        REQUIRE(obj->remove_team(7) == StatusType::SUCCESS);
        REQUIRE(obj->remove_team(8) == StatusType::SUCCESS);
        REQUIRE(obj->remove_team(9) == StatusType::SUCCESS);
        REQUIRE(obj->remove_team(9) == StatusType::FAILURE);

        delete obj;
    }

    SECTION("simple add_team check")
    {
        world_cup_t *obj = new world_cup_t();

        REQUIRE(obj->add_team(1) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(2) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(3) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(4) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(5) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(6) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(7) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(8) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(9) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(10) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(11) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(12) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(13) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(14) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(15) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(16) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(17) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(18) == StatusType::SUCCESS);

        delete obj;
    }

    SECTION("add remove and add team")
    {
        world_cup_t *obj = new world_cup_t();

        REQUIRE(obj->add_team(1) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(2) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(3) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(4) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(5) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(6) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(7) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(8) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(9) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(10) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(11) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(12) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(13) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(14) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(15) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(16) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(17) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(18) == StatusType::SUCCESS);

        REQUIRE(obj->remove_team(1) == StatusType::SUCCESS);
        REQUIRE(obj->remove_team(2) == StatusType::SUCCESS);
        REQUIRE(obj->remove_team(3) == StatusType::SUCCESS);
        REQUIRE(obj->remove_team(4) == StatusType::SUCCESS);
        REQUIRE(obj->remove_team(5) == StatusType::SUCCESS);
        REQUIRE(obj->remove_team(6) == StatusType::SUCCESS);
        REQUIRE(obj->remove_team(7) == StatusType::SUCCESS);
        REQUIRE(obj->remove_team(8) == StatusType::SUCCESS);
        REQUIRE(obj->remove_team(9) == StatusType::SUCCESS);
        REQUIRE(obj->remove_team(9) == StatusType::FAILURE);

        REQUIRE(obj->add_team(1) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(2) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(3) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(4) == StatusType::SUCCESS);

        REQUIRE(obj->add_team(100) == StatusType::SUCCESS);
        REQUIRE(obj->remove_team(100) == StatusType::SUCCESS);

        REQUIRE(obj->add_team(100) == StatusType::SUCCESS);
        REQUIRE(obj->remove_team(100) == StatusType::SUCCESS);

        REQUIRE(obj->add_team(100) == StatusType::SUCCESS);
        REQUIRE(obj->remove_team(100) == StatusType::SUCCESS);

        REQUIRE(obj->add_team(100) == StatusType::SUCCESS);
        REQUIRE(obj->remove_team(100) == StatusType::SUCCESS);

        REQUIRE(obj->add_team(100) == StatusType::SUCCESS);
        REQUIRE(obj->remove_team(100) == StatusType::SUCCESS);

        REQUIRE(obj->add_team(100) == StatusType::SUCCESS);
        REQUIRE(obj->remove_team(100) == StatusType::SUCCESS);

        REQUIRE(obj->add_team(100) == StatusType::SUCCESS);
        REQUIRE(obj->remove_team(100) == StatusType::SUCCESS);

        delete obj;
    }
}

TEST_CASE("check add_player")
{
    SECTION("check errors")
    {
        world_cup_t *obj = new world_cup_t();

        int basePerm1[5] = {1, 2, 3, 4, 0};
        permutation_t perm1(basePerm1);
        int basePerm6[5] = {3, 3, 2, 3, 1};
        permutation_t not_good_perm(basePerm6);

        REQUIRE(obj->add_player(0, 1, perm1, 1, 1, 1, true) == StatusType::INVALID_INPUT);
        REQUIRE(obj->add_player(-1, 1, perm1, 1, 1, 1, true) == StatusType::INVALID_INPUT);
        REQUIRE(obj->add_player(1, 0, perm1, 1, 1, 1, true) == StatusType::INVALID_INPUT);
        REQUIRE(obj->add_player(1, -1, perm1, 1, 1, 1, true) == StatusType::INVALID_INPUT);
        REQUIRE(obj->add_player(1, 1, not_good_perm, 1, 1, 1, true) == StatusType::INVALID_INPUT);
        REQUIRE(obj->add_player(1, 1, perm1, 1, 1, -1, true) == StatusType::INVALID_INPUT);

        REQUIRE(obj->add_player(1, 1, perm1, 1, 1, 1, true) == StatusType::FAILURE);
        REQUIRE(obj->add_team(1) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(1, 1, perm1, 1, 1, 1, true) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(1, 1, perm1, 1, 1, 1, true) == StatusType::FAILURE);
        REQUIRE(obj->remove_team(1) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(2) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(1, 2, perm1, 1, 1, 1, true) == StatusType::FAILURE);
        REQUIRE(obj->add_player(2, 1, perm1, 1, 1, 1, true) == StatusType::FAILURE);

        delete obj;
    }

    SECTION("add player tests")
    {
        int basePerm1[5] = {1, 2, 3, 4, 0};
        permutation_t perm1(basePerm1);
        int basePerm2[5] = {1, 2, 3, 0, 4};
        permutation_t perm2(basePerm2);
        int basePerm3[5] = {3, 2, 1, 4, 0};
        permutation_t perm3(basePerm3);
        int basePerm4[5] = {0, 1, 3, 2, 4};
        permutation_t perm4(basePerm4);
        int basePerm5[5] = {3, 4, 2, 0, 1};
        permutation_t perm5(basePerm5);

        world_cup_t *obj = new world_cup_t();

        REQUIRE(obj->add_team(1) == StatusType::SUCCESS);
        REQUIRE(obj->add_team(2) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(1, 1, perm1, 1, 1, 1, true) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(2, 1, perm2, 1, 1, 1, false) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(3, 1, perm3, 1, 1, 1, false) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(4, 1, perm4, 1, 1, 1, false) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(5, 1, perm5, 1, 1, 1, true) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(6, 2, perm1, 1, 1, 1, true) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(7, 2, perm2, 1, 1, 1, false) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(8, 2, perm3, 1, 1, 1, false) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(9, 2, perm4, 1, 1, 1, true) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(10, 2, perm5, 1, 1, 1, false) == StatusType::SUCCESS);

        delete obj;
    }
}

TEST_CASE("play match test")
{
    SECTION("simple play_match")
    {
        int basePerm1[5] = {1, 2, 3, 4, 0};
        permutation_t perm1(basePerm1);
        int basePerm2[5] = {1, 2, 3, 0, 4};
        permutation_t perm2(basePerm2);
        int basePerm3[5] = {3, 2, 1, 4, 0};
        permutation_t perm3(basePerm3);
        int basePerm4[5] = {0, 1, 3, 2, 4};
        permutation_t perm4(basePerm4);
        int basePerm5[5] = {3, 4, 2, 0, 1};
        permutation_t perm5(basePerm5);

        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(2);
        REQUIRE(res == StatusType::SUCCESS);

        // first team players
        REQUIRE(obj->add_player(1001, 1, perm1, 1, 1, 1, true) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(1002, 1, perm2, 1, 1, 1, false) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(1003, 1, perm3, 1, 1, 1, false) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(1004, 1, perm4, 1, 1, 1, false) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(1005, 1, perm5, 1, 1, 1, true) == StatusType::SUCCESS);

        // second team players
        REQUIRE(obj->add_player(2001, 2, perm1, 1, 1, 1, true) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(2002, 2, perm2, 1, 1, 1, false) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(2003, 2, perm3, 1, 1, 1, false) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(2004, 2, perm4, 1, 1, 1, false) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(2005, 2, perm5, 1, 1, 1, true) == StatusType::SUCCESS);

        output_t<int> resn1 = obj->play_match(1, 2);
        REQUIRE(resn1.status() == StatusType::SUCCESS);
        REQUIRE(resn1.ans() == 0);

        delete obj;
    }

    SECTION("simple play_match 2")
    {
        int basePerm1[5] = {1, 2, 3, 4, 0};
        permutation_t perm1(basePerm1);
        int basePerm2[5] = {1, 2, 3, 0, 4};
        permutation_t perm2(basePerm2);
        int basePerm3[5] = {3, 2, 1, 4, 0};
        permutation_t perm3(basePerm3);
        int basePerm4[5] = {0, 1, 3, 2, 4};
        permutation_t perm4(basePerm4);
        int basePerm5[5] = {3, 4, 2, 0, 1};
        permutation_t perm5(basePerm5);

        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(2);
        REQUIRE(res == StatusType::SUCCESS);

        // first team players
        REQUIRE(obj->add_player(1001, 1, perm1, 1, 1, 1, true) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(1002, 1, perm2, 1, 1, 1, false) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(1003, 1, perm3, 1, 1, 1, false) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(1004, 1, perm4, 1, 1, 1, false) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(1005, 1, perm5, 1, 1, 1, true) == StatusType::SUCCESS);

        // second team players
        REQUIRE(obj->add_player(2001, 2, perm5, 1, 1, 1, true) == StatusType::SUCCESS);

        output_t<int> resn1 = obj->play_match(1, 2);
        REQUIRE(resn1.status() == StatusType::SUCCESS);
        REQUIRE(resn1.ans() == 1);

        delete obj;
    }

    SECTION("simple play_match 3")
    {
        int basePerm1[5] = {1, 2, 3, 4, 0};
        permutation_t perm1(basePerm1);
        int basePerm2[5] = {1, 2, 3, 0, 4};
        permutation_t perm2(basePerm2);
        int basePerm3[5] = {3, 2, 1, 4, 0};
        permutation_t perm3(basePerm3);
        int basePerm4[5] = {0, 1, 3, 2, 4};
        permutation_t perm4(basePerm4);
        int basePerm5[5] = {3, 4, 2, 0, 1};
        permutation_t perm5(basePerm5);

        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(2);
        REQUIRE(res == StatusType::SUCCESS);

        // first team players
        REQUIRE(obj->add_player(1001, 1, perm1, 1, 1, 1, true) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(1002, 1, perm2, 1, 1, 1, false) == StatusType::SUCCESS);
        // second team players
        REQUIRE(obj->add_player(2001, 2, perm5, 1, 1, 1, true) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(2002, 2, perm4, 1, 1, 1, false) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(2003, 2, perm3, 1, 1, 1, false) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(2004, 2, perm2, 1, 1, 1, false) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(2005, 2, perm1, 1, 1, 1, true) == StatusType::SUCCESS);

        output_t<int> resn1 = obj->play_match(2, 1);
        REQUIRE(resn1.status() == StatusType::SUCCESS);
        REQUIRE(resn1.ans() == 1);

        delete obj;
    }

    SECTION("play_match invalid input")
    {
        world_cup_t *obj = new world_cup_t();

        output_t<int> resn1 = obj->play_match(0, 1);
        REQUIRE(resn1.status() == StatusType::INVALID_INPUT);
        output_t<int> resn2 = obj->play_match(1, 0);
        REQUIRE(resn2.status() == StatusType::INVALID_INPUT);
        output_t<int> resn3 = obj->play_match(0, 0);
        REQUIRE(resn3.status() == StatusType::INVALID_INPUT);
        output_t<int> resn4 = obj->play_match(3, 3);
        REQUIRE(resn4.status() == StatusType::INVALID_INPUT);

        delete obj;
    }

    SECTION("play_match failure")
    {
        int basePerm1[5] = {1, 2, 3, 4, 0};
        permutation_t perm1(basePerm1);
        int basePerm2[5] = {1, 2, 3, 0, 4};
        permutation_t perm2(basePerm2);
        int basePerm3[5] = {3, 2, 1, 4, 0};
        permutation_t perm3(basePerm3);
        int basePerm4[5] = {0, 1, 3, 2, 4};
        permutation_t perm4(basePerm4);
        int basePerm5[5] = {3, 4, 2, 0, 1};
        permutation_t perm5(basePerm5);

        world_cup_t *obj = new world_cup_t();

        output_t<int> resn1 = obj->play_match(2, 1);
        REQUIRE(resn1.status() == StatusType::FAILURE);
        REQUIRE(obj->add_team(1) == StatusType::SUCCESS);
        output_t<int> resn2 = obj->play_match(1, 2);
        REQUIRE(resn2.status() == StatusType::FAILURE);

        output_t<int> resn3 = obj->play_match(1, 1);
        REQUIRE(resn3.status() == StatusType::INVALID_INPUT);
        output_t<int> resn4 = obj->play_match(4, 4);
        //******PIAZZA QUESTION - should this be failure or invalid input?****
        REQUIRE(resn4.status() == StatusType::INVALID_INPUT);

        delete obj;
    }

    SECTION("play_match no goal keepers")
    {
        int basePerm1[5] = {1, 2, 3, 4, 0};
        permutation_t perm1(basePerm1);
        int basePerm2[5] = {1, 2, 3, 0, 4};
        permutation_t perm2(basePerm2);
        int basePerm3[5] = {3, 2, 1, 4, 0};
        permutation_t perm3(basePerm3);
        int basePerm4[5] = {0, 1, 3, 2, 4};
        permutation_t perm4(basePerm4);
        int basePerm5[5] = {3, 4, 2, 0, 1};
        permutation_t perm5(basePerm5);

        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(2);
        REQUIRE(res == StatusType::SUCCESS);

        // first team players
        REQUIRE(obj->add_player(1001, 1, perm1, 1, 1, 1, false) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(1002, 1, perm2, 1, 1, 1, false) == StatusType::SUCCESS);
        // second team players
        REQUIRE(obj->add_player(2001, 2, perm5, 1, 1, 1, false) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(2002, 2, perm4, 1, 1, 1, false) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(2003, 2, perm3, 1, 1, 1, false) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(2004, 2, perm2, 1, 1, 1, false) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(2005, 2, perm1, 1, 1, 1, false) == StatusType::SUCCESS);

        output_t<int> resn1 = obj->play_match(2, 1);
        REQUIRE(resn1.status() == StatusType::FAILURE);

        delete obj;
    }

    SECTION("play_match goal keepers only on one")
    {
        int basePerm1[5] = {1, 2, 3, 4, 0};
        permutation_t perm1(basePerm1);
        int basePerm2[5] = {1, 2, 3, 0, 4};
        permutation_t perm2(basePerm2);
        int basePerm3[5] = {3, 2, 1, 4, 0};
        permutation_t perm3(basePerm3);
        int basePerm4[5] = {0, 1, 3, 2, 4};
        permutation_t perm4(basePerm4);
        int basePerm5[5] = {3, 4, 2, 0, 1};
        permutation_t perm5(basePerm5);

        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(2);
        REQUIRE(res == StatusType::SUCCESS);

        // first team players
        REQUIRE(obj->add_player(1001, 1, perm1, 1, 1, 1, false) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(1002, 1, perm2, 1, 1, 1, false) == StatusType::SUCCESS);
        // second team players
        REQUIRE(obj->add_player(2001, 2, perm5, 1, 1, 1, true) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(2002, 2, perm4, 1, 1, 1, false) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(2003, 2, perm3, 1, 1, 1, true) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(2004, 2, perm2, 1, 1, 1, true) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(2005, 2, perm1, 1, 1, 1, false) == StatusType::SUCCESS);

        output_t<int> resn1 = obj->play_match(2, 1);
        REQUIRE(resn1.status() == StatusType::FAILURE);

        delete obj;
    }
}

TEST_CASE("num_played_games_for_player test")
{
    SECTION("failure test")
    {
        world_cup_t *obj = new world_cup_t();
        output_t<int> resn1 = obj->num_played_games_for_player(1);
        REQUIRE(resn1.status() == StatusType::FAILURE);
        delete obj;
    }

    SECTION("invalid input test")
    {
        world_cup_t *obj = new world_cup_t();
        output_t<int> resn1 = obj->num_played_games_for_player(0);
        REQUIRE(resn1.status() == StatusType::INVALID_INPUT);

        output_t<int> resn2 = obj->num_played_games_for_player(-3);
        REQUIRE(resn2.status() == StatusType::INVALID_INPUT);
        delete obj;
    }

    SECTION("simple test")
    {
        int basePerm1[5] = {1, 2, 3, 4, 0};
        permutation_t perm1(basePerm1);
        int basePerm2[5] = {1, 2, 3, 0, 4};
        permutation_t perm2(basePerm2);
        int basePerm3[5] = {3, 2, 1, 4, 0};
        permutation_t perm3(basePerm3);
        int basePerm4[5] = {0, 1, 3, 2, 4};
        permutation_t perm4(basePerm4);
        int basePerm5[5] = {3, 4, 2, 0, 1};
        permutation_t perm5(basePerm5);

        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(2);
        REQUIRE(res == StatusType::SUCCESS);

        // first team players
        REQUIRE(obj->add_player(1001, 1, perm1, 0, 1, 1, true) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(1002, 1, perm2, 0, 1, 1, false) == StatusType::SUCCESS);
        // second team players
        REQUIRE(obj->add_player(2001, 2, perm5, 0, 1, 1, true) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(2002, 2, perm4, 0, 1, 1, false) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(2003, 2, perm3, 0, 1, 1, true) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(2004, 2, perm2, 0, 1, 1, true) == StatusType::SUCCESS);
        REQUIRE(obj->add_player(2005, 2, perm1, 0, 1, 1, false) == StatusType::SUCCESS);

        output_t<int> resn1 = obj->num_played_games_for_player(1001);
        REQUIRE(resn1.status() == StatusType::SUCCESS);
        REQUIRE(resn1.ans() == 0);

        output_t<int> resn2 = obj->num_played_games_for_player(2002);
        REQUIRE(resn2.status() == StatusType::SUCCESS);
        REQUIRE(resn2.ans() == 0);

        output_t<int> resn3 = obj->num_played_games_for_player(2004);
        REQUIRE(resn3.status() == StatusType::SUCCESS);
        REQUIRE(resn3.ans() == 0);

        output_t<int> resn4 = obj->play_match(2, 1);
        REQUIRE(resn4.status() == StatusType::SUCCESS);

        output_t<int> resn5 = obj->num_played_games_for_player(1001);
        REQUIRE(resn5.status() == StatusType::SUCCESS);
        REQUIRE(resn5.ans() == 1);

        output_t<int> resn6 = obj->num_played_games_for_player(2002);
        REQUIRE(resn6.status() == StatusType::SUCCESS);
        REQUIRE(resn6.ans() == 1);

        output_t<int> resn7 = obj->num_played_games_for_player(2004);
        REQUIRE(resn7.status() == StatusType::SUCCESS);
        REQUIRE(resn7.ans() == 1);

        output_t<int> resn8 = obj->play_match(2, 1);
        REQUIRE(resn8.status() == StatusType::SUCCESS);
        output_t<int> resn9 = obj->play_match(2, 1);
        REQUIRE(resn9.status() == StatusType::SUCCESS);
        output_t<int> resn10 = obj->play_match(2, 1);
        REQUIRE(resn10.status() == StatusType::SUCCESS);
        output_t<int> resn11 = obj->play_match(2, 1);
        REQUIRE(resn11.status() == StatusType::SUCCESS);

        output_t<int> resn12 = obj->num_played_games_for_player(1001);
        REQUIRE(resn12.status() == StatusType::SUCCESS);
        REQUIRE(resn12.ans() == 5);

        output_t<int> resn13 = obj->num_played_games_for_player(2002);
        REQUIRE(resn13.status() == StatusType::SUCCESS);
        REQUIRE(resn13.ans() == 5);

        output_t<int> resn14 = obj->num_played_games_for_player(2004);
        REQUIRE(resn14.status() == StatusType::SUCCESS);
        REQUIRE(resn14.ans() == 5);
    }
}

TEST_CASE("add and get player cards")
{
    SECTION("get cards failure test")
    {
        world_cup_t *obj = new world_cup_t();
        output_t<int> resn1 = obj->get_player_cards(1);
        REQUIRE(resn1.status() == StatusType::FAILURE);
        delete obj;
    }

    SECTION("get cards invalid input test")
    {
        world_cup_t *obj = new world_cup_t();
        output_t<int> resn1 = obj->get_player_cards(0);
        REQUIRE(resn1.status() == StatusType::INVALID_INPUT);

        output_t<int> resn2 = obj->get_player_cards(-3);
        REQUIRE(resn2.status() == StatusType::INVALID_INPUT);
        delete obj;
    }

    SECTION("add cards invalid input test")
    {
        int basePerm1[5] = {1, 2, 3, 4, 0};
        permutation_t perm1(basePerm1);

        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_player_cards(0, 1);
        REQUIRE(res == StatusType::INVALID_INPUT);
        res = obj->add_player_cards(-1, 1);
        REQUIRE(res == StatusType::INVALID_INPUT);
        res = obj->add_player_cards(1, -1);
        REQUIRE(res == StatusType::INVALID_INPUT);

        delete obj;
    }

    SECTION("add cards failure test")
    {
        int basePerm1[5] = {1, 2, 3, 4, 0};
        permutation_t perm1(basePerm1);

        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_player_cards(1, 1);
        REQUIRE(res == StatusType::FAILURE);

        res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player_cards(1, 1);
        REQUIRE(res == StatusType::FAILURE);
        res = obj->add_player(1, 1, perm1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn2 = obj->get_player_cards(1);
        REQUIRE(resn2.status() == StatusType::SUCCESS);
        REQUIRE(resn2.ans() == 1);
        res = obj->remove_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player_cards(1, 1);
        REQUIRE(res == StatusType::FAILURE);

        delete obj;
    }

    SECTION("simple add get cards test")
    {
        int basePerm1[5] = {1, 2, 3, 4, 0};
        permutation_t perm1(basePerm1);

        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1, 1, perm1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player_cards(1, 1);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn2 = obj->get_player_cards(1);
        REQUIRE(resn2.status() == StatusType::SUCCESS);
        REQUIRE(resn2.ans() == 2);
        res = obj->add_player_cards(1, 1);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn3 = obj->get_player_cards(1);
        REQUIRE(resn3.status() == StatusType::SUCCESS);
        REQUIRE(resn3.ans() == 3);
        res = obj->add_player_cards(1, 1);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn4 = obj->get_player_cards(1);
        REQUIRE(resn4.status() == StatusType::SUCCESS);
        REQUIRE(resn4.ans() == 4);
        res = obj->add_player_cards(1, 1);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn5 = obj->get_player_cards(1);
        REQUIRE(resn5.status() == StatusType::SUCCESS);
        REQUIRE(resn5.ans() == 5);
        res = obj->add_player_cards(1, 1);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn6 = obj->get_player_cards(1);
        REQUIRE(resn6.status() == StatusType::SUCCESS);
        REQUIRE(resn6.ans() == 6);
        res = obj->add_player_cards(1, 1);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn7 = obj->get_player_cards(1);
        REQUIRE(resn7.status() == StatusType::SUCCESS);
        REQUIRE(resn7.ans() == 7);
        res = obj->add_player_cards(1, 1);
        REQUIRE(res == StatusType::SUCCESS);

        delete obj;
    }
}

TEST_CASE("get team points test")
{
    SECTION("get team points failure test")
    {
        world_cup_t *obj = new world_cup_t();
        output_t<int> resn1 = obj->get_team_points(1);
        REQUIRE(resn1.status() == StatusType::FAILURE);
        delete obj;
    }

    SECTION("get team points invalid input test")
    {
        world_cup_t *obj = new world_cup_t();
        output_t<int> resn1 = obj->get_team_points(0);
        REQUIRE(resn1.status() == StatusType::INVALID_INPUT);

        output_t<int> resn2 = obj->get_team_points(-3);
        REQUIRE(resn2.status() == StatusType::INVALID_INPUT);
        delete obj;
    }

    SECTION("get team points simple test")
    {
        int basePerm1[5] = {1, 2, 3, 4, 0};
        permutation_t perm1(basePerm1);

        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1, 1, perm1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);

        output_t<int> resn2 = obj->get_team_points(1);
        REQUIRE(resn2.status() == StatusType::SUCCESS);
        REQUIRE(resn2.ans() == 0);
        delete obj;
    }

    SECTION("get team points after play match test")
    {
        int basePerm1[5] = {1, 2, 3, 4, 0};
        permutation_t perm1(basePerm1);
        int basePerm2[5] = {1, 2, 3, 0, 4};
        permutation_t perm2(basePerm2);
        int basePerm3[5] = {3, 2, 1, 4, 0};
        permutation_t perm3(basePerm3);

        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1, 1, perm1, 1, 1, 1, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2, 1, perm1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3, 1, perm2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(5, 2, perm1, 1, 1, 1, true);

        REQUIRE(res == StatusType::SUCCESS);
        // team 1 should always win

        output_t<int> resn1 = obj->play_match(1, 2);
        REQUIRE(resn1.status() == StatusType::SUCCESS);
        REQUIRE(resn1.ans() == 1);
        output_t<int> resn11 = obj->get_team_points(1);
        REQUIRE(resn11.status() == StatusType::SUCCESS);
        REQUIRE(resn11.ans() == 3);
        output_t<int> resn12 = obj->get_team_points(2);
        REQUIRE(resn12.status() == StatusType::SUCCESS);
        REQUIRE(resn12.ans() == 0);

        output_t<int> resn2 = obj->play_match(1, 2);
        REQUIRE(resn2.status() == StatusType::SUCCESS);
        REQUIRE(resn2.ans() == 1);
        output_t<int> resn21 = obj->get_team_points(1);
        REQUIRE(resn21.status() == StatusType::SUCCESS);
        REQUIRE(resn21.ans() == 6);
        output_t<int> resn22 = obj->get_team_points(2);
        REQUIRE(resn22.status() == StatusType::SUCCESS);
        REQUIRE(resn22.ans() == 0);

        output_t<int> resn3 = obj->play_match(1, 2);
        REQUIRE(resn3.status() == StatusType::SUCCESS);
        REQUIRE(resn3.ans() == 1);
        output_t<int> resn31 = obj->get_team_points(1);
        REQUIRE(resn31.status() == StatusType::SUCCESS);
        REQUIRE(resn31.ans() == 9);
        output_t<int> resn32 = obj->get_team_points(2);
        REQUIRE(resn32.status() == StatusType::SUCCESS);
        REQUIRE(resn32.ans() == 0);

        output_t<int> resn4 = obj->play_match(2, 1);
        REQUIRE(resn4.status() == StatusType::SUCCESS);
        REQUIRE(resn4.ans() == 3);
        output_t<int> resn41 = obj->get_team_points(1);
        REQUIRE(resn41.status() == StatusType::SUCCESS);
        REQUIRE(resn41.ans() == 12);
        output_t<int> resn42 = obj->get_team_points(2);
        REQUIRE(resn42.status() == StatusType::SUCCESS);
        REQUIRE(resn42.ans() == 0);

        output_t<int> resn5 = obj->play_match(2, 1);
        REQUIRE(resn5.status() == StatusType::SUCCESS);
        REQUIRE(resn5.ans() == 3);
        output_t<int> resn51 = obj->get_team_points(1);
        REQUIRE(resn51.status() == StatusType::SUCCESS);
        REQUIRE(resn51.ans() == 15);
        output_t<int> resn52 = obj->get_team_points(2);
        REQUIRE(resn52.status() == StatusType::SUCCESS);
        REQUIRE(resn52.ans() == 0);

        delete obj;
    }

    SECTION("get team points after a tie")
    {
        int basePerm1[5] = {1, 2, 3, 4, 0};
        permutation_t perm1(basePerm1);

        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(2);
        REQUIRE(res == StatusType::SUCCESS);
    }

    SECTION("get team points 2")
    {
        int basePerm1[5] = {1, 2, 3, 4, 0};
        permutation_t perm1(basePerm1);

        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1, 1, perm1, 1, 1, 1, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2, 1, perm1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3, 1, perm1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(4, 1, perm1, 1, 1, 1, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(5, 2, perm1, 1, 1, 1, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(6, 2, perm1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(7, 2, perm1, 1, 1, 1, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(8, 2, perm1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        // team 1 should always win

        output_t<int> resn1 = obj->play_match(1, 2);
        REQUIRE(resn1.status() == StatusType::SUCCESS);
        REQUIRE(resn1.ans() == 0);
        output_t<int> resn11 = obj->get_team_points(1);
        REQUIRE(resn11.status() == StatusType::SUCCESS);
        REQUIRE(resn11.ans() == 1);
        output_t<int> resn12 = obj->get_team_points(2);
        REQUIRE(resn12.status() == StatusType::SUCCESS);
        REQUIRE(resn12.ans() == 1);

        output_t<int> resn2 = obj->play_match(1, 2);
        REQUIRE(resn2.status() == StatusType::SUCCESS);
        REQUIRE(resn2.ans() == 0);
        output_t<int> resn21 = obj->get_team_points(1);
        REQUIRE(resn21.status() == StatusType::SUCCESS);
        REQUIRE(resn21.ans() == 2);
        output_t<int> resn22 = obj->get_team_points(2);
        REQUIRE(resn22.status() == StatusType::SUCCESS);
        REQUIRE(resn22.ans() == 2);

        output_t<int> resn3 = obj->play_match(1, 2);
        REQUIRE(resn3.status() == StatusType::SUCCESS);
        REQUIRE(resn3.ans() == 0);
        output_t<int> resn31 = obj->get_team_points(1);
        REQUIRE(resn31.status() == StatusType::SUCCESS);
        REQUIRE(resn31.ans() == 3);
        output_t<int> resn32 = obj->get_team_points(2);
        REQUIRE(resn32.status() == StatusType::SUCCESS);
        REQUIRE(resn32.ans() == 3);

        output_t<int> resn4 = obj->play_match(2, 1);
        REQUIRE(resn4.status() == StatusType::SUCCESS);
        REQUIRE(resn4.ans() == 0);
        output_t<int> resn41 = obj->get_team_points(1);
        REQUIRE(resn41.status() == StatusType::SUCCESS);
        REQUIRE(resn41.ans() == 4);
        output_t<int> resn42 = obj->get_team_points(2);
        REQUIRE(resn42.status() == StatusType::SUCCESS);
        REQUIRE(resn42.ans() == 4);

        output_t<int> resn5 = obj->play_match(2, 1);
        REQUIRE(resn5.status() == StatusType::SUCCESS);
        REQUIRE(resn5.ans() == 0);
        output_t<int> resn51 = obj->get_team_points(1);
        REQUIRE(resn51.status() == StatusType::SUCCESS);
        REQUIRE(resn51.ans() == 5);
        output_t<int> resn52 = obj->get_team_points(2);
        REQUIRE(resn52.status() == StatusType::SUCCESS);
        REQUIRE(resn52.ans() == 5);

        delete obj;
    }
}

TEST_CASE("get ith pointless ability")
{
}

TEST_CASE("get_partial_spirit")
{
    SECTION("Basic partial spirit")
    {
        int basePerm1[5] = {1, 2, 3, 4, 0};
        permutation_t perm1(basePerm1);
        permutation_t perm2(basePerm1);
        int basePerm2[5] = {1, 0, 4, 3, 2};
        permutation_t perm3(basePerm2);

        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(10);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1, 10, perm1, 1, 1, 1, true);
        REQUIRE(res == StatusType::SUCCESS);

        output_t<permutation_t> resn1 = obj->get_partial_spirit(1);
        REQUIRE(resn1.status() == StatusType::SUCCESS);
        REQUIRE(str(resn1.ans()) == str(perm1));

        res = obj->add_player(2, 10, perm2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);

        output_t<permutation_t> resn2 = obj->get_partial_spirit(2);
        REQUIRE(resn2.status() == StatusType::SUCCESS);
        REQUIRE(str(resn2.ans()) == str(perm1 * perm2));

        res = obj->add_player(3, 10, perm3, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);

        output_t<permutation_t> resn3 = obj->get_partial_spirit(3);
        REQUIRE(resn3.status() == StatusType::SUCCESS);
        REQUIRE(str(resn3.ans()) == str(perm1 * perm2 * perm3));

        output_t<permutation_t> resn4 = obj->get_partial_spirit(1);
        REQUIRE(resn4.status() == StatusType::SUCCESS);
        REQUIRE(str(resn4.ans()) == str(perm1));

        output_t<permutation_t> resn5 = obj->get_partial_spirit(2);
        REQUIRE(resn5.status() == StatusType::SUCCESS);
        REQUIRE(str(resn5.ans()) == str(perm1 * perm2));

        res = obj->add_team(20);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(4, 20, perm3 * perm2, 1, 1, 1, true);
        REQUIRE(res == StatusType::SUCCESS);

        output_t<permutation_t> resn6 = obj->get_partial_spirit(4);
        REQUIRE(resn6.status() == StatusType::SUCCESS);
        REQUIRE(str(resn6.ans()) == str(perm3 * perm2));

        output_t<permutation_t> resn7 = obj->get_partial_spirit(2);
        REQUIRE(resn7.status() == StatusType::SUCCESS);
        REQUIRE(str(resn7.ans()) == str(perm1 * perm2));

        delete obj;
    }

    SECTION("partial failing cases")
    {
        world_cup_t *obj = new world_cup_t();
        int basePerm[5] = {1, 2, 4, 3, 0};
        permutation_t perm(basePerm);

        output_t<permutation_t> resn1 = obj->get_partial_spirit(-1);
        REQUIRE(resn1.status() == StatusType::INVALID_INPUT);
        output_t<permutation_t> resn2 = obj->get_partial_spirit(0);
        REQUIRE(resn2.status() == StatusType::INVALID_INPUT);

        output_t<permutation_t> resn3 = obj->get_partial_spirit(1);
        REQUIRE(resn3.status() == StatusType::FAILURE);

        StatusType res = obj->add_team(20);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(4, 20, perm, 1, 1, 1, true);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<permutation_t> resn4 = obj->get_partial_spirit(1);
        REQUIRE(resn4.status() == StatusType::FAILURE);

        res = obj->remove_team(20);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<permutation_t> resn5 = obj->get_partial_spirit(4);
        REQUIRE(resn5.status() == StatusType::FAILURE);

        delete obj;
    }
}

TEST_CASE("buy_team")
{
    SECTION("invalid buys")
    {
        int basePerm[5] = {1, 2, 3, 4, 0};
        permutation_t perm = permutation_t(basePerm).inv();

        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->buy_team(-1, 1);
        REQUIRE(res == StatusType::INVALID_INPUT);
        res = obj->buy_team(-1, -2);
        REQUIRE(res == StatusType::INVALID_INPUT);
        res = obj->buy_team(1, -1);
        REQUIRE(res == StatusType::INVALID_INPUT);
        res = obj->buy_team(0, 1);
        REQUIRE(res == StatusType::INVALID_INPUT);
        res = obj->buy_team(1, 1);
        REQUIRE(res == StatusType::INVALID_INPUT);
        res = obj->buy_team(-1, -1);
        REQUIRE(res == StatusType::INVALID_INPUT);
        res = obj->buy_team(1, 0);
        REQUIRE(res == StatusType::INVALID_INPUT);

        res = obj->buy_team(1, 2);
        REQUIRE(res == StatusType::FAILURE);
        res = obj->buy_team(2, 1);
        REQUIRE(res == StatusType::FAILURE);
        res = obj->buy_team(10, 20);
        REQUIRE(res == StatusType::FAILURE);

        res = obj->add_team(20);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(4, 20, perm, 1, 1, 1, true);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->buy_team(1, 2);
        REQUIRE(res == StatusType::FAILURE);
        res = obj->buy_team(2, 1);
        REQUIRE(res == StatusType::FAILURE);
        res = obj->buy_team(10, 20);
        REQUIRE(res == StatusType::FAILURE);
        res = obj->buy_team(20, 10);
        REQUIRE(res == StatusType::FAILURE);
        
        res = obj->add_team(21);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->buy_team(21, 2);
        REQUIRE(res == StatusType::FAILURE);
        res = obj->buy_team(2, 21);
        REQUIRE(res == StatusType::FAILURE);
        res = obj->buy_team(10, 20);
        REQUIRE(res == StatusType::FAILURE);
        res = obj->buy_team(20, 10);
        REQUIRE(res == StatusType::FAILURE);
        
        delete obj;
    }

    SECTION("basic buys")
    {
        int basePerm[5] = {1, 2, 3, 4, 0};
        permutation_t perm = permutation_t(basePerm).inv();

        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(10);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(11, 10, perm, 1, 1, 1, true);
        REQUIRE(res == StatusType::SUCCESS);
        
        output_t<int> resn20 = obj->num_played_games_for_player(11);
        REQUIRE(resn20.status() == StatusType::SUCCESS);
        REQUIRE(resn20.ans() == 1);

        res = obj->add_team(20);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(21, 20, perm, 1, 3, 1, true);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->add_team(30);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(31, 30, perm, 1, 6, 1, true);
        REQUIRE(res == StatusType::SUCCESS);

        output_t<int> resn1 = obj->play_match(10, 20);
        REQUIRE(resn1.status() == StatusType::SUCCESS);
        REQUIRE(resn1.ans() == 3);

        output_t<int> resn21 = obj->num_played_games_for_player(11);
        REQUIRE(resn21.status() == StatusType::SUCCESS);
        REQUIRE(resn21.ans() == 2);

        res = obj->buy_team(10, 20);
        REQUIRE(res == StatusType::SUCCESS);

        output_t<int> resn22 = obj->num_played_games_for_player(11);
        REQUIRE(resn22.status() == StatusType::SUCCESS);
        REQUIRE(resn22.ans() == 2);
        
        output_t<int> resn2 = obj->get_team_points(10);
        REQUIRE(resn2.status() == StatusType::SUCCESS);
        REQUIRE(resn2.ans() == 3);

        output_t<int> resn3 = obj->get_team_points(20);
        REQUIRE(resn3.status() == StatusType::FAILURE);

        output_t<int> resn4 = obj->get_ith_pointless_ability(1);
        REQUIRE(resn4.status() == StatusType::SUCCESS);
        REQUIRE(resn4.ans() == 30);

        output_t<int> resn5 = obj->play_match(10, 30);
        REQUIRE(resn5.status() == StatusType::SUCCESS);
        REQUIRE(resn5.ans() == 1);

        output_t<int> resn23 = obj->num_played_games_for_player(11);
        REQUIRE(resn23.status() == StatusType::SUCCESS);
        REQUIRE(resn23.ans() == 3);

        REQUIRE(obj->add_player(32, 30, perm, 1, 4, 1, true) == StatusType::SUCCESS);

        output_t<int> resn6 = obj->play_match(10, 30);
        REQUIRE(resn6.status() == StatusType::SUCCESS);
        REQUIRE(resn6.ans() == 0);

        output_t<int> resn24 = obj->num_played_games_for_player(11);
        REQUIRE(resn24.status() == StatusType::SUCCESS);
        REQUIRE(resn24.ans() == 4);

        res = obj->buy_team(30, 10);
        REQUIRE(res == StatusType::SUCCESS);

        // Partial spirit is correct
        output_t<permutation_t> resn7 = obj->get_partial_spirit(31);
        REQUIRE(resn7.status() == StatusType::SUCCESS);
        REQUIRE(str(resn7.ans()) == str(perm));

        output_t<permutation_t> resn8 = obj->get_partial_spirit(11);
        REQUIRE(resn8.status() == StatusType::SUCCESS);
        REQUIRE(str(resn8.ans()) == str(perm * perm * perm));
        
        // Num played games is correct
        output_t<int> resn10 = obj->num_played_games_for_player(11);
        REQUIRE(resn10.status() == StatusType::SUCCESS);
        REQUIRE(resn10.ans() == 4);

        output_t<int> resn11 = obj->num_played_games_for_player(21);
        REQUIRE(resn11.status() == StatusType::SUCCESS);
        REQUIRE(resn11.ans() == 4);

        output_t<int> resn12 = obj->num_played_games_for_player(31);
        REQUIRE(resn12.status() == StatusType::SUCCESS);
        REQUIRE(resn12.ans() == 3);

        output_t<int> resn13 = obj->num_played_games_for_player(32);
        REQUIRE(resn13.status() == StatusType::SUCCESS);
        REQUIRE(resn13.ans() == 2);

        // All players get removed together
        res = obj->remove_team(30);
        REQUIRE(res == StatusType::SUCCESS);
        
        REQUIRE(obj->add_player_cards(11, 1) == StatusType::FAILURE);
        REQUIRE(obj->add_player_cards(21, 1) == StatusType::FAILURE);
        REQUIRE(obj->add_player_cards(31, 1) == StatusType::FAILURE);
        REQUIRE(obj->add_player_cards(32, 1) == StatusType::FAILURE);

        delete obj;
    }

    SECTION("basic buys")
    {
    }
}

TEST_CASE("basic tests - all functions")
{
}
