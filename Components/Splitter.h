/*
	This file is part of the GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef GUI_SPLITTER_H
#define GUI_SPLITTER_H

#include "Component.h"
#include "../Base/Listener.h"
#include "../GUI_Manager.h"

namespace GUI{

class Image;

/*! Divides a container into two resizable parts.
	The Splitter should always be the second child of overall three children of the parent.
   Splitter ---|> Component
 */
class Splitter: public Component,public MouseMotionListener {
	PROVIDES_TYPE_NAME(Splitter)
	public:
		enum splittingDirection_t { VERTICAL, HORIZONTAL };
		Splitter(GUI_Manager & gui,splittingDirection_t _direction,flag_t flags=0);
		virtual ~Splitter();

		splittingDirection_t getDirection()const				{	return direction;	}

		// ---|> MouseMotionListener
		virtual listenerResult_t onMouseMove(Component * component, const Util::UI::MotionEvent & motionEvent) override;

		// ---|> Component
		virtual void doLayout() override;
	private:
		// ---|> Component
		virtual void doDisplay(const Geometry::Rect & region) override;

		bool onMouseButton(Component * component, const Util::UI::ButtonEvent & buttonEvent);

		GUI_Manager::MouseButtonListenerHandle mouseButtonListenerHandle;

	private:
		const splittingDirection_t direction;
		Geometry::Vec2 currentMousePos;

};

}

#endif // GUI_SPLITTER_H
