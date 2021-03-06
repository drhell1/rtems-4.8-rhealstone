/*===============================================================*\
| Project: RTEMS virtex BSP                                       |
+-----------------------------------------------------------------+
| Partially based on the code references which are named below.   |
| Adaptions, modifications, enhancements and any recent parts of  |
| the code are:                                                   |
|                    Copyright (c) 2007                           |
|                    Embedded Brains GmbH                         |
|                    Obere Lagerstr. 30                           |
|                    D-82178 Puchheim                             |
|                    Germany                                      |
|                    rtems@embedded-brains.de                     |
+-----------------------------------------------------------------+
| The license and distribution terms for this file may be         |
| found in the file LICENSE in this distribution or at            |
|                                                                 |
| http://www.rtems.com/license/LICENSE.                           |
|                                                                 |
+-----------------------------------------------------------------+
| this file contains the irq controller handler                   |
\*===============================================================*/
#include <libcpu/spr.h>
#include <bsp/irq.h>
#include <bsp.h>
#include <libcpu/raw_exception.h>
#include <rtems/bspIo.h>
#include <rtems/powerpc/powerpc.h>
#include <bsp/vectors.h>

static rtems_irq_connect_data rtemsIrqTbl[BSP_IRQ_NUMBER];
rtems_irq_connect_data *BSP_rtems_irq_tbl;
rtems_irq_global_settings* BSP_rtems_irq_config;

/***********************************************************
 * dummy functions for on/off/isOn calls
 * these functions just do nothing fulfill the semantic
 * requirements to enable/disable a certain interrupt or exception
 */
void BSP_irq_nop_func(const rtems_irq_connect_data *unused)
{
  /*
   * nothing to do
   */
}

void BSP_irq_nop_hdl(void *hdl)
{
  /*
   * nothing to do
   */
}

int BSP_irq_true_func(const rtems_irq_connect_data *unused)
{
  /*
   * nothing to do
   */
  return TRUE;
}

/***********************************************************
 * interrupt handler and its enable/disable functions
 ***********************************************************/

/***********************************************************
 * functions to enable/disable/query external/critical interrupts
 */
void BSP_irqexc_on_fnc(rtems_irq_connect_data *conn_data)
{
  uint32_t msr_value;
  /*
   * get current MSR value
   */
  _CPU_MSR_GET(msr_value);


   msr_value |= PPC_MSR_EE;
   _CPU_MSR_SET(msr_value);
}

void BSP_irqexc_off_fnc(rtems_irq_connect_data *unused)
{
  /*
   * nothing to do
   */
}

/***********************************************************
 * High level IRQ handler called from shared_raw_irq_code_entry
 */
void C_dispatch_irq_handler (CPU_Interrupt_frame *frame, unsigned int excNum)
{


  /*
   * Handle interrupt
   */
  switch(excNum) {
#if 0
  case ASM_DEC_VECTOR:
    _CPU_MSR_GET(msr);
    new_msr = msr | MSR_EE;
    _CPU_MSR_SET(new_msr);
    
    BSP_rtems_irq_tbl[BSP_DECREMENTER].hdl
      (BSP_rtems_irq_tbl[BSP_DECREMENTER].handle);
    
    _CPU_MSR_SET(msr);
    
    break;
#endif
  case ASM_EXT_VECTOR:
    BSP_irq_handle_at_opbintc();
    break;
  case ASM_PIT_VECTOR:
    BSP_rtems_irq_tbl[BSP_PIT].hdl
      (BSP_rtems_irq_tbl[BSP_PIT].handle);    
    break;
#if 0 /* Critical interrupts not yet supported */
  case ASM_CRIT_VECTOR:
    break;
#endif
  }
}
  
void _ThreadProcessSignalsFromIrq (BSP_Exception_frame* ctx)
{
  /*
   * Process pending signals that have not already been
   * processed by _Thread_Displatch. This happens quite
   * unfrequently : the ISR must have posted an action
   * to the current running thread.
   */
  if ( _Thread_Do_post_task_switch_extension ||
       _Thread_Executing->do_post_task_switch_extension ) {
    _Thread_Executing->do_post_task_switch_extension = FALSE;
    _API_extensions_Run_postswitch();
  }
}

