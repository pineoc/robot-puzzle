#include "AppDelegate.h"
#include "firstSplashScene.h"

USING_NS_CC;
using namespace CocosDenshion;

static cocos2d::Size designResolutionSize = cocos2d::Size(1080, 1920);
static cocos2d::Size smallResolutionSize = cocos2d::Size(360, 640);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(750, 1334);
static cocos2d::Size largeResolutionSize = cocos2d::Size(1080, 1920);

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		//glview = GLViewImpl::createWithFullScreen("robotGeneral");
		glview = GLViewImpl::create("robotGeneral");
#if (CC_PLATFORM_WIN32 == CC_TARGET_PLATFORM)
		glview->setFrameSize(360, 640);
#else
		glview->setFrameSize(1080, 1920);
#endif
        director->setOpenGLView(glview);
    }
	//for multi platform
	auto frameRatio = glview->getFrameSize().height / glview->getFrameSize().width;
    
	if (abs(frameRatio - 1.33) < 0.01)
	{
		CCLOG("iPad");
		glview->setDesignResolutionSize(1536, 2048, ResolutionPolicy::SHOW_ALL);
	}
	else if (abs(frameRatio - 1.77) < 0.01)
	{
		CCLOG("phone");
		glview->setDesignResolutionSize(1080, 1920, ResolutionPolicy::SHOW_ALL);
	}
	else if (abs(frameRatio - 1.5) < 0.01)
	{
		CCLOG("iPhone 4");
		glview->setDesignResolutionSize(1080, 1920, ResolutionPolicy::SHOW_ALL);
        
	}
    else
    {
        CCLOG("other ratio");
        glview->setDesignResolutionSize(1080, 1920, ResolutionPolicy::SHOW_ALL);
    }
	

    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    register_all_packages();

    // create a scene. it's an autorelease object
    auto scene = firstSplash::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
