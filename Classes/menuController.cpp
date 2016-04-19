#include "menuController.h"

#include "splashScene.h"
#include "optionScene.h"
#include "p1Scene.h"
#include "p2Scene.h"
#include "p3Scene.h"
#include "p4Scene.h"
#include "p5Scene.h"
#include "p6Scene.h"
#include "finishScene.h"
#include "soundController.h"

menuController::menuController(int _sceneNum)
{
	sceneNum = _sceneNum;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	bool isKor = UserDefault::getInstance()->getBoolForKey("kor");

	//base layout create & setup
	baseLayout = Layout::create();
	baseLayout->setAnchorPoint(Vec2(0.5, 0.5));
	baseLayout->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 205));
	baseLayout->setContentSize(Size(1080, 410));

	//background sprite setup
	layoutBackgroundSpr = Sprite::create("menu1.png");
	layoutBackgroundSpr->setAnchorPoint(Vec2());
	layoutBackgroundSpr->setPosition(Vec2());

	//TODO: animation
	Vector<SpriteFrame*> animFrames(2);
	auto frame1 = SpriteFrame::create("menu1.png", Rect(0, 0, 1080, 259));
	auto frame2 = SpriteFrame::create("menu2.png", Rect(0, 0, 1080, 259));
	animFrames.pushBack(frame1);
	animFrames.pushBack(frame2);
	auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
	auto animate = RepeatForever::create(Animate::create(animation));
	layoutBackgroundSpr->runAction(animate);
	baseLayout->addChild(layoutBackgroundSpr, 0);

	//scrollview setup
	scrollview = ScrollView::create();
	scrollview->setAnchorPoint(Vec2());
	scrollview->setPosition(Vec2(200, 35));
	scrollview->setDirection(ScrollView::Direction::HORIZONTAL);
	scrollview->setContentSize(Size(700, 195));
	scrollview->setInnerContainerSize(Size(1440, 195));
	scrollview->setTouchEnabled(false);
	scrollview->setScrollBarEnabled(false);
	baseLayout->addChild(scrollview, 1);

	//home, option btns setup
	//left arrow btn setup
	homeBtn = Button::create("home.png", "home_s.png");
	homeBtn->setPosition(Vec2(115, 325));
	homeBtn->setTag(20);
	homeBtn->addTouchEventListener(CC_CALLBACK_2(menuController::btnsListener, this));
	baseLayout->addChild(homeBtn, 2);

	//left arrow btn setup
	optionBtn = Button::create("option.png", "option_s.png");
	optionBtn->setPosition(Vec2(965, 325));
	optionBtn->setTag(21);
	optionBtn->addTouchEventListener(CC_CALLBACK_2(menuController::btnsListener, this));
	baseLayout->addChild(optionBtn, 2);

	//arrow btns setup
	//left arrow btn setup
	leftBtn = Button::create("left_arrow.png", "left_arrow_s.png");
	leftBtn->setPosition(Vec2(130, 130));
	leftBtn->setTag(10);
	leftBtn->addTouchEventListener(CC_CALLBACK_2(menuController::btnsListener, this));
	baseLayout->addChild(leftBtn, 2);

	//right arrow btn setup
	rightBtn = Button::create("right_arrow.png", "right_arrow_s.png");
	rightBtn->setPosition(Vec2(950, 130));
	rightBtn->setTag(11);
	rightBtn->addTouchEventListener(CC_CALLBACK_2(menuController::btnsListener, this));
	baseLayout->addChild(rightBtn, 2);

	//btns setup
	
	if(isKor)
		btn1 = Button::create("kmenu_1.png", "kmenu_1_s.png", "kmenu_1_s.png");
	else
		btn1 = Button::create("emenu_1.png", "emenu_1_s.png", "emenu_1_s.png");
	btn1->setPosition(Vec2(100, 190.0 / 2));
	btn1->addTouchEventListener(CC_CALLBACK_2(menuController::btnsListener, this));
	btn1->setTag(1);
	scrollview->addChild(btn1, 1);

	if (isKor)
		btn2 = Button::create("kmenu_2.png", "kmenu_2_s.png", "kmenu_2_s.png");
	else
		btn2 = Button::create("emenu_2.png", "emenu_2_s.png", "emenu_2_s.png");
	btn2->setPosition(Vec2(345, 190.0 / 2));
	btn2->addTouchEventListener(CC_CALLBACK_2(menuController::btnsListener, this));
	btn2->setTag(2);
	scrollview->addChild(btn2, 1);

	if (isKor)
		btn3 = Button::create("kmenu_3.png", "kmenu_3_s.png", "kmenu_3_s.png");
	else
		btn3 = Button::create("emenu_3.png", "emenu_3_s.png", "emenu_3_s.png");
	btn3->setPosition(Vec2(590, 190.0 / 2));
	btn3->addTouchEventListener(CC_CALLBACK_2(menuController::btnsListener, this));
	btn3->setTag(3);
	scrollview->addChild(btn3, 1);

	if (isKor)
		btn4 = Button::create("kmenu_4.png", "kmenu_4_s.png", "kmenu_4_s.png");
	else
		btn4 = Button::create("emenu_4.png", "emenu_4_s.png", "emenu_4_s.png");
	btn4->setPosition(Vec2(835, 190.0 / 2));
	btn4->addTouchEventListener(CC_CALLBACK_2(menuController::btnsListener, this));
	btn4->setTag(4);
	scrollview->addChild(btn4, 1);

	if (isKor)
		btn5 = Button::create("kmenu_5.png", "kmenu_5_s.png", "kmenu_5_s.png");
	else
		btn5 = Button::create("emenu_5.png", "emenu_5_s.png", "emenu_5_s.png");
	btn5->setPosition(Vec2(1080, 190.0 / 2));
	btn5->addTouchEventListener(CC_CALLBACK_2(menuController::btnsListener, this));
	btn5->setTag(5);
	scrollview->addChild(btn5, 1);

	if (isKor)
		btn6 = Button::create("kmenu_6.png", "kmenu_6_s.png", "kmenu_6_s.png");
	else
		btn6 = Button::create("emenu_6.png", "emenu_6_s.png", "emenu_6_s.png");
	btn6->setPosition(Vec2(1325, 190.0 / 2));
	btn6->addTouchEventListener(CC_CALLBACK_2(menuController::btnsListener, this));
	btn6->setTag(6);
	scrollview->addChild(btn6, 1);

	//scrollview set percent with scene number
	setScrollViewPosition();

	//game result popup layout
	resultBaseLayout = Layout::create();
	resultBaseLayout->setContentSize(visibleSize);
	resultBaseLayout->setPosition(Vec2());
	resultBaseLayout->setAnchorPoint(Vec2());
    resultBaseLayout->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
	resultBaseLayout->setBackGroundColor(Color3B::BLACK);
	resultBaseLayout->setBackGroundColorOpacity(255 * POPUPLAYOUT_OPACITY_PERCENT);
	resultBaseLayout->setEnabled(false);

	//replay button
	Button* replayBtn = Button::create("replay.png", "replay_s.png");
	replayBtn->setPosition(Vec2(visibleSize.width / 2 - 200, visibleSize.height / 2 - 600));
	replayBtn->addTouchEventListener(CC_CALLBACK_2(menuController::btnListenerResLayout, this));
	replayBtn->setTag(1);
	resultBaseLayout->addChild(replayBtn, 1);

	//next button
	Button* nextBtn = Button::create("next.png", "next_s.png");
	nextBtn->setPosition(Vec2(visibleSize.width / 2 + 200, visibleSize.height / 2 - 600));
	nextBtn->addTouchEventListener(CC_CALLBACK_2(menuController::btnListenerResLayout, this));
	nextBtn->setTag(2);
	resultBaseLayout->addChild(nextBtn, 1);

	//result sprite of goodjob
	if (isKor)
	{
		Sprite* resultSpr = Sprite::create("kreward.png");
		resultSpr->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));
		resultBaseLayout->addChild(resultSpr, 1);
	}
	else
	{
		string reward_str_arr[3] = {"ereward1.png", "ereward2.png", "ereward3.png" };
		Sprite* resultSpr = Sprite::create(reward_str_arr[RandomHelper::random_int(0,2)]);
		resultSpr->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));
		resultBaseLayout->addChild(resultSpr, 1);
	}
	
}

