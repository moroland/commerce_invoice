<?php
/**
 * @file
 * Fields and instances for the Commerce Invoice module.
 */

/**
 * Default field bases for Commerce Invoice.
 *
 * @return array
 */
function commerce_invoice_default_field_bases() {
  $field_bases = array();

  $field_bases['commerce_invoice_items'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array('commerce_invoice'),
    'field_name' => 'commerce_invoice_items',
    'indexes' => array(
      'line_item_id' => array(
        0 => 'line_item_id',
      ),
    ),
    'locked' => 0,
    'module' => 'commerce_line_item',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'commerce_line_item_reference',
  );

  $field_bases['commerce_invoice_total'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array('commerce_invoice'),
    'field_name' => 'commerce_invoice_total',
    'indexes' => array(
      'currency_price' => array(
        0 => 'amount',
        1 => 'currency_code',
      ),
    ),
    'locked' => 0,
    'module' => 'commerce_price',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'commerce_price',
  );

  return $field_bases;
}

/**
 * Default field instances for Commerce Invoice.
 * 
 * @return array
 */
function commerce_invoice_default_field_instances() {
  $field_instances = array();

  $field_instances['commerce_invoice-commerce_invoice-commerce_invoice_items'] = array(
    'bundle' => 'commerce_invoice',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'commerce_line_item',
        'settings' => array(
          'view' => 'commerce_line_item_table|default',
        ),
        'type' => 'commerce_line_item_reference_view',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'commerce_invoice',
    'field_name' => 'commerce_invoice_items',
    'label' => t('Line items'),
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'commerce_line_item',
      'settings' => array(),
      'type' => 'commerce_line_item_manager',
      'weight' => 0,
    ),
  );

  $field_instances['commerce_invoice-commerce_invoice-commerce_invoice_total'] = array(
    'bundle' => 'commerce_invoice',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'commerce_price',
        'settings' => array(
          'calculation' => FALSE,
        ),
        'type' => 'commerce_price_formatted_components',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'commerce_invoice',
    'field_name' => 'commerce_invoice_total',
    'label' => t('Total'),
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'commerce_price',
      'settings' => array(
        'currency_code' => 'default',
      ),
      'type' => 'commerce_price_full',
      'weight' => 1,
    ),
  );

  return $field_instances;
}
