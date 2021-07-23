

/*================================================================
 *
 *
 *   文件名称：app.h
 *   创 建 者：肖飞
 *   创建日期：2019年10月11日 星期五 16时56分29秒
 *   修改日期：2021年07月22日 星期四 16时55分05秒
 *   描    述：
 *
 *================================================================*/
#ifndef _APP_H
#define _APP_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "app_platform.h"
#include "cmsis_os.h"

#include "eeprom.h"
#include "callback_chain.h"
#include "display_cache.h"
#include "sal_hook.h"

#ifdef __cplusplus
}
#endif
#define VER_MAJOR 0
#define VER_MINOR 0
#define VER_REV 0
#define VER_BUILD 0

#pragma pack(push, 1)

typedef struct {
	char device_id[32];
	//ws://www.baidu.com:80/abc?d=e&f=g
	//tcp://www.baidu.com:80
	//udp://www.baidu.com:80
	char uri[128];
	ip_addr_t ip;
	ip_addr_t sn;
	ip_addr_t gw;
	uint8_t dhcp_enable;

	uint8_t upgrade_enable;
} mechine_info_t;

typedef struct {
	unsigned char available;
	mechine_info_t mechine_info;
	uint8_t mechine_info_invalid;
	display_cache_app_t display_cache_app;
	eeprom_info_t *eeprom_info;
	callback_item_t display_data_invalid_callback_item;
	callback_item_t display_data_changed_callback_item;
} app_info_t;

#pragma pack(pop)

typedef enum {
	APP_EVENT_NONE = 0,
	APP_EVENT_USB,
} app_event_t;

app_info_t *get_app_info(void);
int app_load_config(void);
int app_save_config(void);
void app_init(void);
void send_app_event(app_event_t event);
void load_app_display_cache(app_info_t *app_info);
void sync_app_display_cache(app_info_t *app_info);
void update_network_ip_config(app_info_t *app_info);
void app(void const *argument);
void idle(void const *argument);

#endif //_APP_H
