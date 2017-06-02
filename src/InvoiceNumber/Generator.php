<?php
/**
 * @file
 * Invoice Number Generator
 */

namespace Drupal\commerce_invoice\InvoiceNumber;

use Drupal\commerce_invoice\Entity\Invoice;
use Drupal\commerce_invoice\Entity\InvoiceNumberPattern;

/**
 * Invoice number generator.
 */
class Generator {

  /** @var string */
  protected $name;

  /** @var string */
  protected $pattern;

  /**
   * Constructor.
   *
   * @param \Drupal\commerce_invoice\Entity\InvoiceNumberPattern $pattern
   */
  public function __construct(InvoiceNumberPattern $pattern) {
    $this->name = $pattern->name;
    $this->pattern = $pattern->pattern;
  }

  /**
   * Returns the key which differentiates sequential numbers.
   *
   * @return string
   */
  protected function getKey(Invoice $invoice = NULL) {
    return token_replace($this->pattern, ['commerce_invoice' => $invoice]);
  }

  /**
   * Returns the next invoice number for the pattern.
   */
  public function getNext(Invoice $invoice = NULL) {
    $key = $this->getKey($invoice);

    return new InvoiceNumber($this->getNextSequence($key), $key, $this->name);
  }

  /**
   * Calculates the next sequential number for this pattern.
   *
   * @param string $key
   *
   * @return int
   */
  protected function getNextSequence($key) {
    $last = $this->getLastSequence($key) ?: 0;

    return $last + 1;
  }

  /**
   * Finds the last invoice number generated for this pattern.
   *
   * @param string $key
   *
   * @return int|FALSE
   *   The last number or FALSE if no previous number is found.
   */
  protected function getLastSequence($key) {
    $query = db_select('commerce_invoice', 'ci')
      ->fields('ci', array('number_sequence'))
      ->condition('number_pattern', $this->name)
      ->condition('number_key', $key)
      ->orderBy('number_sequence', 'DESC')
      ->range(0, 1);
    $last = $query->execute()->fetchField();

    return $last !== FALSE ? (int) $last : FALSE;
  }
}
