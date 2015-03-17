#include "InGameScene.h"
//#include "cocostudio\CocoStudio.h"
//#include "ui\UILayout.h"
//#include "ui/CocosGUI.h"

#include "Util/Global.h"
#include "Util/DataSingleton.h"
#include "GPGS/GameSharing.h"
#include "SimpleAudioEngine.h"
#include "network/HttpRequest.h"
using namespace CocosDenshion;
USING_NS_CC;
//using namespace std;
//using namespace ui;
//using namespace cocostudio;




Scene* InGameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = InGameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void InGameScene::InitStage()
{
	m_nCurrStageRepeatCount = 0;
	m_nSubmitCount = 0;
	m_nAnswerDigit = 2;
	m_nDigitCount = 0;

	int nLevel = DataSingleton::getInstance().nLevel;
	int nButtonSize = 0;
	int nStartX = 0;
	int nStartY = 0;
	int nMargin = 1;
	int nFontSize = 0;

	if (nLevel == 1)
	{
		m_nWid = 2;
		m_nHei = 2;
		m_nLife = 3;
		m_nAnswerDigit = 2;

		m_nRepeatStage_MAX = 10;
		m_nRecoverLifeAmount = 1;
		m_nTime = 600;

		nButtonSize = 338;
		nStartX = 190;
		nStartY = 757;
		nFontSize = 135;
	}
	else if (nLevel == 2)
	{
		m_nWid = 3;
		m_nHei = 2;
		m_nLife = 7;
		m_nAnswerDigit = 3;

		m_nRepeatStage_MAX = 8;
		m_nRecoverLifeAmount = 1;
		m_nTime = 660;

		nButtonSize = 224;
		nStartX = 133;
		nStartY = 700;
		nFontSize = 100;
	}
	else if (nLevel == 3)
	{
		m_nWid = 3;
		m_nHei = 3;
		m_nLife = 8;
		m_nAnswerDigit = 4;

		m_nRepeatStage_MAX = 6;
		m_nRecoverLifeAmount = 1;
		m_nTime = 600;

		nButtonSize = 224;
		nStartX = 133;
		nStartY = 814;
		nFontSize = 100;
	}
	else if (nLevel == 4)
	{
		m_nWid = 4;
		m_nHei = 3;
		m_nLife = 9;
		m_nAnswerDigit = 4;

		m_nRepeatStage_MAX = 5;
		m_nRecoverLifeAmount = 2;
		m_nTime = 780;

		nButtonSize = 168;
		nStartX = 105;
		nStartY = 757;
		nFontSize = 85;
	}
	else if (nLevel == 5)
	{
		m_nWid = 4;
		m_nHei = 4;
		m_nLife = 10;
		m_nAnswerDigit = 4;

		m_nRepeatStage_MAX = 4;
		m_nRecoverLifeAmount = 2;
		m_nTime = 840;

		nButtonSize = 168;
		nStartX = 105;
		nStartY = 842;
		nFontSize = 85;
	}
	else if (nLevel == 6)
	{
		m_nWid = 5;
		m_nHei = 4;
		m_nLife = 11;
		m_nAnswerDigit = 4;

		m_nRepeatStage_MAX = 3;
		m_nRecoverLifeAmount = 2;
		m_nTime = 900;

		nButtonSize = 135;
		nStartX = 88;
		nStartY = 804;
		nFontSize = 70;
	}
	else if (nLevel == 7)
	{
		m_nWid = 5;
		m_nHei = 5;
		m_nLife = 12;
		m_nAnswerDigit = 5;

		m_nRepeatStage_MAX = 2;
		m_nRecoverLifeAmount = 3;
		m_nTime = 1020;

		nButtonSize = 135;
		nStartX = 88;
		nStartY = 858;
		nFontSize = 70;
	}
	else if (nLevel == 8)
	{
		m_nWid = 6;
		m_nHei = 5;
		m_nLife = 13;
		m_nAnswerDigit = 5;

		m_nRepeatStage_MAX = 1;
		m_nRecoverLifeAmount = 3;
		m_nTime = 1140;

		nButtonSize = 112;
		nStartX = 77;
		nStartY = 870;
		nFontSize = 58;
	}
	else if (nLevel == 9)
	{
		m_nWid = 6;
		m_nHei = 6;
		m_nLife = 14;
		m_nAnswerDigit = 5;

		m_nRepeatStage_MAX = 1;
		m_nRecoverLifeAmount = 3;
		m_nTime = 1200;


		nButtonSize = 112;
		nStartX = 77;
		nStartY = 870;
		nFontSize = 58;
	}

	// pad setting
	for (int i = 0; i < m_nWid; ++i)
	{
		for (int j = 0; j < m_nHei; ++j)
		{
			auto img1 = MenuItemImage::create("scene4/button/btn_pad_up.png", "scene4/button/btn_pad_press.png");
			auto img2 = MenuItemImage::create("scene4/button/btn_pad_down.png", "scene4/button/btn_pad_press.png");

			MenuItemToggle* button = MenuItemToggle::createWithCallback(
				CC_CALLBACK_1(InGameScene::Touch_NumPad, this), img1, img2, NULL);

			float fResizeFactor = (float)nButtonSize / (float)(button->getContentSize().height);
			button->setScale(fResizeFactor);
			button->setTag(j*m_nWid + (i + 1));

			auto menu = Menu::create(button, NULL);
			menu->setPosition(Vec2(nStartX + (nButtonSize + nMargin) * i, nStartY - (nButtonSize + nMargin) * j));

			auto LBL_number = Label::createWithTTF("0", "fonts/LCDM2N_.TTF", nFontSize);
			LBL_number->setPosition(Vec2(nStartX + (nButtonSize + nMargin) * i, nStartY - (nButtonSize + nMargin) * j));
			LBL_number->setString(to_string2(j*m_nWid + (i + 1)));
			LBL_number->setTextColor(Color4B(17, 140, 24, 200));

			button->setUserObject(LBL_number);

			this->addChild(menu);
			this->addChild(LBL_number);

			m_vButtons.push_back(button);
		}
	}
}

