/*
 *  _____  _               ______         _
 *  /  __ \(_)              | ___ \       | |
 *  | /  \/ _   ___   __ _  | |_/ /  ___  | |_
 *  | |    | | / _ \ / _` | | ___ \ / _ \ | __|
 *  | \__/\| ||  __/| (_| | | |_/ /| (_) || |_
 *  \____/|_| \___| \__,_| \____/  \___/  \__|
 *
 *  於陵汐娅群机器人功能的C++实现
 *  Copyright © 2021 星翛-STASWIT
 *
 *  文件：FlagGenerator.cpp
 *  功能：生成随机flag
 *
*/

#include "FlagGenerator.h"

using namespace std;

string flagChar = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

namespace ciea
{
    void Delay(int time)
    {
        clock_t now = clock();
        while(clock() - now < time);
    }

    int numRand(int first, int end)
    {
        mt19937 rand(clock()); //定义随机数生成器
        uniform_int_distribution<int> dist(first, end);
        return dist(rand);
    }

    std::string rand_flag()
    {
        int flagCut = numRand(0,2);
        int flagLength,partlength,flagCraPos;
        string flagHead = "flag{";
        string flag;
        string flagEnd = "}";
        switch (flagCut)
        {
            case 0:
                flagLength = numRand(7,15);
                for (int c0 = 0; c0 < flagLength + 1; c0++) {
                    flagCraPos = numRand(0,61);
                    flag += flagChar[flagCraPos];
                    Delay(10);
                }
                break;
            case 1:
                flagLength = numRand(10,18);
                partlength = numRand(3,7);
                for (int c11 = 0; c11 < partlength + 1; c11++) {
                    flagCraPos = numRand(0,61);
                    flag += flagChar[flagCraPos];
                    Delay(10);
                }
                flag += "_";
                for (int c12 = 0; c12 < (flagLength - partlength); c12++) {
                    flagCraPos = numRand(0,61);
                    flag += flagChar[flagCraPos];
                    Delay(10);
                }
                break;
            case 2:
                partlength = numRand(3,5);
                for (int c21 = 0; c21 < partlength + 1; c21++) {
                    flagCraPos = numRand(0,61);
                    flag += flagChar[flagCraPos];
                    Delay(10);
                }
                partlength = numRand(4,6);
                flag += "_";
                for (int c22 = 0; c22 < partlength + 1; c22++) {
                    flagCraPos = numRand(0,61);
                    flag += flagChar[flagCraPos];
                    Delay(10);
                }
                partlength = numRand(3,7);
                flag += "_";
                for (int c23 = 0; c23 < partlength + 1; c23++) {
                    flagCraPos = numRand(0,61);
                    flag += flagChar[flagCraPos];
                    Delay(10);
                }
                break;
            default:
                break;
        }

        return flagHead + flag + flagEnd;
    }
}