

/*================================================================
 *
 *
 *   文件名称：app.c
 *   创 建 者：肖飞
 *   创建日期：2019年10月11日 星期五 16时54分03秒
 *   修改日期：2022年07月08日 星期五 08时38分57秒
 *   描    述：
 *
 *================================================================*/
#include "app.h"

#include <string.h>

#include "iwdg.h"

#include "os_utils.h"
#include "config_layout.h"

#include "test_serial.h"
#include "test_event.h"
#include "test_can.h"
#include "file_log.h"
#include "probe_tool.h"
#include "net_client.h"
#include "ftp_client.h"
#include "ntp_client.h"
#include "usb_upgrade.h"
#include "usbh_user_callback.h"

#include "channels.h"
//#include "duty_cycle_pattern.h"
#include "channels_notify_voice.h"
#include "vfs.h"

#include "sal_socket.h"
#include "sal_netdev.h"
#include "sal_netdev.h"
#if defined(SAL_WIZNET)
#include "wiz_ethernet.h"
#elif defined(SAL_DTU)
#include "dtu_ethernet.h"
#endif
#include "display.h"
#include "sal_hook.h"

#include "log.h"

//extern IWDG_HandleTypeDef hiwdg;
extern TIM_HandleTypeDef htim1;
//extern TIM_HandleTypeDef htim2;
extern UART_HandleTypeDef huart4;
extern SPI_HandleTypeDef hspi2;
extern I2C_HandleTypeDef hi2c3;

extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;
extern SPI_HandleTypeDef hspi3;

static app_info_t *app_info = NULL;
static os_signal_t app_event = NULL;

app_info_t *get_app_info(void)
{
	return app_info;
}

int app_load_config(void)
{
	config_layout_t *config_layout = get_config_layout();
	size_t offset = (size_t)&config_layout->mechine_info_seg.storage_mechine_info.mechine_info;
	debug("offset:%d", offset);
	return load_config_item(app_info->storage_info, "eva", &app_info->mechine_info, sizeof(mechine_info_t), offset);
}

int app_save_config(void)
{
	config_layout_t *config_layout = get_config_layout();
	size_t offset = (size_t)&config_layout->mechine_info_seg.storage_mechine_info.mechine_info;
	debug("offset:%d", offset);
	return save_config_item(app_info->storage_info, "eva", &app_info->mechine_info, sizeof(mechine_info_t), offset);
}

static void app_event_init(size_t size)
{
	if(app_event != NULL) {
		return;
	}

	app_event = signal_create(size);
	OS_ASSERT(app_event != NULL);
}

void app_init(void)
{
	app_event_init(10);
	mem_info_init();
	mt_file_init();
}

void send_app_event(app_event_t event, uint32_t timeout)
{
	signal_send(app_event, event, timeout);
}

static void app_mechine_info_invalid(void *fn_ctx, void *chain_ctx)
{
	app_info_t *app_info = (app_info_t *)fn_ctx;
	modbus_data_ctx_t *modbus_data_ctx = (modbus_data_ctx_t *)chain_ctx;

	if(modbus_data_ctx->influence < (void *)&app_info->mechine_info) {
		return;
	}

	if(modbus_data_ctx->influence >= (void *)(&app_info->mechine_info + 1)) {
		return;
	}

	debug("[%p, %p, %p]", &app_info->mechine_info, modbus_data_ctx->influence, &app_info->mechine_info + 1);

	app_info->mechine_info_invalid = 1;
}

__weak void load_app_display_cache(app_info_t *app_info)
{
}

__weak void sync_app_display_cache(app_info_t *app_info)
{
}

static void app_mechine_info_changed(void *fn_ctx, void *chain_ctx)
{
	app_info_t *app_info = (app_info_t *)fn_ctx;

	sync_app_display_cache(app_info);

	if(app_info->mechine_info_invalid != 0) {
		app_info->mechine_info_invalid = 0;
		app_save_config();
	}
}

