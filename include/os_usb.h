/**************************************************************************************************
 *
 *  Description : USB Controller
 *
 *  Project     : SMOS
 *                Public header file
 *
 *  Author(s)   : Dipl. Ing. Sven Kaltschmidt
 *                Utimaco
 *
 **************************************************************************************************/
#ifndef __OS_USB_PUB_INCLUDED__
#define __OS_USB_PUB_INCLUDED__

/******************************************************************************
 *
 * Definitions
 *
 ******************************************************************************/
typedef struct os_usb_endpoint_desc_t
{
  unsigned char  bLength;
  unsigned char  bDescriptorType;
  unsigned char  bEndpointAddress;
  unsigned char  bmAttributes;
  unsigned short wMaxPacketSize;
  unsigned char  bInterval;
  // unused
  unsigned char  bRefresh;
  unsigned char  bSynchAddress;
}
T_OS_USB_ENDPOINT_DESC;

#define ENDPOINT_DESC_LEN   7

typedef struct os_usb_interface_desc_t
{
  unsigned char  bLength;
  unsigned char  bDescriptorType;
  unsigned char  bInterfaceNumber;
  unsigned char  bAlternateSetting;
  unsigned char  bNumEndpoints;
  unsigned char  bInterfaceClass;
  unsigned char  bInterfaceSubClass;
  unsigned char  bInterfaceProtocol;
  unsigned char  iInterface;

  T_OS_USB_ENDPOINT_DESC *p_ep;
}
T_OS_USB_INTERFACE_DESC;

#define INTERFACE_DESC_LEN  9

typedef struct os_usb_config_desc_t
{
  unsigned char  bLength;
  unsigned char  bDescriptorType;
  unsigned short wTotalLength;
  unsigned char  bNumInterfaces;
  unsigned char  bConfigurationValue;
  unsigned char  iConfiguration;
  unsigned char  bmAttributes;
  unsigned char  MaxPower;

  T_OS_USB_INTERFACE_DESC *p_iface;
}
T_OS_USB_CONFIG_DESC;

#define CONFIG_DESC_LEN 9

typedef struct os_usb_device_desc_t
{
  unsigned char  bLength;
  unsigned char  bDescriptorType;
  unsigned short bcdUSB;
  unsigned char  bDeviceClass;
  unsigned char  bDeviceSubClass;
  unsigned char  bDeviceProtocol;
  unsigned char  bMaxPacketSize0;
  unsigned short idVendor;
  unsigned short idProduct;
  unsigned short bcdDevice;
  unsigned char  iManufacturer;
  unsigned char  iProduct;
  unsigned char  iSerialNumber;
  unsigned char  bNumConfigurations;
}
T_OS_USB_DEVICE_DESC;

#define DEVICE_DESC_LEN 18

typedef struct os_usb_dev_t 
#ifndef _SMOS_C_INT_
{
  struct os_usb_dev_t *p_next;
  unsigned short      vid;          // vendor ID
  unsigned short      pid;          // product ID
  unsigned char       port;         // port number (0,1)
  unsigned char       dad;          // device address
  unsigned char       config;       // current configuration
  unsigned char       rfu;
}
#endif
T_OS_USB_DEV_HDL;


#define TYPE_FULL_SPEED               0
#define TYPE_LOW_SPEED                1

// Standard requests
#define USB_REQ_GET_STATUS		        0x00
#define USB_REQ_CLEAR_FEATURE	        0x01
// 0x02 is reserved
#define USB_REQ_SET_FEATURE		        0x03
// 0x04 is reserved
#define USB_REQ_SET_ADDRESS		        0x05
#define USB_REQ_GET_DESCRIPTOR		    0x06
#define USB_REQ_SET_DESCRIPTOR		    0x07
#define USB_REQ_GET_CONFIGURATION	    0x08
#define USB_REQ_SET_CONFIGURATION	    0x09
#define USB_REQ_GET_INTERFACE		      0x0A
#define USB_REQ_SET_INTERFACE		      0x0B
#define USB_REQ_SYNCH_FRAME		        0x0C