menuController::~menuController()
{
	baseLayout->autorelease();
}

Layout* menuController::getMenuLayout()
{
	if (baseLayout)
		return baseLayout;
	else
		return NULL;
}

Layout* menuController::getResultLayout()
{
	if (resultBaseLayout)
		return resultBaseLayout;
	else
		return NULL;
}

void menuController::btnListenerResLayout(Ref * pSender, Widget::TouchEventType type)
{
	if (Widget::TouchEventType::ENDED == type) {
		Button* b = (Button*)pSender;
		int tag = b->getTag();
		switch (sceneNum)
		{
		case 1:
			//scene1
			if (1 == tag)
			{//regame
				Scene* s = TransitionFade::create(TRANSITION_FADE_TIME, firstPuzzle::createScene());
				Director::getInstance()->replaceScene(s);
			}
			else
			{//next game
				Scene* s = TransitionFade::create(TRANSITION_FADE_TIME, secondPuzzle::createScene());
				Director::getInstance()->replaceScene(s);
			}
				break;
		case 2:
			//scene2
			if (1 == tag)
			{
				Scene* s = TransitionFade::create(TRANSITION_FADE_TIME, secondPuzzle::createScene());
				Director::getInstance()->replaceScene(s);
			}
			else
			{
				Scene* s = TransitionFade::create(TRANSITION_FADE_TIME, thirdPuzzle::createScene());
				Director::getInstance()->replaceScene(s);
			}
			break;
		case 3:
			//scene3
			if (1 == tag)
			{
				Scene* s = TransitionFade::create(TRANSITION_FADE_TIME, thirdPuzzle::createScene());
				Director::getInstance()->replaceScene(s);
			}
			else
			{
				Scene* s = TransitionFade::create(TRANSITION_FADE_TIME, fourthPuzzle::createScene());
				Director::getInstance()->replaceScene(s);
			}
			break;
		case 4:
			//scene4
			if (1 == tag)
			{
				Scene* s = TransitionFade::create(TRANSITION_FADE_TIME, fourthPuzzle::createScene());
				Director::getInstance()->replaceScene(s);
			}
			else
			{
				Scene* s = TransitionFade::create(TRANSITION_FADE_TIME, fifthPuzzle::createScene());
				Director::getInstance()->replaceScene(s);
			}
			break;
		case 5:
			//scene5
			if (1 == tag)
			{
				Scene* s = TransitionFade::create(TRANSITION_FADE_TIME, fifthPuzzle::createScene());
				Director::getInstance()->replaceScene(s);
			}
			else
			{
				Scene* s = TransitionFade::create(TRANSITION_FADE_TIME, sixthPuzzle::createScene());
				Director::getInstance()->replaceScene(s);
			}
			break;
		case 6:
			//scene6
			if (1 == tag)
			{
				Scene* s = TransitionFade::create(TRANSITION_FADE_TIME, sixthPuzzle::createScene());
				Director::getInstance()->replaceScene(s);
			}
			else
			{
				//sound let's rock and roll
				soundController sc;
				sc.letsrock();
				Scene* s = TransitionFade::create(TRANSITION_FADE_TIME + 2.0f, finish::createScene());
				Director::getInstance()->replaceScene(s);
			}
			break;
		default:
			break;
		}
	}
	
}