// on "init" you need to initialize your instance
bool InGameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto keylistener = EventListenerKeyboard::create();
	keylistener->onKeyReleased = CC_CALLBACK_2(InGameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);

	InitStage();
	

	MakeAnswer();


	// 버튼 하나 누르면 타이머 시작함.
	this->schedule(schedule_selector(InGameScene::scheduleCallback), 0.85f);

	// gen answer
	m_TXT_sum = Label::create(to_string2(m_sumNew), "fonts/LCDM2N_.TTF", 54.f);
	m_TXT_sum->setPosition(Vec2(200, 1000));
	m_TXT_sum->setAnchorPoint(Vec2(0, 0));
	m_TXT_sum->setContentSize(Size(200, 100));
	m_TXT_sum->setVerticalAlignment(TextVAlignment::CENTER);
	m_TXT_sum->setAlignment(TextHAlignment::CENTER);
	this->addChild(m_TXT_sum);

	m_LBL_sum = Label::create("sum", "fonts/LCDM2N_.TTF", 24.f);
	m_LBL_sum->setPosition(Vec2(210, 965));
	m_LBL_sum->setAnchorPoint(Vec2(0, 0));
	m_LBL_sum->setTextColor(Color4B(79, 147, 210, 255));
	this->addChild(m_LBL_sum);

	// digit counter
	m_LBL_digit = Label::create("word", "fonts/LCDM2N_.TTF", 24.f);
	m_LBL_digit->setPosition(Vec2(62, 965));
	m_LBL_digit->setAnchorPoint(Vec2(0, 0));
	m_LBL_digit->setTextColor(Color4B(79, 147, 210, 255));
	this->addChild(m_LBL_digit);

	m_TXT_digit = Label::create("0/" + to_string2(m_nAnswerDigit), "fonts/LCDM2N_.TTF", 54.f);
	m_TXT_digit->setPosition(Vec2(50, 1000));
	m_TXT_digit->setAnchorPoint(Vec2(0, 0));
	this->addChild(m_TXT_digit);

	// time
	m_LBL_time = Label::create("time", "fonts/LCDM2N_.TTF", 24.f);
	m_LBL_time->setPosition(Vec2(465, 965));
	m_LBL_time->setAnchorPoint(Vec2(1, 0));
	m_LBL_time->setTextColor(Color4B(79, 147, 210, 255));
	this->addChild(m_LBL_time);

	m_TXT_time = Label::create("0:00", "fonts/LCDM2N_.TTF", 54.f);
	m_TXT_time->setPosition(Vec2(465, 1000));
	m_TXT_time->setAnchorPoint(Vec2(1, 0));
	this->addChild(m_TXT_time);

	// life
	m_TXT_life = Label::create(to_string2(m_nLife), "fonts/LCDM2L_.TTF", 106.f);
	m_TXT_life->setPosition(Vec2(575, 1000));
	m_TXT_life->setAnchorPoint(Vec2(0, 0));
	m_TXT_life->setAlignment(TextHAlignment::RIGHT);
	this->addChild(m_TXT_life);

	//Size visibleSize = Director::getInstance()->getVisibleSize();
	//Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//Size s = this->getContentSize();

	MenuItemImage* img_lifebox = MenuItemImage::create("scene4/box_life.png", "scene4/box_life.png");
	img_lifebox->setPosition(Vec2(604, 1082));
	this->addChild(img_lifebox);


	m_BTN_submit = Button::create("scene4/btn_enter_up.png", "scene4/btn_enter_down.png");
	m_BTN_submit->setPosition(Vec2(359, 180));
	m_BTN_submit->setScale9Enabled(true);
	m_BTN_submit->setSize(Size(676, 86));
	m_BTN_submit->setPressedActionEnabled(false);
	m_BTN_submit->addTouchEventListener(CC_CALLBACK_2(InGameScene::Touch_submit, this));
	m_BTN_submit->setBright(false);
	m_BTN_submit->setEnabled(false);
	this->addChild(m_BTN_submit);

	lst_log = ListView::create();
	lst_log->setDirection(ui::ListView::Direction::VERTICAL);
	lst_log->setBounceEnabled(true);
	lst_log->setBackGroundImage("scene4/box_log.png");
	//lst_log->setBackGroundImageScale9Enabled(true);
	lst_log->setContentSize(Size(446, 130));
	lst_log->setPosition(Vec2(259, 1144));
	lst_log->setAnchorPoint(Vec2(0.5f, 0.5f));

	Text* txt = Text::create("Be sure to match the password!", "fonts/LCDM2N_.TTF", 24.f);

	Layout* default_item = Layout::create();
	default_item->setTouchEnabled(true);
	default_item->setContentSize(txt->getContentSize());
	txt->setPosition(Vec2(default_item->getContentSize().width / 2.0f,
		default_item->getContentSize().height / 2.0f));
	default_item->addChild(txt);

	lst_log->pushBackCustomItem(default_item);
	//lst_log->setItemModel(default_item);
	//lst_log->pushBackDefaultItem();
	this->addChild(lst_log);


	m_LDB_progress = LoadingBar::create("common/slider_bar_active_9patch.png");
	m_LDB_progress->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height-5));
	m_LDB_progress->setDirection(LoadingBar::Direction::LEFT);
	m_LDB_progress->setScale9Enabled(true);
	m_LDB_progress->setCapInsets(Rect(0, 0, 0, 0));
	m_LDB_progress->setContentSize(Size(750, 12));
	m_LDB_progress->setPercent(0.f);
	this->addChild(m_LDB_progress);




	return true;
}

