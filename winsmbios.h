/*
 * Functions to allow to read SMBIOS from physical memory on windows
 * or to get the SMBIOS table on windows 2003 SP1 and above.
 *
 * This file is part of the dmidecode project.
 *
 *   (C) 2002-2006 Hugo Weber <address@hidden>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 *   For the avoidance of doubt the "preferred form" of this code is one which
 *   is in an open unpatent encumbered format. Where cryptographic key signing
 *   forms part of the process of creating an executable the information 
 *   including keys needed to generate an equivalently functional executable
 *   are deemed to be part of the source code.
 */

#ifndef WINSMBIOS_H
#define WINSMBIOS_H
 
#include "types.h"

/*
 * Struct needed to get the SMBIOS table using GetSystemFirmwareTable API.
 */
typedef struct _RawSMBIOSData{
    u8	Used20CallingMethod;
    u8	SMBIOSMajorVersion;
    u8	SMBIOSMinorVersion;
    u8	DmiRevision;
    u32	Length;
    u8	SMBIOSTableData[];
} RawSMBIOSData;

RawSMBIOSData *get_raw_smbios_table(void);
int count_smbios_structures(const void *buff, u32 len);

#endif /*WINSMBIOS_H*/
