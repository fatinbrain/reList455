#include "Styler.h"

int Styler::currStyleId = 0;

int Styler::scrX = 0;
int Styler::scrY = 0;

int Styler::szFontSize1_ =
		Styles::items[currStyleId].sizes[SI_SZ_F1];
int Styler::szFontSize2_ =
		Styles::items[currStyleId].sizes[SI_SZ_F2];
int Styler::szFontDaysLeft_ =
		Styles::items[currStyleId].sizes[SI_SZ_FDL];
int Styler::szWidthDaysLeft_ =
		Styles::items[currStyleId].sizes[SI_SZ_WDL];
int Styler::szPadding_ =
		Styles::items[currStyleId].sizes[SI_SZ_P];
int Styler::szFontLittleMessage_ =
		Styles::items[currStyleId].sizes[SI_SZ_FLM];
int Styler::szBottomCtrlHeight =
		Styles::items[currStyleId].sizes[SI_SZ_BCH];
double Styler::szNativeDiagonal =
		static_cast<double>(Styles::items[currStyleId].sizes[SI_SZ_ND]);

const char* Styler::fontnameDaysLeft =
		Styles::items[currStyleId].fonts[SI_FN_DL];
const char* Styler::fontnameEventName =
		Styles::items[currStyleId].fonts[SI_FN_EN];
const char* Styler::fontnameScreenTitle =
		Styles::items[currStyleId].fonts[SI_FN_ST];

////#if STYLE == STYLE_VELCOM
int Styler::clFCDaysLeft =
		Styles::items[currStyleId].colors[SI_CL_FDL];
int Styler::clBGDaysLeft =
		Styles::items[currStyleId].colors[SI_CL_BDL];
int Styler::clBGMessage =
		Styles::items[currStyleId].colors[SI_CL_BM];
int Styler::clFCName =
		Styles::items[currStyleId].colors[SI_CL_FN];
int Styler::clFCMessage =
		Styles::items[currStyleId].colors[SI_CL_FM];

int Styler::clBottomCtrlsLayoutColor =
		Styles::items[currStyleId].colors[SI_CL_BBC];
int Styler::clLabelGradient2 =
		Styles::items[currStyleId].colors[SI_CL_LG1];
int Styler::clLabelGradient1 =
		Styles::items[currStyleId].colors[SI_CL_LG2];
int Styler::clFCTitle =
		Styles::items[currStyleId].colors[SI_CL_FT];


void Styler::subLabel(Label *lb) {
	lb->setFontSize(szFontSize2_);
	lb->setBackgroundGradient(clLabelGradient1, clLabelGradient2);
	lb->setFontColor(clFCTitle);
	lb->fillSpaceHorizontally();
	lb->setTextHorizontalAlignment(MAW_ALIGNMENT_LEFT);
}

void Styler::setLabelStyle(Label *lb, LabelStyles style) {
	switch (style) {
	case LSLevel1:
		lb->setFontSize(szFontSize1_);
		lb->setBackgroundGradient(clLabelGradient2, clLabelGradient1);
		lb->setFontColor(clFCTitle);
		lb->fillSpaceHorizontally();
		lb->setTextHorizontalAlignment(MAW_ALIGNMENT_CENTER);
		break;
	case LSLevel2:
		lb->setFontSize(szFontSize2_);
		lb->setBackgroundGradient(clLabelGradient1, clLabelGradient2);
		lb->fillSpaceHorizontally();
		lb->setTextHorizontalAlignment(MAW_ALIGNMENT_LEFT);
		break;
	case LSPopupMessage:
		lb->fillSpaceHorizontally();
		lb->setTextHorizontalAlignment(MAW_ALIGNMENT_CENTER);
		lb->wrapContentVertically();
		lb->wrapContentHorizontally();
		lb->setFontSize(szFontSize1_);
		break;
	case LSScreenName:
		break;
	default:
		break;
	}
}

int Styler::getSzFontSize2() {
	return szFontSize2_;
}

int Styler::getSzFontSize1() {
	return szFontSize1_;
}

void Styler::setLayoutPadding(Layout* layout, int paddingSize) {
	int currPadding = paddingSize;

	if (paddingSize < 0) {
		currPadding = szPadding_;
	}

	layout->setPaddingTop(currPadding);
	layout->setPaddingBottom(currPadding);
	layout->setPaddingLeft(currPadding);
	layout->setPaddingRight(currPadding);
}

int Styler::getScrX() {
	return scrX;
}

int Styler::getScrY() {
	return scrY;
}

int Styler::getSzPadding() {
	return szPadding_;
}

int Styler::szFontLittleMessage(){
	return szFontLittleMessage_;
}

void Styler::setBottomCtrlLayoutStyle(HorizontalLayout *layout){
	layout->fillSpaceHorizontally();
	layout->setBackgroundColor(clBottomCtrlsLayoutColor);
	layout->setHeight(szBottomCtrlHeight);
	layout->setChildVerticalAlignment(MAW_ALIGNMENT_CENTER);
}

