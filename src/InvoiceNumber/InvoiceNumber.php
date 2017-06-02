<?php
/**
 * @file
 * Invoice Number
 */

namespace Drupal\commerce_invoice\InvoiceNumber;

class InvoiceNumber {

  const SEQUENCE_TOKEN = '{SEQUENCE}';

  protected $sequence;
  protected $key;
  protected $patternName;

  /**
   * Constructor.
   *
   * @param int    $sequence
   * @param string $key
   * @param string $patternName
   */
  public function __construct($sequence, $key, $patternName) {
    $this->sequence = $sequence;
    $this->key = $key;
    $this->patternName = $patternName;
    $this->pattern = commerce_invoice_number_pattern_load($patternName);
  }

  /**
   * @return int
   */
  public function getSequence() {
    return $this->sequence;
  }

  /**
   * @return string
   */
  public function getKey() {
    return $this->key;
  }

  /**
   * @return string
   */
  public function getPatternName() {
    return $this->patternName;
  }

  /**
   * Magic method to convert the invoice number to a string.
   *
   * @see theme_commerce_invoice_number()
   *
   * @return string
   */
  public function __toString() {
    return theme('commerce_invoice_number', ['invoice_number' => $this, 'sanitize' => FALSE]);
  }
}
