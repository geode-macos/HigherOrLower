#pragma once
#include <Geode/Geode.hpp>
using namespace geode::prelude;

struct data {
	bool isHLMenu = false;
	std::vector<Ref<GJGameLevel>> levels;
	Ref<GJGameLevel> level1;
	Ref<GJGameLevel> level2;
	int score = 0;
	bool paused = true;
};

extern data g_data;

namespace HighLow {
	bool getIsHLMenu();
	void setIsHLMenu(bool);
	void setLevels(std::vector<Ref<GJGameLevel>>);
	void addLevels(std::shared_ptr<std::vector<Ref<GJGameLevel>>>);
	Ref<GJGameLevel> getL1();
	Ref<GJGameLevel> getL2();
	void generateNew();
	void reset();
	void select(int);
	bool correct(int);
	bool isGamePaused();
	void setGamePaused(bool);
	int getScore();
	bool noduplicate(std::shared_ptr<std::vector<Ref<GJGameLevel>>>, std::string) ;
}