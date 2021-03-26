#include "ObjectList.h"

namespace df {
	//Default ctor.
	ObjectList::ObjectList() : m_count(0) {

	}

	ObjectList::ObjectList(const ObjectList& other) : m_count(other.m_count) {
		for (int ii = 0; ii < m_count; ii++)
			m_p_obj[ii] = other.m_p_obj[ii];
	}

	//Assignment
	ObjectList& ObjectList::operator=(const ObjectList& other) {
		m_count = other.m_count;
		for (int ii = 0; ii < m_count; ii++)
			m_p_obj[ii] = other.m_p_obj[ii];

		return *this;
	}

	//Insert object pointer in list.
	//Return 0 if ok, else -1.
	int ObjectList::insert(Object* p_o) {
		if (m_count >= MAX_OBJECTS)
			return -1;
		
		m_p_obj[m_count++] = p_o;

		return 0;
	}

	//Remove object pointer from list.
	//Return 0 if found, else -1.
	int ObjectList::remove(Object* p_o) {
		for (int i = 0; i < m_count; i++) {
			if (m_p_obj[i] == p_o) { //Found
				for (int j = i; j < m_count - 1; j++) // Move up
					m_p_obj[j] = m_p_obj[j + 1];
				--m_count;
				return 0;
			}
		}

		return -1;
	}

	//Clear list (sets count to 0).
	void ObjectList::clear() {
		m_count = 0;
	}

	//Return number of objects in list.
	int ObjectList::getCount() const {
		return m_count;
	}

	//Return true if list is empty.
	bool ObjectList::isEmpty() const {
		return m_count == 0;;
	}

	//Return true if full
	bool ObjectList::isFull() const {
		return m_count >= MAX_OBJECTS;
	}

	//Comparison
	bool ObjectList::operator==(const ObjectList& other) {
		if (m_count != other.m_count)
			return false;

		for (int ii = 0; ii < m_count; ii++)
			if (m_p_obj[ii] != other.m_p_obj[ii])
				return false;

		return true;
	}

	//Comparison
	bool ObjectList::operator!=(const ObjectList& other) {
		return !(*this == other);
	}

	//Add two ObjectLists, return new ObjectList.
	ObjectList ObjectList::operator+(const ObjectList& other) const {
		ObjectList objList(*this);
		objList += other;
		return objList;
	}

	//Add to objectList
	ObjectList& ObjectList::operator+=(const ObjectList& other) {
		for (int ii = 0; ii < other.m_count; ii++)
			m_p_obj[ii + m_count] = other.m_p_obj[ii];

		m_count += other.m_count;

		return *this;
	}
}