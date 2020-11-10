CXX					= arm-linux-gnueabihf-gcc  
PROJECT				=  PocCoreIP
BUILD_DIR           ?= build
COPY_EXEC_IN=/home/nfsArcomTst/home/ #tftp server repository

DIR_UTILS           = utils
DIR_OSAL		    = osal
DIR_APP				= application
DIR_ZMQ             = zmq

# Application sources and artifacts
APP_BIN         	= 	$(BUILD_DIR)/$(PROJECT)
APP_SOURCES         = 	$(DIR_UTILS)/src/utilities.c \
						$(DIR_UTILS)/src/logger.c \
						$(DIR_UTILS)/src/fifo.c \
						$(DIR_UTILS)/src/hash_map.c \
						$(DIR_OSAL)/src/PosixOsal.c \
						$(DIR_OSAL)/src/ech_logger.c \

APP_MAIN            =   main.c

APP_OBJS            = $(patsubst %.c,$(BUILD_DIR)/%.o,$(APP_SOURCES) $(APP_MAIN))

# Generated depedecy files
DEPS                = $(APP_OBJS:.o=.d)

# Compiler options
COMMON_CFLAGS       = -Wall -Wextra -MMD -Wno-unused-variable -Wno-unused-parameter -fmessage-length=0
INCLUDE_DIRS 		= -I . -I $(DIR_OSAL)/inc -I $(DIR_UTILS)/inc -I $(DIR_ZMQ)/inc

# Debug/Release mode
ifneq ($(DEBUG),)
  COMMON_CFLAGS     += -g
  BUILD_DIR         := $(BUILD_DIR)/debug
else
  COMMON_CFLAGS     += -DNDEBUG
  BUILD_DIR         := $(BUILD_DIR)/release
endif

LDFLAGS 			= -lpthread -lm -L $(DIR_ZMQ)/lib -lzmq
CFLAGS              = $(COMMON_CFLAGS) $(INCLUDE_DIRS)

# Silence make
ifneq ($(V),)
  SILENCE           =
else
  SILENCE           = @
endif

# Fancy output
SHOW_COMMAND        := @printf "\033[0;32m %-8s\033[0m %s\n"  
SHOW_CXX            := $(SHOW_COMMAND) "[$(CXX)]"
SHOW_CLEAN          := $(SHOW_COMMAND) "[ CLEAN ]"
SHOW_GEN            := $(SHOW_COMMAND) "[ GEN ]"

##############################################################################################
# Default target and help message
##############################################################################################
DEFAULT_TARGET =  $(APP_BIN)

all: $(DEFAULT_TARGET)
.PHONY: all

# Take care of compiler generated depedencies
-include $(DEPS)

##############################################################################################
# Version generated file
##############################################################################################
#src/Version.hpp: src/Version.hpp.in Makefile $(APP_SOURCES)
#	$(SHOW_GEN) $@
#	$(SILENCE)sed -e's/%%VERSION_MAJOR%%/$(VERSION_MAJOR)/g' \
#	  -e 's/%%VERSION_MINOR%%/$(VERSION_MINOR)/g' \
#	  -e 's/%%VERSION_BUGFIX%%/$(VERSION_BUGFIX)/g' \
#	  -e 's/%%VERSION_GIT%%/$(VERSION_GIT)/g' \
#	  $< > $@

##############################################################################################
# Application
##############################################################################################
$(APP_BIN): $(APP_OBJS)
	$(SHOW_CXX) $@
	$(SILENCE)$(CXX) $(APP_OBJS) $(LDFLAGS) -o $@
	$(SILENCE)cp $(BUILD_DIR)/$(PROJECT) $(COPY_EXEC_IN)
#	$(SILENCE) ./generVersion

$(BUILD_DIR)/%.o: %.c
	$(SHOW_CXX) $@
	$(SILENCE)mkdir -p $(dir $@)
	$(SILENCE)$(CXX) $(CFLAGS) -c $< -o $@ 
	
	
##############################################################################################
# Cleanup
##############################################################################################
clean:
	$(SHOW_CLEAN) $(BUILD_DIR)
	$(SILENCE)rm -rf $(BUILD_DIR)/*
.PHONY: clean
