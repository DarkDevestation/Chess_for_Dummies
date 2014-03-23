#include "GameBoard.h"
#include "GameSprite.h"
#include "SimpleAudioEngine.h"

#define BLUE_HIGHLIGHT_TAG 0
#define RED_HIGHLIGHT_TAG 1
#define YELLOW_HIGHLIGHT_TAG 2

using namespace cocos2d;

/// Default constructor
GameBoard::GameBoard()
	: PlayersTurn(1), SelectedPiece(0)
{
	//enable touch
	this->setTouchEnabled(true);

	//create text items
	whosTurn = new CCLabelTTF();
	whosTurn->initWithString("Player Turn", "Courier New", 16.0f);
	whosTurn->setPosition(CCPoint((40*NUM_COLUMNS)/2, 40*NUM_ROWS + 60));
	this->addChild(whosTurn);
	whosTurn->release();


	//create the layers
	BoardLayer = new CCLayer();
	this->addChild(BoardLayer, 1);

	HighlightLayer = new CCLayer();
	this->addChild(HighlightLayer, 2);

	for(int i=0; i<NUM_ROWS; i++)
	{
		RowLayer[i] = new CCLayer();
		this->addChild(RowLayer[i], NUM_ROWS-i+2);
	}

	//create the board sprites
	for(int i=0; i<NUM_ROWS; i++)
	{
		for(int j=0; j<NUM_COLUMNS; j++)
		{
			CCSprite* square = new CCSprite();
			if((j%2==0 && i%2==1) || (j%2==1 && i%2==0)) square->initWithFile("blackTile.png");
			else square->initWithFile("whiteTile.png");
			square->setPosition(CCPoint(i*40 + 20, j*40 + 20));
			this->addChild(square);
			square->release();
		}
	}
}

/// Destructor
GameBoard::~GameBoard()
{
	//this is probably redundant, but doesn't hurt
	this->removeAllChildren();

	// unset this so we unregister with the touch dispatcher
	this->setTouchEnabled(false);
}
		
/// Resets the board to a new game
void GameBoard::reset()
{
	//reset gameplay variables
	PlayersTurn = 1;

	//reset text
	whosTurn->setString("Player 1's Turn");

	//reset highlights
	SelectedPiece = 0;
	showValidMoves(0);

	//remove all existing pieces
	for(int i=0; i<NUM_ROWS; i++)
		RowLayer[i]->removeAllChildren();

	//setup the traditional board
	GameSprite* piece;
	piece = new GameSprite("P1_rook_1", ROOK, 1, 0, 0, "pieces/Rook0.png");
	RowLayer[0]->addChild(piece);
	piece->release();
	piece = new GameSprite("P1_knight_1", KNIGHT, 1, 1, 0, "pieces/Knight0.png");
	RowLayer[0]->addChild(piece);
	piece->release();
	piece = new GameSprite("P1_bishop_1", BISHOP, 1, 2, 0, "pieces/Bishop0.png");
	RowLayer[0]->addChild(piece);
	piece->release();
	piece = new GameSprite("P1_king", KING, 1, 3, 0, "pieces/King0.png");
	RowLayer[0]->addChild(piece);
	piece->release();
	piece = new GameSprite("P1_queen", QUEEN, 1, 4, 0, "pieces/Queen0.png");
	RowLayer[0]->addChild(piece);
	piece->release();
	piece = new GameSprite("P1_bishop_2", BISHOP, 1, 5, 0, "pieces/Bishop0.png");
	RowLayer[0]->addChild(piece);
	piece->release();
	piece = new GameSprite("P1_knight_2", KNIGHT, 1, 6, 0, "pieces/Knight0.png");
	RowLayer[0]->addChild(piece);
	piece->release();
	piece = new GameSprite("P1_rook_2", ROOK, 1, 7, 0, "pieces/Rook0.png");
	RowLayer[0]->addChild(piece);
	piece->release();
	for (int i=0; i<8; i++)
	{
		piece = new GameSprite("P1_pawn_2", PAWN, 1, i, 1, "pieces/Pawn0.png");
		RowLayer[1]->addChild(piece);
		piece->release();
	}

	piece = new GameSprite("P2_rook_1", ROOK, 2, 0, 7, "pieces/Rook1.png");
	RowLayer[7]->addChild(piece);
	piece->release();
	piece = new GameSprite("P2_knight_1", KNIGHT, 2, 1, 7, "pieces/Knight1.png");
	RowLayer[7]->addChild(piece);
	piece->release();
	piece = new GameSprite("P2_bishop_1", BISHOP, 2, 2, 7, "pieces/Bishop1.png");
	RowLayer[7]->addChild(piece);
	piece->release();
	piece = new GameSprite("P2_king", KING, 2, 3, 7, "pieces/King1.png");
	RowLayer[7]->addChild(piece);
	piece->release();
	piece = new GameSprite("P2_queen", QUEEN, 2, 4, 7, "pieces/Queen1.png");
	RowLayer[7]->addChild(piece);
	piece->release();
	piece = new GameSprite("P2_bishop_2", BISHOP, 2, 5, 7, "pieces/Bishop1.png");
	RowLayer[7]->addChild(piece);
	piece->release();
	piece = new GameSprite("P2_knight_2", KNIGHT, 2, 6, 7, "pieces/Knight1.png");
	RowLayer[7]->addChild(piece);
	piece->release();
	piece = new GameSprite("P2_rook_2", ROOK, 2, 7, 7, "pieces/Rook1.png");
	RowLayer[7]->addChild(piece);
	piece->release();
	for (int i=0; i<8; i++)
	{
		piece = new GameSprite("P2_pawn_2", PAWN, 2, i, 6, "pieces/Pawn1.png");
		RowLayer[6]->addChild(piece);
		piece->release();
	}
}

