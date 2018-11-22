#ifndef _ITEM_STATS_H
#define _ITEM_STATS_H
class ItemStats
{
public:
	ItemStats();
	~ItemStats();
	void setStats(int basicStat, int numberItem, int priceItem);
	int _BasicStat;
	int _NumberItem;
	int _Price;
};
#endif // !_ITEM_STATS_H