void update_network_ip_config(app_info_t *app_info)
{
	int exit = 0;

	while(exit == 0) {
		if(set_dhcp_enable(app_info->mechine_info.dhcp_enable) != 0) {
			debug("");
			osDelay(1000);
		} else {
			if(app_info->mechine_info.dhcp_enable == 0) {
				ip_addr_t ip;
				ip_addr_t sn;
				ip_addr_t gw;

				if(ipaddr_aton(app_info->mechine_info.ip, &ip) == 0) {
					debug("ip:%s", app_info->mechine_info.ip);
				}

				if(ipaddr_aton(app_info->mechine_info.sn, &sn) == 0) {
					debug("sn:%s", app_info->mechine_info.sn);
				}

				if(ipaddr_aton(app_info->mechine_info.gw, &gw) == 0) {
					debug("gw:%s", app_info->mechine_info.gw);
				}

				if(set_default_ipaddr(&ip) != 0) {
					debug("");
					osDelay(1000);
					continue;
				}

				if(set_default_netmask(&sn) != 0) {
					debug("");
					osDelay(1000);
					continue;
				}

				if(set_default_gw(&gw) != 0) {
					debug("");
					osDelay(1000);
					continue;
				}

				if(set_default_dns_server(&gw) != 0) {
					debug("");
					osDelay(1000);
					continue;
				}
			}

			exit = 1;
		}
	}
}

static void sync_storage_w25q256(storage_info_t *storage_info)
{
	static uint32_t stamps = 0;
	uint32_t ticks = osKernelSysTick();

	if(ticks_duration(ticks, stamps) >= 1000) {
		stamps = ticks;
		storage_sync(storage_info);
	}
}

static uint8_t reset_config = 0;

void app_set_reset_config(void)
{
	OS_ASSERT(app_info != NULL);
	app_info->mechine_info.reset_config = 1;
}

uint8_t app_get_reset_config(void)
{
	return reset_config;
}

#define CACHE_STORAGE_SECTOR_SIZE 4096
#define CACHE_STORAGE_MAGIC 0x73

#pragma pack(push, 1)
typedef struct {
	uint8_t cache[CACHE_STORAGE_SECTOR_SIZE];
	uint8_t magic;//CACHE_STORAGE_MAGIC
	uint32_t addr;
	uint8_t valid;
} cache_storage_layout_t;
#pragma pack(pop)

static void cache_storage_callback(void *fn_ctx, void *chain_ctx)
{
	storage_info_t *storage_info = (storage_info_t *)fn_ctx;
	cache_event_ctx_t *cache_event_ctx = (cache_event_ctx_t *)chain_ctx;
	cache_storage_layout_t *cache_storage_layout = (cache_storage_layout_t *)0;
	uint32_t addr = cache_event_ctx->addr;
	size_t start = cache_event_ctx->start;
	size_t size = cache_event_ctx->size;
	uint8_t *cache = cache_event_ctx->cache;
	size_t offset;

	switch(cache_event_ctx->cache_event_action) {
		case CACHE_EVENT_ACTION_INVALID: {
			uint8_t valid = 0;

			mutex_lock(storage_info->action_mutex);

			offset = (size_t)&cache_storage_layout->valid;

			while(storage_write(storage_info, offset, (uint8_t *)&valid, sizeof(valid)) != 0) {
				debug("");
			}

			debug("CACHE_EVENT_ACTION_INVALID");

			mutex_unlock(storage_info->action_mutex);
		}
		break;

		case CACHE_EVENT_ACTION_UPDATE: {
			uint8_t valid = 1;

			mutex_lock(storage_info->action_mutex);

			offset = (size_t)&cache_storage_layout->cache[0];

			while(storage_write(storage_info, offset + start, cache + start, size) != 0) {
				debug("");
			}

			offset = (size_t)&cache_storage_layout->addr;

			while(storage_write(storage_info, offset, (uint8_t *)&addr, sizeof(addr)) != 0) {
				debug("");
			}

			offset = (size_t)&cache_storage_layout->valid;

			while(storage_write(storage_info, offset, (uint8_t *)&valid, sizeof(valid)) != 0) {
				debug("");
			}

			debug("CACHE_EVENT_ACTION_UPDATE addr:0x%x, start:%d, size:%d", addr, start, size);

			mutex_unlock(storage_info->action_mutex);
		}
		break;

		case CACHE_EVENT_ACTION_RESTORE: {
			uint8_t magic;
			uint8_t valid;

			cache_event_ctx->cache_event_action = CACHE_EVENT_ACTION_NONE;

			mutex_lock(storage_info->action_mutex);

			offset = (size_t)&cache_storage_layout->magic;

			while(storage_read(storage_info, offset, (uint8_t *)&magic, sizeof(magic)) != 0) {
				debug("");
			}

			debug("magic %x", magic);

			if(magic == CACHE_STORAGE_MAGIC) {
				offset = (size_t)&cache_storage_layout->valid;

				while(storage_read(storage_info, offset, (uint8_t *)&valid, sizeof(valid)) != 0) {
					debug("");
				}

				debug("valid %d", valid);

				if(valid == 1) {
					offset = (size_t)&cache_storage_layout->addr;

					while(storage_read(storage_info, offset, (uint8_t *)&addr, sizeof(addr)) != 0) {
						debug("");
					}

					cache_event_ctx->addr = addr;
					offset = (size_t)&cache_storage_layout->cache[0];

					while(storage_read(storage_info, offset, cache, CACHE_STORAGE_SECTOR_SIZE) != 0) {
						debug("");
					}

					cache_event_ctx->cache_event_action = CACHE_EVENT_ACTION_UPDATE;
					debug("CACHE_EVENT_ACTION_RESTORE addr:%x", addr);
				}
			} else {
				magic = CACHE_STORAGE_MAGIC;
				offset = (size_t)&cache_storage_layout->magic;

				while(storage_write(storage_info, offset, (uint8_t *)&magic, sizeof(magic)) != 0) {
					debug("");
				}

				valid = 0;
				offset = (size_t)&cache_storage_layout->valid;

				while(storage_write(storage_info, offset, (uint8_t *)&valid, sizeof(valid)) != 0) {
					debug("");
				}
			}

			mutex_unlock(storage_info->action_mutex);
		}
		break;

		default: {
		}
		break;
	}
}

