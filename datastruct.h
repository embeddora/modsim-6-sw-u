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

#ifndef _DATASTUCT_H_
#define _DATASTUCT_H_


#if defined(UCSIMM)

/* Old cross compiler does not operate such ANSI macro as __func__ */
#define __func__ "_func_"

#endif /* defined(UCSIMM) */


#if defined(QUASIFLOAT) 
typedef struct _QuasiFloatType
{
	/* Integer part of quasi-float */
	int integer;

	/* Fractal part of quasi-float */
	int fraction;

}  QuasiFloatType, *pQuasiFloatType;
#endif /* defined(QUASIFLOAT) */


/* List of D+(d.IN) and D-(d.OUT) values with relative time points */
typedef struct _TimepointType
{
	/* String to descibe this tm. point */
	char * pcMarquee;

	/* 0 - 256 for ADxx for 'white' */
	unsigned short ushRawXval;

	/* 0 - 256 for ADxx for 'green' */
	unsigned short ushRawYval;

	/* Average qudratic for 'white' */
	unsigned short ushQuadAvgXval;

	/* Average qudratic for 'green' */
	unsigned short ushQuadAvgYval;	

#if !defined(QUASIFLOAT) 
	/* D- , yellow pin */
	float fltXval;

	/* D+ , blue pin */
	float fltYval;

	/* CVS's time stamp */
	float fltAbsTime;
#else
	/* D- , green wire of USB wire quartet */
	QuasiFloatType qfltXval;

	/* D+ , white wire of USB wire quartet */
	QuasiFloatType qfltYval;

	/* CSV's time stamp */
	QuasiFloatType qfltAbsTime;
#endif /* !defined(QUASIFLOAT) */

	/* Next time point in the chain */
	struct _TimepointType * pNext;

	/* Previous time point */
	struct _TimepointType * pPrev;

} TimepointType, *pTimepointType;

int _EnrollPoint(const char * caller, pTimepointType * ppThisPointChain, 
#if !defined(QUASIFLOAT) 
	float * pfltTm, float * pfltX, float * pfltY, 
#else
	pQuasiFloatType pqfltTm, pQuasiFloatType pqfltX, pQuasiFloatType pqfltY, 
#endif /* !defined(QUASIFLOAT) */
	char * pcMrq);

/* Exposed to main() via macro */
int _EnrollPoint(const char * caller, pTimepointType * ppThisPointChain, 
#if !defined(QUASIFLOAT) 
	float * pfltTm, float * pfltX, float * pfltY, 
#else
	pQuasiFloatType pqfltTm, pQuasiFloatType pqfltX, pQuasiFloatType pqfltY, 
#endif /* !defined(QUASIFLOAT) */
char * pcMrq);

/* Exposed to main() via macro  */
int _ProcessPoints(const char * caller, pTimepointType pPointChainPar);

/* Exposed to main() via macro */
void _DeletePoints(const char * caller, pTimepointType * ppThisPointChain);

#define EnrollPoint(x, y, s, t, u) _EnrollPoint(__func__, (x), (y), (s), (t), (u))

#define ProcessPoints(x) _ProcessPoints(__func__, (x))

#define DeletePoints(x) _DeletePoints(__func__, (x))

/* First time, exposed to ProcessPoint() */
#if !defined(QUASIFLOAT) 
	float fFIRST;
#else
	int iFIRST;
#endif /* defined(QUASIFLOAT)  */


#endif /* _DATASTUCT_H_ */
