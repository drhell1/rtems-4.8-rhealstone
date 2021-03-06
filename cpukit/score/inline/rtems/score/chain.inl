/**
 *  @file  rtems/score/chain.inl
 *
 *  This include file contains the bodies of the routines which are
 *  associated with doubly linked chains and inlined.
 *
 *  @note  The routines in this file are ordered from simple
 *         to complex.  No other Chain Handler routine is referenced
 *         unless it has already been defined.
 */

/*
 *  COPYRIGHT (c) 1989-2006.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id$
 */

#ifndef _RTEMS_SCORE_CHAIN_INL
#define _RTEMS_SCORE_CHAIN_INL

/**
 *  @addtogroup ScoreChain 
 *  @{
 */

/** @brief Are Two Nodes Equal
 *
 *  This function returns TRUE if @a left and @a right are equal,
 *  and FALSE otherwise.
 *
 *  @param[in] left is the node on the left hand side of the comparison.
 *  @param[in] right is the node on the left hand side of the comparison.
 *
 *  @return This function returns TRUE if @a left and @a right are equal,
 *          and FALSE otherwise.
 */
RTEMS_INLINE_ROUTINE boolean _Chain_Are_nodes_equal(
  const Chain_Node *left,
  const Chain_Node *right
)
{
  return left == right;
}

/** @brief Is this Chain Control Pointer Null
 *
 *  This function returns TRUE if the_chain is NULL and FALSE otherwise.
 *
 *  @param[in] the_chain is the chain to be checked for empty status.
 *
 *  @return This method returns TRUE if the_chain is NULL and FALSE otherwise.
 */
RTEMS_INLINE_ROUTINE boolean _Chain_Is_null(
  const Chain_Control *the_chain
)
{
  return (the_chain == NULL);
}

/** @brief Is the Chain Node Pointer NULL
 *
 *  This function returns TRUE if the_node is NULL and FALSE otherwise.
 *
 *  @param[in] the_node is the node pointer to check.
 *
 *  @return This method returns TRUE if the_node is NULL and FALSE otherwise.
 */
RTEMS_INLINE_ROUTINE boolean _Chain_Is_null_node(
  const Chain_Node *the_node
)
{
  return (the_node == NULL);
}

/** @brief Return pointer to Chain Head
 *
 *  This function returns a pointer to the first node on the chain.
 *
 *  @param[in] the_chain is the chain to be operated upon.
 *
 *  @return This method returns the permanent head node of the chain.
 */
RTEMS_INLINE_ROUTINE Chain_Node *_Chain_Head(
  Chain_Control *the_chain
)
{
   return (Chain_Node *) the_chain;
}

/** @brief Return pointer to Chain Tail
 *
 *  This function returns a pointer to the last node on the chain.
 *
 *  @param[in] the_chain is the chain to be operated upon.
 *
 *  @return This method returns the permanent tail node of the chain.
 */
RTEMS_INLINE_ROUTINE Chain_Node *_Chain_Tail(
  Chain_Control *the_chain
)
{
   return (Chain_Node *) &the_chain->permanent_null;
}

/** @brief Is the Chain Empty
 *
 *  This function returns TRUE if there a no nodes on @a the_chain and
 *  FALSE otherwise.
 *
 *  @param[in] the_chain is the chain to be operated upon.
 *
 *  @return This function returns TRUE if there a no nodes on @a the_chain and
 *  FALSE otherwise.
 */
RTEMS_INLINE_ROUTINE boolean _Chain_Is_empty(
  Chain_Control *the_chain
)
{
  return (the_chain->first == _Chain_Tail(the_chain));
}

/** @brief Is this the First Node on the Chain
 *
 *  This function returns TRUE if the_node is the first node on a chain and
 *  FALSE otherwise.
 *
 *  @param[in] the_node is the node the caller wants to know if it is
 *             the first node on a chain.
 *
 *  @return This function returns TRUE if @a the_node is the first node on
 *          a chain and FALSE otherwise.
 */
