<?php

/**
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

  return $data;
}
