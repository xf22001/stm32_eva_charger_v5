

/*================================================================
 *
 *
 *   文件名称：channels_config.c
 *   创 建 者：肖飞
 *   创建日期：2021年01月18日 星期一 09时26分44秒
 *   修改日期：2023年03月22日 星期三 09时30分27秒
 *   描    述：
 *
 *================================================================*/
#include "channels_config.h"
#include "os_utils.h"
#include "power_modules.h"
#include "hw_adc.h"
#include "main.h"

#include "log.h"

extern CAN_HandleTypeDef hcan1;//comm
extern CAN_HandleTypeDef hcan2;//charger1
extern SPI_HandleTypeDef hspi3;//charger2
extern UART_HandleTypeDef huart1;//CARD READER
extern UART_HandleTypeDef huart2;//4G
extern UART_HandleTypeDef huart3;//METER1 METER2 FAN
extern UART_HandleTypeDef huart4;//
extern UART_HandleTypeDef huart5;//EXTEND
extern UART_HandleTypeDef huart6;//DISPLAY
extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc3;

static energy_meter_config_item_t energy_meter_config_item_0_0 = {
	.type = ENERGY_METER_TYPE_DC,
	.huart = &huart3,
	.led_gpio = DC_METER1_LED_GPIO_Port,
	.led_pin = DC_METER1_LED_Pin,
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
	.insulation_k1_gpio = K1_PLUG2_GPIO_Port,
	.insulation_k1_pin = K1_PLUG2_Pin,
	.insulation_k3_gpio = K3_PLUG2_GPIO_Port,
	.insulation_k3_pin = K3_PLUG2_Pin,
};

function_board_config_item_t *function_board_1_sz[] = {
	&function_board_config_item_1_0,
};

