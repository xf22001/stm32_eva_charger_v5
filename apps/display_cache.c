

/*================================================================
 *
 *
 *   文件名称：display_cache.c
 *   创 建 者：肖飞
 *   创建日期：2021年07月17日 星期六 09时42分40秒
 *   修改日期：2022年01月20日 星期四 17时42分31秒
 *   描    述：
 *
 *================================================================*/
#include "display_cache.h"
#include "app.h"
#include "channels.h"
#include "channel.h"
#include "net_client.h"

#include "log.h"

static void load_device_id(uint16_t *id, uint16_t *cache, uint16_t size)
{
	u_uint16_bytes_t *u_uint16_bytes_id = (u_uint16_bytes_t *)id;
	u_uint16_bytes_t *u_uint16_bytes_cache = (u_uint16_bytes_t *)cache;
	int i;

	for(i = 0; i < size; i++) {
		uint8_t byte0 = u_uint16_bytes_id->s.byte0;
		uint8_t byte1 = u_uint16_bytes_id->s.byte1;

		if(byte0 == 0) {
			byte0 = 0xff;
		}

		if(byte1 == 0) {
			byte1 = 0xff;
		}

		u_uint16_bytes_cache->s.byte0 = byte1;
		u_uint16_bytes_cache->s.byte1 = byte0;
		u_uint16_bytes_id++;
		u_uint16_bytes_cache++;
	}
}

static void set_device_id(uint16_t *id, uint16_t *cache, uint16_t size)
{
	u_uint16_bytes_t *u_uint16_bytes_id = (u_uint16_bytes_t *)id;
	u_uint16_bytes_t *u_uint16_bytes_cache = (u_uint16_bytes_t *)cache;
	int i;

	for(i = 0; i < size; i++) {
		uint8_t byte0 = u_uint16_bytes_cache->s.byte0;
		uint8_t byte1 = u_uint16_bytes_cache->s.byte1;

		if(byte0 == 0xff) {
			byte0 = 0;
		}

		if(byte1 == 0xff) {
			byte1 = 0;
		}

		u_uint16_bytes_id->s.byte0 = byte1;
		u_uint16_bytes_id->s.byte1 = byte0;
		u_uint16_bytes_id++;
		u_uint16_bytes_cache++;
	}
}

void load_app_display_cache(app_info_t *app_info)
{
	switch(app_info->mechine_info.request_type) {
		case REQUEST_TYPE_NONE: {
			app_info->display_cache_app.request_type = 0;
		}
		break;

		case REQUEST_TYPE_SSE: {
			app_info->display_cache_app.request_type = 1;
		}
		break;

		case REQUEST_TYPE_OCPP_1_6: {
			app_info->display_cache_app.request_type = 2;
		}
		break;

		default: {
			app_info->display_cache_app.request_type = 0;
		}
		break;
	}

	{
		int d0;
		int d1;
		int d2;
		int d3;
		int port;
		int ret = sscanf(app_info->mechine_info.uri, "tcp://%d.%d.%d.%d:%d",
		                 &d0,
		                 &d1,
		                 &d2,
		                 &d3,
		                 &port);

		if(ret == 5) {
			app_info->display_cache_app.ip[0] = d0;
			app_info->display_cache_app.ip[1] = d1;
			app_info->display_cache_app.ip[2] = d2;
			app_info->display_cache_app.ip[3] = d3;
			app_info->display_cache_app.ip[4] = port;
		}
	}

	load_device_id((uint16_t *)app_info->mechine_info.device_id, (uint16_t *)app_info->display_cache_app.device_id, 16);
}

void sync_app_display_cache(app_info_t *app_info)
{
	if(app_info->display_cache_app.request_type_sync != 0) {
		net_client_info_t *net_client_info = get_net_client_info();
		app_info->display_cache_app.request_type_sync = 0;
		debug("app_info->display_cache_app.request_type:%d", app_info->display_cache_app.request_type);

		switch(app_info->display_cache_app.request_type) {
			case 0: {
				app_info->mechine_info.request_type = REQUEST_TYPE_NONE;
			}
			break;

			case 1: {
				app_info->mechine_info.request_type = REQUEST_TYPE_SSE;
			}
			break;

			case 2: {
				app_info->mechine_info.request_type = REQUEST_TYPE_OCPP_1_6;
			}
			break;

			default: {
				app_info->mechine_info.request_type = REQUEST_TYPE_NONE;
			}
			break;
		}

		app_info->mechine_info_invalid = 1;

		if(net_client_info != NULL) {
			set_client_state(net_client_info, CLIENT_REINIT);
		}
	}

	if(app_info->display_cache_app.ip_sync != 0) {
		app_info->display_cache_app.ip_sync = 0;

		snprintf(app_info->mechine_info.uri, 256, "tcp://%d.%d.%d.%d:%d",
		         app_info->display_cache_app.ip[0],
		         app_info->display_cache_app.ip[1],
		         app_info->display_cache_app.ip[2],
		         app_info->display_cache_app.ip[3],
		         app_info->display_cache_app.ip[4]);
		app_info->mechine_info_invalid = 1;
	}

	if(app_info->display_cache_app.device_id_sync != 0) {
		app_info->display_cache_app.device_id_sync = 0;
		set_device_id((uint16_t *)app_info->mechine_info.device_id, (uint16_t *)app_info->display_cache_app.device_id, 16);

		app_info->mechine_info_invalid = 1;
	}
}

