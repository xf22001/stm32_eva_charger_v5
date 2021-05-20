#
#
#================================================================
#   
#   
#   文件名称：user.mk
#   创 建 者：肖飞
#   创建日期：2019年10月25日 星期五 13时04分38秒
#   修改日期：2021年05月19日 星期三 16时03分11秒
#   描    述：
#
#================================================================

include sal/sal.mk

USER_C_INCLUDES += -Iapps
USER_C_INCLUDES += -Iapps/modules
USER_C_INCLUDES += -Iapps/modules/os
USER_C_INCLUDES += -Iapps/modules/drivers
USER_C_INCLUDES += -Iapps/modules/hardware
USER_C_INCLUDES += -Iapps/modules/app
USER_C_INCLUDES += -Iapps/modules/app/vfs_disk
USER_C_INCLUDES += -Iapps/modules/tests

USER_C_INCLUDES += -IMiddlewares/Third_Party/LwIP/src/include
USER_C_INCLUDES += -IMiddlewares/Third_Party/LwIP/system
USER_C_INCLUDES += -IMiddlewares/Third_Party/LwIP/src/include/netif/ppp
USER_C_INCLUDES += -IMiddlewares/Third_Party/LwIP/src/include/lwip
USER_C_INCLUDES += -IMiddlewares/Third_Party/LwIP/src/include/lwip/apps
USER_C_INCLUDES += -IMiddlewares/Third_Party/LwIP/src/include/lwip/priv
USER_C_INCLUDES += -IMiddlewares/Third_Party/LwIP/src/include/lwip/prot
USER_C_INCLUDES += -IMiddlewares/Third_Party/LwIP/src/include/netif
USER_C_INCLUDES += -IMiddlewares/Third_Party/LwIP/src/include/compat/posix
USER_C_INCLUDES += -IMiddlewares/Third_Party/LwIP/src/include/compat/posix/arpa
USER_C_INCLUDES += -IMiddlewares/Third_Party/LwIP/src/include/compat/posix/net
USER_C_INCLUDES += -IMiddlewares/Third_Party/LwIP/src/include/compat/posix/sys
USER_C_INCLUDES += -IMiddlewares/Third_Party/LwIP/src/include/compat/stdc
USER_C_INCLUDES += -IMiddlewares/Third_Party/LwIP/system/arch

USER_C_INCLUDES += -IMiddlewares/Third_Party/mbedTLS/include/mbedtls
USER_C_INCLUDES += -IMiddlewares/Third_Party/mbedTLS/include

C_INCLUDES += $(USER_C_INCLUDES)

USER_C_SOURCES += apps/os_memory.c
USER_C_SOURCES += apps/early_sys_callback.c
USER_C_SOURCES += apps/usbh_user_callback.c
USER_C_SOURCES += apps/app.c
USER_C_SOURCES += apps/uart_debug_handler.c
USER_C_SOURCES += apps/channels_config.c
USER_C_SOURCES += apps/can_config.c
USER_C_SOURCES += apps/channels.c
USER_C_SOURCES += apps/channel.c
USER_C_SOURCES += apps/channel_handler_dc.c
USER_C_SOURCES += apps/channel_handler_ac.c
USER_C_SOURCES += apps/charger.c
USER_C_SOURCES += apps/charger_handler_bms_native.c
USER_C_SOURCES += apps/charger_bms.c
USER_C_SOURCES += apps/charger_bms_gb.c
USER_C_SOURCES += apps/channels_power_module.c
USER_C_SOURCES += apps/channels_power_module_native.c
USER_C_SOURCES += apps/energy_meter.c
USER_C_SOURCES += apps/energy_meter_handler_dc_native.c
USER_C_SOURCES += apps/wiznet_spi.c

