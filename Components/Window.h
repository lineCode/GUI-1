/*
	This file is part of the GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef GUI_WINDOW_H
#define GUI_WINDOW_H

#include "Container.h"
#include "../Base/Listener.h"
#include <memory>

namespace GUI {
class Label;
class Button;

/***
 **     Window ---|> Container ---|> Component
 **                   0..1 ------------> *
 **/
class Window : public Container,public ActionListener,public MouseButtonListener,public KeyListener {
		PROVIDES_TYPE_NAME(Window)
	public:
		static const Util::StringIdentifier ACTION_onWindowClosed;

		// flags
		static const flag_t NO_CLOSE_BUTTON=1<<24;
		static const flag_t NO_MINIMIZE_BUTTON=1<<25;
		static const flag_t NO_RESIZE_PANEL=1<<26;
		static const flag_t HIDDEN_WINDOW=1<<27;  //!< Only the content of the window is shown, if it is not selected.
		static const flag_t ONE_TIME_WINDOW=1<<28; //! Destroy the content when closed.

		Window(GUI_Manager & gui,const Geometry::Rect & r,const std::string & title="",flag_t flags=0);
		virtual ~Window();

		void init();

		Container * getHeader()const 	{	return titlePanel.get();	}
		Container * clientArea()const 	{	return clientAreaPanel.get();	}
		bool isMinimized()const 		{	return minimized;	}
		void minimize();
		void restore();
		void restoreRect();

		void setTitle(const std::string & title);
		std::string getTitle()const;

		void setLogo(Component * newLogo);
		Component * getLogo()const 		{	return logo.get();	}

		float getOpacity()const			{	return opacity;	}
		void setOpacity(float f)		{	opacity=f;	}

		//! start the closing animation, when the animation is finished, onClosed() is called.
		void close();

		//! (internal) Called when the closing animation has finished.
		void _onClosed();


		// ---|> MouseButtonListener
		virtual listenerResult_t onMouseButton(Component * /*component*/, const Util::UI::ButtonEvent & buttonEvent);
		// ---|> ActionListener
		virtual listenerResult_t handleAction(Component *,const Util::StringIdentifier & actionName);
		// ---|> KeyListener
		virtual bool onKeyEvent(Component * component, const Util::UI::KeyboardEvent & keyEvent);
		// ---|> Container
		virtual void addContent(const Ref & child) 						{	clientAreaPanel->addContent(child);	}
		virtual void removeContent(const Ref & child) 					{	clientAreaPanel->removeContent(child);	}
		virtual size_t getContentsCount()const							{	return clientAreaPanel->getContentsCount();	}
		virtual std::vector<Component*> getContents()					{	return clientAreaPanel->getContents();	}
		virtual void clearContents() 									{	clientAreaPanel->clearContents();	}
		virtual void insertAfter(const Ref & child,const Ref & after)	{
			clientAreaPanel->insertAfter(child,after);
		}
		virtual void insertBefore(const Ref & child,const Ref & after){
			clientAreaPanel->insertBefore(child,after);
		}

		// ---|> Component
		virtual Geometry::Rect getInnerRect()const 						{	return clientAreaPanel->getLocalRect();	}
		virtual void invalidateRegion();
		virtual void doLayout();
		virtual bool onSelect();
		virtual bool onUnselect();

	private:
		// ---|> Component
		virtual void doDisplay(const Geometry::Rect & region);
		Util::WeakPointer<Container> clientAreaPanel;
		Util::WeakPointer<Container> titlePanel;
		Util::WeakPointer<Label> titleTextLabel;
		Util::WeakPointer<Component> resizePanel;
		Util::WeakPointer<Button> disableButton;
		Util::WeakPointer<Button> minimizeButton;
		Util::WeakPointer<Button> hiddenButton;
		Util::WeakPointer<Component> logo;
		bool minimized;
		Geometry::Rect storedRect;
		float opacity;

		std::unique_ptr<MouseMotionListener> autoMinimizer;
};
}
#endif // GUI_WINDOW_H
