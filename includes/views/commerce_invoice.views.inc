<?php

/**
 * Export Drupal Commerce invoices to Views.
 */

/**
 * Implements hook_views_data()
 */
function commerce_invoice_views_data() {
  $data = array();

  $data['commerce_invoice']['table']['group']  = t('Commerce Invoice');

  $data['commerce_invoice']['table']['base'] = array(
    'field' => 'invoice_number',
    'title' => t('Commerce Invoice'),
    'help' => t('Invoice generated for an order.'),
  );
  
  // Expose the invoice ID.
  $data['commerce_invoice']['invoice_id'] = array(
    'title' => t('Invoice ID', array(), array('context' => 'a drupal commerce invoice')),
    'help' => t('The unique internal identifier of the invoice.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      /*'name field' => 'order_number',
      'numeric' => TRUE,
      'validate type' => 'order_id',*/
    ),
  );
  
  // Expose the invoice number.
  $data['commerce_invoice']['invoice_number'] = array(
    'title' => t('Invoice number', array(), array('context' => 'a drupal commerce invoice')),
    'help' => t('The unique invoice number.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  // Expose the order id
  $data['commerce_invoice']['order_id'] = array(
    'title' => t('Order id'),
    'help' => t('The order id associated to the invoice.'),
    'relationship' => array(
      'title' => t('Order'),
      'help' => t("Relate this invoice to its order"),
      'handler' => 'views_handler_relationship',
      'base' => 'commerce_order',
      'base field' => 'order_id',
      'field' => 'order_id',
      'label' => t('Order associated to the invoice'),
    ),
  );
  
  // Expose the created timestamp.
  $data['commerce_invoice']['created'] = array(
    'title' => t('Created date'),
    'help' => t('The date the invoice was created.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );
  
  return $data;
}

/**
 * Implements hook_views_data_alter()
 */
function commerce_invoice_views_data_alter(&$data) {
  $data['commerce_order']['invoice_id'] = array(
    'title' => t('Invoice id'),
    'help' => t('The invoice id associated with this order.'),
    'relationship' => array(
      'title' => t('Invoice'),
      'help' => t("Relate this order to its invoice"),
      'handler' => 'views_handler_relationship',
      'base' => 'commerce_invoice',
      'base field' => 'order_id',
      'relationship field' => 'order_id',
      'field' => 'order_id',
      'label' => t('Invoice associated to the order'),
    ),
  );
}