USER_C_SOURCES += apps/modules/app/eeprom_config.c
USER_C_SOURCES += apps/modules/app/poll_loop.c
USER_C_SOURCES += apps/modules/app/uart_debug.c
USER_C_SOURCES += apps/modules/app/file_log.c
USER_C_SOURCES += apps/modules/app/request.c
USER_C_SOURCES += apps/modules/app/net_client.c
USER_C_SOURCES += apps/modules/app/net_protocol_udp.c
USER_C_SOURCES += apps/modules/app/net_protocol_tcp.c
USER_C_SOURCES += apps/modules/app/net_protocol_ws.c
USER_C_SOURCES += apps/modules/app/request_default.c
USER_C_SOURCES += apps/modules/app/https.c
USER_C_SOURCES += apps/modules/app/request_ws.c
USER_C_SOURCES += apps/modules/app/ftp_client.c
USER_C_SOURCES += apps/modules/app/vfs_disk/vfs.c
USER_C_SOURCES += apps/modules/app/mt_file.c
USER_C_SOURCES += apps/modules/app/can_data_task.c
USER_C_SOURCES += apps/modules/app/uart_data_task.c
USER_C_SOURCES += apps/modules/app/duty_cycle_pattern.c
USER_C_SOURCES += apps/modules/app/usbh_user_callback.c
USER_C_SOURCES += apps/modules/app/early_sys_callback.c
USER_C_SOURCES += apps/modules/app/connect_state.c
USER_C_SOURCES += apps/modules/app/power_modules.c
USER_C_SOURCES += apps/modules/app/power_modules_handler_huawei.c
USER_C_SOURCES += apps/modules/app/power_modules_handler_increase.c
USER_C_SOURCES += apps/modules/app/power_modules_handler_infy.c
USER_C_SOURCES += apps/modules/app/power_modules_handler_pseudo.c
USER_C_SOURCES += apps/modules/app/power_modules_handler_stategrid.c
USER_C_SOURCES += apps/modules/app/power_modules_handler_yyln.c
USER_C_SOURCES += apps/modules/app/power_modules_handler_winline.c
USER_C_SOURCES += apps/modules/app/power_modules_handler_zte.c
USER_C_SOURCES += apps/modules/app/can_command.c
USER_C_SOURCES += apps/modules/app/usb_upgrade.c
USER_C_SOURCES += apps/modules/app/voice.c
USER_C_SOURCES += apps/modules/app/ntc_temperature.c
USER_C_SOURCES += apps/modules/hardware/flash.c
USER_C_SOURCES += apps/modules/hardware/eeprom.c
USER_C_SOURCES += apps/modules/hardware/dlt_645_master_txrx.c
#USER_C_SOURCES += apps/modules/hardware/hw_rtc.c
USER_C_SOURCES += apps/modules/hardware/hw_adc.c
USER_C_SOURCES += apps/modules/drivers/spi_txrx.c
USER_C_SOURCES += apps/modules/drivers/can_txrx.c
USER_C_SOURCES += apps/modules/drivers/usart_txrx.c
USER_C_SOURCES += apps/modules/os/event_helper.c
USER_C_SOURCES += apps/modules/os/callback_chain.c
USER_C_SOURCES += apps/modules/os/bitmap_ops.c
USER_C_SOURCES += apps/modules/os/iap.c
USER_C_SOURCES += apps/modules/os/os_utils.c
USER_C_SOURCES += apps/modules/os/net_utils.c
USER_C_SOURCES += apps/modules/os/cpu_utils.c
USER_C_SOURCES += apps/modules/os/log.c
USER_C_SOURCES += apps/modules/os/object_class.c
USER_C_SOURCES += apps/modules/os/soft_timer.c
USER_C_SOURCES += apps/modules/tests/test_serial.c
USER_C_SOURCES += apps/modules/tests/test_event.c

USER_C_SOURCES += Middlewares/Third_Party/LwIP/src/core/def.c
USER_C_SOURCES += Middlewares/Third_Party/LwIP/src/core/ipv4/ip4_addr.c

