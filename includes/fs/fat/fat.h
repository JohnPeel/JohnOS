/*
	This file is part of JohnOS.

	JohnOS is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	JohnOS is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with JohnOS.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef _FAT_H_
#define _FAT_H_

#include <stdint.h>

#define FAT_MAXFILENAME_LENGTH 256

#define FAT_ATTRIB_READ_ONLY 0x01
#define FAT_ATTRIB_HIDDEN 0x02
#define FAT_ATTRIB_SYSTEM 0x04
#define FAT_ATTRIB_VOLUME_ID 0x08
#define FAT_ATTRIB_DIRECTORY 0x10
#define FAT_ATTRIB_ARCHIVE 0x2

#define FAT_ATTRIB_VALID (FAT_ATTRIB_READ_ONLY | \
							FAT_ATTRIB_HIDDEN | \
							FAT_ATTRIB_SYSTEM | \
							FAT_ATTRIB_DIRECTORY | \
							FAT_ATTRIB_ARCHIVE)

#define FAT_ATTRIB_LN_VALID (FAT_ATTRIB_READ_ONLY | \
							FAT_ATTRIB_HIDDEN | \
							FAT_ATTRIB_SYSTEM | \
							FAT_ATTRIB_VOLUME_ID)

struct fat_bpb {
	uint8_t jmp_code[3];
	uint8_t oem_id[8];
	uint16_t bytes_per_sector;
	uint8_t sectors_per_cluster;
	uint16_t reserved_sectors;
	uint8_t num_of_FATs;
	uint16_t num_of_directory;
	uint16_t num_of_sec_16;
	uint8_t media_descriptor;
	uint16_t sectors_per_fat;
	uint16_t sectors_per_track;
	uint16_t num_of_heads;
	uint32_t num_of_hidden_sec;
	uint32_t num_of_sec_32;

	union {
		struct {
			uint8_t drive_number;
			uint8_t reserved_flags;
			uint8_t signature;
			uint32_t volume_id;
			uint8_t volume_label[11];
			uint8_t system_id[8];
		} __attribute__((__packed__)) fat_12_16;

		struct {
			uint32_t sectors_per_fat;
			uint16_t flags;
			uint16_t fat_version;
			uint32_t root_cluster;
			uint16_t fsinfo_cluster;
			uint16_t backup_cluster;
			uint8_t reserved[12];
			uint8_t drive_number;
			uint8_t reserved_flags;
			uint8_t signature;
			uint32_t volume_id;
			uint8_t volume_label[11];
			uint8_t system_id[8];
		} __attribute__((__packed__)) fat_32;
	} __attribute__((__packed__));

	uint8_t pad[422]; /* Boot Code and Boot Sig */
} __attribute__((__packed__));

struct fat_dir {
	uint8_t name[11];
	uint8_t attributes;
	uint8_t reserved;
	uint8_t creation_time;
	uint16_t time_created;
	uint16_t date_created;
	uint16_t access_date;
	uint16_t high_cluster_num;
	uint16_t mod_time;
	uint16_t mod_date;
	uint16_t low_cluster_num;
	uint32_t size;
} __attribute__((__packed__));

struct fat_long_name {
	uint8_t order;
	uint16_t name_1[5];
	uint8_t attrib;
	uint8_t type;
	uint8_t checksum;
	uint16_t name_2[6];
	uint16_t always_zero;
	uint16_t name_3[2];
} __attribute__((__packed__));

#endif