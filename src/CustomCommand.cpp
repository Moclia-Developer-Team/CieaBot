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
        //SQLite::Database db("CustomCommand.db",SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
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

    string addCommand(string commandName, MessageChain commandResult)
    {
        /*json commandJson = commandResult.ToJson();
        fullCommand[commandName].push_back(commandJson);
        ofstream save("./CustomCommand.json");
        save << std::setw(4) << fullCommand << endl;
        save.close();*/

        string commandJsonStr, commandReturnStr;
        commandJsonStr = commandResult.ToString();
        commandReturnStr = commandJsonStr.substr(0,strlen("[{\"text\":\"")) + commandJsonStr.substr(commandJsonStr.find(commandName + " ") +
                                                                                                            strlen(commandName.c_str()) + 1);
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

    string deleteCommand(string commandName)
    {
        /*fullCommand.at(commandName).clear();
        ofstream save("./CustomCommand.json");
        save << std::setw(4) << fullCommand << endl;
        save.close();*/
        db = nullptr;
        db = std::make_unique<SQLite::Database>("./CustomCommand.db", SQLite::OPEN_READWRITE);
        SQLite::Transaction tran(*db);
        SQLite::Statement st(*db,"DELETE FROM CustomCommand WHERE commandName = ?");
        st.bind(1,commandName);
        st.exec();
        tran.commit();
        cout << st.getErrorCode() << endl;
        db.release();
        return "删除成功";
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
        //db.release();
        return mc;
    }
}