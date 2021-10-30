#ifndef GAME_H_
#define GAME_H_
#include<stdlib.h>
#include <iostream>
#include"Card.h"
#include"cardstack.h"
#include<time.h>
using namespace std;
class Game
{
private:
	CardStack cardArr;//用于一开始顺序存储52张牌
    CardStack cardStacks[13];//0 闲置堆，1 暂时用于转换的堆，2-8桌面堆，9-12输出堆
	int counter = 0;//用于乱序发牌
	int step = 0;//步数
	int flag = 0;//用于标记步骤一到三是否发生过移动
	int faceUp[7] = {0,1,2,3,4,5,6};//各个堆正面朝上的是第几个并标记，-1代表空堆以及空堆后用king填充
	int money;//赢的钱
	int move = 0;//移动次数
	int playtime = 0;//玩的次数
public:
	void init()//初始化游戏
	{   
		for (int i = 0; i < 7; i++)//桌面堆正面朝上牌进行初始化
			faceUp[i] = i;
		//各个数据成员初始化
		counter = 0;
		step = 0;
		flag = 0;
		move = 0;
		//清空13个牌组
		for (int i = 0; i < 13; i++)
			cardStacks[i].clear();
		cardArr.clear();
		srand((unsigned)time(0));
		for (Suit i = CLUBS; i <= HEARTS; i = (Suit)(i + 1))//52张牌的初始化
		{
			for (Rank j = ACE; j <= KING; j = (Rank)(j + 1))
			{
				Card a(j, i);
				a.setFaceUp(false);
				cardArr.push(a);
			}
		}
		//初始化七个桌面牌堆
		int count = 52;
		int index = 0; 
		for (int i = 1; i <=7; i++)
		{
			for (int j = 1; j <=i; j++)
			{
				index = rand() % count;
				cardStacks[i +1].push(cardArr.peek(index));
				cardArr.erase(index);
				count--;
			}
		}
		for (int i = 2; i < 9; i++) cardStacks[i].top().setFaceUp(true);
		//剩下的牌压入闲置堆
		for (int i = 0; i < 24; i++)
		{
			index = rand() % count;
			cardStacks[0].push(cardArr.peek(index));
			cardArr.erase(index);
			count--;
		}
		testToDisplay();
	}
	//步骤一 桌面堆或闲置堆顶部到输出堆
	int toOutput()
	{//桌面堆移动到输出堆
		for (int i = 2; i <= 8; i++)
		{
			if (cardStacks[i].size() != 0)
			{
				int a = cardStacks[i].top().getSuit();//确定最后此张牌的花色用于后面确定放入什么输出堆
				if( cardStacks[i].top().getRank() == 0)//有A移动到输出堆
                {//压入堆，移动加一，出原先的堆，判断是否有新翻面的牌有则翻牌改变标记翻牌数位置
					cardStacks[a+ 9].push(cardStacks[i].top());
					cout << cardStacks[a + 9].top().getRank() << "+" << cardStacks[a + 9].top().getSuit() << endl;//测试代码，用于显示哪一张牌移动
					move++;
					cardStacks[i].pop();
                    flag = 1;
					if(cardStacks[i].size() == 0)faceUp[i - 2]--;
					else if (cardStacks[i].top().isFaceUp() == false)
					{
						cardStacks[i].top().setFaceUp(true);
						faceUp[i-2]--;
					}
					return 1;
				}
				else if(cardStacks[a + 9].size()!=0)//翻出来的牌不为A
				{//同为A操作
					if (cardStacks[i].top().getRank() == cardStacks[a + 9].top().getRank() + 1)
					{
						cardStacks[a + 9].push(cardStacks[i].top());
						move++;
						cardStacks[i].pop();
                        flag = 1;
						if (cardStacks[i].size() == 0)faceUp[i - 2]--;
						else if (cardStacks[i].top().isFaceUp() == false)
						{
							cardStacks[i].top().setFaceUp(true);
							faceUp[i - 2]--;
						}
						return 1;
					}
				}
			}
		}
	//闲置堆正面朝上的牌若符合条件则放入输出堆，闲置堆正面朝上的牌默认为第一张牌
		if (cardStacks[0].size() > 0)
		{//分为A和非A两种情况
			int suitNum = cardStacks[0].peek(0).getSuit();
			if (cardStacks[0].peek(0).getRank() == 0)
			{
				cardStacks[9 + suitNum].push(cardStacks[0].peek(0));
				cardStacks[0].erase(0);
				flag = 1;
				move++;
				return 1;
			}
			if (cardStacks[9 + suitNum].size() > 0)
			{
				if (cardStacks[0].peek(0).getRank() == cardStacks[9 + suitNum].top().getRank() + 1)
				{
					cardStacks[9 + suitNum].push(cardStacks[0].peek(0));
					cardStacks[0].erase(0);
					flag = 1;
					move++;
					return 1;
				}
			}
		}
			cout << "step 1 no match" << endl;
		    return 0;
	}
	//步骤二 king放入空堆
	int kingToNull()
	{//步骤一没有移动
		if (flag == 0)
		{
			int nullIndex = -1;
			//判断是否有空堆并做标记，-1，为没有空堆
			for (int i = 2; i <= 8; i++)
				if (cardStacks[i].size() == 0)
				{
					nullIndex = i;
					break;
				}
			//桌面堆中正面朝上的牌中找king并替补空缺牌堆
			if (nullIndex >= 0)
			{
				for (int i = 2; i <= 8; i++)
				{
					if (cardStacks[i].size() == 0)continue;//跳过对空堆的查找
					else for (int j = faceUp[i-2]; j < cardStacks[i].size(); j++)
						if (cardStacks[i].peek(j).getRank() == 12 && j > 0 )//检验是否为king且king不在堆的开头
						{
                            cardStacks[i].peek(j-1).setFaceUp(true);
							faceUp[i-2] =j-1 ;//修改堆第一张正面朝上的牌
							for (int k = j; k < cardStacks[i].size(); k++)//king以下牌移动到空堆删除原来牌堆被移动的牌
							{
								cardStacks[nullIndex].push(cardStacks[i].peek(k));
								cardStacks[i].erase(k);
							}
							move++;
							nullIndex = -1;
							flag = 1;
							return 1;
						}
				}
				//闲置堆中寻找有没有king
				while(cardStacks[0].size() > 0)
				{
					{
						if (cardStacks[0].peek(0).getRank() == 12)
						{
							cardStacks[0].peek(0).setFaceUp(true);
							cardStacks[nullIndex].push(cardStacks[0].peek(0));
							cardStacks[0].erase(0);
                            faceUp[nullIndex-2] = -1;
							nullIndex = -1;
							flag = 1;
							move++;
							//牌组0：top->0，牌组1：top->0
							//牌组0从0往后排压入牌组1尾部，牌组1压入牌组0，改变牌组0正面朝上的牌
							if (cardStacks[1].size() > 0)
								cardStacks[0].push(cardStacks[1]);
							cardStacks[1].clear();
							return 1;
						}
						else
						{
							cardStacks[1].push(cardStacks[0].peek(0));
							cardStacks[0].erase(0);
						}
					}
				}
			}
		}
		if (cardStacks[1].size() > 0)
						cardStacks[0].push(cardStacks[1]);
					cardStacks[1].clear();
		cout << "step 2 no match" << endl;
		return 0;
	}
	
