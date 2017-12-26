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

#ifndef _MODSIM_H_
#define _MODSIM_H_

/* Success. Returned by most functions as an integer */
#define P_SUCCESS	0

#define P_ERROR		(-1)
/* Error. Data were not scanned from external file */
#define P_ERROR_SCN	(-2)

/* Error. Memory was not allocated, or saoem relative memory error */
#define P_ERROR_MEM	(-3)

/* Error. Bad hardware environment detected or some unexpected hardware responce occured */
#define P_ERROR_HW	(-4)

#define FILE_NAME	"./RawData/12d1_14fe_0_60.txt"
//#define FILE_NAME	"./RawData/090c:1000/data.TXT"
//OBSOLETE FILE FORMAT TODO: remove #define FILE_NAME	"./RawData/12d1:1446/NewFile1.csv"
//OBSOLETE FILE FORMAT TODO: remove#define FILE_NAME	"./RawData/1bbb:022c/NewFile1.csv"

/* Local buffer size */
#define LARGE_BUF_SZ	0x100

/* Phony definition to define the place where the code is yet to be added */
#define none ;

/* Marker of not defined operation, to ensure we've computed operation code correctly */
#define DO_NO_OP	0

/* Operation code of issuing USB1.1 signal on gateway #0 */
#define DO_GATE0_OP	1

/* Operation code of issuing USB2.0 signal on gateway #1 */
#define DO_GATE1_OP	2

#if defined(UCSIMM)

/* Old UCLIBC not have such macro in <getopt.h> */
#define no_argument 0

/* Old UCLIBC not have <option> type in <getopt.h> */
struct option
{
	const char *name;

	int         has_arg;

	int        *flag;

	int         val;
};


/* Old UCLIBC does not have <getopt_long()>, but has <getopt()> */
#define getopt_long(a,b,c,d,e)  getopt(a,b,c)

#endif /* (defined(UCSIMM) ) */

/* Exposed to <PeriphInit> */
extern int iOperation;

#endif /* _MODSIM_H_ */
