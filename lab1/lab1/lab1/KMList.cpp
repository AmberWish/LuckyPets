#include "KMList.h"

/*******************************/
KMList::KMList(): Root(0), Color(0xffffff)
{

}
/*******************************/
KMList::~KMList()
{
	//removeAll();
}
/*******************************/
bool KMList::add(const KMVector3f& value)
{
	ListItem* p = new ListItem();
	p->item = value;

	if (Root != 0)
		p->next = Root;

	Root = p;

	return true;
}
/*******************************/
void KMList::removeAll()
{
	ListItem* p = Root;
	ListItem* next;

	while (p != 0)
	{
		next = p;
		p = p->next;
		delete next;
	}
}
/*******************************/
void KMList::setColor(unsigned int aColor)
{
	Color = aColor;
}
/*******************************/
unsigned int KMList::getColor()
{
	return Color;
}
/*******************************/
void KMList::finish()
{
	add(Current);
	//Current.setW(-1.);
}

void KMList::clean()
{
	Root = 0;
	Current = KMVector3f();
	Color = 0;
}
/*******************************/
void KMList::setCurrent(const KMVector3f& car)
{
	Current = car;
}
/*******************************/
KMVector3f KMList::getCurrent()
{
	return Current;
}
/*******************************/
KMList::KMIterator::KMIterator(KMList& list):mList(&list), pos(0) {

}
/*******************************/
KMVector3f KMList::KMIterator::operator*()
{
	if (pos == 0)
		return KMVector3f();
	return pos->item;
}
/*******************************/
bool KMList::KMIterator::operator++()
{
	if (pos == 0)
		return false;

	pos = pos->next;
	return true;
}
/*******************************/
const KMList::KMIterator& KMList::KMIterator::begin()
{
	pos = mList->Root;

	return *(const KMList::KMIterator*)pos;
}
/*******************************/
bool KMList::KMIterator::end()
{
	if (pos == 0)
		return false;
	return true;
}
/*******************************/