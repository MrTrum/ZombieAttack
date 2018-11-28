#include "TestLine2.h"
#include "Parameter.h"
#include "CreateTestLine.h"


USING_NS_CC;

TestLine2::TestLine2()
{
}

TestLine2::~TestLine2()
{
}

bool TestLine2::init()
{
	if (!Node::init())
	{
		return false;
	}
	auto winSize = Director::getInstance()->getWinSize();

	//auto getline = CreateTestLine::create(TAG_LINE);
	//getline->setPosition(winSize.width, 0.0);
	//this->addChild(getline);

	//auto getline2 = CreateTestLine::create(TAG_LINE2);
	//getline2->setPosition(winSize.width * 0.4, 0.0);
	//this->addChild(getline2);

	return true;
}

	


