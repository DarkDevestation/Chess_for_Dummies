#include "SimpleAudioEngine.h"
#include "Layer.h"
#include "windows.h"

Layer::Layer()
{
	// enable touches so we can drag
	// note that if you call CCLayer's init() it will unset touch enabled!
	this->setTouchEnabled(true);

	// create white background, it is Walker's task to change this to an actual background.
	this->colorLayer = new CCLayerColor;
	this->colorLayer->initWithColor( ccc4(255, 255, 255, 255) );
	this->addChild(this->colorLayer, 1);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background.mp3", true);
}

void Layer::addSprite(GameSprite * piece, int priority)
{
	sprites[piece->name] = piece;
	this->addChild(sprites[piece->name], priority);
}



/*void Layer::addSprite(std::string spriteName, char * filename, int priority, float xOffset, float yOffset)
{
	// create sprite and add it the layer's sprite map and as a child
	CCSize iSize = CCDirector::sharedDirector()->getWinSize();
	sprites[spriteName] = new GameSprite(spriteName, 1);
	sprites[spriteName]->initWithFile(filename);
	sprites[spriteName]->setPosition(ccp(iSize.width * xOffset, iSize.height * yOffset));
	sprites[spriteName]->setAnchorPoint(ccp(0.5f, 0.55f)); // nudge the anchor point upward because of the shadow
	this->addChild(sprites[spriteName], priority);
}*/

Layer::~Layer()
{
	// unset this so we unregister with the touch dispatcher
	this->setTouchEnabled(false);
	
	// release our sprites and layer so that they get dealloced
	for(auto iterator = sprites.begin(); iterator != sprites.end(); iterator++)
	{
		CC_SAFE_RELEASE_NULL(this->sprites[iterator->first]);
	}

	CC_SAFE_RELEASE_NULL(this->colorLayer);
}

CCPoint Layer::touchToPoint(CCTouch* touch)
{
	// convert the touch object to a position in our cocos2d space
	return CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
}

bool Layer::isTouchingSprite(std::string spriteName, CCTouch* touch)
{
	// here's one way, but includes the rectangular white space around our sprite
	//return CGRectContainsPoint(this->sprite->boundingBox(), this->touchToPoint(touch));
	
	// this way is more intuitive for the user because it ignores the white space.
	// it works by calculating the distance between the sprite's center and the touch point,
	// and seeing if that distance is less than the sprite's radius
	
	return (ccpDistance(this->sprites[spriteName]->getPosition(), this->touchToPoint(touch)) < TILE_WIDTH/2.0f);
}

void Layer::moveSprite(char * spriteName, CCEvent * event)
{
	/*if (GetAsyncKeyState('a')){
		for(auto iterator = sprites.begin(); iterator != sprites.end(); iterator++)
		{
			this->sprites[iterator->first]->setPosition(ccpAdd(this->sprites[iterator->first]->getPosition(), CCPoint(10, 10)));
		}
	}*/
}

void Layer::showValidMoves(GameSprite * piece)
{
	CCSprite * tile;
	for (auto i : piece->availableMoves)
	{
		if (i.x >= 0 && i.x <= SCREEN_WIDTH && i.y >= 0 && i.y <= SCREEN_HEIGHT)
		{
			tile = new CCSprite();
			tile->initWithFile("Move.png");
			tile->setPosition(i); //ccpAdd(piece->getPosition(), i)); 
			this->addChild(tile, 3);
			//CC_SAFE_DELETE(tile);
		}
	}
	//if (tile != nullptr)
		//CC_SAFE_DELETE(tile);
}

void Layer::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
	for( auto it = touches->begin(); it != touches->end(); it++) 
	{
		CCTouch* touch = dynamic_cast<CCTouch*>(*it);

		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("hit.wav");
		
		for(auto iterator = this->sprites.begin(); iterator != this->sprites.end(); iterator++)
		{
			// reset touch offset
			this->touchOffsets[iterator->first] = CCPointZero;

			// if this touch is within our sprite's boundary
			if( touch && this->isTouchingSprite(iterator->first, touch))
			{
				this->showValidMoves(this->sprites[iterator->first]);

				// calculate offset from sprite to touch point
				this->touchOffsets[iterator->first] = ccpSub(this->sprites[iterator->first]->getPosition(), this->touchToPoint(touch));
			}
		}
	}
}

void Layer::ccTouchesMoved(CCSet* touches, CCEvent* event)
{
	/*for( auto it = touches->begin(); it != touches->end(); it++) 
	{
		CCTouch* touch = dynamic_cast<CCTouch*>(*it);

		for(auto iterator = sprites.begin(); iterator != sprites.end(); iterator++)
		{
			// set the new sprite position
			if( touch && touchOffsets[iterator->first].x && touchOffsets[iterator->first].y )
				this->sprites[iterator->first]->setPosition(ccpAdd(this->touchToPoint(touch), this->touchOffsets[iterator->first]));
		}
	}*/
}

void Layer::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("score.wav");

	for( auto it = touches->begin(); it != touches->end(); it++) 
	{
		CCTouch* touch = dynamic_cast<CCTouch*>(*it);

		for(auto iterator = sprites.begin(); iterator != sprites.end(); iterator++)
		{
			if( touch && touchOffsets[iterator->first].x && touchOffsets[iterator->first].y  )
			{
				// set the new sprite position
				this->sprites[iterator->first]->setPosition(ccpAdd(this->touchToPoint(touch), this->touchOffsets[iterator->first]));

				// stop any existing actions are reset the scale
				this->sprites[iterator->first]->stopAllActions();
				this->sprites[iterator->first]->setScale(1.0f);

				// animate letting go of the sprite
				this->sprites[iterator->first]->runAction(CCSequence::create(
					CCScaleBy::create(0.125f, 1.111f),
					CCScaleBy::create(0.125f, 0.9f),
					nullptr
					));
			}
		}
	}
}
