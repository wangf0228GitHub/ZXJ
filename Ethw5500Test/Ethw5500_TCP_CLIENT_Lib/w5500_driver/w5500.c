/*
 * (c)COPYRIGHT
 * ALL RIGHT RESERVED
 *
 * FileName : w5500.c
  * -----------------------------------------------------------------
 */
#include "w5500.h"
// #include "W5500\socket.h"

#ifdef __DEF_IINCHIP_PPP__
   #include "md5.h"
#endif

uint8_t w5500_Mac[6]={0x00,0x08,0xdc,0x11,0x11,0x11};/*定义Mac变量*/
uint8_t w5500_IP[4]={192,168,0,101};/*定义lp变量*/

uint8_t w5500_SubnetMask[4]={255,255,255,0};/*定义subnet变量*/
uint8_t w5500_GateWay[4]={192,168,0,1};/*定义gateway变量*/

// uint8_t pc_ip[4]={192,168,0,12};/*配置目标服务器的IP地址*/
// uint16 DESPORT=6000;


// static uint8_t I_STATUS[MAX_SOCK_NUM];
// static uint16_t SSIZE[MAX_SOCK_NUM]; /**< Max Tx buffer size by each channel */
// static uint16_t RSIZE[MAX_SOCK_NUM]; /**< Max Rx buffer size by each channel */
// 
// uint8_t getISR(uint8_t s)
// {
//   return I_STATUS[s];
// }
// void putISR(uint8_t s, uint8_t val)
// {
//    I_STATUS[s] = val;
// }
// 
// uint16_t getIINCHIP_RxMAX(uint8_t s)
// {
//    return RSIZE[s];
// }
// uint16_t getIINCHIP_TxMAX(uint8_t s)
// {
//    return SSIZE[s];
// }

void w5500_WriteByte( uint32_t addrbsb,  uint8_t data)
{
   w5500_ISR_DISABLE();                        // Interrupt Service Routine Disable
   w5500_CSoff();                              // CS=0, SPI start
   w5500_SPIProc( (addrbsb & 0x00FF0000)>>16);// Address byte 1
   w5500_SPIProc( (addrbsb & 0x0000FF00)>> 8);// Address byte 2
   w5500_SPIProc( (addrbsb & 0x000000F8) + 4);    // Data write command and Write data length 1
   w5500_SPIProc(data);                    // Data write (write 1byte data)
   w5500_CSon();                               // CS=1,  SPI end
   w5500_ISR_ENABLE();                         // Interrupt Service Routine Enable
}

uint8_t w5500_READ(uint32_t addrbsb)
{
   uint8_t data = 0;
   w5500_ISR_DISABLE();                        // Interrupt Service Routine Disable
   w5500_CSoff();                              // CS=0, SPI start
   w5500_SPIProc( (addrbsb & 0x00FF0000)>>16);// Address byte 1
   w5500_SPIProc( (addrbsb & 0x0000FF00)>> 8);// Address byte 2
   w5500_SPIProc( (addrbsb & 0x000000F8))    ;// Data read command and Read data length 1
   data = w5500_SPIProc(0x00);             // Data read (read 1byte data)
   w5500_CSon();                               // CS=1,  SPI end
   w5500_ISR_ENABLE();                         // Interrupt Service Routine Enable
   return data;    
}

uint16_t w5500_WriteBuf(uint32_t addrbsb,uint8_t* buf,uint16_t len)
{
   uint16_t idx = 0;
   if(len == 0) 
	   return 0;
	   //printf("Unexpected2 length 0\r\n");

   w5500_ISR_DISABLE();
   w5500_CSoff();                              // CS=0, SPI start
   w5500_SPIProc( (addrbsb & 0x00FF0000)>>16);// Address byte 1
   w5500_SPIProc( (addrbsb & 0x0000FF00)>> 8);// Address byte 2
   w5500_SPIProc( (addrbsb & 0x000000F8) + 4);    // Data write command and Write data length 1
   for(idx = 0; idx < len; idx++)                // Write data in loop
   {
     w5500_SPIProc(buf[idx]);
   }
   w5500_CSon();                               // CS=1, SPI end
   w5500_ISR_ENABLE();                         // Interrupt Service Routine Enable    

   return len;  
}

