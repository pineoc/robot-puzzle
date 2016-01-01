
#include "menuController.h"

#include "p1Scene.h"
#include "p2Scene.h"
#include "p3Scene.h"
#include "p4Scene.h"
#include "p5Scene.h"
#include "p6Scene.h"
#include "p7Scene.h"

menuController::menuController(int _sceneNum)
{
	sceneNum = _sceneNum;

	Size visibleSize = Director::getInstance()->getVisibleSize();

	//base layout create & setup
	baseLayout = Layout::create();
	baseLayout->setAnchorPoint(Vec2(0.5, 0.5));
	baseLayout->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 205));
	baseLayout->setSize(Size(1080, 410));

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
	scrollview->setSize(Size(700, 195));
	scrollview->setInnerContainerSize(Size(1440, 195));
	scrollview->setTouchEnabled(false);
	scrollview->setScrollBarEnabled(false);
	//for test--------------------
	scrollview->addEventListener(CC_CALLBACK_2(menuController::scrollEvent, this));
	//----------------------------
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
	btn1 = Button::create("menu_1.png", "menu_1_s.png", "menu_1_s.png");
	btn1->setPosition(Vec2(100, 190.0 / 2));
	btn1->addTouchEventListener(CC_CALLBACK_2(menuController::btnsListener, this));
	btn1->setTag(1);
	scrollview->addChild(btn1, 1);

	btn2 = Button::create("menu_2.png", "menu_2_s.png", "menu_2_s.png");
	btn2->setPosition(Vec2(345, 190.0 / 2));
	btn2->addTouchEventListener(CC_CALLBACK_2(menuController::btnsListener, this));
	btn2->setTag(2);
	scrollview->addChild(btn2, 1);

	btn3 = Button::create("menu_3.png", "menu_3_s.png", "menu_3_s.png");
	btn3->setPosition(Vec2(590, 190.0 / 2));
	btn3->addTouchEventListener(CC_CALLBACK_2(menuController::btnsListener, this));
	btn3->setTag(3);
	scrollview->addChild(btn3, 1);

	btn4 = Button::create("menu_4.png", "menu_4_s.png", "menu_4_s.png");
	btn4->setPosition(Vec2(835, 190.0 / 2));
	btn4->addTouchEventListener(CC_CALLBACK_2(menuController::btnsListener, this));
	btn4->setTag(4);
	scrollview->addChild(btn4, 1);

	btn5 = Button::create("menu_5.png", "menu_5_s.png", "menu_5_s.png");
	btn5->setPosition(Vec2(1080, 190.0 / 2));
	btn5->addTouchEventListener(CC_CALLBACK_2(menuController::btnsListener, this));
	btn5->setTag(5);
	scrollview->addChild(btn5, 1);

	btn6 = Button::create("menu_6.png", "menu_6_s.png", "menu_6_s.png");
	btn6->setPosition(Vec2(1325, 190.0 / 2));
	btn6->addTouchEventListener(CC_CALLBACK_2(menuController::btnsListener, this));
	btn6->setTag(6);
	scrollview->addChild(btn6, 1);

	//scrollview set percent with scene number
	setScrollViewPosition();
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
		btn1->setEnabled(false);
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
			//TODO: replace to home scene

			break;
		case 21://option btn
			//TODO: pushScene to option scene

			break;
		default:
			break;
		}
	}
}

void menuController::scrollEvent(Ref* pSender, ScrollView::EventType type)
{
	CCLOG("scroll percent : %f", scrollview->getPositionPercent().x);
}
