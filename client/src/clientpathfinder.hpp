/*
 * =====================================================================================
 *
 *       Filename: clientpathfinder.hpp
 *        Created: 03/28/2017 21:13:11
 *  Last Modified: 07/01/2017 12:17:48
 *
 *    Description: path finding parameters needed:
 *          
 *                  bCheckGround   : true  : will fail if we can't get a path from valid grids
 *                                   false : always return a path which prefers valid grids
 *                  
 *                  bCheckCreature : true  : return path which prefers valid empty grids if one path found
 *                                   false : find the path by ignoring all creatures
 *
 *
 *                  nMaxStep       : 0 / 1 / 2
 *
 *
 *                  1. set bCheckGround can fail a seach
 *                  2. set bCheckCreature won't fail the search
 *
 *        Version: 1.0
 *       Revision: none
 *       Compiler: gcc
 *
 *         Author: ANHONG
 *          Email: anhonghe@gmail.com
 *   Organization: USTC
 *
 * =====================================================================================
 */

#pragma once
#include "pathfinder.hpp"

class ClientPathFinder final: public AStarPathFinder
{
    public:
        ClientPathFinder(bool, bool, int);
       ~ClientPathFinder() = default;
};
