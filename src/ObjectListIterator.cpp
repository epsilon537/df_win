#include "ObjectListIterator.h"
#include "ObjectList.h"
#include <assert.h>

namespace df {
	//Create iterator over given list.
	ObjectListIterator::ObjectListIterator(const ObjectList* p_l) : m_index(0), m_p_list(p_l) {
		assert(m_p_list);
	}

	//Reassign iterator to a new list;
	void ObjectListIterator::reassign(const ObjectList* p_l) {
		m_index = 0;
		m_p_list = p_l;

		assert(m_p_list);
	}

	void ObjectListIterator::first() { //Set iterator to first item in list.
		m_index = 0;
	}

	void ObjectListIterator::next() { //Set iterator to next item in list.
		if (m_index < m_p_list->m_count) {
			++m_index;
		}
	}

	bool ObjectListIterator::isDone() const { //Return true if at end of list.
		return (m_index >= m_p_list->m_count);
	}

	//Return pointer to current Object, 0, if done/empty.
	Object* ObjectListIterator::currentObject() const {
		if (isDone())
			return 0;

		return m_p_list->m_p_obj[m_index];
	}
}