static int update_price_item_cache(uint8_t i, uint8_t start_seg, uint8_t stop_seg, uint32_t price, void *_price_item_cache)
{
	int ret = -1;
	//price_item_cache_t *price_item_cache = (price_item_cache_t *)_price_item_cache;
	//time_t start;
	//time_t stop;
	//struct tm *tm;

	//if(i >= 12) {
	//	debug("");
	//	return ret;
	//}

	//start = get_ts_by_seg_index(start_seg);
	//stop = get_ts_by_seg_index(stop_seg);

	//debug("[%d] start:%d, stop:%d, price:%d", i, start_seg, stop_seg, price);

	//sse_query_price_item_info += i;

	//tm = localtime(&start);
	//sse_query_price_item_info->start_hour_min = get_u16_from_u8_lh(
	//            get_bcd_from_u8(tm->tm_min),
	//            get_bcd_from_u8(tm->tm_hour));
	//tm = localtime(&stop);
	//sse_query_price_item_info->stop_hour_min = get_u16_from_u8_lh(
	//            get_bcd_from_u8(tm->tm_min),
	//            get_bcd_from_u8((stop == 0) ? 24 : tm->tm_hour));

	//sse_query_price_item_info->price = price;

	//ret = 0;
	return ret;
}

void load_channels_display_cache(channels_info_t *channels_info)
{
	channels_settings_t *channels_settings = &channels_info->channels_settings;
	parse_price_info(&channels_settings->price_info_energy, update_price_item_cache, &channels_info->display_cache_channels.price_item_cache[0]);
}

static void price_seg_to_price_info(channels_settings_t *channels_settings, price_item_cache_t *price_item_cache, uint8_t max_price_seg)
{
	int i;
	int j;
	time_t start = 0;
	time_t stop = 0;

	price_info_t *price_info_energy = &channels_settings->price_info_energy;
	price_info_t *price_info_service = &channels_settings->price_info_service;

	for(i = 0; i < max_price_seg; i++) {
		price_item_cache_t *item = price_item_cache + i;

		stop = get_u8_from_bcd(get_u8_l_from_u16(item->hour)) * 3600 + get_u8_from_bcd(get_u8_l_from_u16(item->min)) * 60;
		start = get_seg_index_by_ts(start);
		stop = get_seg_index_by_ts(stop);

		if(start > stop) {
			stop += PRICE_SEGMENT_SIZE;
		}

		if(stop == 0) {
			stop = PRICE_SEGMENT_SIZE;
		}

		debug("start:%d, stop:%d", (uint32_t)start, (uint32_t)stop);

		for(j = start; j < stop ; j++) {
			int k = j % PRICE_SEGMENT_SIZE;
			uint32_t price_energy = get_u32_from_u16_01(item->price_l, item->price_h);
			uint32_t price_service = get_u32_from_u16_01(item->service_price_l, item->service_price_h);
			debug("energy price[%d]:%d", k, price_energy / 100);
			debug("service price[%d]:%d", k, price_service / 100);
			price_info_energy->price[k] = price_energy / 100;
			price_info_service->price[k] = price_service / 100;
		}

		start = stop;
	}
}

void sync_channels_display_cache(channels_info_t *channels_info)
{
	channels_settings_t *channels_settings = &channels_info->channels_settings;

	if(channels_info->display_cache_channels.price_sync != 0) {
		channels_info->display_cache_channels.price_sync = 0;
		price_seg_to_price_info(channels_settings, &channels_info->display_cache_channels.price_item_cache[0], 20);

		channels_info->channels_settings_invalid = 1;
	}
}

void load_channel_display_cache(channel_info_t *channel_info)
{
}

void sync_channel_display_cache(channel_info_t *channel_info)
{
}

int get_channel_record_page_load_item_number(void)
{
	return RECORD_ITEM_CACHE_NUMBER;
}

void channel_record_item_page_item_refresh(channel_record_item_t *channel_record_item, uint16_t offset, uint16_t id)
{
	channels_info_t *channels_info = get_channels();
	record_item_cache_t *record_item_cache = &channels_info->display_cache_channels.record_item_cache[offset];
	uint8_t hour;
	uint8_t min;
	struct tm *tm;
	time_t ts;

	debug("offset:%d, id:%d", offset, id);

	if(offset >= RECORD_ITEM_CACHE_NUMBER) {
		return;
	}

	memset(record_item_cache, 0, sizeof(record_item_cache_t));

	if(channel_record_item == NULL) {
		return;
	}

	record_item_cache->channel_id = channel_record_item->channel_id + 1;
	memcpy(record_item_cache->account, channel_record_item->account, 32);
	ts = channel_record_item->start_time;
	tm = localtime(&ts);
	hour = get_bcd_from_u8(tm->tm_hour);
	min = get_bcd_from_u8(tm->tm_min);
	record_item_cache->start_hour_min = get_u16_from_u8_lh(min, hour);
	ts = channel_record_item->start_time;
	tm = localtime(&ts);
	hour = get_bcd_from_u8(tm->tm_hour);
	min = get_bcd_from_u8(tm->tm_min);
	record_item_cache->stop_hour_min = get_u16_from_u8_lh(min, hour);
	record_item_cache->energy_h = get_u16_1_from_u32(channel_record_item->energy);
	record_item_cache->energy_l = get_u16_0_from_u32(channel_record_item->energy);
	record_item_cache->amount_h = get_u16_1_from_u32(channel_record_item->amount);
	record_item_cache->amount_l = get_u16_0_from_u32(channel_record_item->amount);
	//record_item_cache->start_reason = get_u16_0_from_u32(channel_record_item->start_reason);
	record_item_cache->stop_reason = get_u16_0_from_u32(channel_record_item->stop_reason);
}

