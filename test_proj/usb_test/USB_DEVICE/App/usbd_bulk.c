/**
  ******************************************************************************
  * @file    usbd_bulk.c
  * @author  MCD Application Team
  * @brief   This file provides the high layer firmware functions to manage the
  *          following functionalities of the USB CDC Class:
  *           - Initialization and Configuration of high and low layer
  *           - Enumeration as CDC Device (and enumeration for each implemented memory interface)
  *           - OUT/IN data transfer
  *           - Command IN transfer (class requests management)
  *           - Error management
  *
  *  @verbatim
  *
  *          ===================================================================
  *                                CDC Class Driver Description
  *          ===================================================================
  *           This driver manages the "Universal Serial Bus Class Definitions for Communications Devices
  *           Revision 1.2 November 16, 2007" and the sub-protocol specification of "Universal Serial Bus
  *           Communications Class Subclass Specification for PSTN Devices Revision 1.2 February 9, 2007"
  *           This driver implements the following aspects of the specification:
  *             - Device descriptor management
  *             - Configuration descriptor management
  *             - Enumeration as CDC device with 2 data endpoints (IN and OUT) and 1 command endpoint (IN)
  *             - Requests management (as described in section 6.2 in specification)
  *             - Abstract Control Model compliant
  *             - Union Functional collection (using 1 IN endpoint for control)
  *             - Data interface class
  *
  *           These aspects may be enriched or modified for a specific user application.
  *
  *            This driver doesn't implement the following aspects of the specification
  *            (but it is possible to manage these features with some modifications on this driver):
  *             - Any class-specific aspect relative to communication classes should be managed by user application.
  *             - All communication classes other than PSTN are not managed
  *
  *  @endverbatim
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2015 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                      www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* BSPDependencies
- "stm32xxxxx_{eval}{discovery}{nucleo_144}.c"
- "stm32xxxxx_{eval}{discovery}_io.c"
EndBSPDependencies */

/* Includes ------------------------------------------------------------------*/
#include "usbd_bulk.h"
#include "usbd_ctlreq.h"


/** @addtogroup STM32_USB_DEVICE_LIBRARY
  * @{
  */


/** @defgroup USBD_BULK
  * @brief usbd core module
  * @{
  */

/** @defgroup USBD_BULK_Private_TypesDefinitions
  * @{
  */
/**
  * @}
  */


/** @defgroup USBD_BULK_Private_Defines
  * @{
  */
/**
  * @}
  */


/** @defgroup USBD_BULK_Private_Macros
  * @{
  */

/**
  * @}
  */


/** @defgroup USBD_BULK_Private_FunctionPrototypes
  * @{
  */
static uint8_t USBD_BULK_Init(USBD_HandleTypeDef *pdev, uint8_t cfgidx);
static uint8_t USBD_BULK_DeInit(USBD_HandleTypeDef *pdev, uint8_t cfgidx);
static uint8_t USBD_BULK_Setup(USBD_HandleTypeDef *pdev, USBD_SetupReqTypedef *req);
static uint8_t USBD_BULK_DataIn(USBD_HandleTypeDef *pdev, uint8_t epnum);
static uint8_t USBD_BULK_DataOut(USBD_HandleTypeDef *pdev, uint8_t epnum);
static uint8_t USBD_BULK_EP0_RxReady(USBD_HandleTypeDef *pdev);

static uint8_t *USBD_BULK_GetFSCfgDesc(uint16_t *length);
//static uint8_t *USBD_BULK_GetHSCfgDesc(uint16_t *length);
//static uint8_t *USBD_BULK_GetOtherSpeedCfgDesc(uint16_t *length);
//static uint8_t *USBD_BULK_GetOtherSpeedCfgDesc(uint16_t *length);
uint8_t *USBD_BULK_GetDeviceQualifierDescriptor(uint16_t *length);
/* USB BULK device Configuration Descriptor */
/* should be const but annoying ST library discards const */
/**
  * @}
  */

/** @defgroup USBD_BULK_Private_Variables
  * @{
  */


