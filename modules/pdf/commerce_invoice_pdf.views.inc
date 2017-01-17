<?php

/**
 * @file
 * Views integration for the Commerce Invoice PDF module.
 */

/**
 * Implements hook_views_data().
 */
function commerce_invoice_pdf_views_data() {
  $data = [];

  $data['commerce_invoice']['pdf'] = [
    'title' => t('PDF'),
    'help' => t('A link to download a PDF file for this invoice.'),
    'field' => [
      'handler' => \Drupal\commerce_invoice_pdf\Views\PdfFieldHandler::class,
      'click sortable' => FALSE,
    ],
    'real field' => 'invoice_id',
  ];

  $data['commerce_order']['commerce_invoice_pdf'] = array(
    'title' => t('Invoice PDF'),
    'help' => t('A link to download a PDF invoice for this order.'),
    'field' => array(
      'handler' => \Drupal\commerce_invoice_pdf\Views\PdfOrderFieldHandler::class,
      'click sortable' => FALSE,
    ),
    'real field' => 'order_id',
  );

  return $data;
}
