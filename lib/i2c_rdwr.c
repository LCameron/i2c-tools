/*
    smbus.c - SMBus level access helper functions

    Copyright (C) 1995-1997  Simon G. Vogl
    Copyright (C) 1998-1999  Frodo Looijaard <frodol@dds.nl>
    Copyright (C) 2012-2013  Jean Delvare <jdelvare@suse.de>

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

#include <errno.h>
#include <stddef.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include "i2c/i2c_rdwr.h"


__s32 i2c_rdwr_access(int file, struct i2c_msg *msgs, __u32 nmsgs)
{
	struct i2c_rdwr_ioctl_data args;
	__s32 err;

	args.msgs = msgs;
	args.nmsgs = nmsgs;

	err = ioctl(file, I2C_RDWR, &args);
	if (err == -1)
		err = -errno;
	return err;
}

/* Reads the response buffer length from response_length */
__s32 i2c_combined_block_transfer(int file,  __u16 addr, __u8 *command, __u8 command_length,
				   __u8 *response, __u8 response_length)
{

	if(command==NULL
		|| response==NULL
		|| response_length==0
		|| file <0
			)
	return -1;

	struct i2c_msg msgs[2];
	__u32 nmsgs=2;

	msgs[0].addr = addr;
	msgs[0].flags = 0;
	msgs[0].buf=command;
	msgs[0].len = command_length;

	msgs[1].flags = I2C_M_NOSTART | I2C_M_RD;
	msgs[1].buf=response;
	msgs[1].len = response_length;

	int err = i2c_rdwr_access(file,msgs,nmsgs);

	if (err < 0)
		return err;

	//No way to know the number actually received by the driver.
	return 0;
}
