/**
 * \file Splasher.h
 * \brief Contains Splasher class to work with splash screen of program.
 */

#ifndef SPLASHER_H_
#define SPLASHER_H_

#include "MAHeaders.h"
#include <NativeUI/Image.h>
#include <NativeUI/Widgets.h>

using namespace NativeUI;

/**
 * \brief Very simple version of splasher.
 *
 * \warning Hardcoded logo handler *LOGO*.
 */
class Splasher:public Screen {
public:
	Splasher();
	~Splasher();
private:
	VerticalLayout* vlMain;
	Image* imgSplash;

	void createUI();
};


#endif /* SPLASHER_H_ */