void InGameScene::scheduleCallback(float delta)
{
	//CCLOG("scheduleCallback : %f", delta);

	--m_nTime;


	int nMinute = m_nTime / 60;
	int nSec = m_nTime % 60;

	char szTime[32] = { NULL, };
	sprintf(szTime, "%d:%02d", nMinute, nSec);
	m_TXT_time->setString(szTime);
	//DataSingleton::getInstance().strSpentTime = time;	// 총 소모한 시간 저장.
	DataSingleton::getInstance().nSpentTime = m_nTime;	// 총 소모한 시간 저장.

	if (m_nTime == 0)	// 시간 내에 전부 못 풀면 실패.
	{
		showResultFailed();
	}

	
	
}


void InGameScene::Touch_submit(Ref* sender, Widget::TouchEventType type)
{
	Button* btn = (Button*)sender;



	//터치 이벤트 실행시 프로그램 종료
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:

		if (btn->isBright() == true)
		{
			auto audio = SimpleAudioEngine::getInstance();
			audio->playEffect("raw/enter.wav", false, 1.0f, 1.0f, 1.0f);
		}


		for (int i = 0; i < m_vButtons.size(); ++i)
		{
			if (m_vButtons[i]->getSelectedIndex() == 1)
			{
				m_vAnswer.push_back(m_vButtons[i]->getTag());	// 눌려져 있으면 정답에 넣고
				//strAnswer.append(to_string2(m_vAnswer[m_vAnswer.size() - 1]));
			}
		}

		if (m_vAnswer.empty())	// 아무것도 눌리지 않으면 동작 안 함.
			return;

		++m_nSubmitCount;
		DataSingleton::getInstance().nSpentCount = m_nSubmitCount;

		// 채점하기
		int nCount = 0;
		string strPrint = "";

		for (int j = 0; j < m_vAnswer.size(); ++j)
		{
			strPrint += to_string2(m_vAnswer[j]);
			if (j != m_vAnswer.size() - 1)
				strPrint += ", ";

			for (int i = 0; i < m_vQuestion.size(); ++i)
			{
				if (m_vQuestion[i] == m_vAnswer[j])
				{
					++nCount;
					break;
				}
			}
		}


		// 다 맞췃고 자릿수도 맞으면 정답임
		if (nCount == m_nAnswerDigit && (m_vQuestion.size() == m_vAnswer.size()))
		{
			if (m_nCurrStageRepeatCount == m_nRepeatStage_MAX-1)
			{
				ClearStage();
			}
			else
			{
				RepeatStage();
			}

			return;
		}

		m_BTN_submit->setBright(false);

		m_nDigitCount = 0;
		m_sumNew = m_nSumFixed;
		for (size_t i = 0; i < m_vButtons.size(); ++i)
		{
			m_vButtons[i]->setSelectedIndex(0);
			Label* lbl = static_cast<Label*>(m_vButtons[i]->getUserObject());
			lbl->enableOutline(Color4B::BLACK, 0);
		}

		// UI refresh
		m_TXT_digit->setString(to_string2(m_nDigitCount) + "/" + to_string2(m_nAnswerDigit));
		m_TXT_sum->setString(to_string2(m_sumNew));
		m_TXT_sum->setTextColor(Color4B(255, 255, 255, 255));
		m_BTN_submit->setBright(false);
		m_vAnswer.clear();

		// list hint element setting
		Text* txt = Text::create(strPrint, "fonts/LCDM2N_.TTF", 28.f);
		txt->setColor(Color3B(183, 183, 183));
		Text* txt2 = Text::create(to_string2(nCount), "fonts/LCDM2N_.TTF", 28.f);
		txt2->setColor(Color3B(227, 29, 29));

		Layout* default_item = Layout::create();
		default_item->setTouchEnabled(true);
		default_item->setContentSize(Size(txt->getContentSize().width + txt2->getContentSize().height
			, txt->getContentSize().height));
		txt->setPosition(Vec2(default_item->getContentSize().width / 2.0f,
			default_item->getContentSize().height / 2.0f));
		txt2->setPosition(Vec2(415,
			default_item->getContentSize().height / 2.0f));
		default_item->addChild(txt);
		default_item->addChild(txt2);

		lst_log->pushBackCustomItem(default_item);
		lst_log->refreshView();
		lst_log->scrollToBottom(.5f, false);

		// life
		this->ChangeLife(false, 1);
		
		
		//stage  over
		if (m_nLife == 0)
		{
			DataSingleton::getInstance().bClear = false;
			DataSingleton::getInstance().nStageRepeatCount = m_nCurrStageRepeatCount;
			DataSingleton::getInstance().nLeftLife = m_nLife;

			showResultFailed();
		}
		break;
	}
}



