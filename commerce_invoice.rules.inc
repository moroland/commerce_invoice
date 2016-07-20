<?php

/**
 * @file
 * Rules integration for the Commerce Invoice module.
 */

/**
 * Implements hook_rules_action_info().
 */
function commerce_invoice_rules_action_info() {
  $actions = array();

  $actions['commerce_invoice_create'] = array(
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
      ),
      'save_revision' => array(
        'type' => 'boolean',
        'label' => t('Save a new order revision when creating the invoice'),
        'default value' => TRUE,
      ),
    ),
    'group' => t('Commerce Invoice'),
    'callbacks' => array(
      'execute' => 'commerce_invoice_create_from_order',
    ),
  );

  return $actions;
}
