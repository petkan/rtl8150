/*
 *  Copyright (c) 2002-2013 Petko Manolov (petkan@nucleusys.com)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 */

#ifndef	__rtl8150_h__
#define	__rtl8150_h__

#define	IDR			0x0120
#define	MAR			0x0126
#define	CR			0x012e
#define	TCR			0x012f
#define	RCR			0x0130
#define	TSR			0x0132
#define	RSR			0x0133
#define	CON0			0x0135
#define	CON1			0x0136
#define	MSR			0x0137
#define	PHYADD			0x0138
#define	PHYDAT			0x0139
#define	PHYCNT			0x013b
#define	GPPC			0x013d
#define	BMCR			0x0140
#define	BMSR			0x0142
#define	ANAR			0x0144
#define	ANLP			0x0146
#define	AER			0x0148
#define CSCR			0x014C  /* This one has the link status */
#define CSCR_LINK_STATUS	(1 << 3)

#define	IDR_EEPROM		0x1202

#define	PHY_READ		0
#define	PHY_WRITE		0x20
#define	PHY_GO			0x40

#define	MII_TIMEOUT		10
#define	INTBUFSIZE		8

#define	RTL8150_REQT_READ	0xc0
#define	RTL8150_REQT_WRITE	0x40
#define	RTL8150_REQ_GET_REGS	0x05
#define	RTL8150_REQ_SET_REGS	0x05


/* Transmit status register errors */
#define TSR_ECOL		(1<<5)
#define TSR_LCOL		(1<<4)
#define TSR_LOSS_CRS		(1<<3)
#define TSR_JBR			(1<<2)
#define TSR_ERRORS		(TSR_ECOL | TSR_LCOL | TSR_LOSS_CRS | TSR_JBR)
/* Receive status register errors */
#define RSR_CRC			(1<<2)
#define RSR_FAE			(1<<1)
#define RSR_ERRORS		(RSR_CRC | RSR_FAE)

/* Media status register definitions */
#define MSR_DUPLEX		(1<<4)
#define MSR_SPEED		(1<<3)
#define MSR_LINK		(1<<2)

/* Interrupt pipe data */
#define INT_TSR			0x00
#define INT_RSR			0x01
#define INT_MSR			0x02
#define INT_WAKSR		0x03
#define INT_TXOK_CNT		0x04
#define INT_RXLOST_CNT		0x05
#define INT_CRERR_CNT		0x06
#define INT_COL_CNT		0x07


#define	RTL8150_MTU		1540
#define	RTL8150_TX_TIMEOUT	(HZ)

/* rtl8150 flags */
#define	RTL8150_HW_CRC		0
#define	RX_REG_SET		1
#define	RTL8150_UNPLUG		2
#define	RX_URB_FAIL		3

/* Define these values to match your device */
#define	VENDOR_ID_REALTEK		0x0bda
#define	VENDOR_ID_MELCO			0x0411
#define	VENDOR_ID_MICRONET		0x3980
#define	VENDOR_ID_LONGSHINE		0x07b8
#define	VENDOR_ID_OQO			0x1557
#define	VENDOR_ID_ZYXEL			0x0586

#define PRODUCT_ID_RTL8150		0x8150
#define	PRODUCT_ID_LUAKTX		0x0012
#define	PRODUCT_ID_LCS8138TX		0x401a
#define PRODUCT_ID_SP128AR		0x0003
#define	PRODUCT_ID_PRESTIGE		0x401a

#undef	EEPROM_WRITE

/* table of devices that work with this driver */
static struct usb_device_id rtl8150_table[] = {
	{USB_DEVICE(VENDOR_ID_REALTEK, PRODUCT_ID_RTL8150)},
	{USB_DEVICE(VENDOR_ID_MELCO, PRODUCT_ID_LUAKTX)},
	{USB_DEVICE(VENDOR_ID_MICRONET, PRODUCT_ID_SP128AR)},
	{USB_DEVICE(VENDOR_ID_LONGSHINE, PRODUCT_ID_LCS8138TX)},
	{USB_DEVICE(VENDOR_ID_OQO, PRODUCT_ID_RTL8150)},
	{USB_DEVICE(VENDOR_ID_ZYXEL, PRODUCT_ID_PRESTIGE)},
	{}
};

struct rtl8150 {
	unsigned long flags;
	struct usb_device *udev;
	struct tasklet_struct tl;
	struct net_device *netdev;
	struct urb *rx_urb, *tx_urb, *intr_urb;
	struct sk_buff *tx_skb, *rx_skb;
	int intr_interval;
	u8 *intr_buff;
	u8 phy;
};

typedef struct rtl8150 rtl8150_t;

struct async_req {
	struct usb_ctrlrequest dr;
	u16 rx_creg;
};

#endif	/* __rtl8150_h__ */
