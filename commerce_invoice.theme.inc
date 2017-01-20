<?php
/**
 * @file
 * Theme functions for the Commerce Invoice module.
 */

use Drupal\commerce_invoice\InvoiceNumber\InvoiceNumber;

/**
 * Pre-processing for theming an invoice number.
 *
 * @param array &$variables
 */
function template_preprocess_commerce_invoice_number(array &$variables) {
  if (!empty($variables['invoice_number'])
    && $variables['invoice_number'] instanceof InvoiceNumber) {
    /** @var InvoiceNumber $number */
    $number = $variables['invoice_number'];
    $variables['key'] = $number->getKey();
    $variables['pattern_name'] = $number->getPatternName();
    if ($number->pattern->skip_sequence) {
      $variables['sequence'] = '';
    }
    else {
      $variables['sequence'] = $number->getSequence();
    }
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
  if (!strlen($variables['key'])) {
    $invoice_number = (string) $variables['sequence'];
  }
  elseif (strpos($variables['key'], InvoiceNumber::SEQUENCE_TOKEN) !== FALSE) {
    $invoice_number = str_replace(InvoiceNumber::SEQUENCE_TOKEN, $variables['sequence'], $variables['key']);
  }
  else {
    $invoice_number = $variables['key'];
    if (!empty($variables['sequence'])) {
      $invoice_number .= '_' . $variables['sequence'];
    }
  }

  return $variables['sanitize'] ? check_plain($invoice_number) : $invoice_number;
}
