#include "Lang.h"

int Lang::currLangId = 0;

lanuage Lang::languages[] = {
		//english
		{0, "English",
				{"Upcoming events",
					"Please wait...",
					"Please wait",
					"New event",
					"Import",
					"Export",
					"Exit",
					"Read data from device",
					"Parsing events",
					"Create Alarms from Events",
					"Render alarms",
					"Font refresh",
					"m",
					"y",
					"now",
					"ytd",
					"Event name\n    ",
					"\nEvent periods\n    ",
					"Alarm context menu",
					"Edit current event",
					"Delete period",
					"Delete whole event",
					"Write event list to device",
					"Sort Alarms",
					"since",
					"* no periods *",
					"Add/Edit event",
					"Event name",
					"Event date",
					"Event repeat period",
					"Add event period",
					"Cancel",
					"Ok",
					"Add event period",
					"Select period",
					"Change period",
					"Select period count",
					"Add",
					"Back",
					"years",
					"months",
					"Options",
					"Language",
					"Change",
					"Select language",
					"    Choose language from list.\n    Need restart to apply.",
					"Style",
					"Style selector",
					"    Select style form list.\n    App restart needed to apply."
				}},
		//russian
		{1, "Russian",
				{"Грядущие события",
					"Подождите...",
					"Подождите",
					"Добавить",
					"Импортировать",
					"Экспортировать",
					"Выход",
					"Чтение данных",
					"Разбор событий",
					"Создание списка событий",
					"Наполнение списка напоминаний",
					"Настройка шрифтов",
					"м",
					"г",
					"сегодня",
					"вчера",
					"Событие\n    ",
					"\nПериоды\n    ",
					"Действия",
					"Изменить",
					"Удалить период",
					"Удалить событие",
					"Запись событий на устройство",
					"Сортировка напоминаний",
					"начиная с",
					"* нет периодов *",
					"Изменить событие",
					"Название события",
					"Дата события",
					"Период повтора",
					"Новый период",
					"Отмена",
					"Принять",
					"Добавить период",
					"Выбор периода",
					"Изменить период",
					"Выбор количества",
					"Добавить",
					"Назад",
					"года",
					"месяцы",
					"Настройки",
					"Язык",
					"Изменить",
					"Выбор языка",
					"    Выберите язык из списка.\n    Требуется перезапуск.",
					"Стиль",
					"Выбор стиля",
					"    Выберите стиль из списка.\n    Стиль обновится после перезапуска."
				}}
};

Lang::Lang(){

}

String Lang::getString(int stringIndex) {
	MAASSERT(stringIndex < MAXSTRCOUNT);
	String rez = languages[currLangId].strings[stringIndex];
	return rez;
}

int Lang::getCurrLangId(){
	return currLangId;
}

void Lang::setCurrLangId(int currLangId) {
	Lang::currLangId = currLangId;
}

String Lang::getCurrLangName() {
	return Lang::languages[Lang::currLangId].name;
}

int Lang::getLangsCount() {
	return LANGSCOUNT;
}

String Lang::getLangName(const int index) {
	return Lang::languages[index].name;
}
