#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__


#include <vector>
#include "cocos2d.h"
//#include "cocostudio\CocoStudio.h"        //���ڽ� ��Ʃ��� ���
#include "ui\CocosGUI.h"                //���ڽ� ��Ʃ��� GUI ��� �߰�
//#include "ButtonN.h"
USING_NS_CC;
using namespace ui;
using namespace std;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

protected:
	void Touch_NumPad(Ref* sender);
	void Touch_submit(Ref* sender, Widget::TouchEventType type);
	//Layout* _layout;
	vector<int> m_vQuestion;
	vector<int> m_vAnswer;
	//vector<bool> m_vPressed;

	ListView* lst_log;
	vector<MenuItemToggle*> m_vButtons;
	Button* m_BTN_submit;

	Label* m_LBL_sum;
	Label* m_LBL_life;
	int m_nLife;
	bool m_bGameOver;
};

#endif // __HELLOWORLD_SCENE_H__