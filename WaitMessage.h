#ifndef WAITMESSAGE_H_
#define WAITMESSAGE_H_

#include "Styler.h"

#include <NativeUI/Widgets.h>
#include <MAUtil/String.h>

using namespace MAUtil;
using namespace NativeUI;

class WaitMessage {
public:
	WaitMessage(String title ="Please, wait...", String message = "text message");
	~WaitMessage();

	void show();
	void hide();
	void setMessage(String message);
	void setTitle(String title);
private:
	String message_;
	String title_;
	bool isVisible_;
	Dialog* dia_;
	Label* lbMessage_;
	ActivityIndicator* ai_;

	void createLayout();
};

#endif /* WAITMESSAGE_H_ */