// Descriptor types
#define USB_DT_DEVICE			            0x01
#define USB_DT_CONFIG			            0x02
#define USB_DT_STRING			            0x03
#define USB_DT_INTERFACE	            0x04
#define USB_DT_ENDPOINT		            0x05

#define USB_DT_HID			              0x21
#define USB_DT_REPORT		              0x22
#define USB_DT_PHYSICAL	              0x23
#define USB_DT_HUB			              0x29

// Request types [DIR | TYPE | RECIP]
#define USB_RECIP_DEVICE		          0x00
#define USB_RECIP_INTERFACE	          0x01
#define USB_RECIP_ENDPOINT	          0x02
#define USB_RECIP_OTHER			          0x03
#define USB_RECIP_MASK                0x1F

#ifndef USB_TYPE_STANDARD
#define USB_TYPE_STANDARD		          0x00
#endif
#ifndef USB_TYPE_CLASS
#define USB_TYPE_CLASS			          0x20
#endif
#ifndef USB_TYPE_VENDOR
#define USB_TYPE_VENDOR			          0x40
#endif
#ifndef USB_TYPE_RESERVED
#define USB_TYPE_RESERVED		          0x60
#endif
#define USB_TYPE_MASK                 0x60

#define USB_DIR_DEVICE_TO_HOST        0x80

#define USB_RT_HUB	(USB_TYPE_CLASS | USB_RECIP_DEVICE)
#define USB_RT_PORT	(USB_TYPE_CLASS | USB_RECIP_OTHER)

// Endpoint types
#define USB_ENDPOINT_TYPE_CONTROL		  0
#define USB_ENDPOINT_TYPE_ISOCHRONOUS 1
#define USB_ENDPOINT_TYPE_BULK			  2
#define USB_ENDPOINT_TYPE_INTERRUPT	  3
#define USB_ENDPOINT_TYPE_MASK		    0x03

#define USB_ENDPOINT_IN			          0x80


//--------------------------------------------------------------------------------
// hub
//--------------------------------------------------------------------------------
typedef struct os_usb_hub_desc_t
{
  unsigned char  bLength;
  unsigned char  bDescriptorType;
  unsigned char  bNumberOfPorts;
  unsigned short wHubCharacteristics;
  unsigned char  bPowerOnToPowerGood;
  unsigned char  bHubControlCurrent;
  unsigned char  bRemoveAndPowerMask[64];
}
T_OS_USB_HUB_DESC;

typedef struct os_usb_status_t
{
  unsigned short wStatus;
  unsigned short wChange;
}
T_OS_USB_STATUS;

// port features
#define USB_PORT_FEAT_CONNECTION	      0
#define USB_PORT_FEAT_ENABLE		        1
#define USB_PORT_FEAT_SUSPEND		        2	/* L2 suspend */
#define USB_PORT_FEAT_OVER_CURRENT	    3
#define USB_PORT_FEAT_RESET		          4
#define USB_PORT_FEAT_L1		            5	/* L1 suspend */
#define USB_PORT_FEAT_POWER		          8
#define USB_PORT_FEAT_LOWSPEED		      9
/* This value was never in Table 11-17 */
#define USB_PORT_FEAT_HIGHSPEED		      10
/* This value is also fake */
#define USB_PORT_FEAT_SUPERSPEED	      11
#define USB_PORT_FEAT_C_CONNECTION	    16
#define USB_PORT_FEAT_C_ENABLE		      17
#define USB_PORT_FEAT_C_SUSPEND		      18
#define USB_PORT_FEAT_C_OVER_CURRENT	  19
#define USB_PORT_FEAT_C_RESET		        20
#define USB_PORT_FEAT_TEST              21
#define USB_PORT_FEAT_INDICATOR         22
#define USB_PORT_FEAT_C_PORT_L1         23

