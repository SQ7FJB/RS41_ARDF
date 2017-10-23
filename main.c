// STM32F100 and SI4032 RTTY transmitter
// released under GPL v.2 by anonymous developer
// enjoy and have a nice day
// ver 1.5a
#include <stm32f10x_gpio.h>
#include <stm32f10x_tim.h>
#include <stm32f10x_spi.h>
#include <stm32f10x_tim.h>
#include <stm32f10x_usart.h>
#include <stm32f10x_adc.h>
#include <stm32f10x_rcc.h>
#include "stdlib.h"
#include <stdio.h>
#include <string.h>
#include <misc.h>
#include "f_rtty.h"
#include "fun.h"
#include "init.h"
#include "config.h"
#include "radio.h"
#include "ublox.h"
#include "delay.h"
#include "aprs.h"
#include "morse.h"
///////////////////////////// test mode /////////////
const unsigned char test = 0; // 0 - normal, 1 - short frame only cunter, height, flag
char callsign[15] = {CALLSIGN};

//unsigned char aprs_tab[30]={0,6,7,8,9,1,10,11,12,13,2,6,7,8,9,3,10,11,12,13,4,6,7,8,9,5,10,11,12,13};
unsigned char aprs_tab[30]=  {0,6,7,8,9,1,10,11,12,13,2,14,15,16,17,3,6,7,8,9,4,10,11,12,13,5,14,15,16,17};
#define GREEN  GPIO_Pin_7
#define RED  GPIO_Pin_8
#define OFF	GPIO_Pin_12

unsigned int send_cun;        //frame counter
char status[2] = {'N'};
int napiecie;

volatile char flaga = 0;//((((tx_delay / 1000) & 0x0f) << 3) | Smoc);
uint16_t CRC_rtty = 0x12ab;  //checksum
char buf_rtty[200];
char menu[] = "$$$$$$STM32 RTTY tracker by Blasiu, enjoy and see you on the HUB... \n\r";
char init_trx[] = "\n\rPowering up TX\n\r";
volatile unsigned char pun = 0;
volatile unsigned int cun = 10;
unsigned char dev = 0;
volatile unsigned char tx_on = 0;
volatile unsigned int tx_on_delay;
volatile unsigned char tx_enable = 0;
rttyStates send_rtty_status = rttyZero;
volatile char *rtty_buf;
volatile uint16_t button_pressed = 0;
int Button=0;
volatile uint8_t disable_armed = 0;
volatile uint8_t Key_ok = 0;
unsigned char cun_off = 0;
unsigned char cun_rtty=0;
unsigned char changePin = 0;
unsigned char sendCW=0;
unsigned char sendAPRS = 0;
unsigned char timeAPRS = 0;

unsigned int time1s	=0	;
unsigned char b_time1s = 0;
unsigned char time1stoggle=1;
unsigned char time1m = 59;
unsigned char timeCycle = 0;
//                         -------------      --------------           --------------      --------------      --------------           -----
unsigned char *wsk_morse_tab =morse_tab;



/**
 * GPS data processing
 */
void USART1_IRQHandler(void) {
  if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
    ublox_handle_incoming_byte((uint8_t) USART_ReceiveData(USART1));
  }else if (USART_GetITStatus(USART1, USART_IT_ORE) != RESET) {
    USART_ReceiveData(USART1);
  } else {
    USART_ReceiveData(USART1);
  }
}

