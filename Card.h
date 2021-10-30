#ifndef CARD_H_
#define CARD_H_
#include<iostream>
using namespace std;
enum Rank{ ACE=0, TWO, THREE, FOUR, FIVE, SIX, SEVEN, 
	       EIGHT, NINE, TEN, JACK, QUEEN, KING };
//÷�������飬���ң�����
//�����ŷ����������ѽ����ƶ�ʱ��ͨ����ģ2Ϊһȷ��Ϊ��ͬ��ɫ����
enum Suit{ CLUBS=0, DIAMONDS, SPADES, HEARTS};
class Card
{
public:
	Card()=default;
	Card(Rank rank, Suit suit)
	{
		cardRank = rank;
		cardSuit = suit;
	}
	virtual ~Card() {};
	 Card(const Card &card)
	 {
		this->cardRank = card.cardRank;
		this->cardSuit = card.cardSuit;
		this->face = card.face;
	 }
	 Card& operator=(Card &card)
	 {
		 this->cardRank = card.cardRank;
		 this->cardSuit = card.cardSuit;
		 this->face = card.face;
		 return *this;
	 }
	 bool isFaceUp(){ return face; }//�ж��Ƿ����泯��
	 void setFaceUp(bool a) { this->face = a; }//�ı��Ƿ����泯��
	 Suit getSuit(){ return cardSuit; }//�õ���ɫ
	 Rank getRank(){ return cardRank; }//�õ������С
private:
	Rank cardRank;
	Suit cardSuit;
	bool face=false;
};
#endif