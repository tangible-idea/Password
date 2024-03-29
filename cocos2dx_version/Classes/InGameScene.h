#pragma once

#include <vector>
#include "cocos2d.h"
//#include "cocostudio\CocoStudio.h"        //코코스 스튜디오 사용
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "CocosGUI.h"
#else
#include "ui\CocosGUI.h"
#endif

/*#include "ui\CocosGUI.h"  */              //코코스 스튜디오 GUI 기능 추가
#include "SelectStageScene.h"
#include "ResultScene.h"
//#include "ButtonN.h"
USING_NS_CC;
using namespace ui;
using namespace std;

class InGameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	void MakeAnswer();


    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(InGameScene);

	EventListenerTouchOneByOne * listener;

protected:
	void Touch_NumPad(Ref* sender);
	void Touch_submit(Ref* sender, Widget::TouchEventType type);

	void RepeatStage();

	void  ChangeLife(bool bIncrease, int nAmount);

	void InitStage();
	void ClearStage();

	//Layout* _layout;
	vector<int> m_vQuestion;
	vector<int> m_vAnswer;
	//vector<bool> m_vPressed;

	ListView* lst_log;
	//Layout* default_item;	// default layout item for hint list view.
	vector<MenuItemToggle*> m_vButtons;
	Button* m_BTN_submit;

	Label* m_LBL_sum;
	Label* m_LBL_digit;
	Label* m_LBL_time;
		
	Label* m_TXT_sum;	// sum
	Label* m_TXT_digit;	// digit counter
	Label* m_TXT_time;	// time
	Label* m_TXT_life;	// life counter

	LoadingBar* m_LDB_progress;	// stage progress

	int m_nLife;
	int m_nAnswerDigit;	// word count
	//bool m_bGameOver;
	int m_nCurrStageRepeatCount; // 현재 스테이지 반복 횟수

	int m_nSubmitCount;	// total submit count
	int m_nDigitCount;	// 답변 자리수
	int m_sumNew;	// 
	int m_nSumFixed;	// sum (정답 다시 만들기 전까지는 그대로)
	int m_nRepeatStage_MAX;	// 스테이지 반복 횟수
	int m_nRecoverLifeAmount;	// 성공했을 때 회복 라이프 개수
	int m_nTimeLimit;	// time (unit:sec)
	int m_nSpendTime;	// spend time (unit:sec) [3/24/2015 ChoiJunHyeok]

	int m_nWid;
	int m_nHei;

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event);
	void changeScene(void);
	void showResult(void);
	void showResultFailed(void);

	void scheduleCallback(float delta);
	void doNotification(Object *obj);


	void Callback_popup_ok(Ref* pSender);
	void ShowPopup1();
	void ShowPopup2();
	void ShowPopup3();
	void ShowPopup4();
	void ShowPopup5();
	void ShowPopup6();
};