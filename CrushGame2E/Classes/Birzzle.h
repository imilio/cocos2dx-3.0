#ifndef _BIRZZLE_H_
#define _BIRZZLE_H_

#include "cocos2d.h"

USING_NS_CC;

class CBirzzle : public Node
{
public:
	CBirzzle();
	virtual ~CBirzzle();
	CREATE_FUNC(CBirzzle);
	virtual bool init();
	Sprite *GetSprite();

	void BindSprite(Sprite *pSprite);
	CC_SYNTHESIZE(int, m_row, Row);
	CC_SYNTHESIZE(int, m_col, Col);
	CC_SYNTHESIZE(int, m_birzzleType, BirzzleType);
	CC_SYNTHESIZE(bool, m_isNeedRemove, IsNeedRemove);

private:
	Sprite *m_pSprite;

};

#endif 