#include "SimpleAudioEngine.h"
#include "AppDelegate.h"
#include "GameBoard.h"
#include <fstream>

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate() 
{
	//nothing
}

AppDelegate::~AppDelegate() 
{
	//nothing
}

bool AppDelegate::applicationDidFinishLaunching() 
{
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

	SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile("hit.wav", "..\\Resources"));
	SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile("score.wav", "..\\Resources"));
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("background.mp3");

    pDirector->setOpenGLView(pEGLView);
	
    // turn on display FPS
    //pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
	CCScene* scene = CCScene::create();

	//add a background color
	CCLayerColor* background = new CCLayerColor;
	background->initWithColor( ccc4(67, 136, 192, 255) );
	scene->addChild(background, 1);
	background->release();

	// create the game board and add it to the scene
	GameBoard* board = new GameBoard();
	board->setPosition(200,200);
	board->setScale(3.0f);
	scene->addChild(board, 2);
	board->release();

	// setup the board
	board->reset();
   
	//// Writes the name and touch offsets of each sprite to log.txt
	//std::ofstream myfile;
	//myfile.open ("log.txt");
	//for (auto iterator = layer1->sprites.begin(); iterator != layer1->sprites.end(); iterator++)
	//{
		// myfile << iterator->first << ": (" << layer1->touchOffsets[iterator->first].x << ", " << layer1->touchOffsets[iterator->first].y << ")\n";
	//}
	//myfile.close();

	// play music
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background.mp3", true);
   
	// run the first scene
	CCDirector::sharedDirector()->runWithScene(scene);

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() 
{
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() 
{
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
