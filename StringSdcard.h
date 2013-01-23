/**
 * \file StringSdcard.h
 * \brief Functions to perform write/read operation with sdcard.
 *
 * \note Functions process files at default location at /mnt/sdcard/your_file_name.
 */

#ifndef STRINGSDCARD_H_
#define STRINGSDCARD_H_

#include <ma.h>
#include <MAUtil/String.h>

using MAUtil::String;

/**
 * \brief Write string to sdcard.
 * @param data String to write.
 * @param fname Filename where to save data.
 */
void writeStringToSdcard(String data, String fname);

/**
 * \brief Read string from sdcard.
 * @param fname Filename from which read data.
 * @return Result of read.
 */
String readStringFromSdcard(String fname);

#endif /* STRINGSDCARD_H_ */