/* BULK interface class callbacks structure */
USBD_ClassTypeDef  USBD_BULK = 
{
  USBD_BULK_Init,
  USBD_BULK_DeInit,
  USBD_BULK_Setup,
  NULL,                 /* EP0_TxSent, */
  USBD_BULK_EP0_RxReady,
  USBD_BULK_DataIn,
  USBD_BULK_DataOut,
  NULL,
  NULL,
  NULL,
  USBD_BULK_GetFSCfgDesc,  
  USBD_BULK_GetFSCfgDesc,    
  USBD_BULK_GetFSCfgDesc, 
  NULL,
};

/* USB BULK device Configuration Descriptor */
__ALIGN_BEGIN static uint8_t USBD_BULK_CfgFSDesc[USB_BULK_CONFIG_DESC_SIZ] __ALIGN_END =
{
  /* Configuration Descriptor */
  0x09,                                       /* bLength: Configuration Descriptor size */
  USB_DESC_TYPE_CONFIGURATION,                /* bDescriptorType: Configuration */
  USB_BULK_CONFIG_DESC_SIZ,            /* wTotalLength:no of returned bytes */
  0x00,
  0x01,                               /* bNumInterfaces: 1 interface */
  0x01,                               /* bConfigurationValue:  e   */
  0x00,                               /* Index of string descriptor */
  0xC0,                               /* bmAttributes: self powered */
  0x32,                               /* MaxPower 50x2 mA */
  
  /*---------------------------------------------------------------------------*/
  
  /*Interface Descriptor */
  0x09,                               /* bLength: Interface Descriptor size */
  USB_DESC_TYPE_INTERFACE,            /* bDescriptorType: Interface */
  0x00,                               /* bInterfaceNumber: Number of Interface */
  0x00,                               /* bAlternateSetting: Alternate setting  */
  0x02,                               /* bNumEndpoints: two endpoints used     */
  0xFF,                               /* bInterfaceClass: Vendor Specific      */
  0x00,                               /* bInterfaceSubClass:                   */
  0x00,                               /* bInterfaceProtocol:                   */
  0x00,                               /* iInterface:                           */
  
  /*Endpoint OUT Descriptor*/
  0x07,                               /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,             /* bDescriptorType: Endpoint */
  BULK_OUT_EP,                         /* bEndpointAddress */
  0x02,                               /* bmAttributes: Bulk */
  LOBYTE(BULK_DATA_FS_MAX_PACKET_SIZE),/* wMaxPacketSize: */
  HIBYTE(BULK_DATA_FS_MAX_PACKET_SIZE),
  0x00,                               /* bInterval: ignore for Bulk transfer */
  
  /*Endpoint IN Descriptor*/
  0x07,                               /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,             /* bDescriptorType: Endpoint */
  BULK_IN_EP,                          /* bEndpointAddress */
  0x02,                               /* bmAttributes: Bulk */
  LOBYTE(BULK_DATA_FS_MAX_PACKET_SIZE),/* wMaxPacketSize: */
  HIBYTE(BULK_DATA_FS_MAX_PACKET_SIZE),
  0x00                                /* bInterval: ignore for Bulk transfer */
} ;

/**
  * @}
  */

/** @defgroup USBD_BULK_Private_Functions
  * @{
  */

/**
  * @brief  USBD_BULK_Init
  *         Initialize the BULK interface
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
static uint8_t USBD_BULK_Init (USBD_HandleTypeDef *pdev, uint8_t cfgidx)
{
  uint8_t ret = 0;
  USBD_BULK_HandleTypeDef   *hcdc;
  
  {
    /* Open EP IN */
    USBD_LL_OpenEP(pdev, BULK_IN_EP, USBD_EP_TYPE_BULK,
                   BULK_DATA_FS_IN_PACKET_SIZE);
    
    /* Open EP OUT */
    USBD_LL_OpenEP(pdev, BULK_OUT_EP, USBD_EP_TYPE_BULK,
                   BULK_DATA_FS_OUT_PACKET_SIZE);
  }

  pdev->pClassData = USBD_malloc(sizeof (USBD_BULK_HandleTypeDef));
  
  if(pdev->pClassData == NULL)
  {
    ret = 1; 
  }
  else
  {
    hcdc = (USBD_BULK_HandleTypeDef*) pdev->pClassData;
    
    /* Init  physical Interface components */

    ((USBD_BULK_ItfTypeDef *)pdev->pUserData)->Init();
    
    /* Init Xfer states */

    hcdc->TxState =0;
    hcdc->RxState =0;
       
      /* Prepare Out endpoint to receive next packet */

    USBD_LL_PrepareReceive(pdev,
			   BULK_OUT_EP,
			   hcdc->RxBuffer,
			   BULK_DATA_FS_OUT_PACKET_SIZE);
  }
  return ret;
}