USER_C_SOURCES += Src/mbedtls.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/aes.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/aesni.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/arc4.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/aria.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/asn1parse.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/asn1write.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/base64.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/bignum.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/blowfish.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/camellia.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/ccm.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/certs.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/chacha20.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/chachapoly.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/cipher.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/cipher_wrap.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/cmac.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/ctr_drbg.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/debug.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/des.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/dhm.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/ecdh.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/ecdsa.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/ecjpake.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/ecp.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/ecp_curves.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/entropy.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/entropy_poll.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/error.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/gcm.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/havege.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/hkdf.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/hmac_drbg.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/md.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/md2.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/md4.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/md5.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/md_wrap.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/memory_buffer_alloc.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/nist_kw.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/oid.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/padlock.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/pem.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/pk.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/pkcs11.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/pkcs12.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/pkcs5.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/pkparse.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/pkwrite.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/pk_wrap.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/platform.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/platform_util.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/poly1305.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/ripemd160.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/rsa.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/rsa_internal.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/sha1.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/sha256.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/sha512.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/ssl_cache.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/ssl_ciphersuites.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/ssl_cli.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/ssl_cookie.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/ssl_srv.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/ssl_ticket.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/ssl_tls.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/threading.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/timing.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/version.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/version_features.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/x509.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/x509write_crt.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/x509write_csr.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/x509_create.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/x509_crl.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/x509_crt.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/x509_csr.c
USER_C_SOURCES += Middlewares/Third_Party/mbedTLS/library/xtea.c

USER_CFLAGS += -DtraceTASK_SWITCHED_IN=StartIdleMonitor -DtraceTASK_SWITCHED_OUT=EndIdleMonitor
USER_CFLAGS += -DSAL_HOOK -DMBEDTLS_CONFIG_FILE=\"mbedtls_config.h\"

C_SOURCES += $(USER_C_SOURCES)

CFLAGS += $(USER_CFLAGS)
LDFLAGS += -u _printf_float

IAP_FILE := apps/modules/os/iap.h

define update-iap-include
	if [ -f $(IAP_FILE) ]; then
		touch $(IAP_FILE);
	fi
endef

ifeq ("$(origin APP)", "command line")
build-type := .app.stamps
build-type-invalid := .bootloader.stamps
CFLAGS += -DUSER_APP
LDSCRIPT = STM32F407IGTx_FLASH_APP.ld
#$(info $(shell $(update-iap-include)))
$(info "build app!")
else
build-type := .bootloader.stamps
build-type-invalid := .app.stamps
LDSCRIPT = STM32F407IGTx_FLASH.ld
#$(info $(shell $(update-iap-include)))
$(info "build bootloader!")
endif

default: all

all : $(build-type)

$(build-type) :
	-rm $(build-type-invalid)
	$(shell $(update-iap-include))
	touch $@

cscope: all
	rm cscope e_cs -rf
	mkdir -p cscope
	#$(silent)tags.sh prepare;
	$(silent)touch dep_files;
	$(silent)for f in $$(find . -type f -name "*.d" 2>/dev/null); do \
		for i in $$(cat "$$f" | sed 's/^.*://g' | sed 's/[\\ ]/\n/g' | sort -h | uniq); do \
			if test "$${i:0:1}" = "/";then \
				echo "$$i" >> dep_files; \
			else \
				readlink -f "$$i" >> dep_files; \
			fi; \
		done; \
	done;
	$(silent)cat dep_files | sort | uniq | sed 's/^\(.*\)$$/\"\1\"/g' >> cscope/cscope.files;
	$(silent)cat dep_files | sort | uniq >> cscope/ctags.files;
	$(silent)rm dep_files
	$(silent)tags.sh cscope;
	$(silent)tags.sh tags;
	$(silent)tags.sh env;

clean: clean-cscope
clean-cscope:
	rm cscope e_cs -rf
