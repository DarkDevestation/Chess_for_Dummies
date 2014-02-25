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
   GameSprite * SwordMaster = new GameSprite("SwordMaster", SWORDMASTER, 1, 1, "Sword.png");
   GameSprite * Sage = new GameSprite("Sage", SAGE, 25, 15, "Sage.png");
   layer1->addSprite(SwordMaster, 2);
   layer1->addSprite(Sage, 3);
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