int Styler::setLabelFont(Label *lb, const char *fontName, int fontSize){
	MAHandle fo = maFontLoadWithName(fontName, fontSize);
	return lb->setFont(fo);
}

int Styler::getClLabelGradient1(){
	return clLabelGradient1;
}

int Styler::getClLabelGradient2(){
	return clLabelGradient2;
}

void Styler::addSeparator(Layout* lay, int size) {
	Label* separator = new Label();
	separator->setHeight(size);
	separator->fillSpaceHorizontally();

	lay->addChild(separator);
}

int Styler::getCurrStyleId(){
	return currStyleId;
}

void Styler::setCurrStyleId(int currStyleId) {
	if(currStyleId >= Styles::getItemsCount()){
		Styler::currStyleId = 0;
	}else{
//		ASSERT_MSG(0, Convert::toString(currStyleId).c_str());
		Styler::currStyleId = currStyleId;
	}
	update();
}

Styler::Styler() {
	update();
}

int Styler::getSzFontDaysLeft() {
	return szFontDaysLeft_;
}

void Styler::update(){
	Styler::szFontSize1_ =
		Styles::items[currStyleId].sizes[SI_SZ_F1];
	Styler::szFontSize2_ =
		Styles::items[currStyleId].sizes[SI_SZ_F2];
	Styler::szFontDaysLeft_ =
		Styles::items[currStyleId].sizes[SI_SZ_FDL];
	Styler::szWidthDaysLeft_ =
		Styles::items[currStyleId].sizes[SI_SZ_WDL];
	Styler::szPadding_ =
		Styles::items[currStyleId].sizes[SI_SZ_P];
	Styler::szFontLittleMessage_ =
		Styles::items[currStyleId].sizes[SI_SZ_FLM];
	Styler::szBottomCtrlHeight =
			Styles::items[currStyleId].sizes[SI_SZ_BCH];
	Styler::szNativeDiagonal =
			static_cast<double>(Styles::items[currStyleId].sizes[SI_SZ_ND]);

	Styler::fontnameDaysLeft =
			Styles::items[currStyleId].fonts[SI_FN_DL];
	Styler::fontnameEventName =
			Styles::items[currStyleId].fonts[SI_FN_EN];
	Styler::fontnameScreenTitle =
			Styles::items[currStyleId].fonts[SI_FN_ST];

	//#if STYLE == STYLE_VELCOM
	Styler::clFCDaysLeft =
		Styles::items[currStyleId].colors[SI_CL_FDL];
	Styler::clBGDaysLeft =
		Styles::items[currStyleId].colors[SI_CL_BDL];
	Styler::clBGMessage =
		Styles::items[currStyleId].colors[SI_CL_BM];
	Styler::clFCName =
		Styles::items[currStyleId].colors[SI_CL_FN];
	Styler::clFCMessage =
		Styles::items[currStyleId].colors[SI_CL_FM];

	Styler::clBottomCtrlsLayoutColor =
		Styles::items[currStyleId].colors[SI_CL_BBC];
	Styler::clLabelGradient2 =
		Styles::items[currStyleId].colors[SI_CL_LG1];
	Styler::clLabelGradient1 =
		Styles::items[currStyleId].colors[SI_CL_LG2];
	Styler::clFCTitle =
			Styles::items[currStyleId].colors[SI_CL_FT];

	MAExtent scrSz = maGetScrSize();
	scrX = EXTENT_X(scrSz);
	scrY = EXTENT_Y(scrSz);
	int diagonal = static_cast<int>(sqrt(scrX * scrX + scrY * scrY));
	double scaleFactor = sqrt(diagonal / szNativeDiagonal);

	szFontLittleMessage_ = static_cast<int>(szFontLittleMessage_ * scaleFactor);
	szFontDaysLeft_ = static_cast<int>(szFontDaysLeft_ * scaleFactor);
	szWidthDaysLeft_ = static_cast<int>(szFontDaysLeft_ * 2.1);
	szFontSize1_ = static_cast<int>(szFontSize1_ * scaleFactor);
	szFontSize2_ = static_cast<int>(szFontSize2_ * scaleFactor);
	szPadding_ = static_cast<int>(szPadding_ * scaleFactor);
	szBottomCtrlHeight = static_cast<int>(szBottomCtrlHeight * scaleFactor);
}

int Styler::getSzWidthDaysLeft(){
    return szWidthDaysLeft_;
}

int Styler::getClBgDaysLeft(){
    return clBGDaysLeft;
}

int Styler::getClBgMessage(){
    return clBGMessage;
}

int Styler::getClFcDaysLeft(){
    return clFCDaysLeft;
}

int Styler::getClFcMessage(){
    return clFCMessage;
}

int Styler::getClFcName(){
    return clFCName;
}

int Styler::getSzFontLittleMessage(){
    return szFontLittleMessage_;
}