RTEMS_INLINE_ROUTINE boolean _Chain_Is_first(
  const Chain_Node *the_node
)
{
  return (the_node->previous == NULL);
}

/** @brief Is this the Last Node on the Chain
 *
 *  This function returns TRUE if @a the_node is the last node on a chain and
 *  FALSE otherwise.
 *
 *  @param[in] the_node is the node to check as the last node.
 *
 *  @return This function returns TRUE if @a the_node is the last node on
 *          a chain and FALSE otherwise.
 */
RTEMS_INLINE_ROUTINE boolean _Chain_Is_last(
  const Chain_Node *the_node
)
{
  return (the_node->next == NULL);
}

/** @brief Does this Chain have only One Node
 *
 *  This function returns TRUE if there is only one node on @a the_chain and
 *  FALSE otherwise.
 *
 *  @param[in] the_chain is the chain to be operated upon.
 *
 *  @return This function returns TRUE if there is only one node on
 *          @a the_chain and FALSE otherwise.
 */
RTEMS_INLINE_ROUTINE boolean _Chain_Has_only_one_node(
  const Chain_Control *the_chain
)
{
  return (the_chain->first == the_chain->last);
}

/** @brief Is this Node the Chain Head
 *
 *  This function returns TRUE if @a the_node is the head of the_chain and
 *  FALSE otherwise.
 *
 *  @param[in] the_chain is the chain to be operated upon.
 *  @param[in] the_node is the node to check for being the Chain Head.
 *
 *  @return This function returns TRUE if @a the_node is the head of
 *          @a the_chain and FALSE otherwise.
 */
RTEMS_INLINE_ROUTINE boolean _Chain_Is_head(
  Chain_Control *the_chain,
  const Chain_Node    *the_node
)
{
   return (the_node == _Chain_Head(the_chain));
}

/** @brief Is this Node the Chail Tail
 *
 *  This function returns TRUE if the_node is the tail of the_chain and
 *  FALSE otherwise.
 *
 *  @param[in] the_chain is the chain to be operated upon.
 *  @param[in] the_node is the node to check for being the Chain Tail.
 */
RTEMS_INLINE_ROUTINE boolean _Chain_Is_tail(
  Chain_Control *the_chain,
  const Chain_Node    *the_node
)
{
   return (the_node == _Chain_Tail(the_chain));
}

/** @brief Initialize this Chain as Empty
 *
 *  This routine initializes the specified chain to contain zero nodes.
 *
 *  @param[in] the_chain is the chain to be initialized.
 */
RTEMS_INLINE_ROUTINE void _Chain_Initialize_empty(
  Chain_Control *the_chain
)
{
  the_chain->first          = _Chain_Tail(the_chain);
  the_chain->permanent_null = NULL;
  the_chain->last           = _Chain_Head(the_chain);
}

/** @brief Extract this Node (unprotected)
 *
 *  This routine extracts the_node from the chain on which it resides.
 *  It does NOT disable interrupts to ensure the atomicity of the
 *  extract operation.
 *
 *  @param[in] the_node is the node to be extracted.
 */
RTEMS_INLINE_ROUTINE void _Chain_Extract_unprotected(
  Chain_Node *the_node
)
{
  Chain_Node *next;
  Chain_Node *previous;

  next           = the_node->next;
  previous       = the_node->previous;
  next->previous = previous;
  previous->next = next;
}

/** @brief Get the First Node (unprotected)
 *
 *  This function removes the first node from the_chain and returns
 *  a pointer to that node.  It does NOT disable interrupts to ensure
 *  the atomicity of the get operation.
 *
 *  @param[in] the_chain is the chain to attempt to get the first node from.
 *
 *  @return This method returns the first node on the chain even if it is
 *          the Chain Tail.
 *
 *  @note This routine assumes that there is at least one node on the chain
 *        and always returns a node even if it is the Chain Tail.
 */
