#define CATCH_CONFIG_MAIN

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "catch.hpp"
#include <stdlib.h>
#include "../worldcup23a1.h"

using namespace std;

static const char *StatusTypeStr[] =
    {
        "SUCCESS",
        "ALLOCATION_ERROR",
        "INVALID_INPUT",
        "FAILURE"};

void print(string cmd, StatusType res)
{
    cout << cmd << ": " << StatusTypeStr[(int)res] << endl;
}

void print(string cmd, output_t<int> res)
{
    if (res.status() == StatusType::SUCCESS)
    {
        cout << cmd << ": " << StatusTypeStr[(int)res.status()] << ", " << res.ans() << endl;
    }
    else
    {
        cout << cmd << ": " << StatusTypeStr[(int)res.status()] << endl;
    }
}

TEST_CASE("Insert and remove team")
{
    SECTION("simple insert team")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        delete obj;
    }

    SECTION("insert team with negative id")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(-1, 2);
        REQUIRE(res == StatusType::INVALID_INPUT);
        delete obj;
    }

    SECTION("insert team with negative points")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, -2);
        REQUIRE(res == StatusType::INVALID_INPUT);
        delete obj;
    }

    SECTION("insert team with zero points")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 0);
        REQUIRE(res == StatusType::SUCCESS);
        delete obj;
    }

    SECTION("insert team with 0 id")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(0, 5);
        REQUIRE(res == StatusType::INVALID_INPUT);
        delete obj;
    }

    SECTION("insert team with 0 id and 0 points")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(0, 0);
        REQUIRE(res == StatusType::INVALID_INPUT);
        delete obj;
    }

    SECTION("insert team that exists")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(1, 5);
        REQUIRE(res == StatusType::FAILURE);
        delete obj;
    }

    SECTION("simple remove team")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->remove_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        delete obj;
    }

    SECTION("remove team that doesn't exist")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->remove_team(1);
        REQUIRE(res == StatusType::FAILURE);
        delete obj;
    }

    SECTION("remove team twice")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->remove_team(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->remove_team(1);
        REQUIRE(res == StatusType::FAILURE);
        delete obj;
    }

    SECTION("remove team with negative id")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->remove_team(-1);
        REQUIRE(res == StatusType::INVALID_INPUT);
        delete obj;
    }

    SECTION("remove team with 0 id")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->remove_team(0);
        REQUIRE(res == StatusType::INVALID_INPUT);
        delete obj;
    }
}

