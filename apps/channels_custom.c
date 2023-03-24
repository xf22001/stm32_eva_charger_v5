

/*================================================================
 *
 *
 *   文件名称：channels_custom.c
 *   创 建 者：肖飞
 *   创建日期：2023年03月21日 星期二 11时10分17秒
 *   修改日期：2023年03月24日 星期五 09时37分35秒
 *   描    述：
 *
 *================================================================*/
#include "channels.h"
#include "fan_control.h"

#define LOG_DISABLE
#include "log.h"

static void handle_channel_led_state(channel_info_t *channel_info, GPIO_PinState blink_state)
{
	channel_config_t *channel_config = channel_info->channel_config;

	GPIO_PinState red_state = GPIO_PIN_SET;
	GPIO_PinState green_state = GPIO_PIN_SET;
	GPIO_PinState yellow_state = GPIO_PIN_SET;

	switch(channel_info->state) {
		case CHANNEL_STATE_IDLE: {
			green_state = GPIO_PIN_RESET;

			if(channel_info->charger_connect_state == 1) {
				green_state = blink_state;
			}
		}
		break;

		case CHANNEL_STATE_START:
		case CHANNEL_STATE_WAITING:
		case CHANNEL_STATE_STARTING:
		case CHANNEL_STATE_CHARGING: {
			red_state = blink_state;
		}
		break;

		case CHANNEL_STATE_STOP:
		case CHANNEL_STATE_STOPPING:
		case CHANNEL_STATE_END:
		case CHANNEL_STATE_CLEANUP: {
			if(channel_info->channel_record_item.stop_reason == channel_record_item_stop_reason(SOC)) {
				red_state = GPIO_PIN_RESET;
			}
		}
		break;

		default: {
		}
		break;
	}

	if(channel_info->channel_faults != 0) {
		yellow_state = blink_state;
	}

	if(channel_config->fault_port != NULL) {
		debug("channel %d red_state:%d", channel_info->channel_id, red_state);
		HAL_GPIO_WritePin(channel_config->fault_port, channel_config->fault_pin, red_state);
	}

	if(channel_config->led_charge_port != NULL) {
		debug("channel %d green_state:%d", channel_info->channel_id, green_state);
		HAL_GPIO_WritePin(channel_config->led_charge_port, channel_config->led_charge_pin, green_state);
	}

	if(channel_config->led_full_port != NULL) {
		debug("channel %d yellow_state:%d", channel_info->channel_id, yellow_state);
		HAL_GPIO_WritePin(channel_config->led_full_port, channel_config->led_full_pin, yellow_state);
	}
}

void handle_channels_led_state(channels_info_t *channels_info)
{
	int i;
	static GPIO_PinState blink_state = GPIO_PIN_SET;
	static uint32_t ticks = 0;

	if(ticks_duration(ticks, osKernelSysTick()) < 1000) {
		return;
	}

	ticks = osKernelSysTick();

	if(blink_state == GPIO_PIN_SET) {
		blink_state = GPIO_PIN_RESET;
	} else {
		blink_state = GPIO_PIN_SET;
	}

	for(i = 0; i < channels_info->channel_number; i++) {
		channel_info_t *channel_info = channels_info->channel_info + i;
		handle_channel_led_state(channel_info, blink_state);
	}
}

void handle_channels_fan_state(channels_info_t *channels_info)
{
	int i;
	static uint32_t ticks = 0;
	uint8_t channels_idle = 1;
	static uint32_t fan_alive_stamp = 0;

	if(ticks_duration(ticks, osKernelSysTick()) < 1000) {
		return;
	}

	ticks = osKernelSysTick();

	for(i = 0; i < channels_info->channel_number; i++) {
		channel_info_t *channel_info = channels_info->channel_info + i;

		switch(channel_info->state) {
			case CHANNEL_STATE_IDLE:
			case CHANNEL_STATE_START:
			case CHANNEL_STATE_WAITING: {
			}
			break;

			default: {
				channels_idle = 0;
			}
			break;
		}

		if(channels_idle == 0) {
			break;
		}
	}

	if(channels_idle == 0) {
		fan_alive_stamp = osKernelSysTick();
	}

	if(ticks_duration(ticks, fan_alive_stamp) < 60 * 1000) {
		fan_control_set_strength((fan_control_info_t *)channels_info->fan_control_info, 9);
	} else {
		fan_control_set_strength((fan_control_info_t *)channels_info->fan_control_info, 0);
	}
}

void handle_channels_common_periodic_custom(channels_info_t *channels_info)
{
	handle_channels_led_state(channels_info);
	handle_channels_fan_state(channels_info);
}

