#ifndef  _W5500_H_
#define  _W5500_H_

#include "main.h"
#include "w5500_Conf.h"

typedef uint8_t	SOCKET;


#ifndef w5500_ISR_DISABLE_Ex
#define w5500_ISR_DISABLE()
#endif

#ifndef w5500_ISR_ENABLE_Ex
#define w5500_ISR_ENABLE()
#endif

extern uint8_t w5500_Mac[6]={0x00,0x08,0xdc,0x11,0x11,0x11};/*定义Mac变量*/
extern uint8_t w5500_IP[4]={192,168,0,101};/*定义lp变量*/

extern uint8_t w5500_SubnetMask[4]={255,255,255,0};/*定义subnet变量*/
extern uint8_t w5500_GateWay[4]={192,168,0,1};/*定义gateway变量*/

#define w5500_SetMac_self() w5500_WriteBuf(w5500_Reg_SHAR0, w5500_Mac, 6)
#define w5500_SetIP_self() w5500_WriteBuf(w5500_Reg_SIPR0, w5500_IP, 4)
#define w5500_SetSubnetMask_self() w5500_WriteBuf(w5500_Reg_SUBR0, w5500_SubnetMask, 4)
#define w5500_SetGateWay_self() w5500_WriteBuf(w5500_Reg_GAR0, w5500_GateWay, 4)
/**
 @brief Mode Register address
 * W5500 SPI Frame consists of 16bits Offset Address in Address Phase, 
 * 8bits Control Phase and N bytes Data Phase.
 * 0                8                16               24                   ~
 * |----------------|----------------|----------------|----------------------
 * |        16bit offset Address     | Control Bits   |  Data Phase
 *
 * The 8bits Control Phase is reconfigured with Block Select bits (BSB[4:0]), 
 * Read/Write Access Mode bit (RWB) and SPI Operation Mode (OM[1:0]). 
 * Block Select bits select a block as like common register, socket register, tx buffer and tx buffer.
 * Address value is defined as 16bit offset Address, BSB[4:0] and the three bits of zero-padding.(The RWB and OM [1:0] are '0 'padding)
 * Please, refer to W5500 datasheet for more detail about Memory Map.
 *
 */

/**
 @brief Mode Register address
 */
#define w5500_Reg_MR	(0x000000)

/* MODE register values */
#define w5500_RegVal_MR_RST	0x80 /**< reset */
#define w5500_RegVal_MR_WOL	0x20 /**< Wake on Lan */
#define w5500_RegVal_MR_PB	0x10 /**< ping block */
#define w5500_RegVal_MR_PPPOE	0x08 /**< enable pppoe */
#define w5500_RegVal_MR_UDP_FARP	0x02 /**< enbale FORCE ARP */

/**
 @brief Gateway IP Register address
 */
#define w5500_Reg_GAR0                        (0x000100)
#define w5500_Reg_GAR1                        (0x000200)
#define w5500_Reg_GAR2                        (0x000300)
#define w5500_Reg_GAR3                        (0x000400)
/**
 @brief Subnet mask Register address
 */
#define w5500_Reg_SUBR0                       (0x000500)
#define w5500_Reg_SUBR1                       (0x000600)
#define w5500_Reg_SUBR2                       (0x000700)
#define w5500_Reg_SUBR3                       (0x000800)

/**
 @brief Source MAC Register address
 */
#define w5500_Reg_SHAR0                       (0x000900)
#define w5500_Reg_SHAR1                       (0x000A00)
#define w5500_Reg_SHAR2                       (0x000B00)
#define w5500_Reg_SHAR3                       (0x000C00)
#define w5500_Reg_SHAR4                       (0x000D00)
#define w5500_Reg_SHAR5                       (0x000E00)
/**
 @brief Source IP Register address
 */
#define w5500_Reg_SIPR0                       (0x000F00)
#define w5500_Reg_SIPR1                       (0x001000)
#define w5500_Reg_SIPR2                       (0x001100)
#define w5500_Reg_SIPR3                       (0x001200)
/**
 @brief set Interrupt low level timer register address
 */
#define w5500_Reg_INTLEVEL0                   (0x001300)
#define w5500_Reg_INTLEVEL1                   (0x001400)
/**
 @brief Interrupt Register
 */
#define w5500_Reg_IR                          (0x001500)
/**
 @brief Interrupt mask register
 */