static channel_config_t channel0_config = {
	.channel_type = CHANNEL_TYPE_NATIVE,
	.charger_config = {
		.charger_type = CHANNEL_CHARGER_BMS_TYPE_GB,
		.output_relay_gpio_p = MAIN_RLY_PLUG1_GPIO_Port,
		.output_relay_pin_p = MAIN_RLY_PLUG1_Pin,
		.output_relay_gpio_n = MAIN_RLY_PLUG1_GPIO_Port,
		.output_relay_pin_n = MAIN_RLY_PLUG1_Pin,
		.output_relay_gpio_fb_p = MAIN_RLY_PLUG1_BACK_GPIO_Port,
		.output_relay_pin_fb_p = MAIN_RLY_PLUG1_BACK_Pin,
		.output_relay_gpio_fb_n = MAIN_RLY_PLUG1_BACK_GPIO_Port,
		.output_relay_pin_fb_n = MAIN_RLY_PLUG1_BACK_Pin,
		.hcan_bms = &hcan2,
		.relay_charger_lock_p_gpio = PLUG1_LOCK_1_GPIO_Port,
		.relay_charger_lock_p_pin = PLUG1_LOCK_1_Pin,
		.relay_charger_lock_n_gpio = PLUG1_LOCK_2_GPIO_Port,
		.relay_charger_lock_n_pin = PLUG1_LOCK_2_Pin,
		.charger_lock_state_gpio = PLUG1_LOCK_BACK_GPIO_Port,
		.charger_lock_state_pin = PLUG1_LOCK_BACK_Pin,
		.charger_auxiliary_power_choose_gpio = VTRANS_1_12V_24_GPIO_Port,
		.charger_auxiliary_power_choose_pin = VTRANS_1_12V_24_Pin,
		.charger_auxiliary_power_onoff_gpio = BMSPOWER_PLUG1_GPIO_Port,
		.charger_auxiliary_power_onoff_pin = BMSPOWER_PLUG1_Pin,
	},
	.energy_meter_config = {
		.default_type = ENERGY_METER_TYPE_DC,
		.request_addr = 1,
		.slot = 0,
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
	.cp_ad_adc_rank = 1,
	//.fault_port = LED_RED_PLUG1_GPIO_Port,
	//.fault_pin = LED_RED_PLUG1_Pin,
	//.led_charge_port = LED_GREEN_POWER1_GPIO_Port,
	//.led_charge_pin = LED_GREEN_POWER1_Pin,
	//.led_full_port = LED_YELLOW_PLUG1_GPIO_Port,
	//.led_full_pin = LED_YELLOW_PLUG1_Pin,
	.fault_port = CHARGING_LED_LCLK1_GPIO_Port,
	.fault_pin = CHARGING_LED_LCLK1_Pin,
	.led_charge_port = CHARGING_LED_SCLK1_GPIO_Port,
	.led_charge_pin = CHARGING_LED_SCLK1_Pin,
	.led_full_port = CHARGING_LED_DS1_GPIO_Port,
	.led_full_pin = CHARGING_LED_DS1_Pin,
};

static energy_meter_config_item_t energy_meter_config_item_1_0 = {
	.type = ENERGY_METER_TYPE_DC,
	.huart = &huart3,
	.led_gpio = DC_METER2_LED_GPIO_Port,
	.led_pin = DC_METER2_LED_Pin,
};

static energy_meter_config_item_t *energy_meter_config_item_1_sz[] = {
	&energy_meter_config_item_1_0,
};

static channel_config_t channel1_config = {
	.channel_type = CHANNEL_TYPE_NATIVE,
	.charger_config = {
		.charger_type = CHANNEL_CHARGER_BMS_TYPE_GB,
		.output_relay_gpio_p = MAIN_RLY_PLUG2_GPIO_Port,
		.output_relay_pin_p = MAIN_RLY_PLUG2_Pin,
		.output_relay_gpio_n = MAIN_RLY_PLUG2_GPIO_Port,
		.output_relay_pin_n = MAIN_RLY_PLUG2_Pin,
		.output_relay_gpio_fb_p = MAIN_RLY_PLUG2_BACK_GPIO_Port,
		.output_relay_pin_fb_p = MAIN_RLY_PLUG2_BACK_Pin,
		.output_relay_gpio_fb_n = MAIN_RLY_PLUG2_BACK_GPIO_Port,
		.output_relay_pin_fb_n = MAIN_RLY_PLUG2_BACK_Pin,
		.hcan_bms = &hspi3,
		.relay_charger_lock_p_gpio = PLUG2_LOCK_1_GPIO_Port,
		.relay_charger_lock_p_pin = PLUG2_LOCK_1_Pin,
		.relay_charger_lock_n_gpio = PLUG2_LOCK_2_GPIO_Port,
		.relay_charger_lock_n_pin = PLUG2_LOCK_2_Pin,
		.charger_lock_state_gpio = PLUG2_LOCK_BACK_GPIO_Port,
		.charger_lock_state_pin = PLUG2_LOCK_BACK_Pin,
		.charger_auxiliary_power_choose_gpio = VTRANS_2_12V_24_GPIO_Port,
		.charger_auxiliary_power_choose_pin = VTRANS_2_12V_24_Pin,
		.charger_auxiliary_power_onoff_gpio = BMSPOWER_PLUG2_GPIO_Port,
		.charger_auxiliary_power_onoff_pin = BMSPOWER_PLUG2_Pin,
	},
	.energy_meter_config = {
		.default_type = ENERGY_METER_TYPE_DC,
		.request_addr = 1,
		.slot = 1,
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
	.cp_ad_adc_rank = 0,
	//.fault_port = LED_RED_PLUG2_GPIO_Port,
	//.fault_pin = LED_RED_PLUG2_Pin,
	//.led_charge_port = LED_GREEN_POWER2_GPIO_Port,
	//.led_charge_pin = LED_GREEN_POWER2_Pin,
	//.led_full_port = LED_YELLOW_PLUG2_GPIO_Port,
	//.led_full_pin = LED_YELLOW_PLUG2_Pin,
	.fault_port = CHARGING_LED_LCLK2_GPIO_Port,
	.fault_pin = CHARGING_LED_LCLK2_Pin,
	.led_charge_port = CHARGING_LED_SCLK2_GPIO_Port,
	.led_charge_pin = CHARGING_LED_SCLK2_Pin,
	.led_full_port = CHARGING_LED_DS2_GPIO_Port,
	.led_full_pin = CHARGING_LED_DS2_Pin,
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

static fan_control_config_item_t fan_control_config_item_0 = {
	.type = FAN_CONTROL_TYPE_STC12,
	.huart = &huart3,
};

static fan_control_config_item_t *fan_control_config_item_sz[] = {
	&fan_control_config_item_0,
};

static channels_config_t channels_config_0 = {
	.id = 0,
	.channel_number = ARRAY_SIZE(channel_config_sz),
	.channel_config = channel_config_sz,
	.power_module_config = {
		.hcan = &hcan1,
		.power_module_default_type = POWER_MODULE_TYPE_STATEGRID,
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
	.fan_control_config = {
		.default_type = FAN_CONTROL_TYPE_STC12,
		.size = ARRAY_SIZE(fan_control_config_item_sz),
		.items = fan_control_config_item_sz,
	},
	.display_config = {
		.huart = &huart6,
		.station = 2,
	},
	.proxy_channel_info = {
		.hcan = &hcan1,
	},
	.board_temperature_adc = &hadc3,
	.board_temperature_adc_rank = 8,
	.force_stop_port = EPO_GPIO_Port,
	.force_stop_pin = EPO_Pin,
	.force_stop_normal_state = GPIO_PIN_RESET,
	.fan_port = FAN1_RLY_DRV_GPIO_Port,
	.fan_pin = FAN1_RLY_DRV_Pin,
	.door_port = DOOR1_OPEN_GPIO_Port,
	.door_pin = DOOR1_OPEN_Pin,
	.door_normal_state = GPIO_PIN_RESET,
	.power_supply_port = CONTACTOR_DRV_GPIO_Port,
	.power_supply_pin = CONTACTOR_DRV_Pin,
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
			//debug("channel %d cp voltage:%d", channel_info->channel_id, value);
		}
		break;

		default: {
			app_panic();
		}
		break;
	}

	return value;
}
