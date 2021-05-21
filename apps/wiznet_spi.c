

/*================================================================
 *
 *
 *   文件名称：wiznet_spi.c
 *   创 建 者：肖飞
 *   创建日期：2021年05月19日 星期三 09时47分16秒
 *   修改日期：2021年05月21日 星期五 10时15分39秒
 *   描    述：
 *
 *================================================================*/
#include "app_platform.h"
#include "cmsis_os.h"

#include <wizchip_socket.h>
#include "DHCP/wizchip_dhcp.h"

#include "os_utils.h"
#include "spi_txrx.h"
#include "main.h"

extern SPI_HandleTypeDef hspi1;
static spi_info_t *spi_info = NULL;

int wiznet_spi_init(void)
{
	int ret = 0;
	spi_info = get_or_alloc_spi_info(&hspi1);
	OS_ASSERT(spi_info != NULL);
	return ret;
}

void wiznet_spi_write_byte(uint8_t data)
{
	int ret = spi_tx_data(spi_info, &data, 1, 10);

	if(ret != 0) {
		//debug("");
	}
}

uint8_t wiznet_spi_read_byte(void)
{
	uint8_t byte = 0;

	int ret = spi_rx_data(spi_info, &byte, 1, 10);

	if(ret != 0) {
		//debug("");
	}

	return byte;
}

void wiznet_spi_write_burst(uint8_t *pbuf, uint16_t len)
{
	int ret = spi_tx_data(spi_info, pbuf, len, 10);

	if(ret != 0) {
		//debug("");
	}
}

void wiznet_spi_read_burst(uint8_t *pbuf, uint16_t len)
{
	int ret = spi_rx_data(spi_info, pbuf, len, 10);

	if(ret != 0) {
		//debug("");
	}
}

void wiznet_spi_cs_select(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
}

void wiznet_spi_cs_deselect(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
}

void wiz_reset(void)
{
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET);
	osDelay(2);

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET);
	osDelay(2);
}

extern uint8_t DHCP_allocated_ip[4];
extern uint8_t DHCP_SOCKET;
int8_t check_DHCP_leasedIP(void)
{
	uint8_t tmp;
	int32_t ret;

	//WIZchip RCR value changed for ARP Timeout count control
	tmp = getRCR();
	setRCR(0x03);

	// IP conflict detection : ARP request - ARP reply
	// Broadcasting ARP Request for check the IP conflict using UDP sendto() function
	ret = wizchip_sendto(DHCP_SOCKET, (uint8_t *)"CHECK_IP_CONFLICT", 17, DHCP_allocated_ip, 5000);

	ret = ret;

	// RCR value restore
	setRCR(tmp);

	return 1;
}
