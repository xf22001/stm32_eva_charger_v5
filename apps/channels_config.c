

/*================================================================
 *
 *
 *   文件名称：channels_config.c
 *   创 建 者：肖飞
 *   创建日期：2021年01月18日 星期一 09时26分44秒
 *   修改日期：2023年03月08日 星期三 14时42分00秒
 *   描    述：
 *
 *================================================================*/
#include "channels_config.h"
#include "os_utils.h"
#include "power_modules.h"
#include "hw_adc.h"

#include "log.h"

extern CAN_HandleTypeDef hcan1;//comm
extern CAN_HandleTypeDef hcan2;//charger1
extern SPI_HandleTypeDef hspi3;//charger2
extern UART_HandleTypeDef huart1;//CARD READER
extern UART_HandleTypeDef huart2;//4G
extern UART_HandleTypeDef huart3;//METER2
extern UART_HandleTypeDef huart4;//METER1
extern UART_HandleTypeDef huart5;//EXTEND
extern UART_HandleTypeDef huart6;//DISPLAY
extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc3;

static energy_meter_config_item_t energy_meter_config_item_0_0 = {
	.type = ENERGY_METER_TYPE_DC,
	.huart = &huart4,
	.led_gpio = GPIOE,
	.led_pin = GPIO_PIN_13,
};

static energy_meter_config_item_t *energy_meter_config_item_0_sz[] = {
	&energy_meter_config_item_0_0,
};

function_board_config_item_t function_board_config_item_0_0 = {
	.type = FUNCTION_BOARD_TYPE_V5,
	.charge_voltage_adc = &hadc3,
	.charge_voltage_adc_rank = 2,
	.battery_voltage_adc = &hadc3,
	.battery_voltage_adc_rank = 10,
	.insulation_voltage_adc = &hadc3,
	.insulation_voltage_adc_rank = 3,
	.insulation_k1_gpio = GPIOD,
	.insulation_k1_pin = GPIO_PIN_15,
	.insulation_k3_gpio = GPIOG,
	.insulation_k3_pin = GPIO_PIN_3,
};

function_board_config_item_t *function_board_0_sz[] = {
	&function_board_config_item_0_0,
};

function_board_config_item_t function_board_config_item_1_0 = {
	.type = FUNCTION_BOARD_TYPE_V5,
	.charge_voltage_adc = &hadc3,
	.charge_voltage_adc_rank = 6,
	.battery_voltage_adc = &hadc3,
	.battery_voltage_adc_rank = 7,
	.insulation_voltage_adc = &hadc3,
	.insulation_voltage_adc_rank = 4,
	.insulation_k1_gpio = GPIOG,
	.insulation_k1_pin = GPIO_PIN_6,
	.insulation_k3_gpio = GPIOG,
	.insulation_k3_pin = GPIO_PIN_7,
};

function_board_config_item_t *function_board_1_sz[] = {
	&function_board_config_item_1_0,
};

static channel_config_t channel0_config = {
	.channel_type = CHANNEL_TYPE_NATIVE,
	.charger_config = {
		.charger_type = CHANNEL_CHARGER_BMS_TYPE_GB,
		.output_relay_gpio_p = GPIOD,
		.output_relay_pin_p = GPIO_PIN_11,
		.output_relay_gpio_n = GPIOD,
		.output_relay_pin_n = GPIO_PIN_11,
		.output_relay_gpio_fb_p = GPIOG,
		.output_relay_pin_fb_p = GPIO_PIN_4,
		.output_relay_gpio_fb_n = GPIOG,
		.output_relay_pin_fb_n = GPIO_PIN_4,
		.hcan_bms = &hcan2,
		.relay_charger_lock_p_gpio = GPIOD,
		.relay_charger_lock_p_pin = GPIO_PIN_13,
		.relay_charger_lock_n_gpio = GPIOD,
		.relay_charger_lock_n_pin = GPIO_PIN_14,
		.charger_lock_state_gpio = GPIOG,
		.charger_lock_state_pin = GPIO_PIN_5,
		.charger_auxiliary_power_choose_gpio = GPIOI,
		.charger_auxiliary_power_choose_pin = GPIO_PIN_9,
		.charger_auxiliary_power_onoff_gpio = GPIOD,
		.charger_auxiliary_power_onoff_pin = GPIO_PIN_12,
	},
	.energy_meter_config = {
		.default_type = ENERGY_METER_TYPE_DC,
		.request_addr = 1,
		.energy_accuracy = VALUE_ACCURACY_2,
		.voltage_accuracy = VALUE_ACCURACY_1,
		.curent_accuracy = VALUE_ACCURACY_3,
		.size = ARRAY_SIZE(energy_meter_config_item_0_sz),
		.items = energy_meter_config_item_0_sz,
	},
	.function_board_config = {
		.default_type = FUNCTION_BOARD_TYPE_V5,
		.size = ARRAY_SIZE(function_board_0_sz),
		.items = function_board_0_sz,
	},
	.charger_temperature_p_adc = &hadc3,
	.charger_temperature_p_adc_rank = 5,
	.charger_temperature_n_adc = &hadc3,
	.charger_temperature_n_adc_rank = 9,
	.cp_ad_adc = &hadc1,
	.cp_ad_adc_rank = 0,
	//.fault_port = GPIOI,
	//.fault_pin = GPIO_PIN_8,
	.led_charge_port = GPIOF,
	.led_charge_pin = GPIO_PIN_1,
	.led_full_port = GPIOE,
	.led_full_pin = GPIO_PIN_5,
};