#define w5500_Reg_IMR                         (0x001600)
/**
 @brief Socket Interrupt Register
 */
#define w5500_Reg_SIR                         (0x001700) 
/**
 @brief Socket Interrupt Mask Register
 */
#define w5500_Reg_SIMR                        (0x001800)
/**
 @brief Timeout register address( 1 is 100us )
 */
#define w5500_Reg_RTR0                        (0x001900)
#define w5500_Reg_RTR1                        (0x001A00)
/**
 @brief Retry count reigster
 */
#define w5500_Reg__RCR                         (0x001B00)
/**
 @briefPPP LCP Request Timer register  in PPPoE mode
 */
#define w5500_Reg_PTIMER                      (0x001C00)
/**
 @brief PPP LCP Magic number register  in PPPoE mode
 */
#define w5500_Reg_PMAGIC                      (0x001D00)
/**
 @brief PPP Destination MAC Register address
 */
#define w5500_Reg_PDHAR0                      (0x001E00)
#define w5500_Reg_PDHAR1                      (0x001F00)
#define w5500_Reg_PDHAR2                      (0x002000)
#define w5500_Reg_PDHAR3                      (0x002100)
#define w5500_Reg_PDHAR4                      (0x002200)
#define w5500_Reg_PDHAR5                      (0x002300)
/**
 @brief PPP Session Identification Register
 */
#define w5500_Reg_PSID0                       (0x002400)
#define w5500_Reg_PSID1                       (0x002500)
/**
 @brief PPP Maximum Segment Size(MSS) register
 */
#define w5500_Reg_PMR0                        (0x002600)
#define w5500_Reg_PMR1                        (0x002700)
/**
 @brief Unreachable IP register address in UDP mode
 */
#define w5500_Reg_UIPR0                       (0x002800)
#define w5500_Reg_UIPR1                       (0x002900)
#define w5500_Reg_UIPR2                       (0x002A00)
#define w5500_Reg_UIPR3                       (0x002B00)
/**
 @brief Unreachable Port register address in UDP mode
 */
#define w5500_Reg_UPORT0                      (0x002C00)
#define w5500_Reg_UPORT1                      (0x002D00)
/**
 @brief PHY Configuration Register
 */
#define w5500_Reg_PHYCFGR                      (0x002E00)
/**
 @brief chip version register address
 */
#define w5500_Reg_VERSIONR                    (0x003900)   



/**
 @brief socket Mode register
 */
#define w5500_Reg_Sn_MR(ch)                       (0x000008 + (ch<<5))

/**
 @brief channel Sn_CR register
 */
#define w5500_Reg_Sn_CR(ch)                       (0x000108 + (ch<<5))
/**
 @brief channel interrupt register
 */
#define w5500_Reg_Sn_IR(ch)                       (0x000208 + (ch<<5))
/**
 @brief channel status register
 */
#define w5500_Reg_Sn_SR(ch)                       (0x000308 + (ch<<5))
/**
 @brief source port register
 */
#define w5500_Reg_Sn_PORT0(ch)                    (0x000408 + (ch<<5))
#define w5500_Reg_Sn_PORT1(ch)                    (0x000508 + (ch<<5))
/**
 @brief Peer MAC register address
 */
#define w5500_Reg_Sn_DHAR0(ch)                    (0x000608 + (ch<<5))
#define w5500_Reg_Sn_DHAR1(ch)                    (0x000708 + (ch<<5))
#define w5500_Reg_Sn_DHAR2(ch)                    (0x000808 + (ch<<5))
#define w5500_Reg_Sn_DHAR3(ch)                    (0x000908 + (ch<<5))
#define w5500_Reg_Sn_DHAR4(ch)                    (0x000A08 + (ch<<5))
#define w5500_Reg_Sn_DHAR5(ch)                    (0x000B08 + (ch<<5))
/**
 @brief Peer IP register address
 */
#define w5500_Reg_Sn_DIPR0(ch)                    (0x000C08 + (ch<<5))
#define w5500_Reg_Sn_DIPR1(ch)                    (0x000D08 + (ch<<5))
#define w5500_Reg_Sn_DIPR2(ch)                    (0x000E08 + (ch<<5))
#define w5500_Reg_Sn_DIPR3(ch)                    (0x000F08 + (ch<<5))
/**
 @brief Peer port register address
 */
