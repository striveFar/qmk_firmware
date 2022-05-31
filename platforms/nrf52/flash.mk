define EXEC_NRFJPROG
	@echo Flashing: s140_nrf52_7.2.0_softdevice.hex
	nrfjprog -f nrf52 --program $(SDK_ROOT)/components/softdevice/s140/hex/s140_nrf52_7.2.0_softdevice.hex --sectorerase
	nrfjprog -f nrf52 --reset
	@echo Flashing: $(OUTPUT_DIRECTORY)/nrf52840_xxaa.hex
	nrfjprog -f nrf52 --program $(OUTPUT_DIRECTORY)/nrf52840_xxaa.hex --sectorerase
	nrfjprog -f nrf52 --reset
endef

define EXEC_UF2_UTIL_DEPLOY
	if ! $(UF2CONV) --deploy $(BUILD_DIR)/$(TARGET).uf2 2>/dev/null; then \
		printf "$(MSG_BOOTLOADER_NOT_FOUND_QUICK_RETRY)" ;\
		sleep $(BOOTLOADER_RETRY_TIME) ;\
		while ! $(UF2CONV) --deploy $(BUILD_DIR)/$(TARGET).uf2  2>/dev/null; do \
			printf "." ;\
			sleep $(BOOTLOADER_RETRY_TIME) ;\
		done ;\
		printf "\n" ;\
	fi
endef

flash: $(BUILD_DIR)/$(TARGET).bin cpfirmware sizeafter
ifneq ($(strip $(PROGRAM_CMD)),)
	$(UNSYNC_OUTPUT_CMD) && $(PROGRAM_CMD)
else ifeq ($(strip $(BOOTLOADER)),nrfjprog)
	$(UNSYNC_OUTPUT_CMD) && $(call EXEC_NRFJPROG)
else ifeq ($(strip $(BOOTLOADER)),nrf52uf2)
	$(UNSYNC_OUTPUT_CMD) && $(call EXEC_UF2_UTIL_DEPLOY)
	$(PRINT_OK); $(SILENT) || printf "$(MSG_FLASH_BOOTLOADER)"
endif

erase:
	nrfjprog -f nrf52 --eraseall

nrfjprog: $(BUILD_DIR)/$(TARGET).bin cpfirmware sizeafter
	$(call EXEC_NRFJPROG)
