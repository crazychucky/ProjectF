//自己写的链表类
#ifndef __DSLIST_H__
#define __DSLIST_H__

template <class myData>
struct Element
{
	myData* pData;
	Element* pNext;
	Element* pPrev;
};

template <class myData>
class DSList
{
public:
	DSList()
	{
		head=NULL;
		tail=NULL;
	}
	~DSList()
	{
		Element<myData>* p=head;
		while (p)
		{
			erase(p);
			p=head;
		}
	}
	bool isEmpyt()
	{
		return (head==NULL);
	}
	Element<myData>* getHead()
	{
		return head;
	}
	Element<myData>* getTail()
	{
		return tail;
	}
	void insert(myData *d)
	{
		Element<myData>* pNew=new Element<myData>;
		pNew->pData=d;
		pNew->pNext=NULL;
		pNew->pPrev=NULL;
		insert(pNew);
	}
	void  erase(Element<myData> *e)
	{
		if (e==head)
		{
			head=e->pNext;
		}
		if (e==tail)
		{
			tail=e->pPrev;
		}

		if (e->pPrev)
		{
			e->pPrev->pNext=e->pNext;
		}
		if(e->pNext)
		{
			e->pNext->pPrev=e->pPrev;
		}
		if (e->pData)
		{
			delete(e->pData);
			e->pData=NULL;
		}
		delete(e);
	}
private:
	Element<myData>* head;
	Element<myData>* tail;
	void insert(Element<myData> *e)
	{
		if (e->pNext)
		{
			e->pNext=NULL;
		}
		if (tail)
		{
			tail->pNext=e;
			e->pPrev=tail;
			tail=e;
		}
		else
		{
			e->pPrev=NULL;
			head=e;
			tail=e;
		}
	}
};

#endif