static energy_meter_config_item_t energy_meter_config_item_1_0 = {
	.type = ENERGY_METER_TYPE_DC,
	.huart = &huart3,
	.led_gpio = GPIOE,
	.led_pin = GPIO_PIN_14,
};

static energy_meter_config_item_t *energy_meter_config_item_1_sz[] = {
	&energy_meter_config_item_1_0,
};

static channel_config_t channel1_config = {
	.channel_type = CHANNEL_TYPE_NATIVE,
	.charger_config = {
		.charger_type = CHANNEL_CHARGER_BMS_TYPE_GB,
		.output_relay_gpio_p = GPIOG,
		.output_relay_pin_p = GPIO_PIN_9,
		.output_relay_gpio_n = GPIOG,
		.output_relay_pin_n = GPIO_PIN_9,
		.output_relay_gpio_fb_p = GPIOG,
		.output_relay_pin_fb_p = GPIO_PIN_10,
		.output_relay_gpio_fb_n = GPIOG,
		.output_relay_pin_fb_n = GPIO_PIN_10,
		.hcan_bms = &hspi3,
		.relay_charger_lock_p_gpio = GPIOG,
		.relay_charger_lock_p_pin = GPIO_PIN_12,
		.relay_charger_lock_n_gpio = GPIOG,
		.relay_charger_lock_n_pin = GPIO_PIN_13,
		.charger_lock_state_gpio = GPIOG,
		.charger_lock_state_pin = GPIO_PIN_14,
		.charger_auxiliary_power_choose_gpio = GPIOI,
		.charger_auxiliary_power_choose_pin = GPIO_PIN_10,
		.charger_auxiliary_power_onoff_gpio = GPIOG,
		.charger_auxiliary_power_onoff_pin = GPIO_PIN_11,
	},
	.energy_meter_config = {
		.default_type = ENERGY_METER_TYPE_DC,
		.request_addr = 1,
		.energy_accuracy = VALUE_ACCURACY_2,
		.voltage_accuracy = VALUE_ACCURACY_1,
		.curent_accuracy = VALUE_ACCURACY_3,
		.size = ARRAY_SIZE(energy_meter_config_item_1_sz),
		.items = energy_meter_config_item_1_sz,
	},
	.function_board_config = {
		.default_type = FUNCTION_BOARD_TYPE_V5,
		.size = ARRAY_SIZE(function_board_1_sz),
		.items = function_board_1_sz,
	},
	.charger_temperature_p_adc = &hadc3,
	.charger_temperature_p_adc_rank = 1,
	.charger_temperature_n_adc = &hadc3,
	.charger_temperature_n_adc_rank = 0,
	.cp_ad_adc = &hadc1,
	.cp_ad_adc_rank = 1,
	//.fault_port = GPIOF,
	//.fault_pin = GPIO_PIN_0,
	.led_charge_port = GPIOI,
	.led_charge_pin = GPIO_PIN_11,
	.led_full_port = GPIOE,
	.led_full_pin = GPIO_PIN_6,
};

static channel_config_t *channel_config_sz[] = {
	&channel0_config,
	&channel1_config,
};

