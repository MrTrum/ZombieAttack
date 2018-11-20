#include "UI/GameStats/ItemStats.h"
ItemStats::ItemStats()
{
	_BasicStat = 0;
	_NumberItem = 0;
	_Price = 0;
}

ItemStats::~ItemStats()
{
	_BasicStat = 0;
	_NumberItem = 0;
	_Price = 0;
}
void ItemStats::setStats(int basicStat, int numberItem, int priceItem)
{
	_BasicStat = basicStat;
	_NumberItem = numberItem;
	_Price = priceItem;
}