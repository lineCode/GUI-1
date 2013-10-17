/*
	This file is part of the GUI library.
	Copyright (C) 2008-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2008-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2008-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef GUI_Panel_H
#define GUI_Panel_H

#include "ScrollableContainer.h"
#include "LayoutHelper.h"
#include <iostream>

namespace GUI {
class Scrollbar;
class FlowLayouter;
/***
 **     Panel ---|> ScrollableContainer
 **/
class Panel: public ScrollableContainer {
		PROVIDES_TYPE_NAME(Panel)
	public:
		typedef GUI::NextRow NextRow; //! @deprecated  Only for backward compatibility!
		typedef GUI::NextColumn NextColumn; //! @deprecated  Only for backward compatibility!
		
		static const flag_t AUTO_LAYOUT=1<<24; //! unused!

		Panel(GUI_Manager & gui,flag_t flags=0);
		Panel(GUI_Manager & gui,const Geometry::Rect & r,flag_t flags=0);
		virtual ~Panel();

		void nextRow(float additionalSpacing=0);
		void nextColumn(float additionalSpacing=0);

		void disableAutoBreak();
		void enableAutoBreak();

		void setMargin(int _margin);
		void setPadding(int _padding);

	private:
		FlowLayouter & accessLayouter();
		
		void init();
};
}
#endif // GUI_Panel_H
