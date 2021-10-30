#ifndef CARD_H_
#define CARD_H_
#include<iostream>
using namespace std;
enum Rank{ ACE=0, TWO, THREE, FOUR, FIVE, SIX, SEVEN, 
	       EIGHT, NINE, TEN, JACK, QUEEN, KING };
//梅花，方块，黑桃，红桃
//交错安排方便后面桌面堆进行移动时，通过和模2为一确定为不同花色的牌
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
	 bool isFaceUp(){ return face; }//判断是否正面朝上
	 void setFaceUp(bool a) { this->face = a; }//改变是否正面朝上
	 Suit getSuit(){ return cardSuit; }//得到花色
	 Rank getRank(){ return cardRank; }//得到牌面大小
private:
	Rank cardRank;
	Suit cardSuit;
	bool face=false;
};
#endif