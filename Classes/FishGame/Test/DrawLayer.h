//DEBUG 绘制
//代理机制
#ifndef __DrawLayer_H__
#define __DrawLayer_H__

#include "Base/TestBaseScene.h"
#include "FishGame/FishObj.h"

class DrawDelegate
{
public:
	virtual void debugDraw()=0;
};

class DrawLayer:public CCLayer
{
public:
	DrawLayer();
	virtual ~DrawLayer();
	static DrawLayer* create(DrawDelegate* pDelegate);

private:
	CREATE_FUNC(DrawLayer);
	void draw();

protected:
	DrawDelegate* m_drawDelegate;
};

#endif