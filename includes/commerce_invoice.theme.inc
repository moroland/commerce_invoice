<?php
/**
 * @file
 * Theme functions for the Commerce Invoice module.
 */

/**
 * Pre-processing for theming an invoice number.
 *
 * @param array &$variables
 */
function template_preprocess_commerce_invoice_number(array &$variables) {
  if (!empty($variables['invoice_number'])
    && $variables['invoice_number'] instanceof \Drupal\commerce_invoice\InvoiceNumber\InvoiceNumber) {
    /** @var \Drupal\commerce_invoice\InvoiceNumber\InvoiceNumber $number */
    $number = $variables['invoice_number'];
    $variables['pattern'] = $number->getKey();
    $variables['sequence'] = $number->getSequence();
  }
}

/**
 * Themes an invoice number.
 *
 * @see template_preprocess_commerce_invoice_number()
 *
 * @param array $variables
 *   An array of variables containing 'sequence' and 'key'.
 *
 * @return string
 *   A sanitized string.
 */
function theme_commerce_invoice_number(array $variables) {
  if (empty($variables['sequence'])) {
    return '';
  }

  if (!strlen($variables['pattern'])) {
    return (string) $variables['sequence'];
  }

  if (strpos($variables['pattern'], '[sequence]') !== FALSE) {
    return str_replace('[sequence]', $variables['sequence'], $variables['pattern']);
  }

  return $variables['pattern'] . '--' . $variables['sequence'];
}
