

/*================================================================
 *
 *
 *   文件名称：channels_addr_handler.c
 *   创 建 者：肖飞
 *   创建日期：2021年07月16日 星期五 14时03分28秒
 *   修改日期：2022年01月20日 星期四 17时08分05秒
 *   描    述：
 *
 *================================================================*/
#include "modbus_data_value.h"
#include "app.h"
#include "channels.h"
#include "display.h"
#include "power_manager.h"

#include "log.h"

void channels_modbus_data_action(void *fn_ctx, void *chain_ctx)
{
	channels_info_t *channels_info = (channels_info_t *)fn_ctx;
	channels_settings_t *channels_settings = &channels_info->channels_settings;
	modbus_data_ctx_t *modbus_data_ctx = (modbus_data_ctx_t *)chain_ctx;

	switch(modbus_data_ctx->addr) {
		case 0: {//模块个数
			power_manager_info_t *power_manager_info = (power_manager_info_t *)channels_info->power_manager_info;
			uint8_t power_module_number = power_manager_info->power_modules_info->power_module_number;
			modbus_data_value_r(modbus_data_ctx, power_module_number);
		}
		break;

		case 1: {//模块最大输出电压 0.1V
			modbus_data_value_rw(modbus_data_ctx, channels_settings->module_max_output_voltage);
		}
		break;

		case 2: {//模块最小输出电压 0.1V
			modbus_data_value_rw(modbus_data_ctx, channels_settings->module_min_output_voltage);
		}
		break;

		case 3: {//模块最大输出电流 0.1A
			modbus_data_value_rw(modbus_data_ctx, channels_settings->module_max_output_current);
		}
		break;

		case 4: {//模块最小输出电流 0.1A
			modbus_data_value_rw(modbus_data_ctx, channels_settings->module_min_output_current);
		}
		break;

		case 5: {//输入过压阈值 0.1V
			modbus_data_value_rw(modbus_data_ctx, channels_settings->module_max_input_voltage);
		}
		break;

		case 6: {//输入欠压阈值 0.1V
			modbus_data_value_rw(modbus_data_ctx, channels_settings->module_min_input_voltage);
		}
		break;

		case 7: {//输出过压阈值 0.1V
		}
		break;

		case 8: {//输出过流阈值 0.1a
		}
		break;

		case 9: {//刷卡设置 (0:不刷卡 1:刷卡 )
			modbus_data_value_rw(modbus_data_ctx, channels_settings->authorize);
		}
		break;

		case 10: {//枪充电模式 (0:单枪充电  1:双枪充电 2: 两枪一车 3:四枪)
			uint8_t mode = 1;
			modbus_data_value_rw(modbus_data_ctx, mode);
		}
		break;

		case 11: {//宇通修改电流偏移量模式 (0:未使能   1:使能)
			uint8_t mode = 0;
			modbus_data_value_rw(modbus_data_ctx, mode);
		}
		break;

		case 12: {//直流表交流表选择
		}
		break;

		case 13: {//后台设置
			app_info_t *app_info = get_app_info();
			modbus_data_value_rw(modbus_data_ctx, app_info->display_cache_app.request_type);

			if(modbus_data_ctx->action == MODBUS_DATA_ACTION_SET) {
				app_info->display_cache_app.request_type_sync = 1;
			}
		}
		break;

		case 14: {//辅助电源模式
		}
		break;

		case 15: {//0:同时充 1:轮流充
		}
		break;

		case 16: {//CP AD 采样
		}
		break;

		case 17: {//电表倍率
		}
		break;

		case 18: {//空载保护(0:保护 1:不保护)
			modbus_data_value_rw(modbus_data_ctx, channels_settings->noload_protect_disable);
		}
		break;

		case 19: {//SOC值，设置。达到此SOC值，充电桩会保护停机
			modbus_data_value_rw(modbus_data_ctx, channels_settings->soc_threshold);
		}
		break;

		case 20: {//小时(bcd) 分钟(bcd) 电价(0.0001元) 电价(0.0001元) 服务费(0.0001元) 服务费(0.0001元)
			modbus_data_buffer_rw(modbus_data_ctx, channels_info->display_cache_channels.price_item_cache, 6 * 20 * 2, modbus_data_ctx->addr - 20);
			if(modbus_data_ctx->action == MODBUS_DATA_ACTION_SET) {
				channels_info->display_cache_channels.price_sync = 1;
			}
		}
		break;

		case 308 ... 312: {//ASCII码  IP 250
			app_info_t *app_info = get_app_info();
			modbus_data_buffer_rw(modbus_data_ctx, app_info->display_cache_app.ip, 5 * 2, modbus_data_ctx->addr - 308);

			if(modbus_data_ctx->action == MODBUS_DATA_ACTION_SET) {
				app_info->display_cache_app.ip_sync = 1;
			}
		}
		break;

		case 313: {//1号堆模块个数
			power_manager_settings_t *power_manager_settings = &channels_settings->power_manager_settings;
			power_manager_group_settings_t *power_manager_group_settings = &power_manager_settings->power_manager_group_settings[0];
			power_module_group_settings_t *power_module_group_settings = &power_manager_group_settings->power_module_group_settings[0];
			modbus_data_value_rw(modbus_data_ctx, power_module_group_settings->power_module_number);
		}
		break;

		case 314: {//2号堆模块个数
			power_manager_settings_t *power_manager_settings = &channels_settings->power_manager_settings;
			power_manager_group_settings_t *power_manager_group_settings = &power_manager_settings->power_manager_group_settings[0];
			power_module_group_settings_t *power_module_group_settings = &power_manager_group_settings->power_module_group_settings[1];
			modbus_data_value_rw(modbus_data_ctx, power_module_group_settings->power_module_number);
		}
		break;

		case 315: {//3号堆模块个数
			power_manager_settings_t *power_manager_settings = &channels_settings->power_manager_settings;
			power_manager_group_settings_t *power_manager_group_settings = &power_manager_settings->power_manager_group_settings[0];
			power_module_group_settings_t *power_module_group_settings = &power_manager_group_settings->power_module_group_settings[2];
			modbus_data_value_rw(modbus_data_ctx, power_module_group_settings->power_module_number);
		}
		break;

		case 316: {//4号堆模块个数
			power_manager_settings_t *power_manager_settings = &channels_settings->power_manager_settings;
			power_manager_group_settings_t *power_manager_group_settings = &power_manager_settings->power_manager_group_settings[0];
			power_module_group_settings_t *power_module_group_settings = &power_manager_group_settings->power_module_group_settings[3];
			modbus_data_value_rw(modbus_data_ctx, power_module_group_settings->power_module_number);
		}
		break;

		case 317 ... 332: {//后台使用的域名
		}
		break;

		case 333: {//自动充电 1:打开  0:关闭
		}
		break;

		case 334: {//电压电流数据源 0:电表采样 1:模块采样
		}
		break;

		case 335: {//预充使能
			modbus_data_value_rw(modbus_data_ctx, channels_settings->precharge_enable);
		}
		break;

		case 336: {//电价精度设置 0：两位   1：四位
		}
		break;

		case 337 ... 342: {//电表A表号
		}
		break;

		case 343 ... 348: {//电表B表号
		}
		break;

		case 349 ... 354: {//电表C表号
		}
		break;

		case 355 ... 360: {//电表D表号
		}
		break;

		case 361 ... 376: {//ASCII码  设备ID
			app_info_t *app_info = get_app_info();
			modbus_data_buffer_rw(modbus_data_ctx, app_info->display_cache_app.device_id, 16 * 2, modbus_data_ctx->addr - 361);

			if(modbus_data_ctx->action == MODBUS_DATA_ACTION_SET) {
				app_info->display_cache_app.device_id_sync = 1;
			}
		}
		break;

		case 377 ... 380: {//静态ip设置
		}
		break;

		case 381 ... 384: {//子网掩码
		}
		break;

		case 385 ... 388: {//网关
		}
		break;

		case 389: {//ip获取设置
		}
		break;

		case 390 ... 395: {//Mac地址设置
		}
		break;

		case 396: {//mac地址获取设置
		}
		break;

		case 397: {//整机最大输出功率 0.1kW
		}
		break;

		case 398: {//电源模块类型      (0:英可瑞协议    1:华为协议  2:国网协议 3:英飞源协议)
		}
		break;

		case 399: {//华为模块基准参考电流 (0.1A)
		}
		break;

		case 400: {//双桩一车模式  (0:正常模式  1：双桩一车模式)
		}
		break;

		case 401: {//电量设置 (0:2位小数   1:3位小数)
		}
		break;

		case 2000: {//主控板版本号
		}
		break;

		case 2001: {//主控板扩展版本号
		}
		break;

		case 2002 ... 2008: {//BCD码 系统时间 秒 分 时 日 月 年 星期
		}
		break;

		case 2009: {//BCD码 时间更新标志
		}
		break;

		case 2010 ... 2015: {//BCD码 设置时间 秒 分 时 日 月 年
		}
		break;

		case 2016 ... 2031: {//ASCII  密码输入区
		}
		break;

		case 2032: {//网络通信状态
		}
		break;

		case 2033: {//刷卡板连接状态 0：未连接 1：连接
		}
		break;

		case 2034: {//测试模式
		}
		break;

		case 2035: {//A相输入电压 0.1V
		}
		break;

		case 2036: {//B相输入电压 0.1V
		}
		break;

		case 2037: {//C相输入电压 0.1V
		}
		break;

		case 2038: {//系统运行时间 1分钟
		}
		break;

		case 2039: {//弹窗提示地址
		}
		break;

		case 2040: {//系统故障状态
		}
		break;

		case 2041 ... 2044: {//系统故障状态 按位表示
		}
		break;

		case 2045: {//控制板温度
		}
		break;

		case 2046: {//接触器粘连状态
		}
		break;

		case 2047: {//最小剩余栈空间 1 byte
		}
		break;

		case 2048: {//剩余堆空间 1 byte
		}
		break;

		case 2500: {//当前记录条数
		}
		break;

		case 2501 ... 2502: {//检索年 月 日
		}
		break;

		case 2504: {//查询确认
		}
		break;

		case 2505: {//未上传记录数
		}
		break;

		case 2506: {//查询尖峰平谷电量
		}
		break;

		case 2550 ... 3049: {//
			modbus_data_buffer_rw(modbus_data_ctx, channels_info->display_cache_channels.record_item_cache, 50 * 10 * 2, modbus_data_ctx->addr - 906);
		}
		break;

		case 3500: {//充电状态 (0:待机  1:准备就绪  2:正在充电)
		}
		break;

		case 3501: {//充电电压 0.1V
		}
		break;

		case 3502: {//充电电流 0.1A
		}
		break;

		case 3503: {//充电电量 0.001度
		}
		break;

		case 3504: {//充电电量 0.001度
		}
		break;

		case 3505: {//充电时间 1分
		}
		break;

		case 3506: {//BMS需求电压 0.1V
		}
		break;

		case 3507: {//BMS需求电流 0.1A
		}
		break;

		case 3508: {//预付款 0.01元
		}
		break;

		case 3509: {//预付款 0.01元
		}
		break;

		case 3510 ... 3525: {//账户ID
		}
		break;

		case 3526: {//账户余额 0.01元
		}
		break;

		case 3527: {//账户余额 0.01元
		}
		break;

		case 3528: {//消费金额 0.01元
		}
		break;

		case 3529: {//消费金额 0.01元
		}
		break;

		case 3530: {//当前电价 0.0001元
		}
		break;

		case 3531: {//当前电价 0.0001元
		}
		break;

		case 3532: {//服务费率 0.0001元
		}
		break;

		case 3533: {//服务费率 0.0001元
		}
		break;

		case 3534: {//开关机 (0:关机 1:开机)
		}
		break;

		case 3535: {//充电剩余时间 1分
		}
		break;

		case 3536: {//电池当前电量 1%
		}
		break;

		case 3537: {//电表电量读数 0.001度
		}
		break;

		case 3538: {//电表电量读数 0.001度
		}
		break;

		case 3539: {//显示屏下发消息
		}
		break;

		case 3540: {//主板上报提示
		}
		break;

		case 3541 ... 3549: {//当前充电VIN码
		}
		break;

		case 3600: {//插枪状态
		}
		break;

		case 3601: {//电子锁状态
		}
		break;

		case 3602: {//BMS状态
		}
		break;

		case 3603: {//BMS停机原因
		}
		break;

		case 3604: {//充电机停机原因
		}
		break;

		case 3605: {//充电机开机原因
		}
		break;

		case 3606: {//绝缘电阻
		}
		break;

		case 3607: {//绝缘状态
		}
		break;

		case 3608: {//枪头正极温度
		}
		break;

		case 3609: {//枪头负极温度
		}
		break;

		case 3610: {//电表连接状态
		}
		break;

		case 3611: {//查找Channel_Err_enum
		}
		break;

		case 3612 ... 3613: {//channel_err_bit
		}
		break;

		case 3700: {//BMS版本号
		}
		break;

		case 3701: {//电池类型 见地址表
		}
		break;

		case 3702: {//电池容量 0.1Ah
		}
		break;

		case 3703: {//电池额定总电压 0.1V
		}
		break;

		case 3704: {//单体最高允许电压 0.01V
		}
		break;

		case 3705: {//单体最高电压 0.01V
		}
		break;

		case 3706: {//单体最高允许温度 1° -50偏移量(-50 -- 200)
		}
		break;

		case 3707: {//单体最高温度 1° -50偏移量(-50 -- 200)
		}
		break;

		case 3708: {//BMS端测量充电电压 0.1V
		}
		break;

		case 3709: {//BMS端测量充电电流 0.1A
		}
		break;

		case 3710: {//电池最大允许充电电压 0.1V
		}
		break;

		case 3711: {//充电前电池电压 0.1V
		}
		break;

		case 3750: {//控制模式 (0:BMS模式  1:BMS手动  2:手动模式)
		}
		break;

		case 3751: {//手动模式下设定电压 0.1V
		}
		break;

		case 3752: {//手动模式下设定电流 0.1A
		}
		break;

		case 3753: {//辅助电源选择 (0:none 1:12V 2:24V) 查找AUX_Power_enum
		}
		break;

		case 3754: {//条件充电模式 查找 Charge_Mode_Type 见地址表
		}
		break;

		case 3755: {//设定充电金额 0.01元
		}
		break;

		case 3756: {//BCD码 设定充电开始时间 小时 绝对时间
		}
		break;

		case 3757: {//BCD码 设定充电开始时间 分钟
		}
		break;

		case 3758: {//BCD码 设定充电结束时间 小时 绝对时间
		}
		break;

		case 3759: {//BCD码 设定充电结束时间 分钟
		}
		break;

		case 3760: {//设定充电电量 0.001kwh
		}
		break;

		case 3761: {//设定充电时间 1分钟 相对时间
		}
		break;

		case 3762: {//设定结束SOC
		}
		break;

		default:
			debug("error! op:%s, addr:%d",
			      (modbus_data_ctx->action == MODBUS_DATA_ACTION_GET) ? "get" :
			      (modbus_data_ctx->action == MODBUS_DATA_ACTION_SET) ? "set" :
			      "unknow",
			      modbus_data_ctx->addr);
			break;
	}
}
