#pragma once

#include "KMVector3f.h"
//template<typename T>
class KMList {

public:
	KMList();
	~KMList();
	bool add(const KMVector3f& value);
	void removeAll();
	void clean();
	void setCurrent(const KMVector3f& car);
	KMVector3f getCurrent();
	void setColor(unsigned int aColor);
	unsigned int getColor();
	void finish();
	struct ListItem;
	class KMIterator {
	public:
		KMIterator(KMList& list);
		KMVector3f operator*();
			bool operator++();
			const KMIterator& begin();
			bool end();
	private:
		KMList* mList;
		ListItem* pos;
	};

private:

	struct ListItem {
		ListItem() :item(), next(0) {
		}
		KMVector3f item;
		ListItem* next;
	};

	ListItem* Root;
	KMVector3f Current;
	unsigned int Color;
};