// port status
#define USB_PORT_STAT_CONNECTION	      0x0001
#define USB_PORT_STAT_ENABLE		        0x0002
#define USB_PORT_STAT_SUSPEND		        0x0004
#define USB_PORT_STAT_OVERCURRENT	      0x0008
#define USB_PORT_STAT_RESET		          0x0010
#define USB_PORT_STAT_L1		            0x0020
/* bits 6 to 7 are reserved */
#define USB_PORT_STAT_POWER		          0x0100
#define USB_PORT_STAT_LOW_SPEED		      0x0200
#define USB_PORT_STAT_HIGH_SPEED        0x0400
#define USB_PORT_STAT_TEST              0x0800
#define USB_PORT_STAT_INDICATOR         0x1000
/* bits 13 to 15 are reserved */

// port change
#define USB_PORT_STAT_C_CONNECTION	    0x0001
#define USB_PORT_STAT_C_ENABLE		      0x0002
#define USB_PORT_STAT_C_SUSPEND		      0x0004
#define USB_PORT_STAT_C_OVERCURRENT	    0x0008
#define USB_PORT_STAT_C_RESET		        0x0010
#define USB_PORT_STAT_C_L1		          0x0020

/******************************************************************************
 *
 * public interface
 *
 ******************************************************************************/
typedef int (T_OS_USB_EVENT_HANDLER)(T_OS_USB_DEV_HDL *p_dev, unsigned int event);

#define OS_USB_EVENT_INSERT   1
#define OS_USB_EVENT_REMOVE   2

typedef struct _os_usb_public_interface
{
  int  (*_p_os_usb_get_device_list)(T_OS_USB_DEV_HDL **pp_devs);
  int  (*_p_os_usb_get_device_desc)(T_OS_USB_DEV_HDL *p_dev, T_OS_USB_DEVICE_DESC *p_dev_desc);
  int  (*_p_os_usb_get_config_desc)(T_OS_USB_DEV_HDL *p_dev, int index, T_OS_USB_CONFIG_DESC **pp_conf_desc);
  void (*_p_os_usb_free_config_desc)(T_OS_USB_CONFIG_DESC *p_conf_desc);
  int  (*_p_os_usb_set_configuration)(T_OS_USB_DEV_HDL *p_dev, char config);
  int  (*_p_os_usb_reset_device)(T_OS_USB_DEV_HDL *p_dev);

  int (*_p_os_usb_control_msg)(T_OS_USB_DEV_HDL *p_dev,
                               int              reqtype,
                               int              request,
                               int              value,
                               int              index,
                               char             *p_data,
                               int              l_data,
                               int              timeout);

  int (*_p_os_usb_bulk_write)(T_OS_USB_DEV_HDL *p_dev,
                              int              ep,
                              char             *p_data,
                              int              l_data,
                              int              *p_l_data,
                              int              timeout);

  int (*_p_os_usb_bulk_read)(T_OS_USB_DEV_HDL *p_dev,
                             int              ep,
                             char             *p_data,
                             int              l_data,
                             int              *p_l_data,
                             int              timeout);

  int  (*_p_os_usb_set_event_handler)(unsigned short vid, unsigned short pid, T_OS_USB_EVENT_HANDLER *p_handler);
  int  (*_p_os_usb_remove_event_handler)(unsigned short vid, unsigned short pid);
  int  (*_p_os_usb_get_event_handler)(unsigned short vid, unsigned short pid, T_OS_USB_EVENT_HANDLER **pp_handler);    
}
T_OS_USB_TABLE_PUB;


