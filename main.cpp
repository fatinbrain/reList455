#include <ma.h>
#include <MAUtil/Moblet.h>

#include "Splasher.h"
#include "MainScreen.h"

using namespace MAUtil;
using namespace NativeUI;

/**
 * \mainpage reList455
 *
 * Here is some info about **reList455** project.
 *
 * # English
 *
 * ##About
 * **reList455** project is just another event count down application for **Android** devices.
 *
 * ##New
 * - Import/export from/to SDcard.
 * - Fast event parsing.
 * - Adjustable language and style.
 * - Splash screen.
 *
 * ##Features
 * - **Local nature**: works without `GSM` / `WiFi` connection.
 * - **Not hungry**: little battery consumption.
 * - **Easy**: plain, simple.
 * - **Explicit**: all your events in one list.
 *
 * ##Description
 *
 * ###General information
 * **reList455** generates list of upcoming events showing days left to particular event.
 * List is sorted to show sooner at the top.
 * Customer can add new events and edit / remove existing.
 *
 * ###Screenshots
 * \image html mainscreen.png
 * <div style="text-align:center;padding-bottom:4em;">
 * *Main application screen.*
 * </div>
 * \image html newevent.png
 * <div style="text-align:center;padding-bottom:4em;">
 * *Add event screen.*
 * </div>
 *
 * ###Alarm periods
 * Each event has list of alarm periods attached to it.
 * Main feature of application is possibility of advanced setup of event alarm periods.
 * Customer can add desired count of periods.
 * For example, for birthday event you can create period to make every year alarm.
 * For birthday event of your little child you can create monthly alarm event to know how many
 * days left to next month anniversary.
 * And for birthday event of your boss it is possibly reasonable to have 5-years alarm event?
 *
 * ###Limitation
 * - **No Undo**: be careful while deleting events.
 * - **Date Limits**: dates out of 1902-2030 potentially cause not accurate days left calculations.
 *
 * ###ToDo's
 * - **Application settings**: save app settings to device.
 * - **Images integration** for various event types.
 * - **Notifications** of upcoming events.
 * - **Internationalization** user interface.
 * - **Days** event period.
 *
 *
 * ===
 * # Русский
 *
 * ##Коротко
 * **reList455** - приложение обратного отсчёта дней до событий.
 *
 * ##Особенности
 * - Локальность: приложение работает независимо от наличия `GSM` / `WiFi` сетей.
 * - Энерго эффективность: низкий уровень потребления энергии батареи.
 * - Простота
 * - Очевидность: все события одним списком.
 *
 * ##Описание
 *
 * ###Общая информация
 * **reList455** генерирует список грядущих событий с указанием количества оставшихся до них дней.
 * Список отсортирован таким образом, что ближайшие события показаны выше.
 * Пользователь может создавать, изменять и удалять события.
 *
 * ###Снимки
 * \image html v_mainscreen.png
 * <div style="text-align:center;padding-bottom:4em;">
 * Главное окно приложения.
 * </div>
 * \image html v_newevent.png
 * <div style="text-align:center;padding-bottom:4em;">
 * Окно добавления события.
 * </div>
 *
 * ###Периоды повтора
 * Каждое событие содержит список периодов повтора.
 * Отличительной особенностью приложения является возможность настройки этих периодов.
 * Например, для своего дня рождения можно создать ежегодное событие;
 * для дня рождения ребёнка имеет смысл задать ежемесячный период повтора, чтобы знать сколько
 * осталось дней до следующего месячного юбилея.
 * А для дня рождения дальнего родственника можно установить десятилетний период,
 * чтобы знать когда у него произойдёт следующий большой юбилей
 *
 * ###Текущие ограничения
 * - Отсутствует Отмена: будьте осторожны при удалении событий.
 * - Ограничения даты: даты, не входящие в период 1902-2030, могут потенциально неверно обсчитываться.
 *
 */

/**
 * Moblet to be used as a template for a Native UI application.
 */
class NativeUIMoblet: public Moblet {
public:
	/**
	 * The constructor creates the user interface.
	 */
	NativeUIMoblet() {
		splash = new Splasher();
		splash->show();

		ms = new MainScreen();
		ms->show();
	}

	/**
	 * Destructor.
	 */
	virtual ~NativeUIMoblet() {
		delete ms;
	}

	void NativeUIMoblet::keyPressEvent(int keyCode, int nativeCode){
		if (MAK_BACK == keyCode || MAK_0 == keyCode) {
		}else if(MAK_MENU == keyCode){
		}
	}


private:
	Splasher* splash;
	MainScreen* ms;
};

/**
 * Main function that is called when the program starts.
 */
extern "C" int MAMain() {
	Moblet::run(new NativeUIMoblet());
	return 0;
}
