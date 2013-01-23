/**
 * \file Options.h
 * \brief Represent Options class for relist455 project.
 */

#ifndef OPTIONS_H_
#define OPTIONS_H_

#include "Convert.h"
#include <MAUtil/String.h>
#include "conprint.h"

using MAUtil::String;

/**
 * \brief Class to work with relist455 options.
 *
 * ###Format
 * There are several versions of format.
 *
 * **v0** (ver)|(langid)|(styleid)|
 */
class Options{
public:
	/**
	 * \brief Options parser from string.
	 * @param s String to parse.
	 */

	void parse(String s);
	/**
	 * \brief Options exporter to string.
	 * @return Export string of Options class.
	 */
	String toString();

	/**
	 * \brief Getter of current language id.
	 * @return Current language id.
	 */
	int getLangId();

	/**
	 * \brief Set language id.
	 * @param langId Language id.
	 */
	void setLangId(int langId);

	/**
	 * \brief Getter of current style id.
	 * @return Current style id.
	 */
	int getStyleId();

	/**
	 * \brief Set style id.
	 * @param langId Style id.
	 */
	void setStyleId(int styleId);

	/**
	 * \brief Default constructor.
	 */
	Options();

	/**
	 * \brief Default destructor.
	 */
	~Options();


private:
	static int version;
	static int langId;
	static int styleId;


	/**
	 * \brief Internal parser of v0 format.
	 * @param s String to parse.
	 */
	void parse0(String s);
};


#endif /* OPTIONS_H_ */
