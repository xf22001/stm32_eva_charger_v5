

/*================================================================
 *
 *
 *   文件名称：power_manager_group_policy_handler.c
 *   创 建 者：肖飞
 *   创建日期：2021年11月30日 星期二 15时07分16秒
 *   修改日期：2021年12月27日 星期一 10时18分39秒
 *   描    述：
 *
 *================================================================*/
#include "power_manager.h"

#include "main.h"

#include "log.h"

static int _init(void *_power_manager_info)
{
	int ret = 0;

	return ret;
}

static int _deinit(void *_power_manager_info)
{
	int ret = 0;

	return ret;
}

static int _channel_start(void *_power_manager_channel_info)
{
	int ret = 0;
	power_manager_channel_info_t *power_manager_channel_info = (power_manager_channel_info_t *)_power_manager_channel_info;
	debug("power manager channel %d start", power_manager_channel_info->id);
	return ret;
}

static int _channel_charging(void *_power_manager_channel_info)
{
	int ret = 0;
	//power_manager_channel_info_t *power_manager_channel_info = (power_manager_channel_info_t *)_power_manager_channel_info;
	//debug("power manager channel %d charging", power_manager_channel_info->id);
	return ret;
}

static int _free(void *_power_manager_group_info)
{
	int ret = 0;
	power_manager_group_info_t *power_manager_group_info = (power_manager_group_info_t *)_power_manager_group_info;

	debug("power manager group %d free", power_manager_group_info->id);

	return ret;
}

static int _assign(void *_power_manager_group_info)
{
	int ret = 0;
	power_manager_group_info_t *power_manager_group_info = (power_manager_group_info_t *)_power_manager_group_info;
	debug("power manager group %d assign", power_manager_group_info->id);
	return ret;
}

static int _config(void *_power_manager_group_info)
{
	int ret = 0;
	power_manager_group_info_t *power_manager_group_info = (power_manager_group_info_t *)_power_manager_group_info;
	debug("power manager group %d config", power_manager_group_info->id);
	return ret;
}

static int _sync(void *_power_manager_group_info)
{
	int ret = 0;
	power_manager_group_info_t *power_manager_group_info = (power_manager_group_info_t *)_power_manager_group_info;
	debug("power manager group %d sync", power_manager_group_info->id);
	return ret;
}

static power_manager_group_policy_handler_t power_manager_group_policy_handler_0 = {
	.policy = 0,
	.init = _init,
	.deinit = _deinit,
	.channel_start = _channel_start,
	.channel_charging = _channel_charging,
	.free = _free,
	.assign = _assign,
	.config = _config,
	.sync = _sync,
};

static power_manager_group_policy_handler_t *power_manager_group_policy_handler_sz[] = {
	&power_manager_group_policy_handler_0,
};

power_manager_group_policy_handler_t *get_power_manager_group_policy_handler(uint8_t policy)
{
	int i;
	power_manager_group_policy_handler_t *power_manager_group_policy_handler = NULL;

	for(i = 0; i < ARRAY_SIZE(power_manager_group_policy_handler_sz); i++) {
		power_manager_group_policy_handler_t *power_manager_group_policy_handler_item = power_manager_group_policy_handler_sz[i];

		if(power_manager_group_policy_handler_item->policy == policy) {
			power_manager_group_policy_handler = power_manager_group_policy_handler_item;
		}
	}

	return power_manager_group_policy_handler;
}
