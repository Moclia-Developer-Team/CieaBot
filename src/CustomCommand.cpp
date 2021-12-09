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
 *  文件：CustomCommand.cpp
 *  功能：自定义回复
 *
*/

#include "CustomCommand.h"

using json = nlohmann::json;
using namespace std;
using namespace Cyan;

//json fullCommand;
unique_ptr<SQLite::Database> db;

namespace ciea
{
    void initCommand()
    {
        db = nullptr;
        db = make_unique<SQLite::Database>("CustomCommand.db",SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
        cout << "打开数据库：" << db->getFilename().c_str() << " 成功。" << endl;
        if (!db->tableExists("CustomCommand"))
        {
            SQLite::Transaction Tran(*db);
            db->exec("CREATE TABLE IF NOT EXISTS CustomCommand (commandName TEXT PRIMARY KEY, commandJson TEXT)");
            Tran.commit();
            cout << "创建表CustomCommand成功" << endl;
        }
        db.release();
    }

    int checkCommand(string command)
    {
        db = nullptr;
        db = std::make_unique<SQLite::Database>("./CustomCommand.db");
        SQLite::Statement check(*db,"SELECT commandName FROM CustomCommand WHERE commandName = ?");
        check.bind(1,command);
        if (check.executeStep())
        {
            db.release();
            return 1;
        }
        db.release();
        return 0;
    }

    string addCommand(string commandName, MessageChain commandResult)
    {
        string commandJsonStr, commandReturnStr;
        commandJsonStr = commandResult.ToString();
        commandReturnStr = commandJsonStr.substr(0,strlen("[{\"text\":\"")) + commandJsonStr.substr(commandJsonStr.find(commandName + " ") +
                                                                                                            strlen(commandName.c_str()) + 1);

        if (commandName.empty())
        {
            return "没有输入指令或指令非文字";
        }

        if (checkCommand(commandName) == 1)
        {
            return "指令已存在";
        }
        else
        {
            while (commandName.find("&nbsp;") != string::npos)
            {
                commandName.replace(commandName.find("&nbsp;"), strlen("&nbsp;")," ");
            }

            db = nullptr;
            db = std::make_unique<SQLite::Database>("./CustomCommand.db", SQLite::OPEN_READWRITE);
            SQLite::Transaction tran(*db);
            SQLite::Statement st(*db,"INSERT INTO CustomCommand (commandName,commandJson) VALUES (?,?)");
            st.bind(1,commandName);
            st.bind(2,commandReturnStr);
            st.exec();
            tran.commit();
            db.release();
            return "添加成功";
        }

    }

    string deleteCommand(string commandName)
    {
        if (commandName == "")
        {
            return "没有输入指令或指令非文字";
        }

        if (checkCommand(commandName) == 1)
        {
            while (commandName.find("&nbsp;") != string::npos)
            {
                commandName.replace(commandName.find("&nbsp;"), strlen("&nbsp;")," ");
            }

            db = nullptr;
            db = std::make_unique<SQLite::Database>("./CustomCommand.db", SQLite::OPEN_READWRITE);
            SQLite::Transaction tran(*db);
            SQLite::Statement st(*db,"DELETE FROM CustomCommand WHERE commandName = ?");
            st.bind(1,commandName);
            st.exec();
            tran.commit();
            db.release();
            return "删除成功";
        }
        else
        {
            return "无法删除不存在的指令";
        }
    }

    MessageChain showCommand(std::string commandName)
    {
        MessageChain mc;
        db = nullptr;
        db = std::make_unique<SQLite::Database>("./CustomCommand.db");
        SQLite::Statement read(*db, "SELECT commandJson FROM CustomCommand WHERE commandName = ?");
        read.bind(1,commandName);
        if (read.executeStep())
        {
            cout << read.getColumn("commandJson").getString() << endl;
            string msgString = read.getColumn("commandJson").getString();
            json jmsg;
            jmsg.clear();
            jmsg = json::parse("{\"messageChain\":" + msgString + "}");
            mc.Set(jmsg["messageChain"]);
            db.release();
        }
        db.release();
        return mc;
    }

    string showAllCommand()
    {
        string commandList;

        db = nullptr;
        db = std::make_unique<SQLite::Database>("./CustomCommand.db");
        SQLite::Statement show(*db, "SELECT commandName FROM CustomCommand");
        if (show.executeStep())
        {
            commandList = show.getColumn("commandName").getString();
            db.release();
        }
        db.release();
        return commandList;
    }
}