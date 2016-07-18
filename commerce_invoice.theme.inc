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
    $variables['key'] = $number->getKey();
    $variables['pattern_name'] = $number->getPatternName();
    $variables['sequence'] = $number->getSequence();
  }
}

/**
 * Themes an invoice number.
 *
 * @see template_preprocess_commerce_invoice_number()
 *
 * @param array $variables
 *   An array of variables containing 'sequence', 'key', and 'pattern_name'.
 *
 * @return string
 *   A sanitized string.
 */
function theme_commerce_invoice_number(array $variables) {
  if (empty($variables['sequence'])) {
    return '';
  }

  if (!strlen($variables['key'])) {
    $invoice_number = (string) $variables['sequence'];
  }
  elseif (strpos($variables['key'], '[sequence]') !== FALSE) {
    $invoice_number = str_replace('[sequence]', $variables['sequence'], $variables['key']);
  }
  else {
    $invoice_number = $variables['key'] . '_' . $variables['sequence'];
  }

  return check_plain($invoice_number);
}
