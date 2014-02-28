#include "cocos2d.h"
#include "GameSprite.h"
#include "string.h"

using namespace cocos2d;

GameSprite::GameSprite(std::string pieceName, int pieceType, bool p1, int x, int y, char * fileName) 
{
	this->name = pieceName;
	this->type = pieceType;
	this->player1 = p1;
	// (x, y) tile position of this sprite
	this->location = CCPoint(x, y);

	CCSize iSize = CCDirector::sharedDirector()->getWinSize();
	// filename is the png file
	this->initWithFile(fileName);
	// The subtractions here are so the sprite is centered on the tile
	this->setPosition(ccp((x * TILE_WIDTH) - (TILE_WIDTH / 2), (y * TILE_HEIGHT) - (TILE_HEIGHT / 2)));
	this->setAnchorPoint(ccp(0.5f, 0.55f)); // nudge the anchor point upward because of the shadow

	switch(pieceType)
	{
		//case WARRIOR:
			// skills
		//break;

		//case ROGUE:
			// skills
		//break;
	}

	this->updateAvailableMoves();
}

GameSprite::~GameSprite() {}

void GameSprite::updateAvailableMoves()
{
	switch(this->type)
	{
		case ROOK:
			for (int i = 1; i < 8; i++)
			{
				this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(i * TILE_WIDTH, 0)));
				this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(-i * TILE_WIDTH, 0)));
				this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(0, i * TILE_HEIGHT)));
				this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(0, -i * TILE_HEIGHT)));
			}
		break;

		case KNIGHT:
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(1 * TILE_WIDTH, 2 * TILE_HEIGHT)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(1 * TILE_WIDTH, -2 * TILE_HEIGHT)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(2 * TILE_WIDTH, 1 * TILE_HEIGHT)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(2 * TILE_WIDTH, -1 * TILE_HEIGHT)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(-1 * TILE_WIDTH, 2 * TILE_HEIGHT)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(-1 * TILE_WIDTH, -2 * TILE_HEIGHT)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(-2 * TILE_WIDTH, 1 * TILE_HEIGHT)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(-2 * TILE_WIDTH, -1 * TILE_HEIGHT)));
		break;
		
		case BISHOP:
			for (int i = 1; i < 8; i++)
			{
				this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(i * TILE_WIDTH, i * TILE_HEIGHT)));
				this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(i * TILE_WIDTH, -i * TILE_HEIGHT)));
				this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(-i * TILE_WIDTH, i * TILE_HEIGHT)));
				this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(-i * TILE_WIDTH, -i * TILE_HEIGHT)));
			}	
		break;

		case KING:
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(-TILE_WIDTH, TILE_HEIGHT)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(0, TILE_HEIGHT)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(TILE_WIDTH, TILE_HEIGHT)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(-TILE_WIDTH, 0)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(TILE_WIDTH, 0)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(-TILE_WIDTH, -TILE_HEIGHT)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(0, -TILE_HEIGHT)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(TILE_WIDTH, -TILE_HEIGHT)));
		break;

		case QUEEN:
			for (int i = 1; i < 8; i++)
			{
				this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(i * TILE_WIDTH, 0)));
				this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(-i * TILE_WIDTH, 0)));
				this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(0, i * TILE_HEIGHT)));
				this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(0, -i * TILE_HEIGHT)));
				this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(i * TILE_WIDTH, i * TILE_HEIGHT)));
				this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(i * TILE_WIDTH, -i * TILE_HEIGHT)));
				this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(-i * TILE_WIDTH, i * TILE_HEIGHT)));
				this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(-i * TILE_WIDTH, -i * TILE_HEIGHT)));
			}
		break;

		case PAWN:
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(0, this->player1 * TILE_HEIGHT + !this->player1 * -TILE_HEIGHT)));
			/*this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(1 * TILE_WIDTH, 0 * TILE_HEIGHT)));
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(-1 * TILE_WIDTH, 0 * TILE_HEIGHT)));
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
			this->availableMoves.push_back(ccpAdd(this->getPosition(), CCPoint(-2 * TILE_WIDTH, -2 * TILE_HEIGHT)));*/
		break;
	}
}

// This function is not ebing implemented. Ignore.
void GameSprite::updateValidMoves()
{
	//this->validMoves.assign(this->availableMoves.begin(), this->availableMoves.end());
	for (auto i = this->availableMoves.begin(); i != this->availableMoves.end(); i++)
	{
		//if (!(i->x < 0 || i->x > 1000 || i->y < 0 || i->y > 1000))
			this->validMoves.push_back(*i);
	}
}

// This function is not ebing implemented. Ignore.
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