#include <Geode/modify/LevelBrowserLayer.hpp>
#include <Geode/Geode.hpp>
#include <Geode/binding/BoomListView.hpp>
#include "../HighLow.hpp"

using namespace geode::prelude;

class $modify(CustomLevelBrowserLayer, LevelBrowserLayer) {
	
	bool init(GJSearchObject* p0) 
	{
		if (!LevelBrowserLayer::init(p0)) return false;
		if (HighLow::getIsHLMenu())
		{
			//not removing to prevent crashes
			this->getChildByID("info-menu")->setPositionX(1000000);
			this->getChildByID("level-count-label")->setPositionX(1000000);
			this->getChildByID("search-menu")->setPositionX(1000000);
			this->getChildByIDRecursive("refresh-button")->setPositionX(1000000);
			this->getChildByID("page-menu")->setPositionX(1000000);
			this->getChildByID("next-page-menu")->setPositionX(1000000);
			this->getChildByID("prev-page-menu")->setPositionX(1000000);
		}
		return true;
	}

	virtual void onEnter()
	{
		LevelBrowserLayer::onEnter();
		if (HighLow::getIsHLMenu())
		{
			CCLabelBMFont* title = (CCLabelBMFont*)this->getChildByID("GJListLayer")->getChildByID("title");
			std::stringstream ss;
			ss << "Score: " << HighLow::getScore();
			auto text = ss.str();
			//auto text = std::format("Score: {}", HighLow::getScore());
			if (title != NULL) title->setString(text.c_str());
		}
	}
	
	virtual void onBack(CCObject* sender)
	{
		LevelBrowserLayer::onBack(sender);
		HighLow::setIsHLMenu(false);
	}

	virtual void loadLevelsFinished(CCArray* p0, char const* p1, int p2) 
	{
		CCArray* arr = CCArray::create();
		auto l1 = HighLow::getL1();
		auto l2 = HighLow::getL2();
		if (l1 != NULL) arr->addObject(l1);
		if (l2 != NULL) arr->addObject(l2);
		if(!HighLow::getIsHLMenu()) LevelBrowserLayer::loadLevelsFinished(p0, p1, p2);
		else 
		{
			LevelBrowserLayer::loadLevelsFinished(arr, p1, p2);
			CCLabelBMFont* title = (CCLabelBMFont*)this->getChildByID("GJListLayer")->getChildByID("title");	
			std::stringstream ss;
			ss << "Score: " << HighLow::getScore();
			auto text = ss.str();
			//auto text = std::format("Score: {}", HighLow::getScore());
			if (title != NULL) title->setString(text.c_str());
		}
	}

	void onRefresh(CCObject* p0) 
	{
		CCLabelBMFont* title = (CCLabelBMFont*)this->getChildByID("GJListLayer")->getChildByID("title");
		std::stringstream ss;
		ss << "Score: " << HighLow::getScore();
		auto text = ss.str();
		//auto text = std::format("Score: {}", HighLow::getScore());
		if (title != NULL) title->setString(text.c_str());

		LevelBrowserLayer::onRefresh(p0);
	}
};