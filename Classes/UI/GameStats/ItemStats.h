#ifndef _ITEM_STATS_H
#define _ITEM_STATS_H
class ItemStats
{
public:
	ItemStats();
	~ItemStats();
	void setStats(int basicStat, int numberItem, int priceItem);
private:
	int _BasicStat,_NumberItem,_Price;
};
#endif // !_ITEM_STATS_H