void app(void const *argument)
{
	poll_loop_t *poll_loop;
	channels_info_t *channels_info = NULL;
	display_info_t *display_info = NULL;
	int ret;
	storage_info_t *cache_storage_info;

	app_info = (app_info_t *)os_calloc(1, sizeof(app_info_t));

	OS_ASSERT(app_info != NULL);

	cache_storage_info = get_or_alloc_storage_info(&hi2c3);
	OS_ASSERT(cache_storage_info != NULL);

	app_info->storage_info = get_or_alloc_storage_info(&hspi2);
	OS_ASSERT(app_info->storage_info != NULL);

	storage_set_cache(app_info->storage_info, cache_storage_info, cache_storage_callback);

	ret = app_load_config();

	if(ret == 0) {
		//app_info->mechine_info.reset_config = 1;
		debug("app load config successful!");
		reset_config = app_info->mechine_info.reset_config;

		if(app_get_reset_config() != 0) {
			debug("try to reset config!");
			ret = -1;
		}
	} else {
		debug("app load config failed!");
	}

	if(ret == 0) {
		debug("device id:\'%s\', server uri:\'%s\'!", app_info->mechine_info.device_id, app_info->mechine_info.uri);
	} else {
		snprintf(app_info->mechine_info.device_id, sizeof(app_info->mechine_info.device_id), "%s", "0000000000");
		snprintf(app_info->mechine_info.uri, sizeof(app_info->mechine_info.uri), "%s", "tcp://112.74.40.227:12345");
		debug("device id:\'%s\', server uri:\'%s\'!", app_info->mechine_info.device_id, app_info->mechine_info.uri);
		snprintf(app_info->mechine_info.ip, sizeof(app_info->mechine_info.ip), "%d.%d.%d.%d", 10, 42, 0, 122);
		snprintf(app_info->mechine_info.sn, sizeof(app_info->mechine_info.sn), "%d.%d.%d.%d", 255, 255, 255, 0);
		snprintf(app_info->mechine_info.gw, sizeof(app_info->mechine_info.gw), "%d.%d.%d.%d", 10, 42, 0, 1);
		app_info->mechine_info.dhcp_enable = 0;
		app_info->mechine_info.request_type = REQUEST_TYPE_SSE;
		app_info->mechine_info.reset_config = 0;
		app_info->mechine_info.tz = 8;
		app_save_config();
	}

	load_app_display_cache(app_info);

	sal_init();
#if defined(SAL_WIZNET)
	wiz_init();
#elif defined(SAL_DTU)
	dtu_init();
#endif

	update_network_ip_config(app_info);

	poll_loop = get_or_alloc_poll_loop(0);
	OS_ASSERT(poll_loop != NULL);

	probe_broadcast_add_poll_loop(poll_loop);
	probe_server_add_poll_loop(poll_loop);

	while(is_log_server_valid() == 0) {
		osDelay(1);
	}

	add_log_handler((log_fn_t)log_udp_data);
	//add_log_handler((log_fn_t)log_file_data);

	debug("===========================================start app============================================");

	//ftpd_init();

	//test_event();
	//test_can(&hcan2, &hspi3);

	channels_info = start_channels();
	OS_ASSERT(channels_info != NULL);

	//net_client_add_poll_loop(poll_loop);
	//ftp_client_add_poll_loop(poll_loop);
	ntp_client_add_poll_loop(poll_loop);

	display_info = (display_info_t *)channels_info->display_info;
	OS_ASSERT(display_info != NULL);

	if(display_info->modbus_slave_info != NULL) {
		app_info->display_data_invalid_callback_item.fn = app_mechine_info_invalid;
		app_info->display_data_invalid_callback_item.fn_ctx = app_info;
		OS_ASSERT(register_callback(display_info->modbus_slave_info->data_invalid_chain, &app_info->display_data_invalid_callback_item) == 0);

		app_info->display_data_changed_callback_item.fn = app_mechine_info_changed;
		app_info->display_data_changed_callback_item.fn_ctx = app_info;
		OS_ASSERT(register_callback(display_info->modbus_slave_info->data_changed_chain, &app_info->display_data_changed_callback_item) == 0);
	}

	if(init_channels_notify_voice(channels_info) != 0) {
		debug("");
	}

	while(1) {
		uint32_t event;
		ret = signal_wait(app_event, &event, 1000);

		if(ret == 0) {
			switch(event) {
				case APP_EVENT_HOST_USER_CLASS_ACTIVE: {
					if(mt_f_mount(get_vfs_fs(), "", 0) == FR_OK) {
						start_usb_upgrade();
					}
				}
				break;

				case APP_EVENT_HOST_USER_CONNECTION: {
				}
				break;

				case APP_EVENT_HOST_USER_DISCONNECTION: {
					try_to_close_log();

					if(mt_f_mount(0, "", 0) != FR_OK) {
					}
				}
				break;

				default: {
					debug("unhandled event %x", event);
				}
				break;
			}
		}

		handle_open_log();
		handle_usb_upgrade();
		//sync_storage_w25q256(app_info->storage_info);
	}
}