#define w5500_Reg_Sn_DPORT0(ch)                   (0x001008 + (ch<<5))
#define w5500_Reg_Sn_DPORT1(ch)                   (0x001108 + (ch<<5))
/**
 @brief Maximum Segment Size(Sn_MSSR0) register address
 */
#define w5500_Reg_Sn_MSSR0(ch)                    (0x001208 + (ch<<5))
#define w5500_Reg_Sn_MSSR1(ch)                    (0x001308 + (ch<<5))
/** 
 @brief IP Type of Service(TOS) Register 
 */
#define w5500_Reg_Sn_TOS(ch)                      (0x001508 + (ch<<5))
/**
 @brief IP Time to live(TTL) Register 
 */
#define w5500_Reg_Sn_TTL(ch)                      (0x001608 + (ch<<5))
/**
 @brief Receive memory size reigster
 */
#define w5500_Reg_Sn_RXMEM_SIZE(ch)               (0x001E08 + (ch<<5))
/**
 @brief Transmit memory size reigster
 */
#define w5500_Reg_Sn_TXMEM_SIZE(ch)               (0x001F08 + (ch<<5))
/**
 @brief Transmit free memory size register
 */
#define w5500_Reg_Sn_TX_FSR0(ch)                  (0x002008 + (ch<<5))
#define w5500_Reg_Sn_TX_FSR1(ch)                  (0x002108 + (ch<<5))
/**
 @brief Transmit memory read pointer register address
 */
#define w5500_Reg_Sn_TX_RD0(ch)                   (0x002208 + (ch<<5))
#define w5500_Reg_Sn_TX_RD1(ch)                   (0x002308 + (ch<<5))
/**
 @brief Transmit memory write pointer register address
 */
#define w5500_Reg_Sn_TX_WR0(ch)                   (0x002408 + (ch<<5))
#define w5500_Reg_Sn_TX_WR1(ch)                   (0x002508 + (ch<<5))
/**
 @brief Received data size register
 */
#define w5500_Reg_Sn_RX_RSR0(ch)                  (0x002608 + (ch<<5))
#define w5500_Reg_Sn_RX_RSR1(ch)                  (0x002708 + (ch<<5))
/**
 @brief Read point of Receive memory
 */
#define w5500_Reg_Sn_RX_RD0(ch)                   (0x002808 + (ch<<5))
#define w5500_Reg_Sn_RX_RD1(ch)                   (0x002908 + (ch<<5))
/**
 @brief Write point of Receive memory
 */
#define w5500_Reg_Sn_RX_WR0(ch)                   (0x002A08 + (ch<<5))
#define w5500_Reg_Sn_RX_WR1(ch)                   (0x002B08 + (ch<<5))
/**
 @brief socket interrupt mask register
 */
#define w5500_Reg_Sn_IMR(ch)                      (0x002C08 + (ch<<5))
/**
 @brief frag field value in IP header register
 */
#define w5500_Reg_Sn_FRAG(ch)                     (0x002D08 + (ch<<5))
/**
 @brief Keep Timer register
 */
#define w5500_Reg_SocketN_Keepalive(ch)                  (0x002F08 + (ch<<5))

/* IR register values */
#define w5500_RegVal_IR_CONFLICT                  0x80 /**< check ip confict */
#define w5500_RegVal_IR_UNREACH                   0x40 /**< get the destination unreachable message in UDP sending */
#define w5500_RegVal_IR_PPPoE                     0x20 /**< get the PPPoE close message */
#define w5500_RegVal_IR_MAGIC                     0x10 /**< get the magic packet interrupt */

/* Sn_MR values */
#define w5500_RegVal_Sn_MR_CLOSE                  0x00     /**< unused socket */
#define w5500_RegVal_Sn_MR_TCP                    0x01     /**< TCP */
#define w5500_RegVal_Sn_MR_UDP                    0x02     /**< UDP */
#define w5500_RegVal_Sn_MR_IPRAW                  0x03      /**< IP LAYER RAW SOCK */
#define w5500_RegVal_Sn_MR_MACRAW                 0x04      /**< MAC LAYER RAW SOCK */
#define w5500_RegVal_Sn_MR_PPPOE                  0x05     /**< PPPoE */
#define w5500_RegVal_Sn_MR_UCASTB                 0x10     /**< Unicast Block in UDP Multicating*/
#define w5500_RegVal_Sn_MR_ND                     0x20     /**< No Delayed Ack(TCP) flag */
#define w5500_RegVal_Sn_MR_MC                     0x20     /**< Multicast IGMP (UDP) flag */
#define w5500_RegVal_Sn_MR_BCASTB                 0x40     /**< Broadcast blcok in UDP Multicating */
#define w5500_RegVal_Sn_MR_MULTI                  0x80     /**< support UDP Multicating */

 /* Sn_MR values on MACRAW MODE */
