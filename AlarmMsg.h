/**
 * \file  AlarmMsg.h
 * \author  fat
 * \brief  Contains AlarmMsg structure
 * \version 0.1
 */

#ifndef ALARMMSG_H_
#define ALARMMSG_H_

#include <MAUtil/String.h>

/**
 * \brief Structure to represent alarm message of event.
 * \version  0.1
 */
struct AlarmMsg{
public:
	int DaysTo;
	    /**<Days to next alarm date*/
	MAUtil::String Name;
		/**<Name of event*/
	MAUtil::String Message;
	    /**<Alarm message*/
	int EventIndex;
		/**<Index of event in event list connected with this alarm message.*/
	int EventPeriodIndex;
		/**<Index of current event period connected with this alarm message.*/

	/**
	 * Default constructor
	 */
	AlarmMsg();
private:

};


#endif /* ALARMMSG_H_ */
