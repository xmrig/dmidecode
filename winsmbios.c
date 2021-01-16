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

#include <windows.h>
#include <stdio.h>
#include <stdint.h>

#include "dmidecode.h"
#include "winsmbios.h"


/*
 * Counts the number of SMBIOS structures present in
 * the SMBIOS table.
 *
 * buff - Pointer that receives the SMBIOS Table address.
 *        This will be the address of the BYTE array from
 *        the RawSMBIOSData struct.
 *
 * len - The length of the SMBIOS Table pointed by buff.
 *
 * return - The number of SMBIOS strutctures.
 *
 * Remarks:
 * The SMBIOS Table Entry Point has this information,
 * however the GetSystemFirmwareTable API doesn't
 * return all fields from the Entry Point, and
 * DMIDECODE uses this value as a parameter for
 * dmi_table function. This is the reason why
 * this function was make.
 *
 * Hugo Weber address@hidden
 */
int count_smbios_structures(const void *buff, u32 len){

	int icount = 0;//counts the strutures
	void *offset = (void *)buff;//points to the actual address in the buff that's been checked
	struct dmi_header *header = NULL;//header of the struct been read to get the length to increase the offset

	//searches structures on the whole SMBIOS Table
	while(offset  < (buff + len)){
		//get the header to read te length and to increase the offset
		header = (struct dmi_header *)offset;
		offset += header->length;

		icount++;

		/*
		 * increses the offset to point to the next header that's
		 * after the strings at the end of the structure.
		 */
		while( (*(WORD *)offset != 0)  &&  (offset < (buff + len))  ){
			offset++;
		}

		/*
		 * Points to the next stucture thas after two null BYTEs
		 * at the end of the strings.
		 */
		offset += 2;
	}

	return icount;
}

/*
 * Gets the raw SMBIOS table. This function only works
 * on Windows 2003 and above. Since Windows 2003 SP1
 * Microsoft blocks access to physical memory.
 *
 * return - pointer to the SMBIOS table returned
 * by GetSystemFirmwareTable.
 *
 * see RawSMBIOSData on winsmbios.h
 *
 * Hugo Weber address@hidden
 */
RawSMBIOSData *get_raw_smbios_table(void)
{
	const uint32_t size = GetSystemFirmwareTable('RSMB', 0, NULL, 0);
	void *buf = malloc(size);
	if (!buf) {
		return NULL;
	}

	if (GetSystemFirmwareTable('RSMB', 0, buf, size) != size) {
		free(buf);

		return NULL;
	}

	return buf;
}