#define w5500_RegVal_Sn_MR_MIP6N                  0x10     /**< IPv6 packet Block */
#define w5500_RegVal_Sn_MR_MMB                    0x20     /**< IPv4 Multicasting Block */
//#define w5500_RegVal_Sn_MR_BCASTB                 0x40     /**< Broadcast blcok */
#define w5500_RegVal_Sn_MR_MFEN                   0x80     /**< support MAC filter enable */


/* Sn_CR values */
#define w5500_RegVal_Sn_CR_OPEN                   0x01     /**< initialize or open socket */
#define w5500_RegVal_Sn_CR_LISTEN                 0x02     /**< wait connection request in tcp mode(Server mode) */
#define w5500_RegVal_Sn_CR_CONNECT                0x04     /**< send connection request in tcp mode(Client mode) */
#define w5500_RegVal_Sn_CR_DISCON                 0x08     /**< send closing reqeuset in tcp mode */
#define w5500_RegVal_Sn_CR_CLOSE                  0x10     /**< close socket */
#define w5500_RegVal_Sn_CR_SEND                   0x20     /**< update txbuf pointer, send data */
#define w5500_RegVal_Sn_CR_SEND_MAC               0x21     /**< send data with MAC address, so without ARP process */
#define w5500_RegVal_Sn_CR_SEND_KEEP              0x22     /**<  send keep alive message */
#define w5500_RegVal_Sn_CR_RECV                   0x40     /**< update rxbuf pointer, recv data */

#ifdef __DEF_IINCHIP_PPP__
   #define w5500_RegVal_Sn_CR_PCON                0x23      
   #define w5500_RegVal_Sn_CR_PDISCON             0x24      
   #define w5500_RegVal_Sn_CR_PCR                 0x25      
   #define w5500_RegVal_Sn_CR_PCN                 0x26     
   #define w5500_RegVal_Sn_CR_PCJ                 0x27     
#endif

/* Sn_IR values */
#ifdef __DEF_IINCHIP_PPP__
   #define w5500_RegVal_Sn_IR_PRECV               0x80     
   #define w5500_RegVal_Sn_IR_PFAIL               0x40     
   #define w5500_RegVal_Sn_IR_PNEXT               0x20     
#endif

#define w5500_RegVal_Sn_IR_SEND_OK                0x10     /**< complete sending */
#define w5500_RegVal_Sn_IR_TIMEOUT                0x08     /**< assert timeout */
#define w5500_RegVal_Sn_IR_RECV                   0x04     /**< receiving data */
#define w5500_RegVal_Sn_IR_DISCON                 0x02     /**< closed socket */
#define w5500_RegVal_Sn_IR_CON                    0x01     /**< established connection */

/* Sn_SR values */
#define w5500_RegVal_SOCK_CLOSED                  0x00     /**< closed */
#define w5500_RegVal_SOCK_INIT                    0x13     /**< init state */
#define w5500_RegVal_SOCK_LISTEN                  0x14     /**< listen state */
#define w5500_RegVal_SOCK_SYNSENT                 0x15     /**< connection state */
#define w5500_RegVal_SOCK_SYNRECV                 0x16     /**< connection state */
#define w5500_RegVal_SOCK_ESTABLISHED             0x17     /**< success to connect */
#define w5500_RegVal_SOCK_FIN_WAIT                0x18     /**< closing state */
#define w5500_RegVal_SOCK_CLOSING                 0x1A     /**< closing state */
#define w5500_RegVal_SOCK_TIME_WAIT               0x1B     /**< closing state */
#define w5500_RegVal_SOCK_CLOSE_WAIT              0x1C     /**< closing state */
#define w5500_RegVal_SOCK_LAST_ACK                0x1D     /**< closing state */
#define w5500_RegVal_SOCK_UDP                     0x22     /**< udp socket */
#define w5500_RegVal_SOCK_IPRAW                   0x32     /**< ip raw mode socket */
#define w5500_RegVal_SOCK_MACRAW                  0x42     /**< mac raw mode socket */
#define w5500_RegVal_SOCK_PPPOE                   0x5F     /**< pppoe socket */