void TIM2_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    if (aprs_is_active()){
          aprs_timer_handler();
        } else {


    if (++tx_on_delay >= 300)
    {
    	tx_on_delay = 0;
    					if (*(wsk_morse_tab) != 0x00)
    					{
    						if (*(wsk_morse_tab++) == 0xff)
    						{
    		    			  GPIO_ResetBits(GPIOB, GREEN);
    		    			  pun =1;
    		    			  //GPIO_SetBits(GPIOB, radioSDIpin);
    		    			  if (sendCW)
    		    				  {
    		    				  //spi_init();
    		    				  //radio_enable_tx();
    		    				  //spi_deinit();
    		    				  }
    		    			}
    		    		else
    		    			{
    		    			GPIO_SetBits(GPIOB, GREEN);

    		    			pun = 0;
    		    			if (sendCW)
    		    				{
    		    				//spi_init();
    		    				//radio_disable_tx();
    		    				//spi_deinit();
    		    				}

    		    			}
    					}
    					else
    					{
    					wsk_morse_tab = morse_tab;

    					}

    }

     /* if (!tx_on && ++cun_rtty == 2)
      	  {*/
    	  tx_enable = 1;
    	  if (pun && sendCW) {


    	  			  if (changePin)
    	  			  {
    	  				changePin=0;
    	  				GPIO_SetBits(GPIOB, radioSDIpin);
    	  			  }
    	  			  else
    	  			  {
    	  				changePin = 1;
    	  			    GPIO_ResetBits(GPIOB, radioSDIpin);
    	  			  }
    	  	  }
    	  /*cun_rtty=0;
      	  }*/
  }
	if (++time1s >= 1250)  //2500 - 1s
  		{
		if (++timeAPRS >=10)
			{
			//sendAPRS = 1;
			timeAPRS =0;
			}
			time1s = 0;
			b_time1s = 1;






  	  	  if (ALLOW_DISABLE_BY_BUTTON && Key_ok)
  	  	  {


  	  		if ((ADCVal[1]- Button ) >= 200)
  	  					{
  	  					if (++button_pressed >= 3)
  	  						{
  	  						disable_armed = 1;
  	  						GPIO_SetBits(GPIOB, RED);
  	  					    GPIO_SetBits(GPIOB, GREEN);
  	  					    button_pressed = 2;
  	  						}
  	  					}
  	  				else
  	  					{
  	  					Button = ADCVal[1];
  	  				  	button_pressed = 0;
  	  					if (disable_armed)
  	  						{
  	  					    disable_armed = 1;
  	  				        GPIO_SetBits(GPIOA, GPIO_Pin_12);
  	  				        }

  	  					}
  	  	   }
  		}
  }
 }


int main(void) {
#ifdef DEBUG
  debug();
#endif
  RCC_Conf();
  NVIC_Conf();
  init_port();
  //init_usart_debug();
   delay_init();
  ublox_init();
  init_timer(RTTY_SPEED);
  GPIO_SetBits(GPIOB, RED);
  USART_SendData(USART3, 0xc);
  sprintf(buf_rtty, "init ON\n\r");
  print(buf_rtty);
  radio_rw_register(0x02, 0xff, 0);

  radio_rw_register(0x03, 0xff, 0);
  radio_rw_register(0x04, 0xff, 0);
  radio_soft_reset();
  // programowanie czestotliwosci nadawania
  radio_set_tx_frequency(RTTY_FREQUENCY);

  // Programowanie mocy nadajnika
  radio_rw_register(0x6D, 00 | (Smoc & 0x0007), 1);

  radio_rw_register(0x71, 0x00, 1);
  //radio_rw_register(0x87, 0x08, 0);
  radio_rw_register(0x02, 0xff, 0);
  radio_rw_register(0x75, 0xff, 0);
  radio_rw_register(0x76, 0xff, 0);
  radio_rw_register(0x77, 0xff, 0);
  radio_rw_register(0x12, 0x20, 1);
  radio_rw_register(0x13, 0x00, 1);
  radio_rw_register(0x12, 0x00, 1);
  radio_rw_register(0x0f, 0x80, 1);
  rtty_buf = buf_rtty;
  tx_on = 0;
  tx_enable = 1;

  aprs_init();
  //radio_enable_tx();
  Button =ADCVal[1];
  uint8_t rtty_before_aprs_left = RTTY_TO_APRS_RATIO;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

  //radio_set_tx_frequency(APRS_FREQUENCY);
  GPIO_SetBits(GPIOC, radioNSELpin);
  radio_rw_register(0x71, 0b00010010, 1);
  //radio_rw_register(0x72, 5, 1);
  spi_deinit();


  //Button = ADCVal[1];
  //tx_on_delay = tx_delay / (1000/RTTY_SPEED);//2500;
  tx_on = 0;
  GPSEntry gpsData;
  sprintf(buf_rtty, "APRS init\n\r\0");
  print(buf_rtty);
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

  while(1) {

	  	  Key_ok = 1;
		  if (b_time1s)
		  {
			  ublox_get_last_data(&gpsData);
			  sprintf(buf_rtty, "t=%02u:%02u.%02u:butt:%04u:sendAPRS:%01u:sendCW:%01u\n\r", gpsData.hours, gpsData.minutes, gpsData.seconds,ADCVal[1],sendAPRS,sendCW);
			  print(buf_rtty);
			  b_time1s = 0;
			  // synchro z GPSu
			  			if (((gpsData.minutes % No_Fox) == Fox) || Fox == 5)
			  			{
			  						if (!sendCW)
			  							{
			  							GPIO_ResetBits(GPIOB,RED);
			  							wsk_morse_tab = morse_tab;
			  				  			spi_init();
			  				  			GPIO_SetBits(GPIOC, radioNSELpin);
			  				  			//radio_set_tx_frequency(ACW_FREQUENCY);
			  				  			radio_rw_register(0x71, 0b00010010, 1);
			  				  		  	if (Fox == 5)
			  				  		  	{
			  				  		  	radio_set_tx_frequency(ACW_MO_FREQUENCY);
			  				  		  	}
			  				  		  	else {
										radio_set_tx_frequency(ACW_FREQUENCY);
			  				  		  	}
			  				  			radio_rw_register(0x72, 5, 1);
			  				  			radio_enable_tx();
			  				  			spi_deinit();
			  				  			sendCW = 1;
			  							}
			  			}
			  			else
			  			{
			  							GPIO_SetBits(GPIOB,RED);
			  							spi_init();
			  							radio_disable_tx();
			  							spi_deinit();
			  							sendCW = 0;

			  			}
			  	    //
		   if ((aprs_tab[gpsData.seconds >> 1]== Fox) && !sendCW)
			   {
			   if (!sendAPRS)
				   {
				   sendAPRS = 1;
				   sprintf(buf_rtty, "APRS ON\n\r");
				   print(buf_rtty);

				 	 //sendAPRS = 0;
						  	  	 spi_init();
						  	  	radio_rw_register(0x72, 10, 1);
						         radio_enable_tx();
						         //spi_deinit();
						         //GPSEntry gpsData;
						         ublox_get_last_data(&gpsData);
						         USART_Cmd(USART1, DISABLE);
						         GPIO_SetBits(GPIOC, radioNSELpin);
						         aprs_send_position(gpsData,1,napiecie);
						         USART_Cmd(USART1, ENABLE);
						         spi_init();
						         radio_disable_tx();
						         spi_deinit();
				   }
			   else
			   	   {
				   sprintf(buf_rtty, "APRS OFF\n\r");
				   				   print(buf_rtty);
			   	   }
			   }
		   else
		   	   {
			   sendAPRS = 0;

		   	   }
		  }
		  else {
		    	      NVIC_SystemLPConfig(NVIC_LP_SEVONPEND, DISABLE);
		    	      __WFI();
		    	    }


  	 }

#pragma clang diagnostic pop
}