/**
  * @brief  USBD_BULK_Init
  *         DeInitialize the BULK layer
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
static uint8_t  USBD_BULK_DeInit (USBD_HandleTypeDef *pdev, uint8_t cfgidx)
{
  UNUSED(cfgidx);

  /* Close EP IN */
  (void)USBD_LL_CloseEP(pdev,BULK_IN_EP);
  pdev->ep_in[BULK_IN_EP & 0xFU].is_used = 0U;
  
  /* Close EP OUT */
  USBD_LL_CloseEP(pdev, BULK_OUT_EP);
  
  /* DeInit  physical Interface components */
  if(pdev->pClassData != NULL)
  {
    ((USBD_BULK_ItfTypeDef *)pdev->pUserData)->DeInit();
    (void)USBD_free(pdev->pClassData);
    pdev->pClassData = NULL;
  }

  return (uint8_t)USBD_OK;
}

/**
  * @brief  USBD_BULK_Setup
  *         Handle the BULK specific requests
  * @param  pdev: instance
  * @param  req: usb requests
  * @retval status
  */
static uint8_t  USBD_BULK_Setup (USBD_HandleTypeDef *pdev, 
                                USBD_SetupReqTypedef *req)
{
  static uint8_t ifalt = 0;
    
  switch (req->bmRequest & USB_REQ_TYPE_MASK)
  {
  case USB_REQ_TYPE_STANDARD:
    switch (req->bRequest)
    {      
    case USB_REQ_GET_INTERFACE :
      USBD_CtlSendData (pdev,
                        &ifalt,
                        1);
      break;
      
    case USB_REQ_SET_INTERFACE :
      break;
    }
 
  default: 
    break;
  }
  return USBD_OK;
}

/**
  * @brief  USBD_BULK_DataIn
  *         Data sent on non-control IN endpoint
  * @param  pdev: device instance
  * @param  epnum: endpoint number
  * @retval status
  */
static uint8_t  USBD_BULK_DataIn (USBD_HandleTypeDef *pdev, uint8_t epnum)
{
  USBD_BULK_HandleTypeDef   *hcdc = (USBD_BULK_HandleTypeDef*) pdev->pClassData;
  
  if(pdev->pClassData != NULL)
  {
    
    hcdc->TxState = 0;

    return USBD_OK;
  }
  else
  {
    return USBD_FAIL;
  }
}

/**
  * @brief  USBD_BULK_DataOut
  *         Data received on non-control Out endpoint
  * @param  pdev: device instance
  * @param  epnum: endpoint number
  * @retval status
  */
static uint8_t  USBD_BULK_DataOut (USBD_HandleTypeDef *pdev, uint8_t epnum)
{
  USBD_BULK_HandleTypeDef   *hcdc = (USBD_BULK_HandleTypeDef*) pdev->pClassData;

  if (pdev->pClassData == NULL)
  {
    return (uint8_t)USBD_FAIL;
  }

  /* Get the received data length */
  hcdc->RxLength = USBD_LL_GetRxDataSize(pdev, epnum);

  /* USB data will be immediately processed, this allow next USB traffic being
  NAKed till the end of the application Xfer */
  if(pdev->pClassData != NULL)
  {
    ((USBD_BULK_ItfTypeDef *)pdev->pUserData)->Receive(hcdc->RxBuffer, 
						      &hcdc->RxLength);

    return USBD_OK;
  }
  else
  {
    return USBD_FAIL;
  }
}
/**
  * @brief  USBD_BULK_EP0_RxReady
  *         Handle EP0 Rx Ready event
  * @param  pdev: device instance
  * @retval status
  */
