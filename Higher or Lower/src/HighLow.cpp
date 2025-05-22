#include "HighLow.hpp"
#include <Geode/binding/FMODAudioEngine.hpp>
#include <random>

data g_data;

namespace HighLow 
{

	bool getIsHLMenu() {
		return g_data.isHLMenu;
	}

	void setIsHLMenu(bool p0) {
		g_data.isHLMenu = p0;
	}

	void setLevels(std::vector<Ref<GJGameLevel>> p0) {
		g_data.levels = p0;
	}


	bool noduplicate(std::shared_ptr<std::vector<Ref<GJGameLevel>>> lvls, std::string p1)
	{
		for (int i = 0; i < g_data.levels.size(); i++) if (strcmp(g_data.levels.at(i)->m_levelName.c_str(), p1.c_str()) == 0) return false;
		return true;
	}

	void addLevels(std::shared_ptr<std::vector<Ref<GJGameLevel>>> lvls)
	{
		while (!lvls->empty())
		{
			auto lvl = lvls->back();
			bool lowendDemonAllowed = false;

			//randomization for low end demons to remove tactics from knowing the 12M threshold
			if (lvl->m_downloads > 12000000 || rand() % 3 == 0) lowendDemonAllowed = true;

			if(HighLow::noduplicate(lvls, lvl->m_levelName) && (lvl->m_difficulty == GJDifficulty::DemonExtreme || lvl->m_difficulty == GJDifficulty::DemonInsane || lvl->m_difficulty == GJDifficulty::Demon || lowendDemonAllowed)) g_data.levels.push_back(lvl);
			lvls->pop_back();
		}
	}

	Ref<GJGameLevel> getL1()
	{
		return g_data.level1;
	}

	Ref<GJGameLevel> getL2()
	{
		return g_data.level2;
	}

	void generateNew()
	{
		if (g_data.levels.size() <= 0) return;
		g_data.level1 = g_data.level2;
		g_data.level2 = g_data.levels.at(rand() % g_data.levels.size());
	}

	void reset()
	{
		if (g_data.levels.size() < 2) return;
		g_data.level1 = g_data.levels.at(rand() % g_data.levels.size());
		g_data.level2 = g_data.levels.at(rand() % g_data.levels.size());
		g_data.score = 0;
		g_data.paused = false;
		auto layer = (LevelBrowserLayer*)CCDirector::get()->getRunningScene()->getChildByID("HLLayer"_spr);
		if (layer != NULL) layer->onRefresh(layer);
	}

	void select(int p0)
	{
		if (HighLow::correct(p0))
		{
			g_data.score++;
			HighLow::generateNew();
			auto layer = (LevelBrowserLayer*)CCDirector::get()->getRunningScene()->getChildByID("HLLayer"_spr);
			if (layer != NULL) layer->onRefresh(layer);

		}
		else g_data.paused = true;
	}

	bool correct(int p0)
	{
		if (g_data.level1->m_downloads == g_data.level2->m_downloads) return true;
		if (g_data.level1->m_downloads > g_data.level2->m_downloads && p0 == 1) return true;
		if (g_data.level1->m_downloads < g_data.level2->m_downloads && p0 == 2) return true;
		return false;
	}

	bool isGamePaused()
	{
		return g_data.paused;
	}

	void setGamePaused(bool p0)
	{
		g_data.paused = p0;
	}

	int getScore()
	{
		return g_data.score;
	}
};
