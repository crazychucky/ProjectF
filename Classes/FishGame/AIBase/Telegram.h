#ifndef Telegram_H
#define Telegram_H
#include "cocos2d.h"

struct Telegram
{
	int SenderID;
	int ReceiverID;

	int MsgID;

	int DelayTime;   //¼ÆÊ±Æ÷ÑÓ³Ù
	void* ExtraInfo;

	Telegram():DelayTime(-1),
		SenderID(-1),
		ReceiverID(-1),
		MsgID(-1)
	{}

	Telegram(int delayTime,
		int sender,
		int receiver,
		int    msg,
		void*  info = NULL): DelayTime(delayTime),
		SenderID(sender),
		ReceiverID(receiver),
		MsgID(msg),
		ExtraInfo(info)
	{}

};
const int SmallestDelay = 1;


//handy helper function for dereferencing the ExtraInfo field of the Telegram 
//to the required type.
template <class T>
inline T DereferenceToType(void* p)
{
	return *(T*)(p);
}

#endif