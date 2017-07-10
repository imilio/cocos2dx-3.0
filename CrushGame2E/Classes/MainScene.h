#ifndef _MAINSCENE_H_
#define _MAINSCENE_H_

#include "cocos2d.h"
#include "GameLayer.h"

USING_NS_CC;

class CBirzzleManagement;
class CMainScene : public Layer
{
public:
	virtual bool init();
	static Scene *createScene();
	CREATE_FUNC(CMainScene);

private:
	void InitBg();

private:

};














#endif 