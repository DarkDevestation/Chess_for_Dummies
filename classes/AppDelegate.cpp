#include "SimpleAudioEngine.h"
#include "AppDelegate.h"
//#include "HelloWorldScene.h"
#include "Layer.h"
#include <fstream>

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

	SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile("hit.wav", "..\\Resources"));
	SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile("score.wav", "..\\Resources"));
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("background.mp3");

    pDirector->setOpenGLView(pEGLView);
	
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
	CCScene* scene = CCScene::create();

   // add the layer
   Layer * layer1 = new Layer();

   GameSprite * P1_rook_1 = new GameSprite("P1_rook_1", ROOK, true, 1, 1, "Sword.png");
   GameSprite * P1_knight_1 = new GameSprite("P1_knight_1", KNIGHT, true, 2, 1, "Sword.png");
   GameSprite * P1_bishop_1 = new GameSprite("P1_bishop_1", BISHOP, true, 3, 1, "Sword.png");
   GameSprite * P1_king = new GameSprite("P1_king", KING, true, 4, 1, "Sword.png");
   GameSprite * P1_queen = new GameSprite("P1_queen", QUEEN, true, 5, 1, "Sword.png");
   GameSprite * P1_bishop_2 = new GameSprite("P1_bishop_2", BISHOP, true, 6, 1, "Sword.png");
   GameSprite * P1_knight_2 = new GameSprite("P1_knight_2", KNIGHT, true, 7, 1, "Sword.png");
   GameSprite * P1_rook_2 = new GameSprite("P1_rook_2", ROOK, true, 8, 1, "Sword.png");
   std::vector<GameSprite *> P1_pawns;
   for (int i = 0; i < 8; i++)
   {
	   P1_pawns.push_back(new GameSprite((std::string("P1_pawn_") + std::to_string(i+1)), PAWN, true, i+1, 2, "Sword.png"));
	   layer1->addSprite(P1_pawns[i], 3);
   }

   GameSprite * P2_rook_1 = new GameSprite("P2_rook_1", ROOK, false, 1, 8, "Sage.png");
   GameSprite * P2_knight_1 = new GameSprite("P2_knight_1", KNIGHT, false, 2, 8, "Sage.png");
   GameSprite * P2_bishop_1 = new GameSprite("P2_bishop_1", BISHOP, false, 3, 8, "Sage.png");
   GameSprite * P2_king = new GameSprite("P2_king", KING, false, 4, 8, "Sage.png");
   GameSprite * P2_queen = new GameSprite("P2_queen", QUEEN, false, 5, 8, "Sage.png");
   GameSprite * P2_bishop_2 = new GameSprite("P2_bishop_2", BISHOP, false, 6, 8, "Sage.png");
   GameSprite * P2_knight_2 = new GameSprite("P2_knight_2", KNIGHT, false, 7, 8, "Sage.png");
   GameSprite * P2_rook_2 = new GameSprite("P2_rook_2", ROOK, false, 8, 8, "Sage.png");
   std::vector<GameSprite *> P2_pawns;
   for (int i = 0; i < 8; i++)
   {
	   P2_pawns.push_back(new GameSprite((std::string("P2_pawn_") + std::to_string(i+1)), PAWN, false, i+1, 7, "Sage.png"));
	   layer1->addSprite(P2_pawns[i], 3);
   }

   /*GameSprite * P1_rook_1 = new GameSprite("P1_rook_1", ROOK, true, 1, 1, "Rook0.png");
   GameSprite * P1_knight_1 = new GameSprite("P1_knight_1", KNIGHT, true, 2, 1, "Knight0.png");
   GameSprite * P1_bishop_1 = new GameSprite("P1_bishop_1", BISHOP, true, 3, 1, "Bishop0.png");
   GameSprite * P1_king = new GameSprite("P1_king", KING, true, 4, 1, "King0.png");
   GameSprite * P1_queen = new GameSprite("P1_queen", QUEEN, true, 5, 1, "Queen0.png");
   GameSprite * P1_bishop_2 = new GameSprite("P1_bishop_2", BISHOP, true, 6, 1, "Bishop0.png");
   GameSprite * P1_knight_2 = new GameSprite("P1_knight_2", KNIGHT, true, 7, 1, "Knight0.png");
   GameSprite * P1_rook_2 = new GameSprite("P1_rook_2", ROOK, true, 8, 1, "Rook0.png");
   std::vector<GameSprite *> P1_pawns;
   for (int i = 0; i < 8; i++)
   {
	   P1_pawns.push_back(new GameSprite((std::string("P1_pawn_") + std::to_string(i+1)), PAWN, true, i+1, 2, "Pawn0.png"));
	   layer1->addSprite(P1_pawns[i], 3);
   }

   GameSprite * P2_rook_1 = new GameSprite("P2_rook_1", ROOK, false, 1, 8, "Rook1.png");
   GameSprite * P2_knight_1 = new GameSprite("P2_knight_1", KNIGHT, false, 2, 8, "Knight1.png");
   GameSprite * P2_bishop_1 = new GameSprite("P2_bishop_1", BISHOP, false, 3, 8, "Bishop1.png");
   GameSprite * P2_king = new GameSprite("P2_king", KING, false, 4, 8, "King1.png");
   GameSprite * P2_queen = new GameSprite("P2_queen", QUEEN, false, 5, 8, "Queen1.png");
   GameSprite * P2_bishop_2 = new GameSprite("P2_bishop_2", BISHOP, false, 6, 8, "Bishop1.png");
   GameSprite * P2_knight_2 = new GameSprite("P2_knight_2", KNIGHT, false, 7, 8, "Knight1.png");
   GameSprite * P2_rook_2 = new GameSprite("P2_rook_2", ROOK, false, 8, 8, "Rook1.png");
   std::vector<GameSprite *> P2_pawns;
   for (int i = 0; i < 8; i++)
   {
	   P2_pawns.push_back(new GameSprite((std::string("P2_pawn_") + std::to_string(i+1)), PAWN, false, i+1, 7, "Pawn1.png"));
	   layer1->addSprite(P2_pawns[i], 3);
   }*/

   layer1->addSprite(P1_rook_1, 3);
   layer1->addSprite(P1_knight_1, 3);
   layer1->addSprite(P1_bishop_1, 3);
   layer1->addSprite(P1_king, 3);
   layer1->addSprite(P1_queen, 3);
   layer1->addSprite(P1_bishop_2, 3);
   layer1->addSprite(P1_knight_2, 3);
   layer1->addSprite(P1_rook_2, 3);

   layer1->addSprite(P2_rook_1, 3);
   layer1->addSprite(P2_knight_1, 3);
   layer1->addSprite(P2_bishop_1, 3);
   layer1->addSprite(P2_king, 3);
   layer1->addSprite(P2_queen, 3);
   layer1->addSprite(P2_bishop_2, 3);
   layer1->addSprite(P2_knight_2, 3);
   layer1->addSprite(P2_rook_2, 3);

   scene->addChild(layer1, 1);

   std::ofstream myfile;
   myfile.open ("log.txt");

   // Writes the name and touch offsets of each sprite to log.txt
   for (auto iterator = layer1->sprites.begin(); iterator != layer1->sprites.end(); iterator++)
   {
	   myfile << iterator->first << ": (" << layer1->touchOffsets[iterator->first].x << ", " << layer1->touchOffsets[iterator->first].y << ")\n";
   }

   //myfile << layer1->sprites["Rogue"]->validMoves.size() << " " << layer1->sprites["Warrior"]->validMoves.size() << std::endl;

   myfile.close();
   
   // run the first scene
   CCDirector::sharedDirector()->runWithScene(scene);
   
   layer1->release();

   return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
