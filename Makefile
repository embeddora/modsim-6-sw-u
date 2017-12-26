#
# Copyright (c) 2018 [n/a] info@embeddora.com All rights reserved
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#        * Redistributions of source code must retain the above copyright
#          notice, this list of conditions and the following disclaimer.
#        * Redistributions in binary form must reproduce the above copyright
#          notice, this list of conditions and the following disclaimer in the
#          documentation and/or other materials provided with the distribution.
#        * Neither the name of The Linux Foundation nor
#          the names of its contributors may be used to endorse or promote
#          products derived from this software without specific prior written
#          permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NON-INFRINGEMENT ARE DISCLAIMED.    IN NO EVENT SHALL THE COPYRIGHT OWNER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# Abstract: 
#

ifeq ($(strip $(platform)),)
$(error "Define 'platform', as one of those: 'platform=PC', 'platform=SITARA' ")
endif

ifeq ($(strip $(platform)),PC)
	PREFIX=
	CFLAGS=-O3  -DDEBUG_DATA 
	OBJS= modsim.o datastruct.o hal_x86.o
	GRBG=*.o *~ m

	EXTRA=
else
	ifeq ($(strip $(platform)),SITARA)
		# Prefix for Cortex-8 ARM crosscompiler 
		PREFIX= #arm-none-linux-gnueabi-
		CFLAGS=-O3 -DSITARA  #-DSH_FOPS

		OBJS= modsim.o datastruct.o beagle.o hal_arm8.o
		GRBG=*.o *~ m
	endif
endif

# (cross-)compiler
CC=$(PREFIX)gcc
LD=$(PREFIX)ld

# Excessive debug info not needed when program is ready. Spoils 'realtime' operating mode. Keep commented-out.
# CFLAGS+=-DDEBUG_DATA

# Basic diagnistocs of ADxx Converter. Endless loop
# CFLAGS+= -DHW_AD53_TEST

.o: .s
	$(CC) $(ASMFLAGS) -o $@ -c $< 

.o: .c
	$(CC) $(CFLAGS) -o $@ -c $<  -lm 

all:	m

m: $(OBJS)
	$(CC) $(CFLAGS)  -o m $(OBJS)  -lm 
	$(EXTRA)

clean:
	rm $(GRBG)
