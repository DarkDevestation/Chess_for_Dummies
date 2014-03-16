#ifndef __GAMESPRITE_H__
#define __GAMESPRITE_H__

#include "cocos2d.h"
#include "string.h"

#define TILE_WIDTH 40
#define TILE_HEIGHT 40
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600
#define SPRITE_WIDTH 40
#define SPRITE_HEIGHT 80
#define SPRITE_HEIGHT_OFFSET 5

using namespace cocos2d;

/// Enum for the type of piece
enum{ROOK, KNIGHT, BISHOP, KING, QUEEN, PAWN};

class GameSprite : public CCSprite 
{
public:
	/// Main constructor
	GameSprite(std::string, int type, int player, int x, int y, char *);

	/// Destructor
	~GameSprite();

	/// Re-generates the available paths and positions a piece can travel
	void updateAvailableMoves();

	/// List of available move positions based on pieces move set (includes possible invalid moves)
	std::vector<std::vector<CCPoint>> availableMoves;

	/// List of additional moves a piece can attack by
	std::vector<CCPoint> attackMoves;

	/// The player which this piece belongs to
	int player;

	//void initMoves(int);
	//void initSkills(int);		
		
private:
	/// Variables
	std::string name;
	int type;
	CCSprite * defaultSprite;
	float spriteRadius;
	std::map<std::string, int> stats;
	std::map<std::string, CCSprite *> spriteStates;
	//CCPoint location;
	//std::vector<CCPoint> validMoves;
};

#endif