/*
 * gps_hw.cpp
 *
 *      Author: LiberdaA
 */


#include <iostream>
#include <string.h>
//#include <windows.h> // Sleep()
#include "gpshw.hpp"

#define	GPSHW_NBR_OF_MESSAGES	3
static const char *msg[GPSHW_NBR_OF_MESSAGES] = {
					"This is a first message",
					"This is a second message",
					"This is a third message"
			};


#if 0
void gpsHw()
{
	bool run = false;
	uint16_t idx = 0;

	run = true;
	while(run)
	{


		// https://stackoverflow.com/questions/158585/how-do-you-add-a-timed-delay-to-a-c-program
		// Win32: Sleep(milliseconds) is what you what
		// Linux: sleep(seconds)
		Sleep(1);  // send data every 1 sec
	}


}
#endif


void GPSHW_GetMsg(char *b)
{
	static uint16_t idx = 0;

	strcpy(b, msg[idx]);  //todo: what type of second parameter here ?
	idx++;
	if (idx > GPSHW_NBR_OF_MESSAGES)
		idx = 0;

}