//static pattern_state_t work_pattern_state = {
//	.type = PWM_COMPARE_COUNT_UP,
//	.duty_cycle = 0,
//};

static void update_work_led(void)
{
	//计数值小于duty_cycle,输出1;大于duty_cycle输出0
	//uint16_t duty_cycle = get_duty_cycle_pattern(&work_pattern_state, 1000, 0, 20);
	//__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, duty_cycle);
}

static uint32_t work_led_blink_periodic = 1000;

void set_work_led_fault_state(uint8_t state)
{
	if(state == 1) {
		work_led_blink_periodic = 125;
	}
}

static void blink_work_led()
{
	static uint32_t ledcpu_stamp = 0;
	uint32_t ticks = osKernelSysTick();

	if(ticks_duration(ticks, ledcpu_stamp) < work_led_blink_periodic) {
		return;
	}

	ledcpu_stamp = ticks;

	HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_12);
}

void idle(void const *argument)
{
	MX_IWDG_Init();
	//HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);

	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 500);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 500);

	while(1) {
		HAL_IWDG_Refresh(&hiwdg);
		update_work_led();
		blink_work_led();
		osDelay(10);
	}
}

int force_bootloader(void)
{
	int ret = -1;
	u_uint8_bits_t u_uint8_bits;
	u_uint8_bits.v = 0;

	HAL_Init();
	MX_GPIO_Init();

	//u_uint8_bits.s.bit0 = (HAL_GPIO_ReadPin(d1_GPIO_Port, d1_Pin) == GPIO_PIN_SET) ? 1 : 0;
	//u_uint8_bits.s.bit1 = (HAL_GPIO_ReadPin(d2_GPIO_Port, d2_Pin) == GPIO_PIN_SET) ? 1 : 0;
	//u_uint8_bits.s.bit2 = (HAL_GPIO_ReadPin(d3_GPIO_Port, d3_Pin) == GPIO_PIN_SET) ? 1 : 0;

	if(u_uint8_bits.v == 0x07) {
		ret = 0;
	}

	HAL_DeInit();

	return ret;
}