TEST_CASE("add and remove player")
{

    SECTION("simple add player")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1, 1, 3, 3, 3, false);
        REQUIRE(res == StatusType::SUCCESS);
        delete obj;
    }

    SECTION("simple add goal keeper player")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(2, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1, 2, 3, 3, 3, true);
        REQUIRE(res == StatusType::SUCCESS);
        delete obj;
    }

    SECTION("add player with negative id")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(2, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(-1, 2, 3, 3, 3, true);
        REQUIRE(res == StatusType::INVALID_INPUT);
        delete obj;
    }

    SECTION("add player with negative team id")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(2, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1, -2, 3, 3, 3, true);
        REQUIRE(res == StatusType::INVALID_INPUT);
        delete obj;
    }

    SECTION("add player with negative games")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(2, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1, 2, -3, 3, 3, true);
        REQUIRE(res == StatusType::INVALID_INPUT);
        delete obj;
    }

    SECTION("add player with 0 id")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(2, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(0, 2, 3, 3, 3, true);
        REQUIRE(res == StatusType::INVALID_INPUT);
        delete obj;
    }

    SECTION("add player with 0 team id")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1, 0, 3, 3, 3, true);
        REQUIRE(res == StatusType::INVALID_INPUT);
        delete obj;
    }

    SECTION("add player with negative cards")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1, 2, 3, 3, -3, true);
        REQUIRE(res == StatusType::INVALID_INPUT);
        delete obj;
    }

    SECTION("add player with 0 games and positive goals")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1, 2, 0, 3, 0, true);
        REQUIRE(res == StatusType::INVALID_INPUT);
        delete obj;
    }

    SECTION("add player with 0 games and positive cards")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1, 2, 0, 0, 3, true);
        REQUIRE(res == StatusType::INVALID_INPUT);
        delete obj;
    }

    SECTION("add player with 0 games and positive goals and cards")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1, 2, 0, 3, 3, true);
        REQUIRE(res == StatusType::INVALID_INPUT);
        delete obj;
    }

    SECTION("add player with 0 id and 0 team id")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(0, 0, 3, 3, 3, true);
        REQUIRE(res == StatusType::INVALID_INPUT);
        delete obj;
    }

    SECTION("add player with many zeroes")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(0, 2, 0, 0, 0, true);
        REQUIRE(res == StatusType::INVALID_INPUT);
        delete obj;
    }

    SECTION("add player with zero all")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(0, 0, 0, 0, 0, true);
        REQUIRE(res == StatusType::INVALID_INPUT);
        delete obj;
    }

    SECTION("add player that exists")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1, 1, 3, 3, 3, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1, 1, 3, 3, 3, true);
        REQUIRE(res == StatusType::FAILURE);
        delete obj;
    }

    SECTION("add player with team that doesn't exist")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1, 1, 3, 3, 3, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(4, 4, 4, 4, 4, true);
        REQUIRE(res == StatusType::FAILURE);
        delete obj;
    }

    SECTION("add teams and players - segel test")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 10000);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(2, 20000);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(3, 30000);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(4, 40000);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1001, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1003, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 1, 10, 0, 2, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1005, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1006, 1, 10, 4, 3, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1007, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1008, 1, 10, 0, 0, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1009, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1010, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1011, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1012, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->add_player(2001, 2, 20, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2002, 2, 20, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2003, 2, 20, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2004, 2, 20, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2005, 2, 20, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2006, 2, 20, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2007, 2, 20, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2008, 2, 20, 6, 4, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2009, 2, 20, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2010, 2, 0, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2011, 2, 20, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->add_player(3001, 3, 30, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3002, 3, 30, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3003, 3, 30, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3004, 3, 30, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3005, 3, 30, 2, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3006, 3, 30, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3007, 3, 30, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3008, 3, 30, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3009, 3, 30, 0, 2, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3010, 3, 30, 0, 0, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3011, 3, 30, 0, 0, true);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->add_player(4001, 4, 2, 1, 2, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(4002, 4, 2, 2, 2, false);
        REQUIRE(res == StatusType::SUCCESS);

        delete obj;
    }

    SECTION("simple remove player")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1, 1, 3, 3, 3, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->remove_player(1);
        REQUIRE(res == StatusType::SUCCESS);
        delete obj;
    }

    SECTION("remove player that doesn't exist")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->remove_player(1);
        REQUIRE(res == StatusType::FAILURE);
        delete obj;
    }

    SECTION("remove player twice")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1, 1, 3, 3, 3, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->remove_player(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->remove_player(1);
        REQUIRE(res == StatusType::FAILURE);
        delete obj;
    }

    SECTION("remove player with negative id")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->remove_player(-1);
        REQUIRE(res == StatusType::INVALID_INPUT);
        delete obj;
    }

    SECTION("remove player with 0 id")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->remove_player(0);
        REQUIRE(res == StatusType::INVALID_INPUT);
        delete obj;
    }

    SECTION("add teams and players - segel test - remove at random stages")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 10000);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(2, 20000);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(3, 30000);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(4, 40000);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1001, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1003, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 1, 10, 0, 2, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1005, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1006, 1, 10, 4, 3, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1007, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->remove_player(1007);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->remove_player(1002);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1008, 1, 10, 0, 0, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1009, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1010, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1011, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->remove_player(1001);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1012, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->add_player(2001, 2, 20, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2002, 2, 20, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2003, 2, 20, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2004, 2, 20, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2005, 2, 20, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->remove_player(1011);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2006, 2, 20, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2007, 2, 20, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2008, 2, 20, 6, 4, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2009, 2, 20, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->remove_player(2001);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2010, 2, 0, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2011, 2, 20, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->remove_player(2010);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->add_player(3001, 3, 30, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3002, 3, 30, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3003, 3, 30, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3004, 3, 30, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3005, 3, 30, 2, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3006, 3, 30, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3007, 3, 30, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3008, 3, 30, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3009, 3, 30, 0, 2, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3010, 3, 30, 0, 0, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3011, 3, 30, 0, 0, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->remove_player(3011);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->remove_player(3008);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->remove_player(3002);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->remove_player(3010);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->remove_player(3009);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->remove_player(3005);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->remove_player(3004);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->remove_player(3006);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->remove_player(3007);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->remove_player(3001);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->remove_player(3003);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->add_player(4001, 4, 2, 1, 2, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(4002, 4, 2, 2, 2, false);
        REQUIRE(res == StatusType::SUCCESS);

        delete obj;
    }
}

TEST_CASE("update player stats")
{
    SECTION("simple update player stats")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1, 1, 3, 3, 3, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->update_player_stats(1, 1, 1, 1);
        REQUIRE(res == StatusType::SUCCESS);
        delete obj;
    }

    SECTION("update player stats with negative id")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->update_player_stats(-1, 1, 1, 1);
        REQUIRE(res == StatusType::INVALID_INPUT);
        delete obj;
    }

    SECTION("update player stats with 0 id")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->update_player_stats(0, 1, 1, 1);
        REQUIRE(res == StatusType::INVALID_INPUT);
        delete obj;
    }

    SECTION("update player stats with negative games")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->update_player_stats(1, -1, 1, 1);
        REQUIRE(res == StatusType::INVALID_INPUT);
        delete obj;
    }

    SECTION("update player stats with negative goals")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->update_player_stats(1, 1, -1, 1);
        REQUIRE(res == StatusType::INVALID_INPUT);
        delete obj;
    }

    SECTION("update player stats with negative cards")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->update_player_stats(1, 1, 1, -1);
        REQUIRE(res == StatusType::INVALID_INPUT);
        delete obj;
    }

    SECTION("update player stats of a player that doesn't exist")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->update_player_stats(1, 1, 1, 1);
        REQUIRE(res == StatusType::FAILURE);
        delete obj;
    }

    SECTION("update player stats of a player that was removed")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1, 1, 3, 3, 3, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->remove_player(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->update_player_stats(1, 1, 1, 1);
        REQUIRE(res == StatusType::FAILURE);
        delete obj;
    }

    SECTION("update player stats of a player that was removed and added again")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1, 1, 3, 3, 3, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->remove_player(1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1, 1, 3, 3, 3, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->update_player_stats(1, 1, 1, 1);
        REQUIRE(res == StatusType::SUCCESS);
        delete obj;
    }

    SECTION("update twice player stats")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1, 1, 3, 3, 3, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->update_player_stats(1, 1, 1, 1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->update_player_stats(1, 1, 1, 1);
        REQUIRE(res == StatusType::SUCCESS);
        delete obj;
    }

    SECTION("add teams and players - segel test")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 10000);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(2, 20000);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(3, 30000);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(4, 40000);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1001, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1003, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 1, 10, 0, 2, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1005, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1006, 1, 10, 4, 3, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1007, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1008, 1, 10, 0, 0, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1009, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1010, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1011, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1012, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->add_player(2001, 2, 20, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2002, 2, 20, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2003, 2, 20, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2004, 2, 20, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2005, 2, 20, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2006, 2, 20, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2007, 2, 20, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2008, 2, 20, 6, 4, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2009, 2, 20, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2010, 2, 0, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2011, 2, 20, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->add_player(3001, 3, 30, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3002, 3, 30, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3003, 3, 30, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3004, 3, 30, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3005, 3, 30, 2, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3006, 3, 30, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3007, 3, 30, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3008, 3, 30, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3009, 3, 30, 0, 2, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3010, 3, 30, 0, 0, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3011, 3, 30, 0, 0, true);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->add_player(4001, 4, 2, 1, 2, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(4002, 4, 2, 2, 2, false);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->update_player_stats(3001, 2, 1, 1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->update_player_stats(3011, 2, 1, 1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->update_player_stats(1001, 2, 1, 1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->update_player_stats(4001, 2, 1, 1);
        REQUIRE(res == StatusType::SUCCESS);
        // play_match 2 3 play_match 1 2 get_num_played_games 2003 get_team_points 3 unite_teams 1 2 2 get_top_scorer - 1 get_all_players_count 3 get_all_players 4 get_closest_player 2008 2 knockout_winner 0 3 remove_team 2 remove_player 3008

        delete obj;
    }
}

TEST_CASE("get num played games")
{
    SECTION("simple get played")
    {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1, 3);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1001, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1, 0, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn = obj->get_num_played_games(1001);
        REQUIRE(resn.status() == StatusType::SUCCESS);
        REQUIRE(resn.ans() == 10);

        delete obj;
    }

    SECTION("simple get played")
    {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1, 3);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1001, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1, 0, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn = obj->get_num_played_games(1002);
        REQUIRE(resn.status() == StatusType::SUCCESS);
        REQUIRE(resn.ans() == 0);

        delete obj;
    }

    SECTION("get num played for non exist player")
    {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1, 3);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1001, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1, 0, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn = obj->get_num_played_games(1003);
        REQUIRE(resn.status() == StatusType::FAILURE);

        delete obj;
    }

    SECTION("get num played for non exist player2")
    {
        world_cup_t *obj = new world_cup_t();
        output_t<int> resn = obj->get_num_played_games(1003);
        REQUIRE(resn.status() == StatusType::FAILURE);

        delete obj;
    }

    SECTION("get_num_played for negative player id")
    {
        world_cup_t *obj = new world_cup_t();
        output_t<int> resn = obj->get_num_played_games(-1);
        REQUIRE(resn.status() == StatusType::INVALID_INPUT);

        delete obj;
    }

    SECTION("get_num_played for 0 player id")
    {
        world_cup_t *obj = new world_cup_t();
        output_t<int> resn = obj->get_num_played_games(0);
        REQUIRE(resn.status() == StatusType::INVALID_INPUT);

        delete obj;
    }

    SECTION("segel test")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 10000);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(2, 20000);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(3, 30000);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(4, 40000);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1001, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);

        output_t<int> resn1 = obj->get_num_played_games(1002);
        REQUIRE(resn1.status() == StatusType::SUCCESS);
        REQUIRE(resn1.ans() == 10);

        res = obj->add_player(1003, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 1, 10, 0, 2, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1005, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1006, 1, 10, 4, 3, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1007, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);

        output_t<int> resn2 = obj->get_num_played_games(1006);
        REQUIRE(resn2.status() == StatusType::SUCCESS);
        REQUIRE(resn2.ans() == 10);

        res = obj->add_player(1008, 1, 10, 0, 0, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1009, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1010, 1, 10, 0, 0, false);

        output_t<int> resn3 = obj->get_num_played_games(1010);
        REQUIRE(resn3.status() == StatusType::SUCCESS);
        REQUIRE(resn3.ans() == 10);

        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1011, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1012, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->add_player(2001, 2, 20, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2002, 2, 20, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2003, 2, 20, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2004, 2, 20, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2005, 2, 20, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2006, 2, 20, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2007, 2, 20, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2008, 2, 20, 6, 4, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2009, 2, 20, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2010, 2, 0, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2011, 2, 20, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->add_player(3001, 3, 30, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3002, 3, 30, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3003, 3, 30, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3004, 3, 30, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3005, 3, 30, 2, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3006, 3, 30, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3007, 3, 30, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3008, 3, 30, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3009, 3, 30, 0, 2, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3010, 3, 30, 0, 0, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3011, 3, 30, 0, 0, true);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->add_player(4001, 4, 2, 1, 2, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(4002, 4, 2, 2, 2, false);
        REQUIRE(res == StatusType::SUCCESS);

        output_t<int> resn4 = obj->get_num_played_games(3001);
        REQUIRE(resn4.status() == StatusType::SUCCESS);
        REQUIRE(resn4.ans() == 30);

        output_t<int> resn5 = obj->get_num_played_games(3011);
        REQUIRE(resn5.status() == StatusType::SUCCESS);
        REQUIRE(resn5.ans() == 30);

        output_t<int> resn6 = obj->get_num_played_games(1001);
        REQUIRE(resn6.status() == StatusType::SUCCESS);
        REQUIRE(resn6.ans() == 10);

        output_t<int> resn7 = obj->get_num_played_games(4001);
        REQUIRE(resn7.status() == StatusType::SUCCESS);
        REQUIRE(resn7.ans() == 2);

        res = obj->update_player_stats(3001, 2, 1, 1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->update_player_stats(3011, 2, 1, 1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->update_player_stats(1001, 2, 1, 1);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->update_player_stats(4001, 2, 1, 1);
        REQUIRE(res == StatusType::SUCCESS);

        output_t<int> resn8 = obj->get_num_played_games(3001);
        REQUIRE(resn8.status() == StatusType::SUCCESS);
        REQUIRE(resn8.ans() == 32);

        output_t<int> resn9 = obj->get_num_played_games(3011);
        REQUIRE(resn9.status() == StatusType::SUCCESS);
        REQUIRE(resn9.ans() == 32);

        output_t<int> resn10 = obj->get_num_played_games(1001);
        REQUIRE(resn10.status() == StatusType::SUCCESS);
        REQUIRE(resn10.ans() == 12);

        output_t<int> resn11 = obj->get_num_played_games(4001);
        REQUIRE(resn11.status() == StatusType::SUCCESS);
        REQUIRE(resn11.ans() == 4);

        delete obj;
    }
}

TEST_CASE("get team points")
{
    SECTION("simple get_team_points")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn1 = obj->get_team_points(1);
        REQUIRE(resn1.status() == StatusType::SUCCESS);
        REQUIRE(resn1.ans() == 2);

        delete obj;
    }

    SECTION("get_team_points negative teamid")
    {
        world_cup_t *obj = new world_cup_t();
        output_t<int> resn1 = obj->get_team_points(-6);
        REQUIRE(resn1.status() == StatusType::INVALID_INPUT);

        delete obj;
    }

    SECTION("get_team_points 0 teamid")
    {
        world_cup_t *obj = new world_cup_t();
        output_t<int> resn1 = obj->get_team_points(0);
        REQUIRE(resn1.status() == StatusType::INVALID_INPUT);

        delete obj;
    }

    SECTION("get_team_points no team id")
    {
        world_cup_t *obj = new world_cup_t();
        output_t<int> resn1 = obj->get_team_points(1);
        REQUIRE(resn1.status() == StatusType::FAILURE);

        delete obj;
    }

    SECTION("get_team_points 2 teams")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(2, 3);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn1 = obj->get_team_points(1);
        REQUIRE(resn1.status() == StatusType::SUCCESS);
        REQUIRE(resn1.ans() == 2);
        output_t<int> resn2 = obj->get_team_points(2);
        REQUIRE(resn2.status() == StatusType::SUCCESS);
        REQUIRE(resn2.ans() == 3);

        delete obj;
    }

    SECTION("get_team_points with add player")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1001, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn1 = obj->get_team_points(1);
        REQUIRE(resn1.status() == StatusType::SUCCESS);
        REQUIRE(resn1.ans() == 2);

        delete obj;
    }

    SECTION("get_team_points with 10 teams")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(2, 3);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(3, 4);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(4, 5);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(5, 6);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(6, 7);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(7, 8);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(8, 9);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(9, 10);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(10, 11);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn1 = obj->get_team_points(1);
        REQUIRE(resn1.status() == StatusType::SUCCESS);
        REQUIRE(resn1.ans() == 2);
        output_t<int> resn2 = obj->get_team_points(2);
        REQUIRE(resn2.status() == StatusType::SUCCESS);
        REQUIRE(resn2.ans() == 3);
        output_t<int> resn3 = obj->get_team_points(3);
        REQUIRE(resn3.status() == StatusType::SUCCESS);
        REQUIRE(resn3.ans() == 4);
        output_t<int> resn4 = obj->get_team_points(4);
        REQUIRE(resn4.status() == StatusType::SUCCESS);
        REQUIRE(resn4.ans() == 5);
        output_t<int> resn5 = obj->get_team_points(5);
        REQUIRE(resn5.status() == StatusType::SUCCESS);
        REQUIRE(resn5.ans() == 6);
        output_t<int> resn6 = obj->get_team_points(6);
        REQUIRE(resn6.status() == StatusType::SUCCESS);
        REQUIRE(resn6.ans() == 7);
        output_t<int> resn7 = obj->get_team_points(7);
        REQUIRE(resn7.status() == StatusType::SUCCESS);
        REQUIRE(resn7.ans() == 8);
        output_t<int> resn8 = obj->get_team_points(8);
        REQUIRE(resn8.status() == StatusType::SUCCESS);
        REQUIRE(resn8.ans() == 9);
        output_t<int> resn9 = obj->get_team_points(9);
        REQUIRE(resn9.status() == StatusType::SUCCESS);
        REQUIRE(resn9.ans() == 10);
        output_t<int> resn10 = obj->get_team_points(10);
        REQUIRE(resn10.status() == StatusType::SUCCESS);
        REQUIRE(resn10.ans() == 11);

        delete obj;
    }
}

