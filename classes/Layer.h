#pragma once

#include "cocos2d.h"
#include "string.h"
#include "GameSprite.h"

using namespace cocos2d;

class Layer : public CCLayer
{
	private:
		/// The background color layer
		CCLayerColor* colorLayer;

	public:
		Layer();
		~Layer();
		
		// adds a sprite to the sprite map and as a child to the layer
		//void addSprite(std::string, char *, int, float, float);
		
		void addSprite(GameSprite *, int);

		void moveSprite(char * spriteName, CCEvent * event);

		/// Returns the Cocos2d position of the touch
		CCPoint touchToPoint(CCTouch* touch);
		
		/// Returns true if the touch is within the boundary of our sprite
		bool isTouchingSprite(std::string, CCTouch* touch);

		void showValidMoves(GameSprite *);

		// Mapping of strings to sprites
		std::map<std::string, GameSprite *> sprites;

		/// The offset of a touch for each sprite
		std::map<std::string, CCPoint> touchOffsets;

		// we are multi-touch enabled, so we must use the ccTouches functions
		// vs the ccTouch functions
		void ccTouchesBegan(CCSet* touches, CCEvent* event);
		void ccTouchesMoved(CCSet* touches, CCEvent* event);
		void ccTouchesEnded(CCSet* touches, CCEvent* event);
};
