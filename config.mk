# set project top directory
PJT_DIR := $(PWD)
export PJT_DIR

ifndef EXECDIR
	export EXECDIR = $(PJT_DIR)/bin
endif

# tool chains
CC     	= $(CROSS)gcc
LD      = $(CROSS)ld
AR      = $(CROSS)ar
NM      = $(CROSS)nm
RANLIB  = $(CROSS)ranlib
STRIP   = $(CROSS)strip

export CC
export GPP
export AR
export LD
export NM
export RANLIB
export STRIP


# header file search path
#INCDIR  =  $(LIBRARY_PREFIX)/include
INCDIR  += $(PJT_DIR)/../../common
INCDIR  += $(PJT_DIR)/robot/motor
INCDIR  += $(PJT_DIR)/robot/log
INCDIR  += $(PJT_DIR)/robot/lib
INCDIR  += $(PJT_DIR)/robot/timer
INCDIR  += .

INC_DIR := $(addprefix -I , $(INCDIR))
export INC_DIR

# library search path
#LIBDIR  = $(LIB_INS_DIR)
LIBDIR  = $(PJT_DIR)
LIBDIR  += $(LIBRARY_PREFIX)/lib

# library linked
#.a lib
LIBS_A =
#.so lib
LIBS_SO = -lpthread
LIBS    = $(LIBS_A) $(LIBS_SO)


#addprefix -L  ;;-L LIBDIR
LIB_DIR := $(addprefix -L , $(LIBDIR))
export LIB_DIR

# compile options
CFLAGS  = $(EXDEFINE_FLAG)  -Wall -g -W -O2  $(LIB_DIR) $(INC_DIR) $(LIBS) -DENABLE_TRACE
export CFLAGS

CFLAGS_SO = $(EXDEFINE_FLAG) -Wall -g -W -O2 $(LIB_DIR) $(INC_DIR) $(LIBS_SO) -DENABLE_TRACE
export CFLAGS_SO



