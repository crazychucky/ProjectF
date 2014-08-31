//通用函数类
#ifndef __COMMONFUNCTION_H__
#define __COMMONFUNCTION_H__
#include "cocos2d.h"
USING_NS_CC;

class CommonFunction
{
public:
	~CommonFunction();
	static void VectorTruncate(CCPoint &v,float maxLen);
	static bool getCrossPoint(const CCPoint p1,const CCPoint p2,const CCPoint p3,const CCPoint p4,CCPoint &resultPt);

private:
	CommonFunction();

};

#endif