/***********************************************************
 * functions to set/get/remove interrupt handlers
 ***********************************************************/
int BSP_install_rtems_irq_handler  (const rtems_irq_connect_data* irq)
{
  rtems_interrupt_level level;

  /*
   * check for valid irq name
   * if invalid, print error and return 0
   */
  if (!BSP_IS_VALID_IRQ(irq->name)) {
    printk("Invalid interrupt vector %d\n",irq->name);
    return 0;
  }

  /*
   * disable interrupts
   */
  rtems_interrupt_disable(level);
  /*
   * check, that default handler is installed now
   */
  if (rtemsIrqTbl[irq->name].hdl != BSP_rtems_irq_config->defaultEntry.hdl) {
    rtems_interrupt_enable(level);
    printk("IRQ vector %d already connected\n",irq->name);
    return 0;
  }
  /*
   * store new handler data
   */
  rtemsIrqTbl[irq->name] = *irq;

  /*
   * enable irq at interrupt controller
   */
  if (BSP_IS_OPBINTC_IRQ(irq->name)) {
    BSP_irq_enable_at_opbintc(irq->name);
  }
  /*
   * call "on" function to enable interrupt at device
   */
  irq->on(irq);
  /*
   * reenable interrupts
   */
  rtems_interrupt_enable(level);

  return 1;
}

int BSP_get_current_rtems_irq_handler	(rtems_irq_connect_data* irq)
{
  rtems_interrupt_level level;
  
  /*
   * check for valid IRQ name
   */
  if (!BSP_IS_VALID_IRQ(irq->name)) {
    return 0;
  }
  rtems_interrupt_disable(level);
  /*
   * return current IRQ entry
   */
  *irq = rtemsIrqTbl[irq->name];
  rtems_interrupt_enable(level);
  return 1;
}

int BSP_remove_rtems_irq_handler  (const rtems_irq_connect_data* irq)
{
  rtems_interrupt_level level;
  
  /*
   * check for valid IRQ name
   */
  if (!BSP_IS_VALID_IRQ(irq->name)) {
    return 0;
  }
  rtems_interrupt_disable(level);
  /*
   * check, that specified handler is really connected now
   */
  if (rtemsIrqTbl[irq->name].hdl != irq->hdl) {
    rtems_interrupt_enable(level);
    return 0;
  }
  /*
   * disable interrupt at interrupt controller
   */
  if (BSP_IS_OPBINTC_IRQ(irq->name)) {
    BSP_irq_disable_at_opbintc(irq->name);
  }
  /*
   * disable interrupt at source
   */
  irq->off(irq);
  /*
   * restore default interrupt handler
   */
  rtemsIrqTbl[irq->name] = BSP_rtems_irq_config->defaultEntry;

  /*
   * reenable interrupts
   */
  rtems_interrupt_enable(level);

  return 1;
}

/***********************************************************
 * functions to set/get the basic interrupt management setup
 ***********************************************************/
/*
 * (Re) get info on current RTEMS interrupt management.
 */
int BSP_rtems_irq_mngt_get(rtems_irq_global_settings** ret_ptr)
{
  *ret_ptr = BSP_rtems_irq_config;
  return 0;
}


/*
 * set management stuff
 */
int BSP_rtems_irq_mngt_set(rtems_irq_global_settings* config)
{
  int                    i;
  rtems_interrupt_level  level;

  rtems_interrupt_disable(level);
  /*
   * store given configuration
   */
  BSP_rtems_irq_config = config;
  BSP_rtems_irq_tbl    = BSP_rtems_irq_config->irqHdlTbl;
  /*
   * enable any non-empty IRQ entries at OPBINTC
   */
  for (i =  BSP_OPBINTC_IRQ_LOWEST_OFFSET;
       i <= BSP_OPBINTC_IRQ_MAX_OFFSET;
       i++) {
    if (BSP_rtems_irq_tbl[i].hdl != config->defaultEntry.hdl) {
      BSP_irq_enable_at_opbintc(i);
      BSP_rtems_irq_tbl[i].on((&BSP_rtems_irq_tbl[i]));
    }
    else {
      BSP_rtems_irq_tbl[i].off(&(BSP_rtems_irq_tbl[i]));
      BSP_irq_disable_at_opbintc(i);
    }
  }
  /*
   * store any irq-like processor exceptions
   */
  for (i = BSP_PROCESSOR_IRQ_LOWEST_OFFSET; 
       i < BSP_PROCESSOR_IRQ_MAX_OFFSET;
       i++) {
    if (BSP_rtems_irq_tbl[i].hdl != config->defaultEntry.hdl) {
      if (BSP_rtems_irq_tbl[i].on != NULL) {
	BSP_rtems_irq_tbl[i].on
	  (&(BSP_rtems_irq_tbl[i]));
      }
    }
    else {
      if (BSP_rtems_irq_tbl[i].off != NULL) {
	BSP_rtems_irq_tbl[i].off
	  (&(BSP_rtems_irq_tbl[i]));
      }
    }
  }
  rtems_interrupt_enable(level);
  return 1;
}
/**********************************************
 * list of exception vectors to tap for interrupt handlers
 */
