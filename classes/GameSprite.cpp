#include "cocos2d.h"
#include "GameSprite.h"
#include "string.h"

using namespace cocos2d;

GameSprite::GameSprite(std::string pieceName, int pieceType, int player, int x, int y, char * fileName) 
{
	this->name = pieceName;
	this->type = pieceType;
	this->player = player;
	// (x, y) tile position of this sprite
	//this->location = CCPoint(x, y);

	CCSize iSize = CCDirector::sharedDirector()->getWinSize();
	// filename is the png file
	this->initWithFile(fileName);
	// The subtractions here are so the sprite is centered on the tile
	this->setPosition(ccp(x*TILE_WIDTH + SPRITE_WIDTH/2, y*TILE_HEIGHT + SPRITE_HEIGHT/2 + SPRITE_HEIGHT_OFFSET));
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

	updateAvailableMoves();
}

GameSprite::~GameSprite() {}

void GameSprite::updateAvailableMoves()
{
	//clear any old moves
	for(int i=0; i<availableMoves.size(); i++) this->availableMoves[i].clear();
	this->availableMoves.clear();

	//add new move positions
	int yOffset = - SPRITE_HEIGHT/4 - SPRITE_HEIGHT_OFFSET;
	switch(this->type)
	{
		case ROOK:
			this->availableMoves.push_back(std::vector<CCPoint>()); //front
			this->availableMoves.push_back(std::vector<CCPoint>()); //back
			this->availableMoves.push_back(std::vector<CCPoint>()); //right
			this->availableMoves.push_back(std::vector<CCPoint>()); //left
			for (int i = 1; i < 8; i++)
			{
				this->availableMoves[0].push_back(this->getPosition() + CCPoint(i * TILE_WIDTH, 0 + yOffset)); //front
				this->availableMoves[1].push_back(this->getPosition() + CCPoint(-i * TILE_WIDTH, 0 + yOffset)); //back
				this->availableMoves[2].push_back(this->getPosition() + CCPoint(0, i * TILE_HEIGHT + yOffset)); //left
				this->availableMoves[3].push_back(this->getPosition() + CCPoint(0, -i * TILE_HEIGHT + yOffset)); //right
			}
		break;

		case KNIGHT:
			this->availableMoves.push_back(std::vector<CCPoint>()); //move1
			this->availableMoves.push_back(std::vector<CCPoint>()); //move2
			this->availableMoves.push_back(std::vector<CCPoint>()); //move3
			this->availableMoves.push_back(std::vector<CCPoint>()); //move4
			this->availableMoves.push_back(std::vector<CCPoint>()); //move5
			this->availableMoves.push_back(std::vector<CCPoint>()); //move6
			this->availableMoves.push_back(std::vector<CCPoint>()); //move7
			this->availableMoves.push_back(std::vector<CCPoint>()); //move8
			this->availableMoves[0].push_back(this->getPosition() + CCPoint(1 * TILE_WIDTH, 2 * TILE_HEIGHT + yOffset)); //move1
			this->availableMoves[1].push_back(this->getPosition() + CCPoint(1 * TILE_WIDTH, -2 * TILE_HEIGHT + yOffset)); //move2
			this->availableMoves[2].push_back(this->getPosition() + CCPoint(2 * TILE_WIDTH, 1 * TILE_HEIGHT + yOffset)); //move3
			this->availableMoves[3].push_back(this->getPosition() + CCPoint(2 * TILE_WIDTH, -1 * TILE_HEIGHT + yOffset)); //move4
			this->availableMoves[4].push_back(this->getPosition() + CCPoint(-1 * TILE_WIDTH, 2 * TILE_HEIGHT + yOffset)); //move5
			this->availableMoves[5].push_back(this->getPosition() + CCPoint(-1 * TILE_WIDTH, -2 * TILE_HEIGHT + yOffset)); //move6
			this->availableMoves[6].push_back(this->getPosition() + CCPoint(-2 * TILE_WIDTH, 1 * TILE_HEIGHT + yOffset)); //move7
			this->availableMoves[7].push_back(this->getPosition() + CCPoint(-2 * TILE_WIDTH, -1 * TILE_HEIGHT + yOffset)); //move8
		break;
		
		case BISHOP:
			this->availableMoves.push_back(std::vector<CCPoint>()); //front right
			this->availableMoves.push_back(std::vector<CCPoint>()); //front left
			this->availableMoves.push_back(std::vector<CCPoint>()); //back right
			this->availableMoves.push_back(std::vector<CCPoint>()); //back left
			for (int i = 1; i < 8; i++)
			{
				this->availableMoves[0].push_back(this->getPosition() + CCPoint(i * TILE_WIDTH, i * TILE_HEIGHT + yOffset)); //front right
				this->availableMoves[1].push_back(this->getPosition() + CCPoint(i * TILE_WIDTH, -i * TILE_HEIGHT + yOffset)); //front left
				this->availableMoves[2].push_back(this->getPosition() + CCPoint(-i * TILE_WIDTH, i * TILE_HEIGHT + yOffset)); //back right
				this->availableMoves[3].push_back(this->getPosition() + CCPoint(-i * TILE_WIDTH, -i * TILE_HEIGHT + yOffset)); //back left
			}	
		break;

		case KING:
			this->availableMoves.push_back(std::vector<CCPoint>()); //move1
			this->availableMoves.push_back(std::vector<CCPoint>()); //move2
			this->availableMoves.push_back(std::vector<CCPoint>()); //move3
			this->availableMoves.push_back(std::vector<CCPoint>()); //move4
			this->availableMoves.push_back(std::vector<CCPoint>()); //move5
			this->availableMoves.push_back(std::vector<CCPoint>()); //move6
			this->availableMoves.push_back(std::vector<CCPoint>()); //move7
			this->availableMoves.push_back(std::vector<CCPoint>()); //move8
			this->availableMoves[0].push_back(this->getPosition() + CCPoint(-TILE_WIDTH, TILE_HEIGHT + yOffset)); //move1
			this->availableMoves[1].push_back(this->getPosition() + CCPoint(0, TILE_HEIGHT + yOffset)); //move2
			this->availableMoves[2].push_back(this->getPosition() + CCPoint(TILE_WIDTH, TILE_HEIGHT + yOffset)); //move3
			this->availableMoves[3].push_back(this->getPosition() + CCPoint(-TILE_WIDTH, 0 + yOffset)); //move4
			this->availableMoves[4].push_back(this->getPosition() + CCPoint(TILE_WIDTH, 0 + yOffset)); //move5
			this->availableMoves[5].push_back(this->getPosition() + CCPoint(-TILE_WIDTH, -TILE_HEIGHT + yOffset)); //move6
			this->availableMoves[6].push_back(this->getPosition() + CCPoint(0, -TILE_HEIGHT + yOffset)); //move7
			this->availableMoves[7].push_back(this->getPosition() + CCPoint(TILE_WIDTH, -TILE_HEIGHT + yOffset)); //move8
		break;

		case QUEEN:
			this->availableMoves.push_back(std::vector<CCPoint>()); //front
			this->availableMoves.push_back(std::vector<CCPoint>()); //back
			this->availableMoves.push_back(std::vector<CCPoint>()); //right
			this->availableMoves.push_back(std::vector<CCPoint>()); //left
			this->availableMoves.push_back(std::vector<CCPoint>()); //front right
			this->availableMoves.push_back(std::vector<CCPoint>()); //front left
			this->availableMoves.push_back(std::vector<CCPoint>()); //back right
			this->availableMoves.push_back(std::vector<CCPoint>()); //back left
			for (int i = 1; i < 8; i++)
			{
				this->availableMoves[0].push_back(this->getPosition() + CCPoint(i * TILE_WIDTH, 0 + yOffset)); //front
				this->availableMoves[1].push_back(this->getPosition() + CCPoint(-i * TILE_WIDTH, 0 + yOffset)); //back
				this->availableMoves[2].push_back(this->getPosition() + CCPoint(0, i * TILE_HEIGHT + yOffset)); //right
				this->availableMoves[3].push_back(this->getPosition() + CCPoint(0, -i * TILE_HEIGHT + yOffset)); //left
				this->availableMoves[4].push_back(this->getPosition() + CCPoint(i * TILE_WIDTH, i * TILE_HEIGHT + yOffset)); //front right
				this->availableMoves[5].push_back(this->getPosition() + CCPoint(i * TILE_WIDTH, -i * TILE_HEIGHT + yOffset)); //front left
				this->availableMoves[6].push_back(this->getPosition() + CCPoint(-i * TILE_WIDTH, i * TILE_HEIGHT + yOffset)); //back right
				this->availableMoves[7].push_back(this->getPosition() + CCPoint(-i * TILE_WIDTH, -i * TILE_HEIGHT + yOffset)); //back left
			}
		break;

		case PAWN:
			this->availableMoves.push_back(std::vector<CCPoint>()); //move1
			if(this->player == 1) this->availableMoves[0].push_back(this->getPosition() + CCPoint(0, TILE_HEIGHT + yOffset));
			else this->availableMoves[0].push_back(this->getPosition() + CCPoint(0, -TILE_HEIGHT + yOffset));
		break;
	}
}