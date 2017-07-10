#include "MainScene.h"


Scene *CMainScene::createScene()
{
	auto scene = Scene::create();

	auto BgLayer = CMainScene::create();

	auto GameLayer = CGameLayer::create();

	scene->addChild(BgLayer);

	scene->addChild(GameLayer);

	return scene;

}

bool CMainScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	InitBg();

	return true;
}


void CMainScene::InitBg()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite *pSpriteBg = Sprite::create("Background.png");
	pSpriteBg->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(pSpriteBg, 0);

	Sprite *pSpriteBorder = Sprite::create("stage_bg_landscape_RGB_RETINA.png");
	pSpriteBorder->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	pSpriteBorder->setScaleX(0.95f);
	pSpriteBorder->setScaleY(0.98f);
	this->addChild(pSpriteBorder, 1);
}