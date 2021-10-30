#ifndef CARDSTACK_H_
#define CARDSTACK_H_
#include"Card.h"
using namespace std;
class CardStack:public Card//父类
{
public:
	CardStack()
	{
		pokers = new Card[52];
		stacksize = 0;
	}
	Card& operator[](int index)
	{
		return pokers[index];
	}
	int size() { return stacksize; }//返回牌组大小
	Card& top() { return pokers[stacksize - 1]; }//牌组顶部（尾部）的牌
	Card& peek(int index)//牌组特定位置的牌
	{
		if (index >= 0 && index < stacksize)return pokers[index];
	}
	void push(CardStack pStack, int index)//压入特定牌组特定位置及以后的牌
	{
		for (int i = index; i < pStack.size(); i++)
			pokers[stacksize++] = pStack[i];
	}
	void push(CardStack pStack)//压入某个牌组
	{
		for (int i = 0; i < pStack.size(); i++)
			pokers[stacksize++] = pStack[i];
	}
	void push(Card aCard)
	{
		pokers[stacksize++] = aCard;
	}//压入某张牌
	void pop()//弹出顶部（尾部）牌
	{
		if (size() != 0)
		{
			stacksize--;
		};
	}
	void erase(int k)//删除某个位置的牌
	{
		for (int i = k; i < stacksize - 1; i++)
			pokers[i] = pokers[i + 1];
		pop();
	}
	void clear() { stacksize = 0; }//清空牌组
private:
	Card *pokers;
	int stacksize;
};
#endif 
