/*
	This file is part of the GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef GUI_Slider_H
#define GUI_Slider_H

#include "Container.h"
#include "../Base/Listener.h"
#include "../GUI_Manager.h"

namespace GUI {
class Button;

/***
 **     Slider ---|> Container
 **/
class Slider : public Container, public MouseButtonListener {
		PROVIDES_TYPE_NAME(Slider)
	public:
		// flags
		static const flag_t SHOW_VALUE=1<<25;
		static const flag_t SLIDER_BUTTONS=1<<26;

		Slider(GUI_Manager & gui,const Geometry::Rect & r,float left,float right,int steps,Util::StringIdentifier  dataName,flag_t flags=0);
		virtual ~Slider();

		void setRange(float left,float right,int steps);

		void setValue(float f);
		float getValue()const;

		void setValueRef(float * valueRef);

		void updateDataFromPos(const Geometry::Vec2 & p);
		void updateData(float f);
		float getStepWidth()const 			{	return stepWidth;	}

		void setMarkerSize(const int newMarkerSize)	{	markerSize=newMarkerSize;	}
		int getMarkerSize()const					{	return markerSize;	}
		void setRelMarkerSize(const float relMarkerSize);

		// ---o
		virtual void dataUpdated() ;

		// ---|> MouseButtonListener
		virtual bool onMouseButton(Component * component, const Util::UI::ButtonEvent & buttonEvent) override;

		// ---|> Component
		virtual void doLayout() override;

	private:
		// ---|> Component
		virtual void doDisplay(const Geometry::Rect & region) override;

		bool onKeyEvent(const Util::UI::KeyboardEvent & keyEvent);

	protected:
		// ---o
		virtual float getPosFromValue(float value)const;
		virtual float getValueFromPos(float pos)const;

		float rangeLeft;
		float rangeRight;
		int numSteps;
		float stepWidth;
		int markerSize;

		float value;
		float * floatValueRef;

		Util::WeakPointer<Component> sliderMarker;
		Util::WeakPointer<Button> button1;
		Util::WeakPointer<Button> button2;

		Util::StringIdentifier dataName;

		GUI_Manager::KeyListenerHandle keyListenerHandle;
};
}
#endif // GUI_Slider_H
