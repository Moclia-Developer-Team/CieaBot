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
 *  文件：CustomCommand.h
 *  功能：自定义指令
 *
*/

#include <nlohmann/json.hpp>
#include <SQLiteCpp/SQLiteCpp.h>

#include "Global.h"

namespace ciea
{
    void initCommand();
    std::string addCommand(std::string commandName, Cyan::MessageChain commandResult);
    std::string deleteCommand(std::string commandName);
    Cyan::MessageChain showCommand(std::string commandName);
    std::string showAllCommand();
}