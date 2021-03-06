/**
 *  @file rtems/dosfs.h
 *
 *  Application interface to MSDOS filesystem.
 */
 
/*
 *  Copyright (C) 2001 OKTET Ltd., St.-Petersburg, Russia
 *  Author: Eugeny S. Mints <Eugeny.Mints@oktet.ru>
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  @(#) $Id$
 */
 
#ifndef _RTEMS_DOSFS_H
#define _RTEMS_DOSFS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <rtems.h>
#include <rtems/libio.h>

extern rtems_filesystem_operations_table  msdos_ops;

#define MSDOS_FMT_FATANY 0
#define MSDOS_FMT_FAT12  1
#define MSDOS_FMT_FAT16  2
#define MSDOS_FMT_FAT32  3

/*
 * data to be filled out for formatter: parameters for format call
 * any parameter set to 0 or NULL will be automatically detected/computed
 */
typedef struct {
  const char *OEMName;            /* OEM Name string or NULL               */
  const char *VolLabel;           /* Volume Label string or NULL           */
  uint32_t  sectors_per_cluster;  /* request value: sectors per cluster    */
  uint32_t  fat_num;              /* request value: number of FATs on disk */
  uint32_t  files_per_root_dir;   /* request value: file entries in root   */
  uint8_t   fattype;              /* request value: MSDOS_FMT_FAT12/16/32  */
  uint8_t   media;                /* media code. default: 0xF8             */
  boolean   quick_format;         /* TRUE: do not clear out data sectors   */
  uint32_t  cluster_align;        /* requested value: cluster alignment    */
                                  /*   make sector number of first sector  */
                                  /*   of first cluster divisible by this  */
                                  /*   value. This can optimize clusters   */
                                  /*   to be located at start of track     */
                                  /*   or start of flash block             */
} msdos_format_request_param_t;

/*=========================================================================*\
| Function:                                                                 |
\*-------------------------------------------------------------------------*/
int msdos_format
(
/*-------------------------------------------------------------------------*\
| Purpose:                                                                  |
|     format device with msdos filesystem                                   |
+---------------------------------------------------------------------------+
| Input Parameters:                                                         |
\*-------------------------------------------------------------------------*/
 const char *devname,                        /* device name                */
 const msdos_format_request_param_t *rqdata  /* requested fmt parameters   */
                                             /* set to NULL for automatic  */
                                             /* determination              */
 );
/*-------------------------------------------------------------------------*\
| Return Value:                                                             |
|    0, if success, -1 and errno if failed                                  |
\*=========================================================================*/

#ifdef __cplusplus
}
#endif

#endif
