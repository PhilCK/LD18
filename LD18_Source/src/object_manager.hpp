// object_manager.hpp

#ifndef __object_manager_hpp__
#define __object_manager_hpp__


#include <boost/ptr_container/ptr_list.hpp>
#include <boost/foreach.hpp>
#include <Gosu/Gosu.hpp>
#include <string>
#include "game_object.hpp"

using std::string;


class ObjectManager
{
	typedef boost::ptr_list<GameObject> ObjectList;
	ObjectList objectList;

public:

	// ** LOOP METHODS ** //
	void update() {	

		ObjectList::iterator checkIter     = objectList.begin();

		while (checkIter != objectList.end())
		{
			ObjectList::iterator collisionIter = objectList.begin();

			while (collisionIter != objectList.end())
			{
				if (checkIter->collidable and collisionIter->collidable)
				{

					if ((checkIter->objectTag != collisionIter->objectTag))
					{
						if (Gosu::distance(checkIter->x, checkIter->y, collisionIter->x, collisionIter->y) < 30)
						{
							checkIter->health--;
						}
					}
				}

				collisionIter++;
			}
			checkIter++;
		}

		ObjectList::iterator updateIter = objectList.begin();

		while (updateIter != objectList.end())
		{
			if (updateIter->update())
				updateIter++;
			else
				updateIter = objectList.erase(updateIter);
		}
		
	}

	void draw()	{
		BOOST_FOREACH(GameObject& obj, objectList)
			obj.draw();
	}

	void clear() {
		objectList.clear();
	}

	// Push in a new object.
	void push(GameObject* obj) {objectList.push_back(obj); }

	GameObject& getObject(string type)
	{
		ObjectList::iterator search = objectList.begin();

		while(search != objectList.end())
		{
			if (search->objectTag == type)
				return *search;
		}
	}

};


ObjectManager& objectManagerInstance() {
	static ObjectManager objMan;
	return objMan;
}


#endif