static uint8_t  USBD_BULK_EP0_RxReady (USBD_HandleTypeDef *pdev)
{ 
  return USBD_OK;
}

/**
  * @brief  USBD_BULK_GetDeviceQualifierDescriptor
  *         return Device Qualifier descriptor
  * @param  length : pointer data length
  * @retval pointer to descriptor buffer
  */
static uint8_t *USBD_BULK_GetFSCfgDesc (uint16_t *length)
{
  *length = (uint16_t)sizeof(USBD_BULK_CfgFSDesc);
  return USBD_BULK_CfgFSDesc;
}

/**
  * @brief  USBD_BULK_RegisterInterface
  * @param  pdev: device instance
  * @param  fops: BULK  Interface callback
  * @retval status
  */
uint8_t  USBD_BULK_RegisterInterface  (USBD_HandleTypeDef   *pdev, 
                                      USBD_BULK_ItfTypeDef *fops)
{
  if (fops == NULL)
  {
    return (uint8_t)USBD_FAIL;
  }

  pdev->pUserData = fops;

  return (uint8_t)USBD_OK;
}

/**
  * @brief  USBD_BULK_SetTxBuffer
  * @param  pdev: device instance
  * @param  pbuff: Tx Buffer
  * @retval status
  */
uint8_t USBD_BULK_SetTxBuffer(USBD_HandleTypeDef *pdev,
                                uint8_t  *pbuff,uint32_t length)
{
  USBD_BULK_HandleTypeDef *hcdc = (USBD_BULK_HandleTypeDef *) pdev->pClassData;

  if (hcdc == NULL)
  {
    return (uint8_t)USBD_FAIL;
  }

  hcdc->TxBuffer = pbuff;
  hcdc->TxLength = length;

  return (uint8_t)USBD_OK;
}

/**
  * @brief  USBD_BULK_SetRxBuffer
  * @param  pdev: device instance
  * @param  pbuff: Rx Buffer
  * @retval status
  */
uint8_t USBD_BULK_SetRxBuffer (USBD_HandleTypeDef *pdev, uint8_t *pbuff)
{
  USBD_BULK_HandleTypeDef   *hcdc = (USBD_BULK_HandleTypeDef*) pdev->pClassData;

  if (hcdc == NULL)
  {
    return (uint8_t)USBD_FAIL;
  }

  hcdc->RxBuffer = pbuff;

  return (uint8_t)USBD_OK;
}

/**
  * @brief  USBD_BULK_TransmitPacket
  *         Transmit packet on IN endpoint
  * @param  pdev: device instance
  * @retval status
  */
uint8_t  USBD_BULK_TransmitPacket(USBD_HandleTypeDef *pdev)
{      
  USBD_BULK_HandleTypeDef   *hcdc = (USBD_BULK_HandleTypeDef*) pdev->pClassData;
  
  if(pdev->pClassData != NULL)
  {
    if(((volatile uint32_t)hcdc->TxState) == 0)
    {
      /* Tx Transfer in progress */
      hcdc->TxState = 1;
      
      /* Transmit next packet */
      USBD_LL_Transmit(pdev,
                       BULK_IN_EP,
                       hcdc->TxBuffer,
                       hcdc->TxLength);
      
      return USBD_OK;
    }
    else
    {
      return USBD_BUSY;
    }
  }
  else
  {
    return USBD_FAIL;
  }
}
/**
  * @brief  USBD_BULK_ReceivePacket
  *         prepare OUT Endpoint for reception
  * @param  pdev: device instance
  * @retval status
  */
uint8_t  USBD_BULK_ReceivePacket(USBD_HandleTypeDef *pdev)
{
  USBD_BULK_HandleTypeDef   *hcdc = (USBD_BULK_HandleTypeDef*) pdev->pClassData;
  /* Suspend or Resume USB Out process */
  if (pdev->pClassData == NULL)
  {
    return (uint8_t)USBD_FAIL;
  }
  else
  {
    /* Prepare Out endpoint to receive next packet */
    (void)USBD_LL_PrepareReceive(pdev, BULK_OUT_EP,hcdc->RxBuffer,
			   BULK_DATA_FS_OUT_PACKET_SIZE);
  }

  return (uint8_t)USBD_OK;
}
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