static card_reader_config_item_t card_reader_config_item_0 = {
	.type = CARD_READER_TYPE_ZLG,
	.huart = &huart1,
};

//static card_reader_config_item_t card_reader_config_item_0 = {
//	.type = CARD_READER_TYPE_PSEUDO,
//	.huart = NULL,
//};

static card_reader_config_item_t *card_reader_config_item_sz[] = {
	&card_reader_config_item_0,
};

static channels_config_t channels_config_0 = {
	.id = 0,
	.channel_number = ARRAY_SIZE(channel_config_sz),
	.channel_config = channel_config_sz,
	.power_module_config = {
		.hcan = &hcan1,
		.power_module_default_type = POWER_MODULE_TYPE_WINLINE,
	},
	.power_manager_config = {
		.power_manager_default_type = POWER_MANAGER_TYPE_NATIVE,
	},
	.voice_config = {
	},
	.card_reader_config = {
		.default_type = CARD_READER_TYPE_ZLG,
		.size = ARRAY_SIZE(card_reader_config_item_sz),
		.items = card_reader_config_item_sz,
	},
	.display_config = {
		//.huart = &huart6,
	},
	.proxy_channel_info = {
		.hcan = &hcan1,
	},
	.board_temperature_adc = &hadc3,
	.board_temperature_adc_rank = 8,
	.force_stop_port = GPIOF,
	.force_stop_pin = GPIO_PIN_2,
	.force_stop_normal_state = GPIO_PIN_RESET,
	.fan_port = GPIOG,
	.fan_pin = GPIO_PIN_1,
	.door_port = GPIOE,
	.door_pin = GPIO_PIN_7,
	.door_normal_state = GPIO_PIN_RESET,
	.fault_port = GPIOI,
	.fault_pin = GPIO_PIN_8,
};

static channels_config_t *channels_config_sz[] = {
	&channels_config_0,
};

channels_config_t *get_channels_config(uint8_t id)
{
	int i;
	channels_config_t *channels_config = NULL;
	channels_config_t *channels_config_item = NULL;

	for(i = 0; i < ARRAY_SIZE(channels_config_sz); i++) {
		channels_config_item = channels_config_sz[i];

		if(channels_config_item->id == id) {
			channels_config = channels_config_item;
			break;
		}
	}

	return channels_config;
}

int adc_value_helper(adc_value_type_t adc_value_type, void *ctx)
{
	int value = 0;

	switch(adc_value_type) {
		case ADC_VALUE_TYPE_BOARD_TEMPERATURE: {
			channels_info_t *channels_info = (channels_info_t *)ctx;
			adc_info_t *adc_info = NULL;
			uint16_t temperature_ad = 0;
			adc_info = get_or_alloc_adc_info(channels_info->channels_config->board_temperature_adc);
			OS_ASSERT(adc_info != NULL);
			temperature_ad = get_adc_value(adc_info, channels_info->channels_config->board_temperature_adc_rank);
			//debug("board temperature ad %d", channels_info->temperature_ad);
			value = get_ntc_temperature(10000, temperature_ad, 4095);
		}
		break;

		case ADC_VALUE_TYPE_CP_AD_VOLTAGE: {
			channel_info_t *channel_info = (channel_info_t *)ctx;
			adc_info_t *adc_info = NULL;
			uint16_t cp_ad = 0;
			adc_info = get_or_alloc_adc_info(channel_info->channel_config->cp_ad_adc);
			OS_ASSERT(adc_info != NULL);
			cp_ad = get_adc_value(adc_info, channel_info->channel_config->cp_ad_adc_rank);
			//debug("channel %d cp ad:%d", channel_info->channel_id, cp_ad);
			value = cp_ad * 3300 / 4096;//0v-1.2v 采样 0v-12v

			//(V - 0.5) * 2 / 102 * 8 * 4 / 3 = u
			//V - 0.5 = u / (2 / 102 * 8 * 4 / 3)
			//修正前
			//V = u / (2 / 102 * 8 * 4 / 3) + 0.5
			//修正后
			//V = u / (1.8667 / 101.8667 * 8 * 4 / 3) + 0.5

			value = value * 5.1159817458616805 / 10 + 50;
		}
		break;

		default: {
			app_panic();
		}
		break;
	}

	return value;
}
