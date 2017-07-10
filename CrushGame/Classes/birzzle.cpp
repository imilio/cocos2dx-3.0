#include "birzzle.h"

CBirzzle::CBirzzle()
{
	m_isNeedRemove = false;
	m_pSprite = NULL;
}

CBirzzle::~CBirzzle()
{
}
bool CBirzzle::init()
{
	return true;
}

Sprite *CBirzzle::GetSprite()
{
	return m_pSprite;
}

void CBirzzle::BindSprite(Sprite *pSprite)
{
	m_pSprite = pSprite;
	this->addChild(m_pSprite);
}