void menuController::popUpResultLayout()
{
	soundController sc;
	sc.popUp();

	resultBaseLayout->setLocalZOrder(20);
	resultBaseLayout->setEnabled(true);
}

void menuController::setScrollViewPosition()
{
	switch (sceneNum)
	{
	case 1:
		scrollview->jumpToPercentHorizontal(0.0f);
		btn1->setEnabled(false);
		btn2->setEnabled(true);
		btn3->setEnabled(true);
		btn4->setEnabled(true);
		btn5->setEnabled(true);
		btn6->setEnabled(true);
		break;
	case 2:
		scrollview->jumpToPercentHorizontal(0.0f);
		btn1->setEnabled(true);
		btn2->setEnabled(false);
		btn3->setEnabled(true);
		btn4->setEnabled(true);
		btn5->setEnabled(true);
		btn6->setEnabled(true);
		break;
	case 3:
		scrollview->jumpToPercentHorizontal(0.0f);
		btn1->setEnabled(true);
		btn2->setEnabled(true);
		btn3->setEnabled(false);
		btn4->setEnabled(true);
		btn5->setEnabled(true);
		btn6->setEnabled(true);
		break;
	case 4:
		scrollview->jumpToPercentHorizontal(100.0f);
		btn1->setEnabled(true);
		btn2->setEnabled(true);
		btn3->setEnabled(true);
		btn4->setEnabled(false);
		btn5->setEnabled(true);
		btn6->setEnabled(true);
		break;
	case 5:
		scrollview->jumpToPercentHorizontal(100.0f);
		btn1->setEnabled(true);
		btn2->setEnabled(true);
		btn3->setEnabled(true);
		btn4->setEnabled(true);
		btn5->setEnabled(false);
		btn6->setEnabled(true);
		break;
	case 6:
		scrollview->jumpToPercentHorizontal(100.0f);
		btn1->setEnabled(true);
		btn2->setEnabled(true);
		btn3->setEnabled(true);
		btn4->setEnabled(true);
		btn5->setEnabled(true);
		btn6->setEnabled(false);
		break;
	case 7:
		scrollview->jumpToPercentHorizontal(100.0f);
		break;
	default:
		break;
	}
}