void InGameScene::Touch_NumPad(Ref* sender)
{
	MenuItemToggle* tgl = dynamic_cast<MenuItemToggle*>(sender);
	Label* lbl = static_cast<Label*>(tgl->getUserObject());

	auto audio = SimpleAudioEngine::getInstance();
	audio->playEffect("raw/number.wav", false, 1.0f, 1.0f, 1.0f);

	// change button select status whether it pressed or not.
	
	if (tgl->getSelectedIndex() == 0)	
	{
		if (lbl)
			lbl->enableOutline(Color4B::BLACK, 0);

		++m_nDigitCount;
		m_sumNew = m_sumNew + tgl->getTag();

	}
	else// if this button already selected
	{
		if (abs(m_nDigitCount) == m_nAnswerDigit)
		{
			tgl->setSelectedIndex(0);
			return;
		}

		if (lbl)
			lbl->enableOutline(Color4B::WHITE, 1);

		--m_nDigitCount;
		
		m_sumNew = m_sumNew - tgl->getTag();

	}

	if (m_sumNew < 0)	// minus
	{
		m_TXT_sum->setString("E");
		m_TXT_sum->setTextColor(Color4B::RED);
	}
	else
	{
		m_TXT_sum->setString(to_string2(m_sumNew));
		m_TXT_sum->setTextColor(Color4B::WHITE);
	}

	if (abs(m_nDigitCount)== abs(m_nAnswerDigit))	// 입력해야할 자리수랑 입력한 자리수 같으면..
	{
		m_BTN_submit->setBright(true);
		m_BTN_submit->setEnabled(true);
	}
	else
	{
		m_BTN_submit->setBright(false);
		m_BTN_submit->setEnabled(false);
	}
		
	m_TXT_digit->setString(to_string2(abs(m_nDigitCount)) + "/" + to_string2(m_nAnswerDigit));

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	//MessageBox(str.c_str(), "응?");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//exit(0);		
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#endif

}


void InGameScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
	if (keycode == EventKeyboard::KeyCode::KEY_BACK)
	{
		this->changeScene();
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		this->changeScene();
	}

}



void InGameScene::showResultFailed(void)
{
	//Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);


	auto hScene = ResultScene::createScene();
	auto pScene = TransitionFade::create(1.0f, hScene);
	Director::getInstance()->pushScene(pScene);
}

void InGameScene::showResult(void)
{
	//Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

	auto hScene = ResultScene::createScene();
	auto pScene = TransitionFade::create(1.0f, hScene);
	Director::getInstance()->pushScene(pScene);
}

void InGameScene::changeScene(void)
{
	//Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

	auto hScene = SelectStageScene::createScene();
	auto pScene = TransitionFade::create(1.0f, hScene);
	Director::getInstance()->replaceScene(pScene);
}


void InGameScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void InGameScene::ClearStage()
{
	// play 
	string strClear = "stage_clear_";
	if(DataSingleton::getInstance().nPlayMode == EStage::EASY)
		strClear += "easy";
	else if (DataSingleton::getInstance().nPlayMode == EStage::NORMAL)
		strClear += "normal";
	else if (DataSingleton::getInstance().nPlayMode == EStage::CHALLENGE)
		strClear += "challenge";

	int nSavedStage = UserDefault::getInstance()->getIntegerForKey(strClear.c_str(), 0);	// get current highest stage level.
	if (nSavedStage < DataSingleton::getInstance().nLevel)	// if this level is highest level...
	{
		UserDefault::getInstance()->setIntegerForKey(strClear.c_str(), DataSingleton::getInstance().nLevel);	// update save data.

		//submit score to Google play store game service...
		GameSharing::SubmitScore(DataSingleton::getInstance().nLevel, 0);
		GameSharing::UnlockAchivement(DataSingleton::getInstance().nLevel-1);
	}

	DataSingleton::getInstance().bClear = true;
	DataSingleton::getInstance().nStageRepeatCount = m_nRepeatStage_MAX;
	DataSingleton::getInstance().nLeftLife = m_nLife;
	
	showResult();
}




void InGameScene::MakeAnswer()
{
	// ANSWER_DIGIT자리 난수로 정답을 생성한다.
	m_vAnswer.clear();
	m_vQuestion.clear();
	int nSum = 0;
	//srand((unsigned int)time(NULL));
	while (m_vQuestion.size() != m_nAnswerDigit)
	{
		int nNumber = random(1, m_nWid*m_nHei);
		bool bAlreadyHas = false;
		bool bCountious = false;	// 반복된 숫자 제외.
		for (int i = 0; i < m_vQuestion.size(); ++i)
		{
			if (m_vQuestion[i] == nNumber)
			{
				bAlreadyHas = true;
				break;
			}
			if (m_vQuestion[i]-1 ==  nNumber)
			{
				bCountious = true;
				break;
			}
			if (m_vQuestion[i]+1 == nNumber)
			{
				bCountious = true;
				break;
			}
		}
		if (bAlreadyHas == false && bCountious==false)
		{
			m_vQuestion.push_back(nNumber);
			nSum += nNumber;
		}
	}
	m_sumNew = nSum;
	m_nSumFixed = nSum;
}

