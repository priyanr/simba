/**
 * @file drivers/usb_port.h
 * @version 1.0
 *
 * @section License
 * Copyright (C) 2014-2015, Erik Moqvist
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * This file is part of the Simba project.
 */

#ifndef __DRIVERS_USB_PORT_H__
#define __DRIVERS_USB_PORT_H__

struct usb_device_t {
    struct usb_driver_t *drv_p;
    volatile struct sam_uotghs_t *regs_p;
    int id;
};

struct usb_driver_t {
    struct usb_device_t *dev_p;
};

#endif