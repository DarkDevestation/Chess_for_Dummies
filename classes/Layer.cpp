#include "SimpleAudioEngine.h"
#include "Layer.h"
#include "windows.h"
#include "cocos2d.h"

Layer::Layer()
{
	// enable touches so we can drag
	// note that if you call CCLayer's init() it will unset touch enabled!
	this->setTouchEnabled(true);

	this->pieceName = "";
	this->pieceSelected = false;

	this->turn = 1;

	for (int i = 0; i < (int) (SCREEN_HEIGHT/TILE_HEIGHT) + 1; i++)
		for (int j = 0; j < (int) (SCREEN_WIDTH/TILE_WIDTH) + 1; j++)
			this->isOccupied[i][j] = -1;
	// create white background, it is Walker's task to change this to an actual background.
	this->colorLayer = new CCLayerColor;
	this->colorLayer->initWithColor( ccc4(255, 255, 255, 255) );
	this->addChild(this->colorLayer, 1);

	//this->tileMap = new CCTMXTiledMap();
	//this->tileMap->initWithTMXFile("boardWithBorder.tmx");
	//this->addChild(tileMap, 1);

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background.mp3", true);
}

void Layer::addSprite(GameSprite * piece, int priority)
{
	sprites[piece->name] = piece;
	this->addChild(sprites[piece->name], priority);
}

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
	//CC_SAFE_RELEASE_NULL(this->tileMap);
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

void Layer::showValidMoves(GameSprite * piece)
{
	CCSprite * tile;
	for (auto i : piece->availableMoves)
	{
		// Shows moves by adding tile sprites
		if (i.x >= 0 && i.x <= SCREEN_WIDTH && i.y >= 0 && i.y <= SCREEN_HEIGHT)
		{
			tile = new CCSprite();
			tile->initWithFile("Move.png");
			tile->setPosition(i);
			this->addChild(tile, 2);
		}
	}
}

// Not being implemented. Ignore.
void Layer::hideMoves(GameSprite * piece)
{
	//CCSprite * tile;
	//for (int i = 0; i != this->getChildrenCount(); i++)
	//{
		//if (i.x >= 0 && i.x <= SCREEN_WIDTH && i.y >= 0 && i.y <= SCREEN_HEIGHT)
		//if (this->getChildByTag(i))
		//{
			//tile = new CCSprite();
			//tile->initWithFile("Move.png");
			//tile->setPosition(i); //ccpAdd(piece->getPosition(), i)); 
		//this->getChildren()->removeObjectAtIndex(i);
		//this->getChildren()->objectAtIndex(i);
			//CC_SAFE_DELETE(tile);
		//}
	//}
}

bool Layer::ccTouchBegan(CCTouch * touch, CCEvent* event)
{
	//CCTouch* touch = dynamic_cast<CCTouch*>(*it);

	/*CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("hit.wav");
		
	for(auto iterator = this->sprites.begin(); iterator != this->sprites.end(); iterator++)
	{
		// reset touch offset
		this->touchOffsets[iterator->first] = CCPointZero;

		if (touch && this->isTouchingSprite(iterator->first, touch) && this->pieceSelected)
		{
			this->sprites[iterator->first]->setPosition(this->touchToPoint(touch));
			this->pieceSelected = false;
		}

		// if this touch is within our sprite's boundary
		if( touch && this->isTouchingSprite(iterator->first, touch))
		{
			this->showValidMoves(this->sprites[iterator->first]);

			this->pieceSelected = true;

			//this->hideMoves(this->sprites[iterator->first]);

			// calculate offset from sprite to touch point
			this->touchOffsets[iterator->first] = ccpSub(this->sprites[iterator->first]->getPosition(), this->touchToPoint(touch));
		}
	}*/

	return true;
}

// Find the (x, y) tile location of a selected tile. Used for moving a sprite to a different tile on the board. of point is not
// in the list of available moves for sprite, return the (0, 0) location to indicate no movement.
CCPoint Layer::tileCenter(GameSprite * sprite, CCPoint point)
{
	for (auto i : sprite->availableMoves)
	{
		if (point.x < i.x + (TILE_WIDTH / 2) && point.x > i.x - (TILE_WIDTH / 2) && point.y < i.y + (TILE_HEIGHT / 2) && point.y > i.y - (TILE_HEIGHT / 2))
			return ccp(i.x, i.y);
	}

	return ccp(0, 0);
}

