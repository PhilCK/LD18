// base.hpp

#ifndef __base_hpp__
#define __base_hpp__

#include <Gosu/Gosu.hpp>

namespace Base
{
	namespace Layer
	{
		enum DrawLayers {
			VOID_LAYER,
			BACKGROUND_LAYER,
			BUILDING_LAYER,
			BLOOD_SPLATTER_LAYER,
			ZOMBIE_LAYER,
			PEOPLE_LINEUP_LAYER,
			PLAYER_LAYER,
			PEOPLE_THROWN_LAYER,
			UI_LAYER
		};
	};

	namespace Directory
	{
		#ifdef WIN32
			static const std::wstring MediaDir = Gosu::resourcePrefix() + L"media\\";
		#else
			static const std::wstring MediaDir = Gosu::resourcePrefix() + L"media/";
		#endif
	};

	namespace Screen
	{
		static const int Width = 600;
		static const int Height = 800;
		static const bool Fullscreen = false;
	}
	
};


#endif