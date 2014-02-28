#pragma once

#include "cocos2d.h"
#include "string.h"
#include "GameSprite.h"
//#include "C:\\Users\\Alvaro\\Downloads\\cocos2d-x-2.2.2\\cocos2d-x-2.2.2\\cocos2dx\\tilemap_parallax_nodes\\CCTMXTiledMap.h"

using namespace cocos2d;

class Layer : public CCLayer
{
	private:
		/// The background color layer
		CCLayerColor * colorLayer;
		//CCTMXTiledMap * tileMap;

	public:
		Layer();
		~Layer();
		
		void addSprite(GameSprite *, int);

		/// Returns the Cocos2d position of the touch
		CCPoint touchToPoint(CCTouch* touch);
		
		/// Returns true if the touch is within the boundary of our sprite
		bool isTouchingSprite(std::string, CCTouch* touch);

		// 1 for player 1 piece, 0 for player 2 piece, -1 for unoccupied
		int isOccupied[(int) (SCREEN_HEIGHT/TILE_HEIGHT) + 1][(int) (SCREEN_WIDTH/TILE_WIDTH) + 1];

		void showValidMoves(GameSprite *);

		void hideMoves(GameSprite *);

		// Mapping of strings to sprites
		std::map<std::string, GameSprite *> sprites;

		/// The offset of a touch for each sprite
		std::map<std::string, CCPoint> touchOffsets;

		bool pieceSelected;

		std::string pieceName;

		int turn;

		CCPoint tileCenter(GameSprite *, CCPoint);

		GameSprite * findPieceAtLocation(int x, int y);

		// we are multi-touch enabled, so we must use the ccTouches functions
		// vs the ccTouch functions
		bool ccTouchBegan(CCTouch * touch, CCEvent* event);
		void ccTouchesBegan(CCSet* touches, CCEvent* event);
		void ccTouchesMoved(CCSet* touches, CCEvent* event);
		void ccTouchesEnded(CCSet* touches, CCEvent* event);
};