void menuController::btnsListener(Ref* pSender, Widget::TouchEventType type)
{
	if (Widget::TouchEventType::ENDED == type)
	{
		Button* btn = (Button*)pSender;
		int tag = btn->getTag();
		switch (tag)
		{
		case 1://goto bone scene
		{
			Scene* s = TransitionFade::create(TRANSITION_FADE_TIME, firstPuzzle::createScene());
			Director::getInstance()->replaceScene(s);
		}
			break;
		case 2://goto moter scene
		{
			Scene* s = TransitionFade::create(TRANSITION_FADE_TIME, secondPuzzle::createScene());
			Director::getInstance()->replaceScene(s);
		}
			break;
		case 3://goto power scene
		{
			Scene* s = TransitionFade::create(TRANSITION_FADE_TIME, thirdPuzzle::createScene());
			Director::getInstance()->replaceScene(s);
		}
			break;
		case 4://goto hand scene
		{
			Scene* s = TransitionFade::create(TRANSITION_FADE_TIME, fourthPuzzle::createScene());
			Director::getInstance()->replaceScene(s);
		}
			break;
		case 5://goto head scene
		{
			Scene* s = TransitionFade::create(TRANSITION_FADE_TIME, fifthPuzzle::createScene());
			Director::getInstance()->replaceScene(s);
		}
			break;
		case 6://goto armor scene
		{
			Scene* s = TransitionFade::create(TRANSITION_FADE_TIME, sixthPuzzle::createScene());
			Director::getInstance()->replaceScene(s);
		}
			break;
		case 10://left arrow, slide position to left
			scrollview->scrollToPercentHorizontal(0.0f, 1.0f, true);
			break;
		case 11://right arrow, slide position to right
			scrollview->scrollToPercentHorizontal(100.0f, 1.0f, true);
			break;
		case 20://home btn
		{
			Scene* s = TransitionFade::create(TRANSITION_FADE_TIME, Splash::createScene());
			Director::getInstance()->replaceScene(s);
		}
			break;
		case 21://option btn
		{
			Scene* s = TransitionFade::create(TRANSITION_FADE_TIME, option::createScene());
			Director::getInstance()->pushScene(s);
		}
			break;
		default:
			break;
		}
	}
}

