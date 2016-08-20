/**
 * @file main.c
 *
 * @section License
 * Copyright (C) 2014-2016, Erik Moqvist
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

#include "simba.h"

#define SLAVE_ADDRESS          0x01
#define BAD_SLAVE_ADDRESS      0x02

#define SCL &pin_d4_dev
#define SDA &pin_d5_dev

struct i2c_soft_driver_t i2c_soft;

static int test_init(struct harness_t *harness_p)
{
    BTASSERT(i2c_soft_init(&i2c_soft, SCL, SDA, 100, 1000000, 1000) == 0);
    BTASSERT(i2c_soft_start(&i2c_soft) == 0);

    return (0);
}

static int test_bad_slave(struct harness_t *harness_p)
{
    uint8_t buf[3];

    /* Try to read three bytes from the bad slave device. Is should
       fail since the slave does not exist. */
    memset(buf, 0, sizeof(buf));

    BTASSERT(i2c_soft_read(&i2c_soft,
                           BAD_SLAVE_ADDRESS,
                           buf,
                           3) == 0);

    BTASSERT(i2c_soft_write(&i2c_soft,
                            BAD_SLAVE_ADDRESS,
                            buf,
                            3) == 0);

    return (0);
}

static int test_read(struct harness_t *harness_p)
{
    uint8_t buf[3];

    /* Read three bytes from the slave device. */
    memset(buf, 0, sizeof(buf));

    BTASSERT(i2c_soft_read(&i2c_soft,
                           SLAVE_ADDRESS,
                           buf,
                           3) == 3);

    BTASSERT(buf[0] == 5);
    BTASSERT(buf[1] == 3);
    BTASSERT(buf[2] == 1);

    return (0);
}

static int test_write(struct harness_t *harness_p)
{
    uint8_t buf[5];

    buf[0] = 1;
    buf[1] = 3;
    buf[2] = 5;
    buf[3] = 7;
    buf[4] = 9;

    /* Write 5 bytes to the slave device. */
    BTASSERT(i2c_soft_write(&i2c_soft,
                            SLAVE_ADDRESS,
                            buf,
                            5) == 5);

    return (0);
}

static int test_echo(struct harness_t *harness_p)
{
    uint8_t value;

    /* Write ping value. */
    value = 0x35;

    BTASSERT(i2c_soft_write(&i2c_soft,
                            SLAVE_ADDRESS,
                            &value,
                            1) == 1);

    /* Read pong value (ping + 1). */
    value = 0;

    BTASSERT(i2c_soft_read(&i2c_soft,
                           SLAVE_ADDRESS,
                           &value,
                           1) == 1);

    BTASSERT(value == 0x36);

    return (0);
}

static int test_mem_read(struct harness_t *harness_p)
{
    uint8_t address;
    uint8_t value;

    address = 0x34;

    BTASSERT(i2c_soft_write(&i2c_soft,
                            SLAVE_ADDRESS,
                            &address,
                            1) == 1);

    BTASSERT(i2c_soft_read(&i2c_soft,
                           SLAVE_ADDRESS,
                           &value,
                           1) == 1);

    BTASSERT(value == 0x54);

    return (0);
}

static int test_stop(struct harness_t *harness_p)
{
    BTASSERT(i2c_soft_stop(&i2c_soft) == 0);

    return (0);
}

int main()
{
    struct harness_t harness;
    struct harness_testcase_t harness_testcases[] = {
        { test_init, "test_init" },
        { test_bad_slave, "test_bad_slave" },
        { test_read, "test_read" },
        { test_write, "test_write" },
        { test_echo, "test_echo" },
        { test_mem_read, "test_mem_read" },
        { test_stop, "test_stop" },
        { NULL, NULL }
    };

    sys_start();
    i2c_soft_module_init();

    harness_init(&harness);
    harness_run(&harness, harness_testcases);

    return (0);
}