void GameBoard::showValidMoves(GameSprite* piece)
{
	//first remove any previous highlights
	HighlightLayer->removeAllChildren();

	//add move highlight
	if(piece)
	{
		//add selected piece highlight
		CCSprite* pieceHighlight = new CCSprite();
		pieceHighlight->initWithFile("highlightYellow.png");
		pieceHighlight->setTag(YELLOW_HIGHLIGHT_TAG);
		pieceHighlight->setPosition(piece->getPosition() + CCPoint(0, -SPRITE_WIDTH/2 - SPRITE_HEIGHT_OFFSET));
		HighlightLayer->addChild(pieceHighlight);
		pieceHighlight->release();

		//loop through paths
		for(int p=0; p<piece->availableMoves.size(); p++)
		{
			//loop through moves in path
			bool exitPath = false;
			for(int i=0; i<piece->availableMoves[p].size() && !exitPath; i++)
			{
				//if the move is on the board
				if(piece->availableMoves[p][i].x < 40*8 && piece->availableMoves[p][i].y < 40*8
					&& piece->availableMoves[p][i].x > 0 && piece->availableMoves[p][i].y > 0)
				{
					//other piece to check if there is a collision
					GameSprite* collisionPiece = 0;

					//check for a collision with another piece
					for(int j=0; j<NUM_ROWS; j++)
					{
						for(int k=0; k<RowLayer[j]->getChildrenCount(); k++)
						{
							GameSprite* tryPiece = (GameSprite*)RowLayer[j]->getChildren()->objectAtIndex(k);
							if(ccpDistance(tryPiece->getPosition() + CCPoint(0, -SPRITE_WIDTH/2 - SPRITE_HEIGHT_OFFSET),
								piece->availableMoves[p][i]) < TILE_WIDTH/2) //other piece collision
							{
								collisionPiece = tryPiece;
							}
						}
					}

					//create the highlight
					CCSprite* highlight = new CCSprite();

					//choose color based on collision
					if(collisionPiece) //there was a collision
					{
						if(collisionPiece->player == PlayersTurn) //friendly piece
						{
							highlight->initWithFile("highlightYellow.png");
							highlight->setTag(YELLOW_HIGHLIGHT_TAG);
						}
						else //enemy
						{
							highlight->initWithFile("highlightRed.png");
							highlight->setTag(RED_HIGHLIGHT_TAG);
						}

						//do not continue to highlight this path, since there's something in the way
						exitPath = true;
					}
					else //no collision
					{
						highlight->initWithFile("highlightBlue.png");
						highlight->setTag(BLUE_HIGHLIGHT_TAG);
					}
				
					//add te highlight to the board
					highlight->setPosition(piece->availableMoves[p][i]);
					HighlightLayer->addChild(highlight);
					highlight->release();

				}//endif move is on the board
			}//endloop through moves in a path
		}//endloop through paths
	}//endif moving piece was valid
}

