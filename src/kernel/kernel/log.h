/**
 * @file kernel/log.h
 * @version 0.6.0
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

#ifndef __KERNEL_LOG_H__
#define __KERNEL_LOG_H__

#include "simba.h"

/* Severity levels' log masks. */

/** System unusable. */
#define LOG_EMERG   0
/** Immediate action required. */
#define LOG_ALERT   1
/** Critical condition. */
#define LOG_CRIT    2
/** Error conditions. */
#define LOG_ERR     3
/** Warning conditions. */
#define LOG_WARNING 4
/** Normal but significant conditions. */
#define LOG_NOTICE  5
/** Informational messages. */
#define LOG_INFO    6
/** Debugging messages. */
#define LOG_DEBUG   7

/** Craete log mask from level. */
#define LOG_MASK(level) (1 << (LOG_ ## level))

/** Set all levels up to and including mask. */
#define LOG_UPTO(level) ((1 << (LOG_ ## level + 1)) - 1)

struct log_handler_t {
    chan_t *chout_p;
    struct log_handler_t *next_p;
};

struct log_object_t {
    const char *name_p;
    char mask;
    struct log_object_t *next_p;
};

/**
 * Initialize the logging module.
 *
 * @return zero(0) or negative error code.
 */
int log_module_init(void);

/**
 * Initialize given log object with given name and mask.
 *
 * @param[in] self_p Log object to initialize.
 * @param[in] name_p Log object name.
 * @param[in] mask Log object mask.
 *
 * @return zero(0) or negative error code.
 */
int log_object_init(struct log_object_t *self_p,
                    const char *name_p,
                    char mask);

/**
 * Check if given log level is set in the log object mask. If so,
 * format a log entry and write it to all log handlers.
 *
 * ``self_p`` may be NULL, and in that case the current thread's log
 * mask is used instead of the log object mask.
 *
 * @param[in] self_p Log object, or NULL to use the thread's log mask.
 * @param[in] level Log level.
 * @param[in] fmt_p Log format string.
 * @param[in] ... Variable argument list.
 *
 * @return zero(0) or negative error code.
 */
int log_object_print(struct log_object_t *self_p,
                     int level,
                     const char *fmt_p,
                     ...);

/**
 * Initialize given log handler with given output channel.
 *
 * @param[in] self_p Log handler to initialize.
 * @param[in] chout_p Output handler.
 *
 * @return zero(0) or negative error code.
 */
int log_handler_init(struct log_handler_t *self_p,
                     chan_t *chout_p);

/**
 * Add given log handler to the list of log handlers. Log entries will
 * be written to all log handlers in the list.
 *
 * @param[in] handler_p Log handler to add.
 *
 * @return zero(0) or negative error code.
 */
int log_add_handler(struct log_handler_t *handler_p);

/**
 * Remove given log handler from the list of log handlers.
 *
 * @param[in] handler_p Log handler to remove.
 *
 * @return zero(0) or negative error code.
 */
int log_remove_handler(struct log_handler_t *handler_p);

/**
 * Add given log object to the list of log objects. There are file
 * system commands to list all log objects in the list and also modify
 * their log mask.
 *
 * @param[in] object_p Log object to add.
 *
 * @return zero(0) or negative error code.
 */
int log_add_object(struct log_object_t *object_p);

/**
 * Remove given log object from the list of log objects.
 *
 * @param[in] object_p Object to remove.
 *
 * @return zero(0) or negative error code.
 */
int log_remove_object(struct log_object_t *object_p);

/**
 * Set the output channel of the default log handler.
 *
 * @param[in] chout_p Channel to set as the default output
 *                    channel. May be NULL if no output should be
 *                    written.
 *
 * @return zero(0) or negative error code.
 */
int log_set_default_handler_output_channel(chan_t *chout_p);

#endif
