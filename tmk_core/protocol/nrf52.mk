PROTOCOL_DIR = protocol
NRF52_DIR = $(PROTOCOL_DIR)/nrf52

SRC += $(NRF52_DIR)/nrf52.c \
       $(NRF52_DIR)/nrf52_keyboard_port.c \
	   $(NRF52_DIR)/keyboard_hosts/nrf52_usbd.c \
	   $(NRF52_DIR)/keyboard_hosts/nrf52_2g4.c \
	   $(NRF52_DIR)/keyboard_hosts/nrf52_ble.c

VPATH += $(TMK_PATH)/$(PROTOCOL_DIR)
VPATH += $(TMK_PATH)/$(NRF52_DIR)/lufa_utils
VPATH += $(TMK_PATH)/$(NRF52_DIR)/keyboard_hosts

# OPT_DEFS +=

ifeq ($(strip $(MIDI_ENABLE)), yes)
  include $(TMK_PATH)/protocol/midi.mk
endif