	int tableToTable()//桌面堆之间的移动
	{
		if(flag == 0)//步骤一二没有牌移动
		{
			for (int i = 2; i <= 8; i++)
			{
				if (cardStacks[i].size() != 0)
				for (int k = 2; k <= 8; k++)//从第一个循环到第七个，直到发生牌或牌堆的移动
				{ 
					if (cardStacks[k].size() != 0)
					{//第一堆开始与其他堆第一个正面朝上的牌看是否符合条件,符合条件移动牌，删除被移动堆相应的牌,被移动堆的顶部牌设置为正面,第一张正面牌的位置减一
						if(faceUp[k - 2]>=0)
						if (cardStacks[i].top().getRank() ==cardStacks[k].peek(faceUp[k-2]).getRank() + 1 &&
							(cardStacks[i].top().getSuit() + cardStacks[k].peek(faceUp[k-2]).getSuit()) % 2 == 1)
						{
							cardStacks[i].push(cardStacks[k], faceUp[k-2]);
							for (int j = cardStacks[k].size() - 1; j >= faceUp[k-2]; j--)
								cardStacks[k].pop();
							if (cardStacks[k].size() != 0)
								cardStacks[k].top().setFaceUp(true);
								faceUp[k-2]--;
							flag = 1;
							return 1;
						}
					}
				}
			}
        }
		cout << "step 3 no match" << endl;
		return 0;
	}
	int wasteToTable()
	{
		while(cardStacks[0].size() > 0)
		{
				for (int j = 2; j <= 8; j++)
				{
					if (cardStacks[j].size() > 0)
					{
						if (cardStacks[0].peek(0).getRank() == cardStacks[j].top().getRank() - 1 &&
							(cardStacks[0].peek(0).getSuit() + cardStacks[j].top().getSuit()) % 2 == 1)
						{
							cardStacks[0].peek(0).setFaceUp(true);
							cardStacks[j].push(cardStacks[0].peek(0));
							move++;
							cardStacks[0].erase(0);
							if (cardStacks[1].size() > 0)
								cardStacks[0].push(cardStacks[1]);
							cardStacks[1].clear();
							return 1;
						}	
					}
				}
				cardStacks[1].push(cardStacks[0].peek(0));
			    cardStacks[0].erase(0);
				cout << endl;
		}
       if (cardStacks[1].size() > 0)
				cardStacks[0].push(cardStacks[1]);
			cardStacks[1].clear();
		cout << "step 4 no match" << endl;
		return 0;
	}
//实现步骤一到步骤三的循环，返回值作为是否进行步骤四的判断
	int circleStepOneToThree()
	{
        do
		{
			flag = 0;
			toOutput();
			kingToNull();
			tableToTable();
			if(flag==1)testToDisplay();
		} while (flag == 1);
		return flag;
	}
//游戏结束判断及完整一次游戏轮次
	void gamePlay()
	{   
		int a;
		do
		{
			playtime++;
			init();
			int flagAllSteps = 0;
			while (!circleStepOneToThree())
			{
				if (cardStacks[9].size() + cardStacks[10].size() + cardStacks[11].size() + cardStacks[12].size() == 52)
				{
					cout << "全部归位，此轮结束" << endl;
					displayGameOutcome();
					break;
				}
				else if (wasteToTable())
				{
					testToDisplay();
					cout << "进行下次步骤一到步骤四的移动:" << endl;
					continue;
				}
				else if (!wasteToTable())
				{
					cout << "四个步骤均无移动，此轮结束" << endl;
					displayGameOutcome();
					break;
				}
			}
			cout << "input 1 to continue,0 to quit" << endl;
			int i;
			cin >> i;
			a = i;
		}while (a);
			
	}
//用于打印过程的函数
	void testToDisplay()
	{
		cout << "桌面七个堆的牌情况（牌大小+牌花色 牌是否正面朝上）如下： " << endl;
		for (int i = 2; i < 9; i++)
		{
			cout << i-1 << "    ";
			for (int j = 0; j < cardStacks[i].size(); j++)
			{
				cout << cardStacks[i].peek(j).getRank() << "+" << cardStacks[i].peek(j).getSuit() << " ";
				if (cardStacks[i].peek(j).isFaceUp() == 1)cout << 1 << "    ";
				if (cardStacks[i].peek(j).isFaceUp() == 0)cout << 0 << "    ";
			}
			cout << endl;
		}
		cout << "七个桌面牌堆，第一张正面朝上的牌的标记数如下：" << endl;
		for (int i = 0; i < 7; i++)cout << faceUp[i] << " ";
		cout << endl;
		cout << "闲置堆的牌情况如下（牌大小+牌花色）：" << endl;
		for (int i = 0; i < cardStacks[0].size(); i++)
			cout << cardStacks[0].peek(i).getRank() << "+" << cardStacks[0].peek(i).getSuit() << " ";
		cout << endl;
		cout << "输出堆的牌四种花色（梅花，方块，黑桃，红桃）中储存的牌情况如下：" << endl;
		for (int i = 9; i < 13; i++)
		{
			for (int j = 0; j < cardStacks[i].size(); j++)
				cout << cardStacks[i].peek(j).getRank() << " ";
			cout << endl;
		}
		cout << endl;
	}
//输出游戏结果的函数
	void displayGameOutcome()
	{
		cout << endl;
		cout << "结果：" << endl;
		testToDisplay();
		cout << endl;
		cout << "Move: " << move << endl;
		money = (cardStacks[9].size() + cardStacks[10].size() + cardStacks[11].size() + cardStacks[12].size()) * 5 -52;
		cout << "Money: " << money << endl;
		cout << "Play Times: " << playtime << endl;
	}
};
#endif