#ifndef __GAME_BOARD_H__
#define __GAME_BOARD_H__

#define NUM_ROWS 8
#define NUM_COLUMNS 8

#include "cocos2d.h"
#include "string.h"

class GameSprite;

using namespace cocos2d;

class GameBoard : public CCLayer
{
	public:
		/// Default constructor
		GameBoard();

		/// Destructor
		~GameBoard();
		
		/// Resets the board to a new game
		void reset();

	private:		
		// we are multi-touch enabled, so we must use the ccTouches functions vs the ccTouch functions
		void ccTouchesBegan(CCSet* touches, CCEvent* event);
		void ccTouchesMoved(CCSet* touches, CCEvent* event);
		void ccTouchesEnded(CCSet* touches, CCEvent* event);

		/// Creates the higlights for available moves given a particular piece. (passing 0 will clear all highlights)
		void showValidMoves(GameSprite* piece);

		/// Moves a piece to a highlighted spot
		void movePiece(GameSprite* piece, CCSprite* highlight);

		/// Layers for the board
		CCLayer* BoardLayer;
		CCLayer* HighlightLayer;
		CCLayer* RowLayer[NUM_ROWS];

		/// Text for displaying game information
		CCLabelTTF* whosTurn;

		/// Keeps track of who's turn it is
		int PlayersTurn;

		/// Keeps track of the selected piece move highlights are shown for
		GameSprite* SelectedPiece;

		/// The background color layer
		CCLayerColor* colorLayer;
};

#endif