/* IP PROTOCOL */
#define w5500_RegVal_IPPROTO_IP                   0        /**< Dummy for IP */
#define w5500_RegVal_IPPROTO_ICMP                 1        /**< Control message protocol */
#define w5500_RegVal_IPPROTO_IGMP                 2        /**< Internet group management protocol */
#define w5500_RegVal_IPPROTO_GGP                  3        /**< Gateway^2 (deprecated) */
#define w5500_RegVal_IPPROTO_TCP                  6        /**< TCP */
#define w5500_RegVal_IPPROTO_PUP                  12       /**< PUP */
#define w5500_RegVal_IPPROTO_UDP                  17       /**< UDP */
#define w5500_RegVal_IPPROTO_IDP                  22       /**< XNS idp */
#define w5500_RegVal_IPPROTO_ND                   77       /**< UNOFFICIAL net disk protocol */
#define w5500_RegVal_IPPROTO_RAW                  255      /**< Raw IP packet */

/*********************************************************
* iinchip access function
*********************************************************/
void w5500_WriteByte( uint32_t addrbsb,  uint8_t data);
uint8_t w5500_READ(uint32_t addrbsb);
uint16_t w5500_WriteBuf(uint32_t addrbsb,uint8_t* buf,uint16_t_t len);
uint16_t w5500_ReadBuf(uint32_t addrbsb, uint8_t* buf,uint16_t len);


void w5500_Init(void); // reset iinchip
//void sysinit(uint8_t * tx_size, uint8_t * rx_size); // setting tx/rx buf size
// uint8_t getISR(uint8_t s);
// void putISR(uint8_t s, uint8_t val);
// uint16_t getIINCHIP_RxMAX(uint8_t s);
// uint16_t getIINCHIP_TxMAX(uint8_t s);
void w5500_Set_ModeReg(uint8_t val);
void w5500_Set_RetransmissionTime(uint16_t timeout); // set retry duration for data transmission, connection, closing ...
void w5500_Set_NumOfRetransmission(uint8_t retry); // set retry count (above the value, assert timeout interrupt)
void w5500_Clear_InterruptReg(uint8_t mask); // clear interrupt
uint8_t w5500_Get_InterruptReg( void );
void w5500_Set_SocketN_MaxSegmentSize(SOCKET s, uint16_t Sn_MSSR); // set maximum segment size
uint8_t w5500_Get_SocketN_InterruptStatus(SOCKET s); // get socket interrupt status
uint8_t w5500_Get_SocketN_SocketStatus(SOCKET s); // get socket status
uint16_t w5500_Get_SocketN_FreeTxBufSize(SOCKET s); // get socket TX free buf size
uint16_t w5500_Get_SocketN_RxBufSize(SOCKET s); // get socket RX recv buf size
uint8_t w5500_Get_SocketN_SocketStatus(SOCKET s);
void w5500_Set_SocketN_Time2Live(SOCKET s, uint8_t ttl);
void w5500_SendDataProc(SOCKET s, uint8_t *wizdata, uint16_t len);
void w5500_RecvDataProc(SOCKET s, uint8_t *wizdata, uint16_t len);

void w5500_SetGateWay(uint8_t * addr); // set gateway address
void w5500_GetGateWay(uint8_t* addr);


void w5500_SetSubnetMask(uint8_t * addr); // set subnet mask address
void w5500_SetMac(uint8_t * addr); // set local MAC address
void w5500_SetIP(uint8_t * addr); // set local IP address

void w5500_GetSubnetMask(uint8_t * addr);
void w5500_Get_Mac(uint8_t * addr);
void w5500_Get_IP(uint8_t * addr);

void w5500_Set_SocketN_InterruptReg(uint8_t s, uint8_t val);

void w5500_SetKeepalive(SOCKET s);
/**
 @brief WIZCHIP_OFFSET_INC on IINCHIP_READ/WRITE
 * case1.
 *  IINCHIP_WRITE(RTR0,val);
 *  IINCHIP_WRITE(RTR1,val);
 * case1. 
 *  IINCHIP_WRITE(RTR0,val);
 *  IINCHIP_WRITE(WIZCHIP_OFFSET_INC(RTR0,1)); 
 */
//#define w5500_RegVal_WIZCHIP_OFFSET_INC(ADDR, N)    (ADDR + (N<<8)) //< Increase offset address

#endif