void send_rtty_packet() {
  start_bits = RTTY_PRE_START_BITS;
   int8_t temperatura = 0; // RWU radio_read_temperature();

  napiecie = srednia(ADCVal[0] * 600 / 4096);
  GPSEntry gpsData;
  ublox_get_last_data(&gpsData);
  if (gpsData.fix >= 3) {
        flaga |= 0x80;
      } else {
        flaga &= ~0x80;
      }
  uint8_t lat_d = (uint8_t) abs(gpsData.lat_raw / 10000000);
  uint32_t lat_fl = (uint32_t) abs(abs(gpsData.lat_raw) - lat_d * 10000000) / 100;
  uint8_t lon_d = (uint8_t) abs(gpsData.lon_raw / 10000000);
  uint32_t lon_fl = (uint32_t) abs(abs(gpsData.lon_raw) - lon_d * 10000000) / 100;

  sprintf(buf_rtty, "$$$$%s,%d,%02u%02u%02u,%s%d.%05ld,%s%d.%05ld,%ld,%d,%d,%d,%d,%d,%02x", callsign, send_cun,
              gpsData.hours, gpsData.minutes, gpsData.seconds,
              gpsData.lat_raw < 0 ? "-" : "", lat_d, lat_fl,
              gpsData.lon_raw < 0 ? "-" : "", lon_d, lon_fl,
              (gpsData.alt_raw / 1000), temperatura, napiecie, gpsData.sats_raw,
              gpsData.ok_packets, gpsData.bad_packets,
              flaga);
  CRC_rtty = 0xffff;                                              //napiecie      flaga
  CRC_rtty = gps_CRC16_checksum(buf_rtty + 4);
  sprintf(buf_rtty, "%s*%04X\n", buf_rtty, CRC_rtty & 0xffff);
  rtty_buf = buf_rtty;
  //RWU radio_enable_tx();
  //RWU tx_on = 1;
 print(buf_rtty);
  send_cun++;
}

#ifdef  DEBUG
void assert_failed(uint8_t* file, uint32_t line)
{
    while (1);
}
#endif