uint16_t w5500_ReadBuf(uint32_t addrbsb, uint8_t* buf,uint16_t len)
{
  uint16_t idx = 0;
  if(len == 0)
  {
	  return 0;
    //printf("Unexpected2 length 0\r\n");
  }

  w5500_ISR_DISABLE();
  //SPI MODE I/F
  w5500_CSoff();                                  // CS=0, SPI start
  w5500_SPIProc( (addrbsb & 0x00FF0000)>>16);// Address byte 1
  w5500_SPIProc( (addrbsb & 0x0000FF00)>> 8);// Address byte 2
  w5500_SPIProc( (addrbsb & 0x000000F8));    // Data write command and Write data length 1
  for(idx = 0; idx < len; idx++)                    // Write data in loop
  {
    buf[idx] = w5500_SPIProc(0x00);
  }
  w5500_CSon();                                   // CS=1, SPI end
  w5500_ISR_ENABLE();                             // Interrupt Service Routine Enable
  
  return len;
}


/**
@brief  This function is for resetting of the iinchip. Initializes the iinchip to work in whether DIRECT or INDIRECT mode
*/
void w5500_Init(void)
{
	w5500_WriteByte(w5500_Reg_MR,w5500_RegVal_MR_RST);
}

/**
@brief  This function set the transmit & receive buffer size as per the channels is used
Note for TMSR and RMSR bits are as follows\n
bit 1-0 : memory size of channel #0 \n
bit 3-2 : memory size of channel #1 \n
bit 5-4 : memory size of channel #2 \n
bit 7-6 : memory size of channel #3 \n
bit 9-8 : memory size of channel #4 \n
bit 11-10 : memory size of channel #5 \n
bit 12-12 : memory size of channel #6 \n
bit 15-14 : memory size of channel #7 \n
Maximum memory size for Tx, Rx in the W5500 is 16K Bytes,\n
In the range of 16KBytes, the memory size could be allocated dynamically by each channel.\n
Be attentive to sum of memory size shouldn't exceed 8Kbytes\n
and to data transmission and receiption from non-allocated channel may cause some problems.\n
If the 16KBytes memory is already  assigned to centain channel, \n
other 3 channels couldn't be used, for there's no available memory.\n
If two 4KBytes memory are assigned to two each channels, \n
other 2 channels couldn't be used, for there's no available memory.\n
*/
// void sysinit( uint8_t * tx_size, uint8_t * rx_size  )
// {
//   int16 i;
//   int16 ssum,rsum;
// #ifdef __DEF_IINCHIP_DBG__
//   printf("sysinit()\r\n");
// #endif
//   ssum = 0;
//   rsum = 0;
// 
//   for (i = 0 ; i < MAX_SOCK_NUM; i++)       // Set the size, masking and base address of Tx & Rx memory by each channel
//   {
//           w5500_WriteByte( (Sn_TXMEM_SIZE(i)), tx_size[i]);
//           w5500_WriteByte( (Sn_RXMEM_SIZE(i)), rx_size[i]);
//           
// #ifdef __DEF_IINCHIP_DBG__
//          printf("tx_size[%d]: %d, Sn_TXMEM_SIZE = %d\r\n",i, tx_size[i], w5500_READ(Sn_TXMEM_SIZE(i)));
//          printf("rx_size[%d]: %d, Sn_RXMEM_SIZE = %d\r\n",i, rx_size[i], w5500_READ(Sn_RXMEM_SIZE(i)));
// #endif
//     SSIZE[i] = (int16)(0);
//     RSIZE[i] = (int16)(0);
// 
// 
//     if (ssum <= 16384)
//     {
//          switch( tx_size[i] )
//       {
//       case 1:
//         SSIZE[i] = (int16)(1024);
//         break;
//       case 2:
//         SSIZE[i] = (int16)(2048);
//         break;
//       case 4:
//         SSIZE[i] = (int16)(4096);
//         break;
//       case 8:
//         SSIZE[i] = (int16)(8192);
//         break;
//       case 16:
//         SSIZE[i] = (int16)(16384);
//       break;
//       default :
//         RSIZE[i] = (int16)(2048);
//         break;
//       }
//     }
// 
//    if (rsum <= 16384)
//     {
//          switch( rx_size[i] )
//       {
//       case 1:
//         RSIZE[i] = (int16)(1024);
//         break;
//       case 2:
//         RSIZE[i] = (int16)(2048);
//         break;
//       case 4:
//         RSIZE[i] = (int16)(4096);
//         break;
//       case 8:
//         RSIZE[i] = (int16)(8192);
//         break;
//       case 16:
//         RSIZE[i] = (int16)(16384);
//         break;
//       default :
//         RSIZE[i] = (int16)(2048);
//         break;
//       }
//     }
//     ssum += SSIZE[i];
//     rsum += RSIZE[i];
// 
//   }
// }

