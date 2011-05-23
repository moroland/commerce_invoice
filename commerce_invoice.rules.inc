<?php

/**
 * @file
 * Rules integration for invoices.
 *
 * @addtogroup rules
 * @{
 */
 
/**
 * Implements hook_rules_action_info().
 */
function commerce_invoice_rules_action_info() {
  $actions = array();

  $actions['commerce_invoice_generate'] = array(
    'label' => t('Generate invoice'),
    'parameter' => array(
      'order' => array(
        'type' => 'commerce_order',
        'label' => t('Order to update'),
      ),
    ),
    'group' => t('Commerce Invoice'),
    'callbacks' => array(
      'execute' => 'commerce_invoice_rules_generate',
    ),
  );
  
  return $actions;
}

function commerce_invoice_rules_generate($order) {
  $invoice = commerce_invoice_new($order->order_id);
  commerce_invoice_save($invoice);
}

  
