#ifndef _DEVICE_H_
#define _DEVICE_H_

#define DEVICE_ID "W5500"

#define FW_VER_HIGH  1
#define FW_VER_LOW    0

extern uint8 txsize[];
extern uint8 rxsize[];

typedef  void (*pFunction)(void);

void set_network(void);


void Reset_W5500(void);

void USART1_Init(void);

void reboot(void);
void get_config(void);
#endif

