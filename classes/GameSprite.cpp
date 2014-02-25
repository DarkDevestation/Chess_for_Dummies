#include "cocos2d.h"
#include "GameSprite.h"
#include "string.h"

using namespace cocos2d;

GameSprite::GameSprite(std::string pieceName, int pieceType, int x, int y, char * fileName) 
{
	this->name = pieceName;
	this->type = pieceType;
	this->location = CCPoint(x * TILE_WIDTH, y * TILE_HEIGHT);

	CCSize iSize = CCDirector::sharedDirector()->getWinSize();
	this->initWithFile(fileName);
	this->setPosition(ccp((x * TILE_WIDTH) - (TILE_WIDTH / 2), (y * TILE_HEIGHT) - (TILE_HEIGHT / 2)));
	//this->setPosition(ccp(iSize.width * startingLocation.x, iSize.height * startingLocation.y));
	this->setAnchorPoint(ccp(0.5f, 0.55f)); // nudge the anchor point upward because of the shadow

	switch(pieceType)
	{
		case WARRIOR:
			// skills
		break;

		case ROGUE:
			// skills
		break;
	}

	this->updateAvailableMoves();   // This causes assertion failure!!!!
	//this->updateValidMoves();
}

GameSprite::~GameSprite() {}

void GameSprite::updateAvailableMoves()
{
	switch(this->type)
	{
		case WARRIOR:
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(3 * TILE_WIDTH, 3 * TILE_HEIGHT)));//(ccpAdd(this->getPosition(), ccp(100, 100)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(1 * TILE_WIDTH, 1 * TILE_HEIGHT)));//(ccpAdd(this->getPosition(), ccp(200, 200)));
		break;

		case ROGUE:
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(-3 * TILE_WIDTH, -3 * TILE_HEIGHT)));//(ccpAdd(this->getPosition(), ccp(0, 100)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(4 * TILE_WIDTH, 1 * TILE_HEIGHT)));//(ccpAdd(this->getPosition(), ccp(100, 0)));
		break;
		
		case SWORDMASTER:
		case SAGE:
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(1 * TILE_WIDTH, 0 * TILE_HEIGHT)));//(ccpAdd(this->getPosition(), ccp(100, 100)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(-1 * TILE_WIDTH, 0 * TILE_HEIGHT)));//(ccpAdd(this->getPosition(), ccp(200, 200)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(2 * TILE_WIDTH, 0 * TILE_HEIGHT)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(-2 * TILE_WIDTH, 0 * TILE_HEIGHT)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(3 * TILE_WIDTH, 0 * TILE_HEIGHT)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(-3 * TILE_WIDTH, 0 * TILE_HEIGHT)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(4 * TILE_WIDTH, 0 * TILE_HEIGHT)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(-4 * TILE_WIDTH, 0 * TILE_HEIGHT)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(5 * TILE_WIDTH, 0 * TILE_HEIGHT)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(-5 * TILE_WIDTH, 0 * TILE_HEIGHT)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(0 * TILE_WIDTH, 1 * TILE_HEIGHT)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(0 * TILE_WIDTH, -1 * TILE_HEIGHT)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(0 * TILE_WIDTH, 2 * TILE_HEIGHT)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(0 * TILE_WIDTH, -2 * TILE_HEIGHT)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(0 * TILE_WIDTH, 3 * TILE_HEIGHT)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(0 * TILE_WIDTH, -3 * TILE_HEIGHT)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(0 * TILE_WIDTH, 4 * TILE_HEIGHT)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(0 * TILE_WIDTH, -4 * TILE_HEIGHT)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(0 * TILE_WIDTH, 5 * TILE_HEIGHT)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(0 * TILE_WIDTH, -5 * TILE_HEIGHT)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(1 * TILE_WIDTH, 1 * TILE_HEIGHT)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(-1 * TILE_WIDTH, 1 * TILE_HEIGHT)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(1 * TILE_WIDTH, -1 * TILE_HEIGHT)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(-1 * TILE_WIDTH, -1 * TILE_HEIGHT)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(2 * TILE_WIDTH, 2 * TILE_HEIGHT)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(-2 * TILE_WIDTH, 2 * TILE_HEIGHT)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(2 * TILE_WIDTH, -2 * TILE_HEIGHT)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(-2 * TILE_WIDTH, -2 * TILE_HEIGHT)));
		break;
	}
}

void GameSprite::updateValidMoves()
{
	//this->validMoves.assign(this->availableMoves.begin(), this->availableMoves.end());
	for (auto i = this->availableMoves.begin(); i != this->availableMoves.end(); i++)
	{
		//if (!(i->x < 0 || i->x > 1000 || i->y < 0 || i->y > 1000))
			this->validMoves.push_back(*i);
	}
}

/*void GameSprite::showValidMoves(Layer * layer)
{
	for (auto i : validMoves)
	{
		CCSprite * tile = new CCSprite();
		tile->initWithFile("Sprite.png");
		tile->setPosition(ccpAdd(this->getPosition(), i)); 
		layer->addChild(tile);
	}
}*/