TEST_CASE("get_top_scorer")
{
    SECTION("simple get_top_scorer in specific team")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1001, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn1 = obj->get_top_scorer(1);
        REQUIRE(resn1.status() == StatusType::SUCCESS);
        REQUIRE(resn1.ans() == 1001);

        delete obj;
    }

    SECTION("get_top_scorer zero team")
    {
        world_cup_t *obj = new world_cup_t();
        output_t<int> resn1 = obj->get_top_scorer(0);
        REQUIRE(resn1.status() == StatusType::INVALID_INPUT);

        delete obj;
    }

    SECTION("get_top_scorer not exist team")
    {
        world_cup_t *obj = new world_cup_t();
        output_t<int> resn1 = obj->get_top_scorer(1);
        REQUIRE(resn1.status() == StatusType::FAILURE);

        delete obj;
    }

    SECTION("get_top_scorer in empty team")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn1 = obj->get_top_scorer(1);
        REQUIRE(resn1.status() == StatusType::FAILURE);

        delete obj;
    }

    SECTION("get_top_scorer in empy all")
    {
        world_cup_t *obj = new world_cup_t();
        output_t<int> resn1 = obj->get_top_scorer(-1);
        REQUIRE(resn1.status() == StatusType::FAILURE);

        delete obj;
    }

    SECTION("get_top_scorer 1 team 5 players")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1001, 1, 10, 15, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1, 10, 20, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1003, 1, 10, 3, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 1, 10, 33, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1005, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn1 = obj->get_top_scorer(1);
        REQUIRE(resn1.status() == StatusType::SUCCESS);
        REQUIRE(resn1.ans() == 1004);

        delete obj;
    }

    SECTION("get_top_scorer from all 5 players")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1001, 1, 10, 15, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1, 10, 33, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1003, 1, 10, 3, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 1, 10, 20, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1005, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn1 = obj->get_top_scorer(-10);
        REQUIRE(resn1.status() == StatusType::SUCCESS);
        REQUIRE(resn1.ans() == 1002);

        delete obj;
    }

    SECTION("get_top_scorer 1 team 5 players tie on goals")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1001, 1, 10, 15, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1, 10, 33, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1003, 1, 10, 3, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 1, 10, 33, 6, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1005, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn1 = obj->get_top_scorer(1);
        REQUIRE(resn1.status() == StatusType::SUCCESS);
        REQUIRE(resn1.ans() == 1002);

        delete obj;
    }

    SECTION("get_top_scorer 1 team 5 players tie on goals2")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1001, 1, 10, 15, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1, 10, 33, 4, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1003, 1, 10, 3, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 1, 10, 33, 2, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1005, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn1 = obj->get_top_scorer(1);
        REQUIRE(resn1.status() == StatusType::SUCCESS);
        REQUIRE(resn1.ans() == 1004);

        delete obj;
    }

    SECTION("get_top_scorer from all 5 players tie on goals")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1001, 1, 10, 15, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1, 10, 33, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1003, 1, 10, 33, 2, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1006, 1, 10, 3, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 1, 10, 33, 5, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1005, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn1 = obj->get_top_scorer(-8);
        REQUIRE(resn1.status() == StatusType::SUCCESS);
        REQUIRE(resn1.ans() == 1002);

        delete obj;
    }

    SECTION("get_top_scorer 1 team 5 players tie on goals and cards")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1001, 1, 10, 15, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1, 10, 33, 5, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1003, 1, 10, 3, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 1, 10, 33, 5, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1005, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn1 = obj->get_top_scorer(1);
        REQUIRE(resn1.status() == StatusType::SUCCESS);
        REQUIRE(resn1.ans() == 1004);

        delete obj;
    }

    SECTION("get_top_scorer 5 teams 0 players")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(2, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(3, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(4, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(5, 2);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn1 = obj->get_top_scorer(1);
        REQUIRE(resn1.status() == StatusType::FAILURE);

        delete obj;
    }

    SECTION("get_top_scorer 2 teams 5 players each")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(2, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1001, 1, 10, 15, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1, 10, 36, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1003, 1, 10, 3, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 1, 10, 33, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1005, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->add_player(1006, 2, 10, 15, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1007, 2, 10, 33, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1008, 2, 10, 3, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1009, 2, 10, 33, 3, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1010, 2, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn1 = obj->get_top_scorer(1);
        REQUIRE(resn1.status() == StatusType::SUCCESS);
        REQUIRE(resn1.ans() == 1002);
        output_t<int> resn2 = obj->get_top_scorer(2);
        REQUIRE(resn2.status() == StatusType::SUCCESS);
        REQUIRE(resn2.ans() == 1007);

        output_t<int> resn3 = obj->get_top_scorer(-1);
        REQUIRE(resn3.status() == StatusType::SUCCESS);
        REQUIRE(resn3.ans() == 1002);

        delete obj;
    }

    SECTION("long one")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(2, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1001, 1, 10, 15, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1, 10, 36, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1003, 1, 10, 3, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 1, 10, 33, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1005, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->add_player(1006, 2, 10, 15, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1007, 2, 10, 38, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1008, 2, 10, 3, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1009, 2, 10, 33, 3, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1010, 2, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn1 = obj->get_top_scorer(1);
        REQUIRE(resn1.status() == StatusType::SUCCESS);
        REQUIRE(resn1.ans() == 1002);
        output_t<int> resn2 = obj->get_top_scorer(2);
        REQUIRE(resn2.status() == StatusType::SUCCESS);
        REQUIRE(resn2.ans() == 1007);

        output_t<int> resn3 = obj->get_top_scorer(-1);
        REQUIRE(resn3.status() == StatusType::SUCCESS);
        REQUIRE(resn3.ans() == 1007);

        res = obj->remove_player(1007);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn4 = obj->get_top_scorer(-1);
        REQUIRE(resn4.status() == StatusType::SUCCESS);
        REQUIRE(resn4.ans() == 1002);

        res = obj->add_player(1007, 2, 10, 38, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn5 = obj->get_top_scorer(-1);
        REQUIRE(resn5.status() == StatusType::SUCCESS);
        REQUIRE(resn5.ans() == 1007);

        res = obj->update_player_stats(1001, 23, 50, 0);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn6 = obj->get_top_scorer(-1);
        REQUIRE(resn6.status() == StatusType::SUCCESS);
        REQUIRE(resn6.ans() == 1001);
        output_t<int> resn7 = obj->get_top_scorer(1);
        REQUIRE(resn7.status() == StatusType::SUCCESS);
        REQUIRE(resn7.ans() == 1001);
        output_t<int> resn8 = obj->get_top_scorer(2);
        REQUIRE(resn8.status() == StatusType::SUCCESS);
        REQUIRE(resn8.ans() == 1007);

        delete obj;
    }
}

TEST_CASE("get_all_players_count")
{
    SECTION("simple get_all_players_count")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(2, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1001, 1, 10, 15, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn1 = obj->get_all_players_count(1);
        REQUIRE(resn1.status() == StatusType::SUCCESS);
        REQUIRE(resn1.ans() == 1);
        output_t<int> resn2 = obj->get_all_players_count(2);
        REQUIRE(resn2.status() == StatusType::SUCCESS);
        REQUIRE(resn2.ans() == 0);
        output_t<int> resn3 = obj->get_all_players_count(-1);
        REQUIRE(resn3.status() == StatusType::SUCCESS);
        REQUIRE(resn3.ans() == 1);
        delete obj;
    }

    SECTION("get_all_players_count big")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(2, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1001, 1, 10, 15, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1, 10, 36, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1003, 1, 10, 3, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 1, 10, 33, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1005, 1, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->add_player(1006, 2, 10, 15, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1007, 2, 10, 38, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1008, 2, 10, 3, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1009, 2, 10, 33, 3, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1010, 2, 10, 0, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn1 = obj->get_all_players_count(1);
        REQUIRE(resn1.status() == StatusType::SUCCESS);
        REQUIRE(resn1.ans() == 5);
        output_t<int> resn2 = obj->get_all_players_count(2);
        REQUIRE(resn2.status() == StatusType::SUCCESS);
        REQUIRE(resn2.ans() == 5);
        output_t<int> resn3 = obj->get_all_players_count(-1);
        REQUIRE(resn3.status() == StatusType::SUCCESS);
        REQUIRE(resn3.ans() == 10);

        res = obj->remove_player(1007);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn4 = obj->get_all_players_count(-1);
        REQUIRE(resn4.status() == StatusType::SUCCESS);
        REQUIRE(resn4.ans() == 9);
        output_t<int> resn5 = obj->get_all_players_count(2);
        REQUIRE(resn5.status() == StatusType::SUCCESS);
        REQUIRE(resn5.ans() == 4);

        delete obj;
    }

    SECTION("get_all_players_count 0 teamId")
    {
        world_cup_t *obj = new world_cup_t();
        output_t<int> resn1 = obj->get_all_players_count(0);
        REQUIRE(resn1.status() == StatusType::INVALID_INPUT);

        delete obj;
    }

    SECTION("get_all_players_count 0 teamId")
    {
        world_cup_t *obj = new world_cup_t();
        output_t<int> resn1 = obj->get_all_players_count(5);
        REQUIRE(resn1.status() == StatusType::FAILURE);

        delete obj;
    }
}

TEST_CASE("get_closest_player")
{
    SECTION("get_closest_player one player")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(2, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1001, 1, 10, 15, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn1 = obj->get_closest_player(1001, 1);
        REQUIRE(resn1.status() == StatusType::FAILURE);
        delete obj;
    }

    SECTION("get_closest_player no player")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn1 = obj->get_closest_player(1001, 1);
        REQUIRE(resn1.status() == StatusType::FAILURE);
        delete obj;
    }

    SECTION("get_closest_player invalid input")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(2, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1001, 1, 10, 15, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn1 = obj->get_closest_player(1001, 0);
        REQUIRE(resn1.status() == StatusType::INVALID_INPUT);
        output_t<int> resn3 = obj->get_closest_player(1001, -1);
        REQUIRE(resn3.status() == StatusType::INVALID_INPUT);
        output_t<int> resn4 = obj->get_closest_player(-1, 5);
        REQUIRE(resn4.status() == StatusType::INVALID_INPUT);
        output_t<int> resn5 = obj->get_closest_player(0, 2);
        REQUIRE(resn5.status() == StatusType::INVALID_INPUT);
        delete obj;
    }

    SECTION("get_closest_player 2 players")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1001, 1, 10, 15, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1, 10, 36, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn1 = obj->get_closest_player(1001, 1);
        REQUIRE(resn1.status() == StatusType::SUCCESS);
        REQUIRE(resn1.ans() == 1002);
        output_t<int> resn2 = obj->get_closest_player(1002, 1);
        REQUIRE(resn2.status() == StatusType::SUCCESS);
        REQUIRE(resn2.ans() == 1001);
    }

    SECTION("get_closest_player - all failure or invalid_input")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1001, 1, 10, 15, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1, 10, 15, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1003, 1, 10, 15, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 1, 10, 15, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1005, 1, 10, 15, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1061, 1, 10, 15, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1032, 1, 10, 15, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1033, 1, 10, 15, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1054, 1, 10, 15, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1065, 1, 10, 15, 0, false);
        REQUIRE(res == StatusType::SUCCESS);

        output_t<int> resn1 = obj->get_closest_player(55, 1);
        REQUIRE(resn1.status() == StatusType::FAILURE);
        output_t<int> resn2 = obj->get_closest_player(1001, 60);
        REQUIRE(resn2.status() == StatusType::FAILURE);

        output_t<int> resn3 = obj->get_closest_player(-1, 1);
        REQUIRE(resn3.status() == StatusType::INVALID_INPUT);
        output_t<int> resn4 = obj->get_closest_player(1001, -1);
        REQUIRE(resn4.status() == StatusType::INVALID_INPUT);
        output_t<int> resn5 = obj->get_closest_player(0, 1);
        REQUIRE(resn5.status() == StatusType::INVALID_INPUT);
        output_t<int> resn6 = obj->get_closest_player(1001, 0);
        REQUIRE(resn6.status() == StatusType::INVALID_INPUT);
        delete obj;
    }

    SECTION("segel example")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(2, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(3, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(4, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(5, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(6, 2);
        REQUIRE(res == StatusType::SUCCESS);

        // add players
        res = obj->add_player(21, 1, 10, 1, 20, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(25, 1, 10, 1, 20, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(3, 1, 10, 1, 5, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(4, 4, 10, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(5, 5, 10, 2, 5, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(6, 6, 10, 2, 4, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(24, 1, 10, 2, 3, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(7, 5, 10, 2, 2, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(8, 6, 10, 2, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(9, 3, 10, 5, 30, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(10, 2, 10, 5, 29, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(11, 2, 10, 5, 28, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(12, 2, 10, 5, 27, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(51, 5, 10, 6, 40, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(52, 6, 10, 6, 40, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(53, 3, 10, 6, 40, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(54, 2, 10, 6, 10, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(60, 2, 10, 6, 5, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(70, 2, 10, 6, 4, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(100, 2, 10, 8, 6, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(80, 2, 10, 10, 7, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(90, 2, 10, 10, 7, false);
        REQUIRE(res == StatusType::SUCCESS);

        // check all closest
        output_t<int> resn1 = obj->get_closest_player(21, 1);
        REQUIRE(resn1.status() == StatusType::SUCCESS);
        REQUIRE(resn1.ans() == 25);
        output_t<int> resn2 = obj->get_closest_player(25, 1);
        REQUIRE(resn2.status() == StatusType::SUCCESS);
        REQUIRE(resn2.ans() == 21);
        output_t<int> resn3 = obj->get_closest_player(3, 1);
        REQUIRE(resn3.status() == StatusType::SUCCESS);
        REQUIRE(resn3.ans() == 4);
        output_t<int> resn4 = obj->get_closest_player(4, 4);
        REQUIRE(resn4.status() == StatusType::SUCCESS);
        REQUIRE(resn4.ans() == 3);
        output_t<int> resn5 = obj->get_closest_player(5, 5);
        REQUIRE(resn5.status() == StatusType::SUCCESS);
        REQUIRE(resn5.ans() == 6);
        output_t<int> resn6 = obj->get_closest_player(6, 6);
        REQUIRE(resn6.status() == StatusType::SUCCESS);
        REQUIRE(resn6.ans() == 5);
        output_t<int> resn7 = obj->get_closest_player(24, 1);
        REQUIRE(resn7.status() == StatusType::SUCCESS);
        REQUIRE(resn7.ans() == 7);
        output_t<int> resn8 = obj->get_closest_player(7, 5);
        REQUIRE(resn8.status() == StatusType::SUCCESS);
        REQUIRE(resn8.ans() == 8);
        output_t<int> resn9 = obj->get_closest_player(8, 6);
        REQUIRE(resn9.status() == StatusType::SUCCESS);
        REQUIRE(resn9.ans() == 7);
        output_t<int> resn10 = obj->get_closest_player(9, 3);
        REQUIRE(resn10.status() == StatusType::SUCCESS);
        REQUIRE(resn10.ans() == 10);
        output_t<int> resn11 = obj->get_closest_player(10, 2);
        REQUIRE(resn11.status() == StatusType::SUCCESS);
        REQUIRE(resn11.ans() == 11);
        output_t<int> resn12 = obj->get_closest_player(11, 2);
        REQUIRE(resn12.status() == StatusType::SUCCESS);
        REQUIRE(resn12.ans() == 12);
        output_t<int> resn13 = obj->get_closest_player(12, 2);
        REQUIRE(resn13.status() == StatusType::SUCCESS);
        REQUIRE(resn13.ans() == 11);
        output_t<int> resn14 = obj->get_closest_player(51, 5);
        REQUIRE(resn14.status() == StatusType::SUCCESS);
        REQUIRE(resn14.ans() == 52);
        output_t<int> resn15 = obj->get_closest_player(52, 6);
        REQUIRE(resn15.status() == StatusType::SUCCESS);
        REQUIRE(resn15.ans() == 53);
        output_t<int> resn16 = obj->get_closest_player(53, 3);
        REQUIRE(resn16.status() == StatusType::SUCCESS);
        REQUIRE(resn16.ans() == 52);
        output_t<int> resn17 = obj->get_closest_player(54, 2);
        REQUIRE(resn17.status() == StatusType::SUCCESS);
        REQUIRE(resn17.ans() == 60);
        output_t<int> resn18 = obj->get_closest_player(60, 2);
        REQUIRE(resn18.status() == StatusType::SUCCESS);
        REQUIRE(resn18.ans() == 70);
        output_t<int> resn19 = obj->get_closest_player(70, 2);
        REQUIRE(resn19.status() == StatusType::SUCCESS);
        REQUIRE(resn19.ans() == 60);
        output_t<int> resn20 = obj->get_closest_player(100, 2);
        REQUIRE(resn20.status() == StatusType::SUCCESS);
        REQUIRE(resn20.ans() == 80);
        output_t<int> resn21 = obj->get_closest_player(80, 2);
        REQUIRE(resn21.status() == StatusType::SUCCESS);
        REQUIRE(resn21.ans() == 90);
        output_t<int> resn22 = obj->get_closest_player(90, 2);
        REQUIRE(resn22.status() == StatusType::SUCCESS);
        REQUIRE(resn22.ans() == 80);

        delete obj;
    }
}

TEST_CASE("play_match")
{
    SECTION("simple play_match")
    {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(2, 2);
        REQUIRE(res == StatusType::SUCCESS);

        // first team players
        res = obj->add_player(1001, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1003, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1005, 1, 1, 1, 1, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1006, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1007, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1008, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1009, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1010, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1011, 1, 1, 1, 1, true);
        REQUIRE(res == StatusType::SUCCESS);

        // second team players
        res = obj->add_player(2001, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2002, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2003, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2004, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2005, 2, 1, 1, 1, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2006, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2007, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2008, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2009, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2010, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2011, 2, 1, 1, 1, true);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->play_match(1, 2);
        REQUIRE(res == StatusType::SUCCESS);

        delete obj;
    }

    SECTION("play_match invalid input")
    {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->play_match(0, 1);
        REQUIRE(res == StatusType::INVALID_INPUT);
        res = obj->play_match(1, 0);
        REQUIRE(res == StatusType::INVALID_INPUT);
        res = obj->play_match(0, 0);
        REQUIRE(res == StatusType::INVALID_INPUT);
        res = obj->play_match(3, 3);
        REQUIRE(res == StatusType::INVALID_INPUT);

        delete obj;
    }

    SECTION("play_match failure")
    {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->play_match(1, 2);
        REQUIRE(res == StatusType::FAILURE);
        res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->play_match(2, 1);
        REQUIRE(res == StatusType::FAILURE);
        res = obj->add_team(2, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->play_match(1, 2);
        REQUIRE(res == StatusType::FAILURE);
        res = obj->add_player(1001, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2001, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2002, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->play_match(1, 2);
        REQUIRE(res == StatusType::FAILURE);
        res = obj->add_player(1003, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2003, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->play_match(1, 2);
        REQUIRE(res == StatusType::FAILURE);
        res = obj->add_player(1004, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1005, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1006, 1, 1, 1, 1, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2004, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2005, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2006, 2, 1, 1, 1, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->play_match(1, 2);
        REQUIRE(res == StatusType::FAILURE);
        res = obj->add_player(1007, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1008, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1009, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1010, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1011, 1, 1, 1, 1, true);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn = obj->get_all_players_count(1);
        REQUIRE(resn.status() == StatusType::SUCCESS);
        REQUIRE(resn.ans() == 11);
        res = obj->play_match(1, 2);
        REQUIRE(res == StatusType::FAILURE);

        delete obj;
    }

    SECTION("play_match no goal keepers")
    {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(2, 2);
        REQUIRE(res == StatusType::SUCCESS);

        // first team players
        res = obj->add_player(1001, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1003, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1005, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1006, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1007, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1008, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1009, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1010, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1011, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);

        // second team players
        res = obj->add_player(2001, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2002, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2003, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2004, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2005, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2006, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2007, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2008, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2009, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2010, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2011, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->play_match(1, 2);
        REQUIRE(res == StatusType::FAILURE);

        delete obj;
    }

    SECTION("play_match goal keepers only on one")
    {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(2, 2);
        REQUIRE(res == StatusType::SUCCESS);

        // first team players
        res = obj->add_player(1001, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1003, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1005, 1, 1, 1, 1, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1006, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1007, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1008, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1009, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1010, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1011, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);

        // second team players
        res = obj->add_player(2001, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2002, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2003, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2004, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2005, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2006, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2007, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2008, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2009, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2010, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2011, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->play_match(1, 2);
        REQUIRE(res == StatusType::FAILURE);

        delete obj;
    }

    SECTION("play_match start with goal keepers then no then yes")
    {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(2, 2);
        REQUIRE(res == StatusType::SUCCESS);

        // first team players
        res = obj->add_player(1001, 1, 1, 1, 1, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1003, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1005, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1006, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1007, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1008, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1009, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1010, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1011, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);

        // second team players
        res = obj->add_player(2001, 2, 1, 1, 1, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2002, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2003, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2004, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2005, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2006, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2007, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2008, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2009, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2010, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(2011, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->play_match(1, 2);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->remove_player(1001);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->play_match(1, 2);
        REQUIRE(res == StatusType::FAILURE);
        res = obj->add_player(1001, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->play_match(1, 2);
        REQUIRE(res == StatusType::FAILURE);
        res = obj->add_player(1020, 1, 1, 1, 1, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->play_match(1, 2);
        REQUIRE(res == StatusType::SUCCESS);

        delete obj;
    }
}

TEST_CASE("get_all_players")
{
    SECTION("get_all_players invalid input")
    {
        world_cup_t *obj = new world_cup_t();
        int players[4] = {};

        StatusType res = obj->get_all_players(1, nullptr);
        REQUIRE(res == StatusType::INVALID_INPUT);
        res = obj->get_all_players(0, players);
        REQUIRE(res == StatusType::INVALID_INPUT);
        delete obj;
    }

    SECTION("get_all_players failure")
    {
        world_cup_t *obj = new world_cup_t();
        int players[4] = {};

        StatusType res = obj->get_all_players(1, players);
        REQUIRE(res == StatusType::FAILURE);
        res = obj->get_all_players(-1, players);
        REQUIRE(res == StatusType::FAILURE);
        res = obj->add_team(1, 3);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->get_all_players(1, players);
        REQUIRE(res == StatusType::FAILURE);
        delete obj;
    }

    SECTION("get_all_players 1 team all with same grades")
    {
        world_cup_t *obj = new world_cup_t();
        int players[10] = {};

        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1001, 1, 1, 1, 1, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->get_all_players(1, players);
        REQUIRE(res == StatusType::SUCCESS);
        REQUIRE(players[0] == 1001);
        for (int i = 1; i < 10; i++)
        {
            REQUIRE(players[i] == 0);
        }

        res = obj->add_player(1002, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1003, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1005, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1006, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1007, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1008, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1009, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1010, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->get_all_players(1, players);
        REQUIRE(res == StatusType::SUCCESS);
        for (int i = 0; i < 10; i++)
        {
            REQUIRE(players[i] == 1001 + i);
        }
        for (int i = 0; i < 10; i++)
        {
            players[i] = 0;
        }
        res = obj->get_all_players(-1, players);
        REQUIRE(res == StatusType::SUCCESS);
        for (int i = 0; i < 10; i++)
        {
            REQUIRE(players[i] == 1001 + i);
        }
        delete obj;
    }

    SECTION("get_all_players 1 team all with same grades")
    {
        world_cup_t *obj = new world_cup_t();
        int players[10] = {};

        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1001, 1, 1, 10, 1, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->get_all_players(1, players);
        REQUIRE(res == StatusType::SUCCESS);
        REQUIRE(players[0] == 1001);
        for (int i = 1; i < 10; i++)
        {
            REQUIRE(players[i] == 0);
        }

        res = obj->add_player(1002, 1, 1, 9, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1003, 1, 1, 8, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 1, 1, 7, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1005, 1, 1, 6, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1006, 1, 1, 5, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1007, 1, 1, 4, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1008, 1, 1, 3, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1009, 1, 1, 2, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1010, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);

        res = obj->get_all_players(1, players);
        REQUIRE(res == StatusType::SUCCESS);
        for (int i = 0; i < 10; i++)
        {
            REQUIRE(players[i] == 1010 - i);
        }
        for (int i = 0; i < 10; i++)
        {
            players[i] = 0;
        }
        res = obj->get_all_players(-1, players);
        REQUIRE(res == StatusType::SUCCESS);
        for (int i = 0; i < 10; i++)
        {
            REQUIRE(players[i] == 1010 - i);
        }
        delete obj;
    }

    SECTION("get_all_players goals")
    {
        world_cup_t *obj = new world_cup_t();
        int players[10] = {};

        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1001, 1, 1, 5, 2, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1, 1, 3, 4, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1003, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->get_all_players(1, players);
        REQUIRE(res == StatusType::SUCCESS);
        REQUIRE(players[0] == 1003);
        REQUIRE(players[1] == 1002);
        REQUIRE(players[2] == 1001);

        for (int i = 3; i < 10; i++)
        {
            REQUIRE(players[i] == 0);
        }

        delete obj;
    }

    SECTION("get_all_players big")
    {
        world_cup_t *obj = new world_cup_t();
        int players[10] = {};

        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1001, 1, 1, 5, 2, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1, 1, 3, 4, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1003, 1, 1, 2, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 1, 1, 1, 2, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1005, 1, 1, 1, 4, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1006, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1007, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->get_all_players(1, players);
        REQUIRE(res == StatusType::SUCCESS);
        REQUIRE(players[0] == 1005);
        REQUIRE(players[1] == 1004);
        REQUIRE(players[2] == 1006);
        REQUIRE(players[3] == 1007);
        REQUIRE(players[4] == 1003);
        REQUIRE(players[5] == 1002);
        REQUIRE(players[6] == 1001);
        REQUIRE(players[7] == 0);
        REQUIRE(players[8] == 0);
        REQUIRE(players[9] == 0);

        delete obj;
    }
}

TEST_CASE("unite_teams")
{
    SECTION("unite_teams failure")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->unite_teams(1, 2, 1);
        REQUIRE(res == StatusType::FAILURE);

        res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->unite_teams(1, 2, 5);
        REQUIRE(res == StatusType::FAILURE);

        res = obj->add_team(2, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(5, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->unite_teams(1, 2, 5);
        REQUIRE(res == StatusType::FAILURE);

        delete obj;
    }

    SECTION("unite_teams invalid input")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->unite_teams(0, 1, 1);
        REQUIRE(res == StatusType::INVALID_INPUT);
        res = obj->unite_teams(1, 0, 1);
        REQUIRE(res == StatusType::INVALID_INPUT);
        res = obj->unite_teams(1, 2, 0);
        REQUIRE(res == StatusType::INVALID_INPUT);
        res = obj->unite_teams(-1, 1, 1);
        REQUIRE(res == StatusType::INVALID_INPUT);
        res = obj->unite_teams(1, -1, 1);
        REQUIRE(res == StatusType::INVALID_INPUT);
        res = obj->unite_teams(1, 3, -1);
        REQUIRE(res == StatusType::INVALID_INPUT);
        res = obj->unite_teams(1, 1, 1);
        REQUIRE(res == StatusType::INVALID_INPUT);

        delete obj;
    }

    SECTION("unite_teams simple")
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1001, 1, 1, 5, 2, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(2, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 2, 1, 3, 4, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->unite_teams(1, 2, 3);
        REQUIRE(res == StatusType::SUCCESS);
        int players[10] = {};
        res = obj->get_all_players(3, players);
        REQUIRE(res == StatusType::SUCCESS);
        REQUIRE(players[0] == 1002);
        REQUIRE(players[1] == 1001);
        REQUIRE(players[2] == 0);
        REQUIRE(players[3] == 0);
        REQUIRE(players[4] == 0);
        REQUIRE(players[5] == 0);
        REQUIRE(players[6] == 0);
        REQUIRE(players[7] == 0);
        REQUIRE(players[8] == 0);
        REQUIRE(players[9] == 0);

        res = obj->add_team(3, 2);
        REQUIRE(res == StatusType::FAILURE);
        res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(2, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(4, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1001, 3, 1, 5, 2, true);
        REQUIRE(res == StatusType::FAILURE);
        res = obj->add_player(1002, 3, 1, 3, 4, false);
        REQUIRE(res == StatusType::FAILURE);
        res = obj->add_player(1003, 3, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 4, 1, 1, 2, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1005, 4, 1, 1, 4, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1006, 4, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1007, 4, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->unite_teams(3, 4, 5);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(5, 2);
        REQUIRE(res == StatusType::FAILURE);
        res = obj->add_team(3, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(4, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1008, 3, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 3, 1, 1, 1, false);
        REQUIRE(res == StatusType::FAILURE);
        res = obj->add_player(1009, 4, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1005, 4, 1, 1, 1, false);
        REQUIRE(res == StatusType::FAILURE);
        res = obj->unite_teams(3, 4, 3);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(3, 2);
        REQUIRE(res == StatusType::FAILURE);

        res = obj->add_team(4, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1009, 3, 1, 1, 1, false);
        REQUIRE(res == StatusType::FAILURE);

        delete obj;
    }

    SECTION("unite_teams that makes it legal team")
    {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1001, 1, 1, 5, 2, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1, 1, 3, 4, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1003, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 1, 1, 1, 2, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1005, 1, 1, 1, 4, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(2, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1006, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1007, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1008, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1009, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1010, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1011, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1012, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1013, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1014, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1015, 2, 1, 1, 1, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1016, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1017, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn3 = obj->knockout_winner(1, 4);
        REQUIRE(resn3.status() == StatusType::SUCCESS);
        REQUIRE(resn3.ans() == 2);

        res = obj->unite_teams(1, 2, 3);
        REQUIRE(res == StatusType::SUCCESS);

        output_t<int> resn1 = obj->get_all_players_count(3);
        REQUIRE(resn1.status() == StatusType::SUCCESS);
        REQUIRE(resn1.ans() == 17);
        output_t<int> resn2 = obj->knockout_winner(1, 4);
        REQUIRE(resn2.status() == StatusType::SUCCESS);
        REQUIRE(resn2.ans() == 3);

        delete obj;
    }

    SECTION("unite_teams two legal teams")
    {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1001, 1, 1, 5, 2, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1, 1, 3, 4, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1003, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 1, 1, 1, 2, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1005, 1, 1, 1, 4, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1301, 1, 1, 5, 2, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1302, 1, 1, 3, 4, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1303, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1304, 1, 1, 1, 2, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1305, 1, 1, 1, 4, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(101, 1, 1, 5, 2, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(333, 1, 1, 3, 4, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(103, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(6004, 1, 1, 1, 2, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(19005, 1, 1, 1, 4, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(2, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1006, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1007, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1008, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1009, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1010, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1011, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1012, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1013, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1014, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1015, 2, 1, 1, 1, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1016, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1017, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn3 = obj->knockout_winner(1, 4);
        REQUIRE(resn3.status() == StatusType::SUCCESS);
        REQUIRE(resn3.ans() == 2);

        res = obj->unite_teams(1, 2, 3);
        REQUIRE(res == StatusType::SUCCESS);

        output_t<int> resn1 = obj->get_all_players_count(3);
        REQUIRE(resn1.status() == StatusType::SUCCESS);
        REQUIRE(resn1.ans() == 27);
        output_t<int> resn2 = obj->knockout_winner(1, 4);
        REQUIRE(resn2.status() == StatusType::SUCCESS);
        REQUIRE(resn2.ans() == 3);

        delete obj;
    }

    SECTION("unite_teams legal and not legal teams to the not legal")
    {
        world_cup_t *obj = new world_cup_t();

        StatusType res = obj->add_team(1, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1001, 1, 1, 5, 2, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1, 1, 3, 4, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1003, 1, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(2, 2);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1006, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1007, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1008, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1009, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1010, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1011, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1012, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1013, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1014, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1015, 2, 1, 1, 1, true);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1016, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(1017, 2, 1, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        output_t<int> resn3 = obj->knockout_winner(1, 4);
        REQUIRE(resn3.status() == StatusType::SUCCESS);
        REQUIRE(resn3.ans() == 2);

        res = obj->unite_teams(1, 2, 1);
        REQUIRE(res == StatusType::SUCCESS);

        output_t<int> resn1 = obj->get_all_players_count(1);
        REQUIRE(resn1.status() == StatusType::SUCCESS);
        REQUIRE(resn1.ans() == 15);
        output_t<int> resn2 = obj->knockout_winner(1, 4);
        REQUIRE(resn2.status() == StatusType::SUCCESS);
        REQUIRE(resn2.ans() == 1);

        delete obj;
    }
}

TEST_CASE("knockout")
{
    SECTION("ILLIGAL_INPUTS")
    {
        world_cup_t *obj = new world_cup_t();

        output_t<int> res1 = obj->knockout_winner(-1, 0);
        REQUIRE(res1.status() == StatusType::INVALID_INPUT);

        output_t<int> res2 = obj->knockout_winner(-4, -1);
        REQUIRE(res2.status() == StatusType::INVALID_INPUT);

        output_t<int> res3 = obj->knockout_winner(0, -1);
        REQUIRE(res3.status() == StatusType::INVALID_INPUT);

        output_t<int> res4 = obj->knockout_winner(-1, -1);
        REQUIRE(res4.status() == StatusType::INVALID_INPUT);

        output_t<int> res5 = obj->knockout_winner(10, 9);
        REQUIRE(res5.status() == StatusType::INVALID_INPUT);

        output_t<int> res5andahalf = obj->knockout_winner(0, 1);
        REQUIRE(res5andahalf.status() == StatusType::FAILURE);

        StatusType res = obj->add_team(7, 10);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_team(9, 10);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(69, 7, 9, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);

        output_t<int> res6 = obj->knockout_winner(0, 10);
        REQUIRE(res6.status() == StatusType::FAILURE);

        output_t<int> res7 = obj->knockout_winner(7, 7);
        REQUIRE(res7.status() == StatusType::FAILURE);

        output_t<int> res8 = obj->knockout_winner(7, 9);
        REQUIRE(res8.status() == StatusType::FAILURE);

        output_t<int> res9 = obj->knockout_winner(7, 10);
        REQUIRE(res9.status() == StatusType::FAILURE);

        output_t<int> res10 = obj->knockout_winner(6, 9);
        REQUIRE(res10.status() == StatusType::FAILURE);

        output_t<int> res11 = obj->knockout_winner(0, 1);
        REQUIRE(res11.status() == StatusType::FAILURE);

        res = obj->add_player(70, 7, 9, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(71, 7, 9, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(72, 7, 9, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(73, 7, 9, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(74, 7, 9, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(75, 7, 9, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(76, 7, 9, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(77, 7, 9, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(78, 7, 9, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(79, 7, 9, 1, 1, false);
        REQUIRE(res == StatusType::SUCCESS);
        res = obj->add_player(80, 7, 9, 1, 1, true);
        REQUIRE(res == StatusType::SUCCESS);

        output_t<int> res12 = obj->knockout_winner(0, 6);
        REQUIRE(res12.status() == StatusType::FAILURE);

        output_t<int> res13 = obj->knockout_winner(8, 9);
        REQUIRE(res13.status() == StatusType::FAILURE);

        delete obj;
    }

    SECTION("Basic Tournements")
    {
        world_cup_t *obj = new world_cup_t();
        int playerId = 1;
        StatusType res;
        for (int teamId = 1; teamId < 10; teamId += 2)
        {
            res = obj->add_team(teamId, 1000 / ((6 - teamId) * (6 - teamId)));
            REQUIRE(res == StatusType::SUCCESS);

            for (int startingId = playerId; playerId < startingId + 10 + teamId; ++playerId)
            {
                res = obj->add_player(playerId, teamId, 1, playerId, 3, true);
                REQUIRE(res == StatusType::SUCCESS);
            }
            ++playerId;
        }
        // Strengths team1:73 team3:319 team5:1485 team7:1816 team9:1384

        res = obj->add_team(4, 1000000);
        REQUIRE(res == StatusType::SUCCESS);

        output_t<int> res1 = obj->knockout_winner(8, 9);
        REQUIRE(res1.status() == StatusType::SUCCESS);
        REQUIRE(res1.ans() == 9);

        output_t<int> res2 = obj->knockout_winner(1, 1);
        REQUIRE(res2.status() == StatusType::SUCCESS);
        REQUIRE(res2.ans() == 1);

        output_t<int> res3 = obj->knockout_winner(2, 4);
        REQUIRE(res3.status() == StatusType::SUCCESS);
        REQUIRE(res3.ans() == 3);

        output_t<int> res4 = obj->knockout_winner(3, 9);
        REQUIRE(res4.status() == StatusType::SUCCESS);
        REQUIRE(res4.ans() == 7);

        output_t<int> res5 = obj->knockout_winner(2, 8);
        REQUIRE(res5.status() == StatusType::SUCCESS);
        REQUIRE(res5.ans() == 7);

        output_t<int> res6 = obj->knockout_winner(0, 5);
        REQUIRE(res6.status() == StatusType::SUCCESS);
        REQUIRE(res6.ans() == 5);

        output_t<int> res7 = obj->knockout_winner(1, 9);
        REQUIRE(res7.status() == StatusType::SUCCESS);
        REQUIRE(res7.ans() == 7);

        res = obj->add_player(999, 3, 1, 3000, 200, false);
        REQUIRE(res == StatusType::SUCCESS);
        // Strengths team1:73 team3:3119 team5:1485 team7:1816 team9:1384

        output_t<int> res8 = obj->knockout_winner(1, 999);
        REQUIRE(res8.status() == StatusType::SUCCESS);
        REQUIRE(res8.ans() == 7);

        res = obj->add_player(998, 3, 1, 2000, 0, false);
        REQUIRE(res == StatusType::SUCCESS);
        // Strengths team1:73 team3: 5119 team5:1485 team7:1816 team9:1384

        output_t<int> res9 = obj->knockout_winner(0, 13);
        REQUIRE(res9.status() == StatusType::SUCCESS);
        REQUIRE(res9.ans() == 3);

        res = obj->add_player(997, 3, 1, 1, 5001, false);
        REQUIRE(res == StatusType::SUCCESS);
        // Strengths team1:73 team3:119 team5:1485 team7:1816 team9:1384

        output_t<int> res9andahalf = obj->knockout_winner(0, 13);
        REQUIRE(res9andahalf.status() == StatusType::SUCCESS);
        REQUIRE(res9andahalf.ans() == 7);

        res = obj->update_player_stats(79, 1, 10000, 0);
        REQUIRE(res == StatusType::SUCCESS);
        // Strengths team1:73 team3:119 team5:1485 team7:1816 team9:11384

        output_t<int> res10 = obj->knockout_winner(1, 9);
        REQUIRE(res10.status() == StatusType::SUCCESS);

        REQUIRE(res10.ans() == 9);

        delete obj;
    }
}