#if defined(_SMOS_C_INT_) || defined(_ALWAYS_C_INT_)

  int  os_usb_init(void);
  int  os_usb_get_device_list(T_OS_USB_DEV_HDL **pp_devs);
  int  os_usb_get_device_desc(T_OS_USB_DEV_HDL *p_dev, T_OS_USB_DEVICE_DESC *p_dev_desc);
  int  os_usb_get_config_desc(T_OS_USB_DEV_HDL *p_dev, int index, T_OS_USB_CONFIG_DESC **pp_conf_desc);
  void os_usb_free_config_desc(T_OS_USB_CONFIG_DESC *p_conf_desc);
  int  os_usb_set_configuration(T_OS_USB_DEV_HDL *p_dev, char config);
  int  os_usb_reset_device(T_OS_USB_DEV_HDL *p_dev);

  int os_usb_control_msg(T_OS_USB_DEV_HDL *p_dev,
                         int              reqtype,
                         int              request,
                         int              value,
                         int              index,
                         char             *p_data,
                         int              l_data,
                         int              timeout);

   int os_usb_bulk_write(T_OS_USB_DEV_HDL *p_dev,
                         int              ep,
                         char             *p_data,
                         int              l_data,
                         int              *p_l_data,
                         int              timeout);

   int os_usb_bulk_read(T_OS_USB_DEV_HDL *p_dev,
                        int              ep,
                        char             *p_data,
                        int              l_data,
                        int              *p_l_data,
                        int              timeout);

  int  os_usb_set_event_handler(unsigned short vid, unsigned short pid, T_OS_USB_EVENT_HANDLER *p_handler);
  int  os_usb_remove_event_handler(unsigned short vid, unsigned short pid);
  int  os_usb_get_event_handler(unsigned short vid, unsigned short pid, T_OS_USB_EVENT_HANDLER **pp_handler);    

#else

  #define _P_OS_USB  ((T_OS_USB_TABLE_PUB*) (((T_OS_TABLE_PUB*)P_SMOS)->p_os_usb))

  #define os_usb_get_device_list        _P_OS_USB->_p_os_usb_get_device_list
  #define os_usb_get_device_desc        _P_OS_USB->_p_os_usb_get_device_desc
  #define os_usb_get_config_desc        _P_OS_USB->_p_os_usb_get_config_desc
  #define os_usb_free_config_desc       _P_OS_USB->_p_os_usb_free_config_desc
  #define os_usb_set_configuration      _P_OS_USB->_p_os_usb_set_configuration
  #define os_usb_reset_device           _P_OS_USB->_p_os_usb_reset_device
  #define os_usb_control_msg            _P_OS_USB->_p_os_usb_control_msg
  #define os_usb_bulk_write             _P_OS_USB->_p_os_usb_bulk_write
  #define os_usb_bulk_read              _P_OS_USB->_p_os_usb_bulk_read
  #define os_usb_set_event_handler      _P_OS_USB->_p_os_usb_set_event_handler
  #define os_usb_remove_event_handler   _P_OS_USB->_p_os_usb_remove_event_handler
  #define os_usb_get_event_handler      _P_OS_USB->_p_os_usb_get_event_handler

#endif


/* --- BEGIN ERROR CODES --- */

#define E_OS_USB                          0xB0003    // USB section

#define E_OS_USB_MALLOC                   0xB0003001  // memory allocation failed
#define E_OS_USB_PARAM                    0xB0003002  // invalid parameter
#define E_OS_USB_NOT_SUPPORTED            0xB0003003  // USB not supported
#define E_OS_USB_INIT_FAILED              0xB0003004  // initialization of host controller failed
#define E_OS_USB_DEVICE_CONNECT           0xB0003005  // device is not connected
#define E_OS_USB_DEVICE_STATE             0xB0003006  // invalid device state
#define E_OS_USB_TIMEOUT                  0xB0003007  // timeout occured
#define E_OS_USB_NAK                      0xB0003008  // NAK received
#define E_OS_USB_PROTOCOL                 0xB0003009  // protocol error
#define E_OS_USB_IDTAB_FULL               0xB000300A  // ID table is full
#define E_OS_USB_NOT_FOUND                0xB000300B  // item not found
#define E_OS_USB_DATA_LEN                 0xB000300C  // invalid data length

#define E_OS_USB_ERR                      0xB00031    // transaction error
#define E_OS_USB_LIBUSB                   0xB00032    // libusb


/* --- END ERROR CODES --- */


#endif

