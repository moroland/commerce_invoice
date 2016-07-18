<?php
/**
 * @file
 * Views integration for the Commerce Invoice module.
 */

/**
 * Implements hook_views_data().
 */
function commerce_invoice_views_data() {
  $data = [];

  $data['commerce_invoice']['invoice_number'] = [
    'title' => t('Invoice number'),
    'help' => t('The invoice number'),
    'field' => [
      'handler' => '\\Drupal\\commerce_invoice\\InvoiceNumber\\ViewsField',
      'click sortable' => TRUE,
      'real field' => 'number_sequence',
      'additional fields' => ['number_pattern', 'number_key'],
    ],
    'sort' => [
      'handler' => '\\Drupal\\commerce_invoice\\InvoiceNumber\\ViewsSort',
    ],
  ];

  return $data;
}
