#ifndef _EEPROM_IO_H
#define _EEPROM_IO_H

#include <linux/i2c.h>
#include <linux/i2c-dev.h>

/* I2C总线ioctl方法所使用的结构体 */
typedef struct i2c_rdwr_ioctl_data ioctl_st;

typedef unsigned char u8;
typedef unsigned int u32;

/* eeprom的slave_address */
enum eeprom_address {
    eeprom_addr0 = 0x50,
    eeprom_addr1 = 0x51,
    eeprom_addr2 = 0x52,
    eeprom_addr3 = 0x53,
};

#define DEV_PATH "/dev/i2c-0"  //设备文件路径
#define I2C_M_WR          0    //定义写标志
#define MAX_MSG_NR        2    //最大消息数为2
#define EEPROM_BLOCK_SIZE 256  //block容量256 bytes
#define EEPROM_PAGE_SIZE  128   //页大小为128 bytes
#define I2C_MSG_SIZE (sizeof(struct i2c_msg))

/* eeprom参数结构体 */
typedef struct eeprom_data {
    u8 slave_addr;
    u8 byte_addr;
    u8 len;
    u8 *buf;
} eeprom_st;


/* 从eeprom的pos位置处读取1个字节
   @pos: eeprom的byte_address, 取值范围为0 ~ 511
   返回值为读取的字节数据 */
extern u8 eeprom_byte_read(u8 pos);

/* 将1个字节数据写入eeprom的pos位置
   @pos: eeprom的byte_address, 取值范围为0 ~ 511
   @data: 待写入的字节数据 */
extern int eeprom_byte_write(u8 pos, u8 data);

/* 从eeprom的pos位置开始读取size长度数据
   @pos: eeprom的byte_address, 取值范围为0 ~ 511
   @data: 接收数据的缓冲区
   @size: 待读取的数据长度, 取值范围为1 ~ 64 */
extern int eeprom_page_read(u8 pos, u8 *data, int size);

/* 自eeprom的pos位置开始写入数据
   @pos: eeprom的byte_address, 取值范围为0 ~ 511
   @data: 待写入的数据
   @size: 待写入数据的长度, 取值范围为1 ~ 64 */
extern int eeprom_page_write(u8 pos, u8 *data, int size);

#endif