// added

/**
@brief  This function sets up gateway IP address.
*/
void w5500_SetGateWay(uint8_t* addr)/**< a pointer to a 4 -byte array responsible to set the Gateway IP address. */  
{
    w5500_WriteBuf(w5500_Reg_GAR0, addr, 4);
}
void w5500_GetGateWay(uint8_t* addr)
{
    w5500_ReadBuf(w5500_Reg_GAR0, addr, 4);
}

/**
@brief  It sets up SubnetMask address
*/
void w5500_SetSubnetMask(uint8_t* pSubnetMask)
{   
    w5500_WriteBuf(w5500_Reg_SUBR0, pSubnetMask, 4);
}
/**
@brief  This function sets up MAC address.
*/
void w5500_SetMac(uint8_t* pMacAddr)  /**< a pointer to a 6 -byte array responsible to set the MAC address. */
{
  w5500_WriteBuf(w5500_Reg_SHAR0, pMacAddr, 6);  
}

/**
@brief  This function sets up Source IP address.
*/
void w5500_SetIP(uint8_t* pIPAddr)  /**< a pointer to a 4 -byte array responsible to set the Source IP address. */
{
    w5500_WriteBuf(w5500_Reg_SIPR0, pIPAddr, 4);  
}
void w5500_SetKeepalive(SOCKET s)
{
  //IINCHIP_WRITE( Sn_CR(0) , Sn_CR_SEND_KEEP );  
  w5500_WriteByte(w5500_Reg_SocketN_Keepalive(s),0x02);
}
/**
@brief  This function sets up Source IP address.
*/
// void getGAR(uint8_t * addr)
// {
//     w5500_ReadBuf(w5500_Reg_GAR0, addr, 4);
// }
void w5500_GetSubnetMask(uint8_t * addr)
{
    w5500_ReadBuf(w5500_Reg_SUBR0, addr, 4);
}
void w5500_Get_Mac(uint8_t * addr)
{
    w5500_ReadBuf(w5500_Reg_SHAR0, addr, 6);
}
void w5500_Get_IP(uint8_t * addr)
{
    w5500_ReadBuf(w5500_Reg_SIPR0, addr, 4);
}

void w5500_Set_ModeReg(uint8_t val)
{
	w5500_WriteByte(w5500_Reg_MR,val);
}

/**
@brief  This function gets Interrupt register in common register.
 */
uint8_t w5500_Get_InterruptReg( void )
{
   return w5500_READ(w5500_Reg_IR);
}

/**
@brief  This function sets up Retransmission time.

If there is no response from the peer or delay in response then retransmission
will be there as per RTR (Retry Time-value Register)setting
*/
void w5500_Set_RetransmissionTime(uint16_t timeout)
{
  w5500_WriteByte(w5500_Reg_RTR0,(uint8_t)((timeout & 0xff00) >> 8));
  w5500_WriteByte(w5500_Reg_RTR1,(uint8_t)(timeout & 0x00ff));
}

/**
@brief  This function set the number of Retransmission.

If there is no response from the peer or delay in response then recorded time
as per RTR & RCR register seeting then time out will occur.
*/
void w5500_Set_NumOfRetransmission(uint8_t retry)
{
  w5500_WriteByte(w5500_Reg__RCR,retry);
}

/**
@brief  This function set the interrupt mask Enable/Disable appropriate Interrupt. ('1' : interrupt enable)

If any bit in IMR is set as '0' then there is not interrupt signal though the bit is
set in IR register.
*/
void w5500_Clear_InterruptReg(uint8_t mask)
{
  w5500_WriteByte(w5500_Reg_IR, ~mask | w5500_Get_InterruptReg() ); // must be setted 0x10.
}

/**
@brief  This sets the maximum segment size of TCP in Active Mode), while in Passive Mode this is set by peer
*/
void w5500_Set_SocketN_MaxSegmentSize(SOCKET s, uint16_t Sn_MSSR)
{
  w5500_WriteByte( Sn_MSSR0(s), (uint8_t)((Sn_MSSR & 0xff00) >> 8));
  w5500_WriteByte( Sn_MSSR1(s), (uint8_t)(Sn_MSSR & 0x00ff));
}
//生存时间
void w5500_Set_SocketN_Time2Live(SOCKET s, uint8_t ttl)
{    
   w5500_WriteByte( Sn_TTL(s) , ttl);
}



