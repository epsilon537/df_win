#ifndef __DF_OBJECT_LIST_H__
#define __DF_OBJECT_LIST_H__

#include "Object.h"

namespace df{
	class ObjectListIterator;

	const int MAX_OBJECTS = 5000;

	class ObjectList {
	private:
		int m_count; // Number of objects in list.
		Object* m_p_obj[MAX_OBJECTS]; // Array of pointers to objects.
	
	public:
		friend class ObjectListIterator;

		//Default ctor.
		ObjectList();

		//Copy ctor
		ObjectList(const ObjectList& other);

		//Assignment
		ObjectList& operator=(const ObjectList& other);

		//Insert object pointer in list.
		//Return 0 if ok, else -1.
		int insert(Object* p_o);

		//Remove object pointer from list.
		//Return 0 if found, else -1.
		int remove(Object* p_o);

		//Clear list (sets count to 0).
		void clear();

		//Return number of objects in list.
		int getCount() const;

		//Return true if list is empty.
		bool isEmpty() const;

		//Return true if full
		bool isFull() const;

		//Comparison
		bool operator==(const ObjectList& other);

		//Comparison
		bool operator!=(const ObjectList& other);

		//Add two ObjectLists, return new ObjectList.
		ObjectList operator+(const ObjectList& other) const;

		//Add to objectList
		ObjectList& operator+=(const ObjectList& other);
	};
}
#endif /*DF_OBJECT_LIST*/
