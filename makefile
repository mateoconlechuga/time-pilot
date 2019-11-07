# ----------------------------
# Program Options
# ----------------------------

NAME         ?= PILOT
ICON         ?= iconc.png
DESCRIPTION  ?= "Time Pilot"
COMPRESSED   ?= YES
ARCHIVED     ?= NO

# ----------------------------
# Compile Options
# ----------------------------

OPT_MODE     ?= -Oz
EXTRA_CFLAGS ?= -Wall -Wextra

# ----------------------------
# Debug Options
# ----------------------------

OUTPUT_MAP   ?= NO

include $(CEDEV)/include/.makefile
