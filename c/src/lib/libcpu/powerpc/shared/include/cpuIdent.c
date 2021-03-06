/*
 *  cpuIdent.c -- Cpu identification code
 *
 *  Copyright (C) 1999 Eric Valette. valette@crf.canon.fr
 *
 *  Added MPC8260 Andy Dachs <a.dachs@sstl.co.uk>
 *  Surrey Satellite Technology Limited
 *
 *  The license and distribution terms for this file may be
 *  found in found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 * $Id$
 *
 */

#include <libcpu/cpuIdent.h>
#include <libcpu/spr.h>
#include <rtems/bspIo.h>

/*
 * Generate inline code to read Processor Version Register
 */
SPR_RO(PVR)

ppc_cpu_id_t current_ppc_cpu = PPC_UNKNOWN;
ppc_cpu_revision_t current_ppc_revision = 0xff;

char *get_ppc_cpu_type_name(ppc_cpu_id_t cpu)
{
  switch (cpu) {
    case PPC_405:		return "PPC405";
    case PPC_601:		return "MPC601";
    case PPC_5XX:		return "MPC5XX";
    case PPC_603:		return "MPC603";
    case PPC_603ev:		return "MPC603ev";
    case PPC_604:		return "MPC604";
    case PPC_750:		return "MPC750";
    case PPC_7400:		return "MPC7400";
    case PPC_7455:		return "MPC7455";
    case PPC_7457:              return "MPC7457";
    case PPC_603le:		return "MPC603le";
    case PPC_604e:		return "MPC604e";
    case PPC_604r:		return "MPC604r";
    case PPC_620:		return "MPC620";
    case PPC_860:		return "MPC860";
    case PPC_8260:		return "MPC8260";
    case PPC_8245:		return "MPC8245";
	case PPC_PSIM:		return "PSIM";
    default:
      printk("Unknown CPU value of 0x%x. Please add it to "
             "<libcpu/powerpc/shared/include/cpuIdent.c>\n", cpu );
  }
  return "UNKNOWN";
}

ppc_cpu_id_t get_ppc_cpu_type()
{
  unsigned int pvr = (_read_PVR() >> 16);
  current_ppc_cpu = (ppc_cpu_id_t) pvr;
  switch (pvr) {
    case PPC_405:
    case PPC_601:
    case PPC_5XX:
    case PPC_603:
    case PPC_603ev:
    case PPC_603le:
    case PPC_604:
    case PPC_604r:
    case PPC_750:
    case PPC_7400:
    case PPC_7455:
    case PPC_7457:
    case PPC_604e:
    case PPC_620:
    case PPC_860:
    case PPC_8260:
    case PPC_8245:
	case PPC_PSIM:
      return current_ppc_cpu;
    default:
      printk("Unknown PVR value of 0x%x. Please add it to "
             "<libcpu/powerpc/shared/include/cpuIdent.c>\n", pvr );
    return PPC_UNKNOWN;
  }
}

ppc_cpu_revision_t get_ppc_cpu_revision()
{
  ppc_cpu_revision_t rev = (ppc_cpu_revision_t) (_read_PVR() & 0xffff);
  current_ppc_revision = rev;
  return rev;
}
