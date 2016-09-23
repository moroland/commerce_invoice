<?php

/**
 * @file
 * Default views for the Commerce Invoice PDF module.
 */

/**
 * Implements hook_views_default_views_alter().
 */
function commerce_invoice_pdf_views_default_views_alter(&$views) {
  // Add the PDF link by default to the admin View for invoices.
  if (isset($views['commerce_invoice_invoices'])) {
    $handler = $views['commerce_invoice_invoices']->display['default']->handler;
    $handler->display->display_options['fields']['pdf']['id'] = 'pdf';
    $handler->display->display_options['fields']['pdf']['table'] = 'commerce_invoice';
    $handler->display->display_options['fields']['pdf']['field'] = 'pdf';
    $handler->display->display_options['fields']['pdf']['label'] = 'PDF';
    if (isset($handler->display->display_options['fields']['ctools_dropdown'])) {
      $handler->display->display_options['fields']['pdf']['exclude'] = TRUE;
      $dropdown = $handler->display->display_options['fields']['ctools_dropdown'];
      unset($handler->display->display_options['fields']['ctools_dropdown']);
      $handler->display->display_options['fields']['ctools_dropdown'] = $dropdown;
      $handler->display->display_options['fields']['ctools_dropdown']['fields']['pdf'] = 'pdf';
    }
  }
}