/**
@brief  get socket interrupt status

These below functions are used to read the Interrupt & Soket Status register
*/
uint8_t w5500_Get_SocketN_InterruptStatus(SOCKET s)
{
   return w5500_READ(w5500_Reg_Sn_IR(s));
}


/**
@brief   get socket status
*/
uint8_t w5500_Get_SocketN_SocketStatus(SOCKET s)
{
   return w5500_READ(Sn_SR(s));
}


/**
@brief  get socket TX free buf size

This gives free buffer size of transmit buffer. This is the data size that user can transmit.
User shuold check this value first and control the size of transmitting data
*/
uint16_t w5500_Get_SocketN_FreeTxBufSize(SOCKET s)
{
  uint16_t val=0,val1=0;
  do
  {
    val1 = w5500_READ(w5500_Reg_Sn_TX_FSR0(s));
    val1 = (val1 << 8) + w5500_READ(w5500_Reg_Sn_TX_FSR1(s));
      if (val1 != 0)
    {
        val = w5500_READ(w5500_Reg_Sn_TX_FSR0(s));
        val = (val << 8) + w5500_READ(w5500_Reg_Sn_TX_FSR1(s));
    }
  } while (val != val1);
   return val;
}


/**
@brief   get socket RX recv buf size

This gives size of received data in receive buffer.
*/
uint16_t w5500_Get_SocketN_RxBufSize(SOCKET s)
{
  uint16_t val=0,val1=0;
  do
  {
    val1 = w5500_READ(w5500_Reg_Sn_RX_RSR0(s));
    val1 = (val1 << 8) + w5500_READ(w5500_Reg_Sn_RX_RSR1(s));
    if(val1 != 0)
    {
        val = w5500_READ(w5500_Reg_Sn_RX_RSR0(s));
        val = (val << 8) + w5500_READ(w5500_Reg_Sn_RX_RSR1(s));
    }
  } while (val != val1);
   return val;
}


/**
@brief   This function is being called by send() and sendto() function also.

This function read the Tx write pointer register and after copy the data in buffer update the Tx write pointer
register. User should read upper byte first and lower byte later to get proper value.
*/
void w5500_SendDataProc(SOCKET s, uint8_t *data, uint16_t len)
{
	uint16_t ptr = 0;
  uint32_t addrbsb = 0;
	
  if(len == 0)
  {
    //printf("CH: %d Unexpected1 length 0\r\n", s);
    return;
  }


  ptr = w5500_READ( w5500_Reg_Sn_TX_WR0(s) );
  ptr = ((ptr & 0x00ff) << 8) + w5500_READ(w5500_Reg_Sn_TX_WR1(s));

  addrbsb = (uint32_t)(ptr<<8) + (s<<5) + 0x10;
  w5500_WriteBuf(addrbsb, data, len);
  
  ptr += len;
  w5500_WriteByte( w5500_Reg_Sn_TX_WR0(s) ,(uint8_t)((ptr & 0xff00) >> 8));
  w5500_WriteByte( w5500_Reg_Sn_TX_WR1(s),(uint8_t)(ptr & 0x00ff));
}


/**
@brief  This function is being called by recv() also.

This function read the Rx read pointer register
and after copy the data from receive buffer update the Rx write pointer register.
User should read upper byte first and lower byte later to get proper value.
*/
void w5500_RecvDataProc(SOCKET s, uint8_t *data, uint16_t len)
{
  uint16_t ptr = 0;
  uint32_t addrbsb = 0;
  
  if(len == 0)
  {
    //printf("CH: %d Unexpected2 length 0\r\n", s);
    return;
  }

  ptr = w5500_READ( w5500_Reg_Sn_RX_RD0(s) );
  ptr = ((ptr & 0x00ff) << 8) + w5500_READ( w5500_Reg_Sn_RX_RD1(s) );

  addrbsb = (uint32_t)(ptr<<8) + (s<<5) + 0x18;
  w5500_ReadBuf(addrbsb, data, len);
  ptr += len;

  w5500_WriteByte( w5500_Reg_Sn_RX_RD0(s), (uint8_t)((ptr & 0xff00) >> 8));
  w5500_WriteByte( w5500_Reg_Sn_RX_RD1(s), (uint8_t)(ptr & 0x00ff));
}

void w5500_Set_SocketN_InterruptReg(uint8_t s, uint8_t val)
{
    w5500_WriteByte(w5500_Reg_Sn_IR(s), val);
}




