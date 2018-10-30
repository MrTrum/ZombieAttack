#include "TestLine2.h"
#include "Parameter.h"
#include "TestLine.h"
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

	auto getline = TestLine::create();
	getline->setPosition(winSize.width * 0.8, 0.0);
	this->addChild(getline);

	auto getline2 = CreateTestLine::create();
	getline2->setPosition(winSize.width * 0.4, 0.0);
	this->addChild(getline2);

	return true;
}


