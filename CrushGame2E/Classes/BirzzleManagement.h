#ifndef _BIRZZLE_MANAGEMENT_H_
#define _BIRZZLE_MANAGEMENT_H_

#include "cocos2d.h"
#include "Birzzle.h"

USING_NS_CC;

#define TOTAL_SP 7


#define ROWS 8
#define COLS 7


class CBirzzleManagement : public Node
{
public:
	CBirzzleManagement();
	virtual ~CBirzzleManagement();
	CREATE_FUNC(CBirzzleManagement);
	virtual bool init();

	CBirzzle* GetBirzzle(int nRow, int nCol);

	void InitData();
	void CreateBirzzle(int nRow, int nCol);
	void GetColChain(CBirzzle *pBirzzle, std::list<CBirzzle *> &listChain);
	void GetRowChain(CBirzzle *pBirzzle, std::list<CBirzzle *> &listChain);
	void BindMap(int nRow, int Col, CBirzzle *pBirzzle);
	bool CheckIsAnimating();
	void CheckAndRemoveChain();
	void RemoveBirzzle(int nRow, int nCol);
	
private:
	CBirzzle *m_pBirzzleMap[ROWS][COLS];
	CBirzzle *m_pBirzzle;
};

#endif 