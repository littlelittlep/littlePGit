#ifndef CARDSTACK_H_
#define CARDSTACK_H_
#include"Card.h"
using namespace std;
class CardStack:public Card//����
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
	int size() { return stacksize; }//���������С
	Card& top() { return pokers[stacksize - 1]; }//���鶥����β��������
	Card& peek(int index)//�����ض�λ�õ���
	{
		if (index >= 0 && index < stacksize)return pokers[index];
	}
	void push(CardStack pStack, int index)//ѹ���ض������ض�λ�ü��Ժ����
	{
		for (int i = index; i < pStack.size(); i++)
			pokers[stacksize++] = pStack[i];
	}
	void push(CardStack pStack)//ѹ��ĳ������
	{
		for (int i = 0; i < pStack.size(); i++)
			pokers[stacksize++] = pStack[i];
	}
	void push(Card aCard)
	{
		pokers[stacksize++] = aCard;
	}//ѹ��ĳ����
	void pop()//����������β������
	{
		if (size() != 0)
		{
			stacksize--;
		};
	}
	void erase(int k)//ɾ��ĳ��λ�õ���
	{
		for (int i = k; i < stacksize - 1; i++)
			pokers[i] = pokers[i + 1];
		pop();
	}
	void clear() { stacksize = 0; }//�������
private:
	Card *pokers;
	int stacksize;
};
#endif 
