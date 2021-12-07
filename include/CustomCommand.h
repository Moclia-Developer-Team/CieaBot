#include <nlohmann/json.hpp>
#include <SQLiteCpp/SQLiteCpp.h>

#include "Global.h"

namespace ciea
{
    void initCommand();
    std::string addCommand(std::string commandName, Cyan::MessageChain commandResult);
    std::string deleteCommand(std::string commandName);
    Cyan::MessageChain showCommand(std::string commandName);
}