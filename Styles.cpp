#include "Styles.h"

Style Styles::items[] = {
			//Silver style.
		{"Silver",
				{"Clockopia", "DroidSerif-Regular", "DroidSerif-Bold"},
				{20, 17, 40, 75, 15, 13, 60, 400},
				{0x000000, 0x9e9e9e, 0x4a4d4a, 0xffffff, 0xdddddd,
					0x777777, 0x999999, 0xdddddd, 0x111111}},

			//Yellow style.
		{"Yellow",
				{"Clockopia", "DroidSerif-Regular", "DroidSerif-Bold"},
				{20, 17, 40, 75, 15, 13, 60, 400},
				{0x0e0e0e, 0xfeee00, 0x3e3e3e, 0xfeee00, 0xeeeeee,
					0xb2b26d, 0xffee00, 0xcccc00, 0x111111}},
 };

int Styles::getItemsCount() {
	return COUNTSTYLES;
}
