/*於陵汐娅机器人项目C++程序*/

/*自定义头文件*/
#include "Global.h" // 自定义头文件
#include "CustomCommand.h"

using namespace std;
using namespace Cyan;

string flagChar = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
bool groupBan = false;

void Delay(int time)//time*1000为秒数
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

string rand_flag()
{
    int flagCut = numRand(0,2);
    int flagLength,partlength,flagCraPos;
    string flagHead = "Flag{";
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
			cout << "尝试与 mirai-api-http 建立连接..." << endl;
			bot.Connect(opts);
			break;
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << endl;
		}
		MiraiBot::SleepSeconds(1);
	}
	cout << "Bot Working..." << endl;
    ciea::initCommand();

	bot.On<GroupMessage>(
		[&](GroupMessage m)
		{
			try
			{
				string plain = m.MessageChain.GetPlainText();

                if (plain == "cat fllllllllag" && !groupBan)
                {
                    m.Reply(MessageChain().Plain("7coin{欢迎来拿flag}"));
                    return;
                }

                if (plain == "flag" && !groupBan)
                {
                    string fakeflag = rand_flag();
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
                }

                if (plain.find("delkw ") == 0)
                {
                    string msg = ciea::deleteCommand(plain.substr(strlen("delkw ")));
                    m.Reply(MessageChain().Plain(msg));
                }

                MessageChain rmc = ciea::showCommand(plain);
                if (!rmc.Empty())
                {
                    m.Reply(rmc);
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
                    if (plain == "cat fllllllllag")
                    {
                        fm.Reply(MessageChain().Plain("7coin{欢迎来拿flag}"));
                        return;
                    }

                    if (plain == "flag")
                    {
                        string fakeflag = rand_flag();
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
                    if (plain == "cat fllllllllag")
                    {
                        tm.Reply(MessageChain().Plain("7coin{欢迎来拿flag}"));
                        return;
                    }

                    if (plain == "flag")
                    {
                        string fakeflag = rand_flag();
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