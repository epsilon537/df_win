#ifndef __DF_OBJECT_LIST_ITERATOR_H__
#define __DF_OBJECT_LIST_ITERATOR_H__

namespace df {
	class ObjectList;
	class Object;

	class ObjectListIterator {
	private:
		ObjectListIterator(); //Disallow default ctor.
		int m_index;	// Index into list.
		const ObjectList* m_p_list;	// List iterating over.

	public:
		//Create iterator over given list.
		ObjectListIterator(const ObjectList* p_l);

		//Reassign iterator to a new list;
		void reassign(const ObjectList* p_l);
		void first(); //Set iterator to first item in list.
		void next(); //Set iterator to next item in list.
		bool isDone() const; //Return true if at end of list.

		//Return point to current Object, 0, if done/empty.
		Object* currentObject() const;
	};
}

#endif /*DF_OBJECT_LIST_ITERATOR*/