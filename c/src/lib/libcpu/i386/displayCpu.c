/*  displayCpu.c
 *
 *  This file contains code for displaying the Intel Cpu identification
 *  that has been performed by checkCPUtypeSetCr0 function.
 *
 *  COPYRIGHT (c) 1998 valette@crf.canon.fr
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id$
 */

/*
 * Tell us the machine setup..
 */
#include <stdio.h>
#include <libcpu/cpu.h>
#include <string.h>
#include <libcpu/cpuModel.h>
#include <rtems/bspIo.h>
#include <rtems.h>

unsigned char Cx86_step = 0;
static const char *Cx86_type[] = {
	"unknown", "1.3", "1.4", "1.5", "1.6", "2.4", "2.5", "2.6", "2.7 or 3.7", "4.2"
	};

static const char * i486model(unsigned int nr)
{
	static const char *model[] = {
		"0","DX","SX","DX/2","4","SX/2","6","DX/2-WB","DX/4","DX/4-WB",
		"10","11","12","13","Am5x86-WT","Am5x86-WB"
	};
	if (nr < sizeof(model)/sizeof(char *))
		return model[nr];
	return NULL;
}

static const char * i586model(unsigned int nr)
{
	static const char *model[] = {
		"0", "Pentium 60/66","Pentium 75+","OverDrive PODP5V83",
		"Pentium MMX", NULL, NULL, "Mobile Pentium 75+",
		"Mobile Pentium MMX"
	};
	if (nr < sizeof(model)/sizeof(char *))
		return model[nr];
	return NULL;
}

static const char * Cx86model(void)
{
	unsigned char nr6x86 = 0;
	static const char *model[] = {
		"unknown", "6x86", "6x86L", "6x86MX", "MII"
	};
	switch (x86) {
		case 5:
			nr6x86 = ((x86_capability & (1 << 8)) ? 2 : 1); /* cx8 flag only on 6x86L */
			break;
		case 6:
			nr6x86 = 3;
			break;
		default:
			nr6x86 = 0;
	}

	/* We must get the stepping number by reading DIR1 */
	outport_byte(0x22,0xff);
        inport_byte(0x23, x86_mask);
	switch (x86_mask) {
		case 0x03:
			Cx86_step =  1;	/* 6x86MX Rev 1.3 */
			break;
		case 0x04:
			Cx86_step =  2;	/* 6x86MX Rev 1.4 */
			break;
		case 0x05:
			Cx86_step =  3;	/* 6x86MX Rev 1.5 */
			break;
		case 0x06:
			Cx86_step =  4;	/* 6x86MX Rev 1.6 */
			break;
		case 0x14:
			Cx86_step =  5;	/* 6x86 Rev 2.4 */
			break;
		case 0x15:
			Cx86_step =  6;	/* 6x86 Rev 2.5 */
			break;
		case 0x16:
			Cx86_step =  7;	/* 6x86 Rev 2.6 */
			break;
		case 0x17:
			Cx86_step =  8;	/* 6x86 Rev 2.7 or 3.7 */
			break;
		case 0x22:
			Cx86_step =  9;	/* 6x86L Rev 4.2 */
			break;
		default:
			Cx86_step = 0;
	}
	return model[nr6x86];
}

static const char * i686model(unsigned int nr)
{
	static const char *model[] = {
		"PPro A-step", "Pentium Pro"
	};
	if (nr < sizeof(model)/sizeof(char *))
		return model[nr];
	return NULL;
}

struct cpu_model_info {
	int x86;
	char *model_names[16];
};

static struct cpu_model_info amd_models[] = {
	{ 4,
	  { NULL, NULL, NULL, "DX/2", NULL, NULL, NULL, "DX/2-WB", "DX/4",
	    "DX/4-WB", NULL, NULL, NULL, NULL, "Am5x86-WT", "Am5x86-WB" }},
	{ 5,
	  { "K5/SSA5 (PR-75, PR-90, PR-100)", "K5 (PR-120, PR-133)",
	    "K5 (PR-166)", "K5 (PR-200)", NULL, NULL,
	    "K6 (166 - 266)", "K6 (166 - 300)", "K6-2 (200 - 450)",
	    "K6-3D-Plus (200 - 450)", NULL, NULL, NULL, NULL, NULL, NULL }},
};

static const char * AMDmodel(void)
{
	const char *p=NULL;
	int i;
	
	if (x86_model < 16)
		for (i=0; i<sizeof(amd_models)/sizeof(struct cpu_model_info); i++)
			if (amd_models[i].x86 == x86) {
				p = amd_models[i].model_names[(int)x86_model];
				break;
			}
	return p;
}

static const char * getmodel(int x86, int model)
{
        const char *p = NULL;
        static char nbuf[12];
	if (strncmp(x86_vendor_id, "Cyrix", 5) == 0)
		p = Cx86model();
	else if(strcmp(x86_vendor_id, "AuthenticAMD")==0)
		p = AMDmodel();
	else {
		switch (x86) {
			case 4:
				p = i486model(model);
				break;
			case 5:
				p = i586model(model);
				break;
			case 6:
				p = i686model(model);
				break;
		}
	}
        if (p)
                return p;

        sprintf(nbuf, "%d", model);
        return nbuf;
}

void printCpuInfo()
{
  int i;
  static const char *x86_cap_flags[] = {
    "fpu", "vme", "de", "pse", "tsc", "msr", "pae", "mce",
    "cx8", "apic", "10", "11", "mtrr", "pge", "mca", "cmov",
    "16", "17", "18", "19", "20", "21", "22", "mmx",
    "24", "25", "26", "27", "28", "29", "30", "31"
  };
        
  printk("cpu\t\t\t: %c86\n", x86+'0'); 
  printk("model\t\t: %s\n",
	 have_cpuid ? getmodel(x86, x86_model) : "unknown");
  if (x86_vendor_id [0] == '\0')
    strcpy(x86_vendor_id, "unknown");
  printk("vendor_id\t: %s\n", x86_vendor_id);
        
  if (x86_mask)
    if (strncmp(x86_vendor_id, "Cyrix", 5) != 0) {
      printk("stepping\t: %d\n", x86_mask);
    }
    else { 			/* we have a Cyrix */
      printk("stepping\t: %s\n", Cx86_type[Cx86_step]);
    }
  else
    printk("stepping\t: unknown\n");
        
  printk("fpu\t\t\t: %s\n", (hard_math ? "yes" : "no"));
  printk("cpuid\t\t: %s\n", (have_cpuid ? "yes" : "no"));
  printk("flags\t\t:");
  for ( i = 0 ; i < 32 ; i++ ) {
    if ( x86_capability & (1 << i) ) {
      printk(" %s", x86_cap_flags[i]);
    }
  }
  printk("\n");
}
