#ifndef STORAGEWORKS_H_
#define STORAGEWORKS_H_

#include <ma.h>
#include <MAUtil/String.h>
#include <NativeUI/Widgets.h>
#include <conprint.h>

using namespace MAUtil;

#define VER "0.4"

class StorageWorks{

private:
	MAHandle storage;
	String storageName;
	NativeUI::Label* lbDbg;

	void dbgLb(const String message);
	void closeStorage();
	bool createStorage();

public:
	StorageWorks(String s = "store01", NativeUI::Label *l = NULL);

	void setDbgLabel(NativeUI::Label *l);
	void setStoreName(String storageName);
	void test();

	String getName();

	bool exists();
	int write(const String data);
	String read();
	void rm();

};


#endif /* STORAGEWORKS_H_ */
