#ifndef __GAMESPRITE_H__
#define __GAMESPRITE_H__

#include "cocos2d.h"
#include "string.h"

#define TILE_WIDTH 40
#define TILE_HEIGHT 40
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600

using namespace cocos2d;

enum{WARRIOR, ROGUE, SWORDMASTER, SAGE};

class GameSprite : public CCSprite 
{
	public:
		GameSprite(std::string, int, int x, int y, char *);
		~GameSprite();
		std::string name;
		CCPoint location;
		int type;
		CCSprite * defaultSprite;
		std::vector<CCPoint> availableMoves;
		std::vector<CCPoint> validMoves;
		std::vector<CCPoint> attackMoves;
		float spriteRadius;
		std::map<std::string, int> stats;
		std::map<std::string, CCSprite *> spriteStates;

		void updateAvailableMoves();
		void updateValidMoves();
		//void showValidMoves(Layer *);
		void initMoves(int);
		void initSkills(int);
};

#endif