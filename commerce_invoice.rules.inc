<?php

/**
 * @file
 * Rules integration for the Commerce Invoice module.
 */

/**
 * Implements hook_rules_condition_info().
 */
function commerce_invoice_rules_condition_info() {
  $conditions = array();

  $conditions['commerce_invoice_order_has_new_revision'] = array(
    'label' => t('Order has a new revision since the last invoice'),
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
  );

  return $actions;
}
