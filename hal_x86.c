/*
 * Copyright (c) 2018 [n/a] info@embeddora.com All rights reserved
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *        * Redistributions of source code must retain the above copyright
 *          notice, this list of conditions and the following disclaimer.
 *        * Redistributions in binary form must reproduce the above copyright
 *          notice, this list of conditions and the following disclaimer in the
 *          documentation and/or other materials provided with the distribution.
 *        * Neither the name of The Linux Foundation nor
 *          the names of its contributors may be used to endorse or promote
 *          products derived from this software without specific prior written
 *          permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NON-INFRINGEMENT ARE DISCLAIMED.    IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Abstract:  
 */

/* printf() */
#include <stdio.h>

/* struct timeval, gettimeofday() */
#include <sys/time.h>

/* Basic project definitions  */
#include "modsim.h"

/* Type 'pTimepointType' definition */
#include "datastruct.h"

/* Time measurement variable to define current position on time scale */
struct timeval endtimePROC;

/* Var. defined in 'datastruct.c' */
extern struct timeval starttimePROC;

/* Process Realtime and Relative-time values: certain data to be oputput onto Port D */
int ProcessPoint(pTimepointType pTimepoint)
{
#if !defined(QUASIFLOAT) 
float fltRelTime;
float _left, _right;
float fltJiffy = 1.0;
#else
QuasiFloatType fltRelTime;
QuasiFloatType _left, _right;
int fltJiffy = 1;
#endif /* defined(QUASIFLOAT)  */

	/* TODO: add plain description here  */

#if !defined(QUASIFLOAT) 
	/* Operate uSeconds multiplied by 10e6 because <usleep> accepts	integer parameters only */
	pTimepoint->fltAbsTime = pTimepoint->fltAbsTime*1000000;

	printf("[%s] : <BEFORE TIME SHIFTING> real tm.: %f\n", __FILE__, pTimepoint->fltAbsTime	);

	/* Don't proceed with this fuction once given an unappicable input data */
	if (0.0 == pTimepoint->fltAbsTime ) return;

	do 
	{	/* Take current time */
		gettimeofday(&endtimePROC,0);

		/* Compute how much time elapsed since head of list processing till now */
		fltRelTime = 1000000*(endtimePROC.tv_sec - starttimePROC.tv_sec - fFIRST) 

			+ endtimePROC.tv_usec - starttimePROC.tv_usec;

		/* If relative time stays on the left from 0 */
		if (fltRelTime < 0)

			/* then '_right' is relative time, '_left' is real time */
			_right = fltRelTime, _left = pTimepoint->fltAbsTime;

		/* If relative time stays on the right from 0, or is exctly 0 */
		else
			/* then '_right' is real time, '_left' is relative time */
			_left = fltRelTime, _right = pTimepoint->fltAbsTime;


		/* Wait for relative time <fltRelTime> to catch up with real time <pTimepoint->fltAbsTime>  */
		usleep (fltJiffy);

		printf("[%s] : <TIME SHIFTING> real tm.: %f, shiftable tm.: %f \n", __FILE__, pTimepoint->fltAbsTime,	fltRelTime ); 

	} while (_right < _left);
	
	/* Now they're equal or least 'relative tm' is not less than 'real tm' */
	printf("[%s] : <AFTER TIME SHIFTING> will pretend like <%f>, is same as <%f> \n", __FILE__,

		pTimepoint->fltAbsTime,	fltRelTime );

	/* PC-based simulation of hardware Port 'D' processing */
	none

#else

#endif /* defined(QUASIFLOAT)  */


} /* int ProcessPoint(pTimepointType pTimepoint) */
