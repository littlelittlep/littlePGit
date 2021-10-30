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
	CardStack cardArr;//����һ��ʼ˳��洢52����
    CardStack cardStacks[13];//0 ���öѣ�1 ��ʱ����ת���Ķѣ�2-8����ѣ�9-12�����
	int counter = 0;//����������
	int step = 0;//����
	int flag = 0;//���ڱ�ǲ���һ�����Ƿ������ƶ�
	int faceUp[7] = {0,1,2,3,4,5,6};//���������泯�ϵ��ǵڼ�������ǣ�-1����ն��Լ��նѺ���king���
	int money;//Ӯ��Ǯ
	int move = 0;//�ƶ�����
	int playtime = 0;//��Ĵ���
public:
	void init()//��ʼ����Ϸ
	{   
		for (int i = 0; i < 7; i++)//��������泯���ƽ��г�ʼ��
			faceUp[i] = i;
		//�������ݳ�Ա��ʼ��
		counter = 0;
		step = 0;
		flag = 0;
		move = 0;
		//���13������
		for (int i = 0; i < 13; i++)
			cardStacks[i].clear();
		cardArr.clear();
		srand((unsigned)time(0));
		for (Suit i = CLUBS; i <= HEARTS; i = (Suit)(i + 1))//52���Ƶĳ�ʼ��
		{
			for (Rank j = ACE; j <= KING; j = (Rank)(j + 1))
			{
				Card a(j, i);
				a.setFaceUp(false);
				cardArr.push(a);
			}
		}
		//��ʼ���߸������ƶ�
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
		//ʣ�µ���ѹ�����ö�
		for (int i = 0; i < 24; i++)
		{
			index = rand() % count;
			cardStacks[0].push(cardArr.peek(index));
			cardArr.erase(index);
			count--;
		}
		testToDisplay();
	}
	//����һ ����ѻ����öѶ����������
	int toOutput()
	{//������ƶ��������
		for (int i = 2; i <= 8; i++)
		{
			if (cardStacks[i].size() != 0)
			{
				int a = cardStacks[i].top().getSuit();//ȷ���������ƵĻ�ɫ���ں���ȷ������ʲô�����
				if( cardStacks[i].top().getRank() == 0)//��A�ƶ��������
                {//ѹ��ѣ��ƶ���һ����ԭ�ȵĶѣ��ж��Ƿ����·�����������Ƹı��Ƿ�����λ��
					cardStacks[a+ 9].push(cardStacks[i].top());
					cout << cardStacks[a + 9].top().getRank() << "+" << cardStacks[a + 9].top().getSuit() << endl;//���Դ��룬������ʾ��һ�����ƶ�
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
				else if(cardStacks[a + 9].size()!=0)//���������Ʋ�ΪA
				{//ͬΪA����
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
	//���ö����泯�ϵ����������������������ѣ����ö����泯�ϵ���Ĭ��Ϊ��һ����
		if (cardStacks[0].size() > 0)
		{//��ΪA�ͷ�A�������
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
	//����� king����ն�
	int kingToNull()
	{//����һû���ƶ�
		if (flag == 0)
		{
			int nullIndex = -1;
			//�ж��Ƿ��пնѲ�����ǣ�-1��Ϊû�пն�
			for (int i = 2; i <= 8; i++)
				if (cardStacks[i].size() == 0)
				{
					nullIndex = i;
					break;
				}
			//����������泯�ϵ�������king���油��ȱ�ƶ�
			if (nullIndex >= 0)
			{
				for (int i = 2; i <= 8; i++)
				{
					if (cardStacks[i].size() == 0)continue;//�����ԿնѵĲ���
					else for (int j = faceUp[i-2]; j < cardStacks[i].size(); j++)
						if (cardStacks[i].peek(j).getRank() == 12 && j > 0 )//�����Ƿ�Ϊking��king���ڶѵĿ�ͷ
						{
                            cardStacks[i].peek(j-1).setFaceUp(true);
							faceUp[i-2] =j-1 ;//�޸Ķѵ�һ�����泯�ϵ���
							for (int k = j; k < cardStacks[i].size(); k++)//king�������ƶ����ն�ɾ��ԭ���ƶѱ��ƶ�����
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
				//���ö���Ѱ����û��king
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
							//����0��top->0������1��top->0
							//����0��0������ѹ������1β��������1ѹ������0���ı�����0���泯�ϵ���
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
	
	int tableToTable()//�����֮����ƶ�
	{
		if(flag == 0)//����һ��û�����ƶ�
		{
			for (int i = 2; i <= 8; i++)
			{
				if (cardStacks[i].size() != 0)
				for (int k = 2; k <= 8; k++)//�ӵ�һ��ѭ�������߸���ֱ�������ƻ��ƶѵ��ƶ�
				{ 
					if (cardStacks[k].size() != 0)
					{//��һ�ѿ�ʼ�������ѵ�һ�����泯�ϵ��ƿ��Ƿ��������,���������ƶ��ƣ�ɾ�����ƶ�����Ӧ����,���ƶ��ѵĶ���������Ϊ����,��һ�������Ƶ�λ�ü�һ
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
//ʵ�ֲ���һ����������ѭ��������ֵ��Ϊ�Ƿ���в����ĵ��ж�
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
//��Ϸ�����жϼ�����һ����Ϸ�ִ�
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
					cout << "ȫ����λ�����ֽ���" << endl;
					displayGameOutcome();
					break;
				}
				else if (wasteToTable())
				{
					testToDisplay();
					cout << "�����´β���һ�������ĵ��ƶ�:" << endl;
					continue;
				}
				else if (!wasteToTable())
				{
					cout << "�ĸ���������ƶ������ֽ���" << endl;
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
//���ڴ�ӡ���̵ĺ���
	void testToDisplay()
	{
		cout << "�����߸��ѵ���������ƴ�С+�ƻ�ɫ ���Ƿ����泯�ϣ����£� " << endl;
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
		cout << "�߸������ƶѣ���һ�����泯�ϵ��Ƶı�������£�" << endl;
		for (int i = 0; i < 7; i++)cout << faceUp[i] << " ";
		cout << endl;
		cout << "���öѵ���������£��ƴ�С+�ƻ�ɫ����" << endl;
		for (int i = 0; i < cardStacks[0].size(); i++)
			cout << cardStacks[0].peek(i).getRank() << "+" << cardStacks[0].peek(i).getSuit() << " ";
		cout << endl;
		cout << "����ѵ������ֻ�ɫ��÷�������飬���ң����ң��д������������£�" << endl;
		for (int i = 9; i < 13; i++)
		{
			for (int j = 0; j < cardStacks[i].size(); j++)
				cout << cardStacks[i].peek(j).getRank() << " ";
			cout << endl;
		}
		cout << endl;
	}
//�����Ϸ����ĺ���
	void displayGameOutcome()
	{
		cout << endl;
		cout << "�����" << endl;
		testToDisplay();
		cout << endl;
		cout << "Move: " << move << endl;
		money = (cardStacks[9].size() + cardStacks[10].size() + cardStacks[11].size() + cardStacks[12].size()) * 5 -52;
		cout << "Money: " << money << endl;
		cout << "Play Times: " << playtime << endl;
	}
};
#endif