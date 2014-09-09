#include "FishGame/Test/DrawLayer.h"

DrawLayer::DrawLayer()
{

}

DrawLayer::~DrawLayer()
{

}

DrawLayer* DrawLayer::create(DrawDelegate* pDelegate)
{
	DrawLayer* ret =DrawLayer::create();
	ret->m_drawDelegate = pDelegate;
	ret->setZOrder(998);

	return ret;
}

void DrawLayer::draw()
{
	if (m_drawDelegate)
	{
		m_drawDelegate->debugDraw();
	}
}
