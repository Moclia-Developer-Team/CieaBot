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
 *  文件：main.cpp
 *  功能：消息处理，与mirai连接
 *
*/

/*自定义头文件*/
#include "Global.h" // 自定义头文件
#include "CustomCommand.h"
#include "FlagGenerator.h"

using namespace std;
using namespace Cyan;

bool groupBan = false;

int main()
{
#if defined(WIN32) || defined(_WIN32)
	// 切换代码页，让 CMD 可以显示 UTF-8 字符
	system("chcp 65001");
#endif

	MiraiBot bot;
	SessionOptions opts = SessionOptions().FromJsonFile("config.json");

	while (true)
	{
		try
		{
			cout << "正在接入通信网络..." << endl;
			bot.Connect(opts); // 连接mirai bot
			break;
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << endl;
		}
		MiraiBot::SleepSeconds(1);
	}
	cout << "汐娅已上线~" << endl;
    ciea::initCommand(); // 检查数据库完整性

	bot.On<GroupMessage>(
		[&](GroupMessage m)
		{
			try
			{
				string plain = m.MessageChain.GetPlainText();

                if (plain == "flag" && !groupBan)
                {
                    string fakeflag = ciea::rand_flag();
                    m.Reply(MessageChain().Plain(fakeflag));
                    return;
                }

                if (plain.find("addkw ") == 0)
                {
                    string delAddKW, delStr, msg;
                    delAddKW = plain.substr(strlen("addkw "));
                    delStr = delAddKW.substr(0, delAddKW.find(" "));
                    msg = ciea::addCommand(
                            delStr,m.MessageChain);
                    m.Reply(MessageChain().Plain(msg));
                    return;
                }

                if (plain.find("delkw ") == 0)
                {
                    string msg = ciea::deleteCommand(plain.substr(strlen("delkw ")));
                    m.Reply(MessageChain().Plain(msg));
                    return;
                }

                if (plain == "kwlist")
                {
                    string msg = ciea::showAllCommand();
                    m.Reply(MessageChain().Plain(msg));
                    return;
                }

                MessageChain rmc = ciea::showCommand(plain);
                if (!rmc.Empty())
                {
                    m.Reply(rmc);
                    return;
                }
			}
			catch (const std::exception& ex)
			{
				cout << ex.what() << endl;
			}
		});

    bot.On<FriendMessage>(
            [&](FriendMessage fm)
            {
                try {
                    string plain = fm.MessageChain.GetPlainText();

                    if (plain == "flag")
                    {
                        string fakeflag = ciea::rand_flag();
                        fm.Reply(MessageChain().Plain(fakeflag));
                        return;
                    }

                    if (plain == "GroupBan")
                    {
                        groupBan = true;
                        fm.Reply(MessageChain().Plain("GroupBan = True"));
                        return;
                    }

                    if (plain == "!GroupBan")
                    {
                        groupBan = false;
                        fm.Reply(MessageChain().Plain("GroupBan = False"));
                        return;
                    }
                }
                catch (const std::exception& ex)
                {
                    cout << ex.what() << endl;
                }
            });

    bot.On<TempMessage>(
            [&](TempMessage tm)
            {
                try {
                    string plain = tm.MessageChain.GetPlainText();

                    if (plain == "flag")
                    {
                        string fakeflag = ciea::rand_flag();
                        tm.Reply(MessageChain().Plain(fakeflag));
                        return;
                    }

                    if (plain == "GroupBan")
                    {
                        groupBan = true;
                        tm.Reply(MessageChain().Plain("GroupBan = True"));
                        return;
                    }

                    if (plain == "!GroupBan")
                    {
                        groupBan = false;
                        tm.Reply(MessageChain().Plain("GroupBan = False"));
                        return;
                    }
                }
                catch (const std::exception& ex)
                {
                    cout << ex.what() << endl;
                }
            });

    /*bot.On<MemberJoinEvent>(
            [&](MemberJoinEvent mj)
            {
               GID_t groupID = mj.NewMember.Group.GID;
               bot.SendMessage(groupID,
                               MessageChain().Plain("这是报名表：https://www.wjx.top/vm/P70jDA9.aspx"));
               return;
            });*/


	// 在失去与mah的连接后重连
	bot.On<LostConnection>([&](LostConnection e)
		{
			cout << e.ErrorMessage << " (" << e.Code << ")" << endl;
			while (true)
			{
				try
				{
					cout << "尝试连接 mirai-api-http..." << endl;
					bot.Reconnect();
					cout << "与 mirai-api-http 重新建立连接!" << endl;
					break;
				}
				catch (const std::exception& ex)
				{
					cout << ex.what() << endl;
				}
				MiraiBot::SleepSeconds(1);
			}
		});

	string cmd;
	while (cin >> cmd)
	{
		if (cmd == "exit")
		{
			// 程序结束前必须调用 Disconnect，否则 mirai-api-http 会内存泄漏。
			bot.Disconnect();
			break;
		}
	}

	return 0;
}