static rtems_raw_except_connect_data BSP_vec_desc[] = {
#if 0 /* ppc405 has no decrementer */
  {ASM_DEC_VECTOR,
   {ASM_DEC_VECTOR,
    decrementer_exception_vector_prolog_code,
    (size_t)decrementer_exception_vector_prolog_code_size
   },
   exception_nop_enable,
   exception_nop_enable,
   exception_always_enabled
  },
#endif
  {ASM_EXT_VECTOR,
   {ASM_EXT_VECTOR,
    external_exception_vector_prolog_code,
    (size_t)&external_exception_vector_prolog_code_size
   },
   exception_nop_enable,
   exception_nop_enable,
   exception_always_enabled
  },
  {ASM_PIT_VECTOR,
   {ASM_PIT_VECTOR,
    pit_exception_vector_prolog_code,
    (size_t)&pit_exception_vector_prolog_code_size
   },
   exception_nop_enable,
   exception_nop_enable,
   exception_always_enabled
  }
#if 0 /* Critical interrupts not yet supported */
  ,{ASM_CRIT_VECTOR,
   {ASM_CRIT_VECTOR,
    critical_exception_vector_prolog_code,
    critical_exception_vector_prolog_code_size
   }
   BSP_irq_nop_func,
   BSP_irq_nop_func,
   BSP_irq_true_func
  }
#endif
};

/*
 * dummy for an empty IRQ handler entry
 */ 
static rtems_irq_connect_data emptyIrq = {
  0, 		         /* Irq Name                 */
  BSP_irq_nop_hdl,       /* handler function         */
  NULL,                  /* handle passed to handler */
  BSP_irq_nop_func,      /* on function              */
  BSP_irq_nop_func,      /* off function             */
  BSP_irq_true_func      /* isOn function            */
};

static rtems_irq_global_settings initialConfig = {
  BSP_IRQ_NUMBER,    /* irqNb */
  {  0, 		         /* Irq Name                 */
     BSP_irq_nop_hdl,       /* handler function         */
     NULL,                  /* handle passed to handler */
     BSP_irq_nop_func,      /* on function              */
     BSP_irq_nop_func,      /* off function             */
     BSP_irq_true_func      /* isOn function            */
  }, /* emptyIrq */
  rtemsIrqTbl, /* irqHdlTbl  */
  0,           /* irqBase    */
  NULL         /* irqPrioTbl */
};

void BSP_rtems_irq_mng_init(unsigned cpuId)
{
  int i;
  /*
   * connect all exception vectors needed
   */
  for (i = 0;
       i < (sizeof(BSP_vec_desc) / 
	    sizeof(BSP_vec_desc[0]));
       i++) {
    if (!ppc_set_exception (&BSP_vec_desc[i])) {
      BSP_panic("Unable to initialize RTEMS raw exception\n");
    }
  }
  /*
   * setup interrupt handlers table
   */
  for (i = 0;
       i < BSP_IRQ_NUMBER;
       i++) {
    rtemsIrqTbl[i]      = emptyIrq;
    rtemsIrqTbl[i].name = i;
  }
  /*
   * init interrupt controller
   */
  opb_intc_init();
  /*
   * initialize interrupt management
   */
  if (!BSP_rtems_irq_mngt_set(&initialConfig)) {
    BSP_panic("Unable to initialize RTEMS interrupt Management!!! System locked\n");
  }  
}

