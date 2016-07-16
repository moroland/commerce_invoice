<?php

namespace Drupal\commerce_invoice\InvoiceNumber\Strategy;

use Drupal\commerce_invoice\InvoiceNumber\InvoiceNumber;

abstract class StrategyBase implements StrategyInterface {

  /**
   * Returns the key which differentiates sequential numbers.
   *
   * @return string|NULL
   *   For example, a monthly strategy would return '2016-07'. A strategy that
   *   wants the sequence to increment sequentially forever would return NULL.
   */
  abstract protected function getKey();

  /**
   * {@inheritdoc}
   */
  public function getNext() {
    $key = $this->getKey();

    return new InvoiceNumber($this->getNextSequence($key), $key, $this);
  }

  /**
   * {@inheritdoc}
   */
  public function format(InvoiceNumber $number) {
    if ($number->getKey() === NULL) {
      return (string) $number->getSequence();
    }

    return $number->getKey() . '-' . $number->getSequence();
  }

  /**
   * Calculates the next sequential number for this strategy and key.
   *
   * @param string|NULL $key
   *
   * @return int
   */
  protected function getNextSequence($key) {
    $last = $this->getLastSequence($key) ?: 0;

    return $last + 1;
  }

  /**
   * Finds the last invoice number generated for this strategy and key.
   *
   * @param string|NULL $key
   *
   * @return int|FALSE
   *   The last number or FALSE if no previous number is found.
   */
  protected function getLastSequence($key) {
    $query = db_select('commerce_invoice')
      ->fields('commerce_invoice', array('invoice_number'))
      ->condition('number_strategy', $this->getName())
      ->condition('number_key', $key)
      ->orderBy('number_sequence', 'DESC')
      ->range(0, 1);
    $last = $query->execute()->fetchField();

    return $last !== FALSE ? (int) $last : FALSE;
  }
}
