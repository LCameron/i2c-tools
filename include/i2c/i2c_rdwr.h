/*
    i2c_rdwr.h - I2C read write ioctl wrapper

    Copyright (C) 2017 Leigh Cameron <leigh.cameron@tacticalresearch.com.au>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
    MA 02110-1301 USA.
*/

#ifndef LIB_I2C_RDWR_H
#define LIB_I2C_RDWR_H

#include <linux/types.h>
#include <linux/i2c.h>

__s32 i2c_rdwr_access(int file, struct i2c_msg *msgs, __u32 nmsgs);

/* Reads the response buffer length from response_length */
__s32 i2c_combined_block_transfer(int file,  __u16 addr, __u8 *command, __u8 command_length,
				   __u8 *response, __u8 response_length);

#endif /* LIB_I2C_RDWR_H */
