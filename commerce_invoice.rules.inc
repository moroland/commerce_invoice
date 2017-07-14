<?php

/**
 * @file
 * Rules integration for the Commerce Invoice module.
 */
use Drupal\commerce_invoice\Entity\InvoiceNumberPattern;

/**
 * Implements hook_rules_condition_info().
 */
function commerce_invoice_rules_condition_info() {
  $conditions = array();

  $conditions['commerce_invoice_order_changed'] = array(
    'label' => t('Order has changed since the last invoice'),
    'parameter' => array(
      'order' => array(
        'type' => 'commerce_order',
        'label' => t('The order'),
      ),
    ),
    'group' => t('Commerce Invoice'),
  );

  $conditions['commerce_invoice_order_has_invoice'] = array(
    'label' => t('Order has a current invoice'),
    'parameter' => array(
      'order' => array(
        'type' => 'commerce_order',
        'label' => t('The order'),
      ),
    ),
    'group' => t('Commerce Invoice'),
  );

  return $conditions;
}

/**
 * Implements hook_rules_action_info().
 */
function commerce_invoice_rules_action_info() {
  $actions = array();

  $actions['commerce_invoice_create_from_order'] = array(
    'base' => 'commerce_invoice_action_create_from_order',
    'label' => t('Create an invoice'),
    'parameter' => array(
      'order' => array(
        'type' => 'commerce_order',
        'label' => t('The order'),
      ),
      'pattern' => array(
        'type' => 'commerce_invoice_number_pattern',
        'label' => t('The invoice number pattern'),
        'optional' => TRUE,
        'options list' => 'commerce_invoice_number_pattern_options_list',
        'default value' => \Drupal\commerce_invoice\Entity\InvoiceNumberPattern::getDefaultName(),
      ),
      'cancel_existing' => array(
        'type' => 'boolean',
        'label' => t('Cancel existing'),
        'description' => t('Cancel all other invoices for the order.'),
        'default value' => TRUE,
      ),
    ),
    'provides' => array(
      'commerce_invoice' => array(
        'type' => 'commerce_invoice',
        'label' => t('Created invoice')
      ),
    ),
    'group' => t('Commerce Invoice'),
  );

  $actions['commerce_invoice_load_current'] = array(
    'base' => 'commerce_invoice_action_load_current',
    'label' => t('Fetch current invoice in order'),
    'parameter' => array(
      'order' => array(
        'type' => 'commerce_order',
        'label' => t('The order'),
      ),
    ),
    'provides' => array(
      'commerce_invoice' => array(
        'type' => 'commerce_invoice',
        'label' => t('Fetched invoice'),
      ),
    ),
    'group' => t('Commerce Invoice'),
  );

  return $actions;
}

/**
 * Rules action: Fetch current invoice in order.
 *
 * @param object $order
 *
 * @return array
 *   An array containing the invoice keyed as commerce_invoice, or an empty
 *   array if no invoice exists.
 */
function commerce_invoice_action_load_current($order) {
  $invoice = commerce_invoice_load_current($order);

  return $invoice ? array('commerce_invoice' => $invoice) : array();
}

/**
 * Action: Create invoice for a given order.
 */
function commerce_invoice_action_create_from_order($order, $pattern = NULL, $cancel_existing = TRUE) {
  if (is_string($pattern)) {
    $pattern = commerce_invoice_number_pattern_load($pattern);
  }
  $invoice = commerce_invoice_create_from_order($order, $pattern, $cancel_existing);

  return ['commerce_invoice' => $invoice];
}

/**
 * Rules condition: whether the order has a current invoice.
 *
 * @return bool
 */
function commerce_invoice_order_has_invoice($order) {
  return commerce_invoice_load_current($order) ? TRUE : FALSE;
}