RTEMS_INLINE_ROUTINE Chain_Node *_Chain_Get_first_unprotected(
  Chain_Control *the_chain
)
{
  Chain_Node  *return_node;
  Chain_Node  *new_first;

  return_node         = the_chain->first;
  new_first           = return_node->next;
  the_chain->first    = new_first;
  new_first->previous = _Chain_Head(the_chain);

  return return_node;
}

/** @brief Get the First Node (unprotected)
 *
 *  This function removes the first node from the_chain and returns
 *  a pointer to that node.  If the_chain is empty, then NULL is returned.
 *
 *  @param[in] the_chain is the chain to attempt to get the first node from.
 *
 *  @return This method returns the first node on the chain or NULL if the
 *          chain is empty.
 *
 *  @note It does NOT disable interrupts to ensure the atomicity of the
 *        get operation.
 */
RTEMS_INLINE_ROUTINE Chain_Node *_Chain_Get_unprotected(
  Chain_Control *the_chain
)
{
  if ( !_Chain_Is_empty(the_chain))
    return _Chain_Get_first_unprotected(the_chain);
  else
    return NULL;
}

/** @brief Insert a Node (unprotected)
 *
 *  This routine inserts the_node on a chain immediately following
 *  after_node.
 *
 *  @param[in] after_node is the node which will precede @a the_node on the
 *             chain.
 *  @param[in] the_node is the node to be inserted.
 *
 *  @note It does NOT disable interrupts to ensure the atomicity
 *        of the extract operation.
 */
RTEMS_INLINE_ROUTINE void _Chain_Insert_unprotected(
  Chain_Node *after_node,
  Chain_Node *the_node
)
{
  Chain_Node *before_node;

  the_node->previous    = after_node;
  before_node           = after_node->next;
  after_node->next      = the_node;
  the_node->next        = before_node;
  before_node->previous = the_node;
}

/** @brief Append a Node (unprotected) 
 *
 *  This routine appends the_node onto the end of the_chain.
 *
 *  @param[in] the_chain is the chain to be operated upon.
 *  @param[in] the_node is the node to be appended.
 *
 *  @note It does NOT disable interrupts to ensure the atomicity of the
 *        append operation.
 */
RTEMS_INLINE_ROUTINE void _Chain_Append_unprotected(
  Chain_Control *the_chain,
  Chain_Node    *the_node
)
{
  Chain_Node *old_last_node;

  the_node->next      = _Chain_Tail(the_chain);
  old_last_node       = the_chain->last;
  the_chain->last     = the_node;
  old_last_node->next = the_node;
  the_node->previous  = old_last_node;
}

/** @brief Prepend a Node (unprotected)
 *
 *  This routine prepends the_node onto the front of the_chain.
 *
 *  @param[in] the_chain is the chain to be operated upon.
 *  @param[in] the_node is the node to be prepended.
 *
 *  @note It does NOT disable interrupts to ensure the atomicity of the
 *        prepend operation.
 */
RTEMS_INLINE_ROUTINE void _Chain_Prepend_unprotected(
  Chain_Control *the_chain,
  Chain_Node    *the_node
)
{
  _Chain_Insert_unprotected(_Chain_Head(the_chain), the_node);
}

/** @brief Prepend a Node (protected)
 *
 *  This routine prepends the_node onto the front of the_chain.
 *
 *  @param[in] the_chain is the chain to be operated upon.
 *  @param[in] the_node is the node to be prepended.
 *
 *  @note It disables interrupts to ensure the atomicity of the
 *        prepend operation.
 */
RTEMS_INLINE_ROUTINE void _Chain_Prepend(
  Chain_Control *the_chain,
  Chain_Node    *the_node
)
{
  _Chain_Insert(_Chain_Head(the_chain), the_node);
}

/**@}*/

#endif
/* end of include file */