GameSprite * Layer::findPieceAtLocation(int x, int y)
{
	for (auto i = this->sprites.begin(); i != this->sprites.end(); i++)
	{
		if ((int) (this->sprites[i->first]->location.x) == x && (int) (this->sprites[i->first]->location.y) == y)
			return this->sprites[i->first];
	}

	return nullptr;
}

void Layer::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
	//this->pieceName = "";

	for( auto it = touches->begin(); it != touches->end(); it++) 
	{
		CCTouch* touch = dynamic_cast<CCTouch*>(*it);

		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("hit.wav");
		
		for(auto iterator = this->sprites.begin(); iterator != this->sprites.end(); iterator++)
		{
			// reset touch offset
			this->touchOffsets[iterator->first] = CCPointZero;
		
			if (touch && this->pieceSelected && this->pieceName != "")
			{
				if (this->tileCenter(this->sprites[pieceName], this->touchToPoint(touch)).x != 0 && 
					this->tileCenter(this->sprites[pieceName], this->touchToPoint(touch)).y != 0 &&
					this->turn % 2 == this->sprites[pieceName]->player1)
				{

					// Update occupied board at initial position of the piece being moved
					this->isOccupied[(int) (this->sprites[pieceName]->location.y)][(int) (this->sprites[pieceName]->location.x)] = -1;
					// Move piece
					this->sprites[pieceName]->setPosition(this->tileCenter(this->sprites[pieceName], this->touchToPoint(touch)));

					int x = (int) (this->tileCenter(this->sprites[pieceName], this->touchToPoint(touch)).x / TILE_WIDTH);
					int y = (int) (this->tileCenter(this->sprites[pieceName], this->touchToPoint(touch)).y / TILE_HEIGHT);

					// Remove enemy piece if destination contains enemy piece
					if (this->sprites[pieceName]->player1 != this->isOccupied[y][x] && this->isOccupied[y][x] != -1)
					{
						this->findPieceAtLocation(x, y)->autorelease();
						this->findPieceAtLocation(x, y)->stopAllActions();
						this->findPieceAtLocation(x, y)->setVisible(false);
						//CC_SAFE_DELETE(this->findPieceAtLocation((int) (this->tileCenter(this->sprites[pieceName], this->touchToPoint(touch)).x / TILE_WIDTH), (int) (this->tileCenter(this->sprites[pieceName], this->touchToPoint(touch)).y / TILE_HEIGHT)));
						this->removeChild(this->findPieceAtLocation(x, y));
					}

					// Set (x, y) coordinates
					this->sprites[pieceName]->location.x = x;
					this->sprites[pieceName]->location.y = y;

					// Set occupy value on board for destination of moved piece
					this->isOccupied[(int) (this->sprites[pieceName]->location.y)][(int) (this->sprites[pieceName]->location.x)] = (int) (this->sprites[pieceName]->player1);
					this->turn++;
				}
				//this->hideMoves(this->sprites[pieceName]);
				this->sprites[pieceName]->updateAvailableMoves();
				this->pieceSelected = false;
				this->pieceName = "";
				break;
			}

			// if this touch is within our sprite's boundary
			if(touch && this->isTouchingSprite(iterator->first, touch) && this->turn % 2 == this->sprites[iterator->first]->player1)
			{
				this->showValidMoves(this->sprites[iterator->first]);
				this->pieceName = iterator->first;
				this->pieceSelected = true;

				//this->hideMoves(this->sprites[iterator->first]);

				// calculate offset from sprite to touch point
				this->touchOffsets[iterator->first] = ccpSub(this->sprites[iterator->first]->getPosition(), this->touchToPoint(touch));
				break;
			}

			this->pieceSelected = false;
			this->pieceName = "";
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
	/*CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("score.wav");

	for( auto it = touches->begin(); it != touches->end(); it++) 
	{
		CCTouch* touch = dynamic_cast<CCTouch*>(*it);

		for(auto iterator = sprites.begin(); iterator != sprites.end(); iterator++)
		{
			if( touch && touchOffsets[iterator->first].x && touchOffsets[iterator->first].y  )
			{
				this->hideMoves(this->sprites[iterator->first]);

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
	}*/
}
