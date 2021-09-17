/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usbd_bulk_if.c
  * @version        : v1.0_Cube
  * @brief          : Usb device bulk example.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "usbd_bulk_if.h"

/* USER CODE BEGIN INCLUDE */

/* USER CODE END INCLUDE */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @brief Usb device library.
  * @{
  */

/** @addtogroup USBD_BULK_IF
  * @{
  */

/** @defgroup USBD_BULK_IF_Private_TypesDefinitions USBD_BULK_IF_Private_TypesDefinitions
  * @brief Private types.
  * @{
  */

/* USER CODE BEGIN PRIVATE_TYPES */

/* USER CODE END PRIVATE_TYPES */

/**
  * @}
  */

/** @defgroup USBD_BULK_IF_Private_Defines USBD_BULK_IF_Private_Defines
  * @brief Private defines.
  * @{
  */

/* USER CODE BEGIN PRIVATE_DEFINES */
/* USER CODE END PRIVATE_DEFINES */

/**
  * @}
  */

/** @defgroup USBD_BULK_IF_Private_Macros USBD_BULK_IF_Private_Macros
  * @brief Private macros.
  * @{
  */

/* USER CODE BEGIN PRIVATE_MACRO */

/* USER CODE END PRIVATE_MACRO */

/**
  * @}
  */

/** @defgroup USBD_BULK_IF_Private_Variables USBD_BULK_IF_Private_Variables
  * @brief Private variables.
  * @{
  */
/* Create buffer for reception and transmission           */
/* It's up to user to redefine and/or remove those define */
/** Received data over USB are stored in this buffer      */
#define APP_RX_DATA_SIZE  64
extern int8_t Receive_FS(uint8_t* Buf,uint32_t *Len);

/** Data to send over USB BULK are stored in this buffer   */
static uint8_t UserRxBufferFS[APP_RX_DATA_SIZE];

USBD_HandleTypeDef  *hUsbDevice_0;
/* USER CODE END PRIVATE_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_BULK_IF_Exported_Variables USBD_BULK_IF_Exported_Variables
  * @brief Public variables.
  * @{
  */

extern USBD_HandleTypeDef hUsbDeviceFS;

/* USER CODE BEGIN EXPORTED_VARIABLES */

/* USER CODE END EXPORTED_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_BULK_IF_Private_FunctionPrototypes USBD_BULK_IF_Private_FunctionPrototypes
  * @brief Private functions declaration.
  * @{
  */

static int8_t BULK_Init_FS    (void);
static int8_t BULK_DeInit_FS  (void);
static int8_t BULK_Control_FS (uint8_t cmd, uint8_t* pbuf, uint16_t length);
static int8_t BULK_Receive_FS (uint8_t* Buf, uint32_t *Len);

/* USER CODE BEGIN PRIVATE_FUNCTIONS_DECLARATION */

/* USER CODE END PRIVATE_FUNCTIONS_DECLARATION */

/**
  * @}
  */

USBD_BULK_ItfTypeDef USBD_Interface_fops_FS = 
{
  BULK_Init_FS,
  BULK_DeInit_FS,
  BULK_Receive_FS
};

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Initializes the BULK media low layer over the FS USB IP
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t BULK_Init_FS(void)
{
  hUsbDevice_0 = &hUsbDeviceFS;
  // here's where the input buffer gets set to kick off 
  // the receiver
  USBD_BULK_SetRxBuffer(hUsbDevice_0,UserRxBufferFS);
  HAL_GPIO_WritePin(GPIOE,LED_GPIO_Port,1);
  return (USBD_OK);
}

static int8_t BULK_DeInit_FS(void)
{
  HAL_GPIO_WritePin(GPIOE,LED_GPIO_Port,0);
  hUsbDevice_0=NULL;
/**
  * @brief  Manage the BULK class requests
  * @param  cmd: Command code
  * @param  pbuf: Buffer containing command data (request parameters)
  * @param  length: Number of data to be sent (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
  return (USBD_OK);
  /* USER CODE END 5 */
}

/**
  * @brief  Data received over USB OUT endpoint are sent over BULK interface
  *         through this function.
  *
  *         @note
  *         This function will issue a NAK packet on any OUT packet received on
  *         USB endpoint until exiting this function. If you exit this function
  *         before transfer is complete on CDC interface (ie. using DMA controller)
  *         it will result in receiving more data while previous ones are still
  *         not sent.
  *
  * @param  Buf: Buffer of data to be received
  * @param  Len: Number of data received (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t BULK_Receive_FS (uint8_t* Buf, uint32_t *Len)
{
  return Receive_FS(Buf, Len);
}

/**
  * @brief  BULK_Transmit_FS
  *         Data to send over USB IN endpoint are sent over BULK interface
  *         through this function.
  *         @note
  *
  *
  * @param  Buf: Buffer of data to be sent
  * @param  Len: Number of data to be sent (in bytes)
  * @retval USBD_OK if all operations are OK else USBD_FAIL or USBD_BUSY
  */
uint8_t BULK_Transmit_FS(uint8_t* Buf, uint16_t Len)
{
  uint8_t result = USBD_OK;
  USBD_BULK_HandleTypeDef *hcdc;
  hcdc = (USBD_BULK_HandleTypeDef*)hUsbDevice_0->pClassData;
  
  if (hUsbDevice_0 == NULL)
    return -1;

  USBD_BULK_SetTxBuffer(hUsbDevice_0, Buf, Len);
  if ((result = USBD_BULK_TransmitPacket(hUsbDevice_0) != USBD_OK))
    return result;

  // blocking transmit -- need to wait until transmit is complete
  // move this up to stlink level

  while (((volatile uint32_t) hcdc->TxState)) {}
  return result;
}

/* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */

/* USER CODE END PRIVATE_FUNCTIONS_IMPLEMENTATION */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
