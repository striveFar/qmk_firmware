PROTOCOL_DIR = protocol
NRF52_DIR = $(PROTOCOL_DIR)/nrf52

SRC += $(NRF52_DIR)/nrf52.c

VPATH += $(TMK_PATH)/$(PROTOCOL_DIR)
VPATH += $(TMK_PATH)/$(NRF52_DIR)/lufa_utils

# OPT_DEFS +=

ifeq ($(strip $(MIDI_ENABLE)), yes)
  include $(TMK_PATH)/protocol/midi.mk
endif
