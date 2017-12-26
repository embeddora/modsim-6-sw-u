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

/* printf(), stdout */
#include <stdio.h>

/* realloc() */
#include <stdlib.h>

/* struct timeval, gettimeofday() */
#include <sys/time.h>

/* Basic project definitions  */
#include "modsim.h"

/* Type 'pTimepointType' definition */
#include "datastruct.h"

int ProcessPoint( pTimepointType pTimepoint )
{
// TODO: workaround. normally the data stream should distributed across all of the attached CPEs
int iCPE=0;

int iJiffie;		
		
	// TODO: the <Jiffies> normally to be compyted dynamically, on-the-run. Anyway shoudl not be a constant.		
	iJiffie = 1000*19/7; // 60 secs		
	//((120*2*100*19/7)/105); // 12 secs

// TODO: remove this workaround
#define max(x,y)	((x>y)?x:y)
// TODO: remove this workaround
#define min(x,y)	((x<y)?x:y)
// TODO: remove this workaround
#define CONV_MAX_SCALE 255
// TODO: remove this workaround
#define VDD_VOLTAGE 	5


		/* Parsing-out redundant data from CVS-datafile yet to be implemented */
		none

		usleep(iJiffie);

		/* Put current value on 'green' wire */
// 07.06.2016 : this line is indifferent for HW->PC
#if 1
#if 0
		/* Logical zero, anyway */
		pTimepoint->ushQuadAvgYval = max(0.012*CONV_MAX_SCALE / VDD_VOLTAGE, pTimepoint->ushQuadAvgYval);
		pTimepoint->ushQuadAvgYval = max(0.012*CONV_MAX_SCALE / VDD_VOLTAGE, pTimepoint->ushQuadAvgYval);
		/* Logical one, anyway */
		pTimepoint->ushQuadAvgXval = min(0.036*CONV_MAX_SCALE / VDD_VOLTAGE, pTimepoint->ushQuadAvgXval);
		pTimepoint->ushQuadAvgYval = min(0.036*CONV_MAX_SCALE / VDD_VOLTAGE, pTimepoint->ushQuadAvgYval);

#endif /* (0) */
		if (pTimepoint->ushQuadAvgYval > 255)pTimepoint->ushQuadAvgYval = 255;  
		if (pTimepoint->ushQuadAvgXval > 255)pTimepoint->ushQuadAvgXval = 255;


		_i_AD5300_Write_W(pTimepoint->ushQuadAvgXval, iCPE);

		/* Put current value on 'white' wire */
		_i_AD5300_Write_G(pTimepoint->ushQuadAvgYval, iCPE);
#else

		if (pTimepoint->ushRawYval > 255)pTimepoint->ushRawYval = 255;  
		if (pTimepoint->ushRawXval > 255)pTimepoint->ushRawXval = 255;


		_i_AD5300_Write_W(pTimepoint->ushRawXval, iCPE);

		/* Put current value on 'white' wire */
		_i_AD5300_Write_G(pTimepoint->ushRawYval, iCPE);
#endif /* (0) */

} /* int ProcessPoint( pTimepointType pTimepoint ) */
