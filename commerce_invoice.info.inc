<?php

/**
 * @file
 * Provides metadata for the invoice entity.
 */

/**
 * Implements hook_entity_property_info().
 */
function commerce_invoice_entity_property_info() {
  $info = array();

  // Add meta-data about the basic commerce_invoice properties.
  $properties = &$info['commerce_invoice']['properties'];

  $properties['status'] = array(
    'type' => 'text',
    'label' => t('Status'),
    'description' => t('The current status of the invoice.'),
    'setter callback' => 'entity_property_verbatim_set',
    'options list' => 'commerce_invoice_statuses',
    'required' => TRUE,
    'schema field' => 'invoice_status',
  );
  return $info;
}