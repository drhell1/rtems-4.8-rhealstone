/*
 * MC68340/349 support routines
 *
 * Geoffroy Montel
 * France Telecom - CNET/DSM/TAM/CAT
 * 4, rue du Clos Courtel
 * 35512 CESSON-SEVIGNE
 * FRANCE
 *
 * e-mail: g_montel@yahoo.com
 *
 *  $Id$
 */

#include <rtems.h>
#include <bsp.h>

/*
 * Initialize MC68340
 */
void _Init68340 (void)
{
	extern void _CopyDataClearBSSAndStart (void);
	m68k_isr_entry *vbr;
	int i;

	/*
	 * Copy  the exception vector table to system RAM
	 */
	m68k_get_vbr (vbr);
	for (i = 0; i < 256; ++i)
		M68Kvec[i] = vbr[i];
	m68k_set_vbr (M68Kvec);

	/*
	 * Copy data, clear BSS, switch stacks and call main()
	 */
	_CopyDataClearBSSAndStart ();
}
