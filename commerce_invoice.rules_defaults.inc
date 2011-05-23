<?php

/**
 * @file
 * Default rule configurations for Commerce Invoice.
 */

/**
 * Implements hook_default_rules_configuration().
 */
function commerce_invoice_default_rules_configuration() {

  $rules = array();

  // Add a reaction rule to generate an invoice number
  // when an order is completed
  $rule = rules_reaction_rule();

  $rule->label = t('Generate invoice when order is completed');
  $rule->active = TRUE;

  $rule
    ->event('commerce_order_update')
    ->condition('data_is', array(
      'data:select' => 'order:status',
      'op' => '==',
      'value' => 'completed'
    ))
    ->action('commerce_invoice_generate', array(
      'order' => 'order',
    ));

  $rules['commerce_invoice_generate_when_completed'] = $rule;

  return $rules;
}