void InGameScene::RepeatStage()
{
	// TODO : 이쪽에 현재 눌린 버튼 초기화, 정답 초기화, 매칭석세스 띄우기, 라이프 회복
	//FinishStage();
	{
		Sprite* SPR_match = Sprite::create("scene4/s4_pup_success.png");
		SPR_match->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
		this->addChild(SPR_match);

		auto *fadein = FadeOut::create(1.5f);    // 시간
		auto *delay = DelayTime::create(1.5f);    // 시간
		auto *fadeout = FadeOut::create(2.5f);    // 시간

		Sequence *action_2 = Sequence::create(fadein, delay, fadeout, NULL);
		SPR_match->runAction(action_2);
	}

	ChangeLife(true, m_nRecoverLifeAmount);




	//this->setTouchEnabled(false);

	MakeAnswer();
	m_nDigitCount = 0;
	for (size_t i = 0; i < m_vButtons.size(); ++i)
	{
		m_vButtons[i]->setSelectedIndex(0);
		Label* lbl = static_cast<Label*>(m_vButtons[i]->getUserObject());
		lbl->enableOutline(Color4B::BLACK, 0);
	}

	// UI refresh
	m_TXT_digit->setString(to_string2(m_nDigitCount) + "/" + to_string2(m_nAnswerDigit));
	m_TXT_sum->setString(to_string2(m_sumNew));
	m_BTN_submit->setBright(false);

	float f = (((float)m_nCurrStageRepeatCount + 1) / (float)m_nRepeatStage_MAX) * 100.f;
	m_LDB_progress->setPercent(f);

	// append listbox
	string str = " ===== SUCCESS! (" + to_string2(m_nCurrStageRepeatCount+1) + "/" + to_string2(m_nRepeatStage_MAX) + ") ===== ";
	Text* txt = Text::create(str, "fonts/LCDM2N_.TTF", 30.f);

	Layout* default_item = Layout::create();
	default_item->setTouchEnabled(true);
	default_item->setContentSize(txt->getContentSize());
	txt->setPosition(Vec2(default_item->getContentSize().width / 2.0f,
		default_item->getContentSize().height / 2.0f));
	default_item->addChild(txt);

	//lst_log->setItemModel(default_item);
	//lst_log->pushBackDefaultItem();
	lst_log->pushBackCustomItem(default_item);
	lst_log->refreshView();
	lst_log->scrollToBottom(0.5f, true);
	//this->addChild(lst_log);

	++m_nCurrStageRepeatCount;	//  repeat stage
}

void InGameScene::ChangeLife(bool bIncrease, int nAmount)
{
	Vec2 vec(m_TXT_life->getPosition().x, m_TXT_life->getPosition().y);
	Label* LBL_lifechange = Label::create("", "fonts/LCDM2N_.TTF", 70.f);
	LBL_lifechange->setPosition(Vec2(vec.x + 100, vec.y+50));

	string str = "";
	if (bIncrease)	// when increase
	{
		str += "+";
		str += to_string2(nAmount);
		LBL_lifechange->setTextColor(Color4B(0, 255, 0, 255));
	}
	else
	{
		str += "-";
		str += to_string2(nAmount);
		LBL_lifechange->setTextColor(Color4B(255, 0, 0, 255));
	}
	LBL_lifechange->setString(str);
	this->addChild(LBL_lifechange);

	auto fadeout = FadeOut::create(1.5f);
	auto move1 = MoveBy::create(1.5f, Vec2(0,200));
	auto spawn1 = Spawn::create(fadeout, move1, NULL);
	LBL_lifechange->runAction(spawn1);
	
	//if (m_nLife / 10 != 0)	// if life is one digit
	//{
	//	m_TXT_life->size
	//}
	//else
	//{
	//	m_TXT_life->setSystemFontSize(100.f);
	//}
	if (bIncrease)
	{
		m_nLife += nAmount;
		auto blink = Blink::create(1.0f, 1);
	}
	else
	{
		m_nLife -= nAmount;
		auto blink = Blink::create(1.5f, 2);
		m_TXT_life->runAction(blink);
	}
		

	m_TXT_life->setString(to_string2(m_nLife));


}