void GameBoard::movePiece(GameSprite* piece, CCSprite* highlight)
{
	//first get the current row the piece sits on, before we change it's position
	int currentRow = (piece->getPosition().y - SPRITE_WIDTH/2 - SPRITE_HEIGHT_OFFSET)/TILE_WIDTH;

	//updates the pieces position
	piece->setPosition(highlight->getPosition() + CCPoint(0, SPRITE_WIDTH/2 + SPRITE_HEIGHT_OFFSET));
	piece->updateAvailableMoves();

	//move piece to the appropriate row layer for correct drawing of pieces in front or behind
	int newRow = (piece->getPosition().y - SPRITE_WIDTH/2 - SPRITE_HEIGHT_OFFSET)/TILE_WIDTH;
	piece->retain();
	RowLayer[currentRow]->removeChild(piece);
	RowLayer[newRow]->addChild(piece);
	piece->release();
}

void GameBoard::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
	//loop through all touches
	for( auto it = touches->begin(); it != touches->end(); it++) 
	{
		CCTouch* touch = dynamic_cast<CCTouch*>(*it);
		
		//did we touch a piece?
		for(int i=0; i<NUM_ROWS; i++)
		{
			for(int j=0; j<RowLayer[i]->getChildrenCount(); j++)
			{
				GameSprite* piece = (GameSprite*)RowLayer[i]->getChildren()->objectAtIndex(j);
				if(piece->player == PlayersTurn)//piece belongs to current player
				{
					if(ccpDistance((piece->getPosition() + CCPoint(0, -SPRITE_WIDTH/2 - SPRITE_HEIGHT_OFFSET))*this->getScale() + this->getPosition(), 
						CCDirector::sharedDirector()->convertToGL(touch->getLocationInView())) 
						< (TILE_WIDTH*this->getScale())/2.0f)
					{
						//play sound effect, set selected piece and show available moves
						CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("hit.wav");
						SelectedPiece = piece;
						showValidMoves(piece);
						return; //touch handled
					}
				}
			}
		}

		//did we touch a move highlight?
		for(int j=0; j<HighlightLayer->getChildrenCount(); j++)
		{
			CCSprite* highlight = (CCSprite*)HighlightLayer->getChildren()->objectAtIndex(j);
			if(ccpDistance(highlight->getPosition()*this->getScale() + this->getPosition(), 
				CCDirector::sharedDirector()->convertToGL(touch->getLocationInView())) 
				< (TILE_WIDTH*this->getScale())/2.0f)
			{
				if(highlight->getTag() == BLUE_HIGHLIGHT_TAG) //if highlight was a valid move
				{
					//play sound effect, move the piece, switch players turn, remove move highilights
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("hit.wav");
					movePiece(SelectedPiece, highlight);
					SelectedPiece = 0;
					PlayersTurn = PlayersTurn%2 + 1;
					if(PlayersTurn == 1) whosTurn->setString("Player 1's Turn");
					else whosTurn->setString("Player 2's Turn");
					showValidMoves(0);
					return; //touch handled
				}

				else if(highlight->getTag() == RED_HIGHLIGHT_TAG)  //if highlight is an enemy piece
				{
					CCPoint pos;
					GameSprite *piece1;
					int row, count;
					//play sound effect
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("hit.wav");
					//get position of enemy peice
					pos = highlight->getPosition() + CCPoint(0, SPRITE_WIDTH/2 + SPRITE_HEIGHT_OFFSET);
					row = (pos.y - SPRITE_WIDTH/2 - SPRITE_HEIGHT_OFFSET)/TILE_WIDTH; 

					//cycle through pieces in the row checking their position against the highlights position until piece to be removed is found
					count = RowLayer[row]->getChildren()->count();
					for(count = count; count > 0; count--)
					{
						piece1 = (GameSprite*)RowLayer[row]->getChildren()->objectAtIndex(count-1);
						if(piece1->getPosition().x == pos.x && piece1->getPosition().y == pos.y)
							break;
					}
					
					//remove the enemy piece
					RowLayer[row]->removeChild(piece1);
					//move the piece, switch players turn, remove move highilights
					movePiece(SelectedPiece, highlight);
					SelectedPiece = 0;
					PlayersTurn = PlayersTurn%2 + 1;
					if(PlayersTurn == 1) whosTurn->setString("Player 1's Turn");
					else whosTurn->setString("Player 2's Turn");
					showValidMoves(0);
					return; //touch handled
				}
			}
		}
	}
}

void GameBoard::ccTouchesMoved(CCSet* touches, CCEvent* event)
{
	//nothing
}

void GameBoard::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
	//nothing
}