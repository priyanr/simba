/**
 * @file drivers/usb/device/descriptors.h
 * @version 3.1.0
 *
 * @section License
 * Copyright (C) 2016, Erik Moqvist
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

#ifndef __DRIVERS_USB_DEVICE_DESCRIPTORS_H__
#define __DRIVERS_USB_DEVICE_DESCRIPTORS_H__

#include "simba.h"

/**
 * An array of all USB device descriptors.
 */
extern FAR const union usb_descriptor_t *usb_device_descriptors[];

extern FAR const uint16_t usb_device_descriptor_string_language[];

extern FAR const uint16_t usb_device_descriptor_string_iproduct[];

extern FAR const uint16_t usb_device_descriptor_string_imanufacturer[];

#endif