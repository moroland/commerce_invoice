<?php

namespace Drupal\commerce_invoice\InvoiceNumber;

use Drupal\commerce_invoice\InvoiceNumber\Strategy\StrategyInterface;

class InvoiceNumber {

  protected $sequence;
  protected $key;
  protected $strategy;

  /**
   * Constructor.
   *
   * @param int               $sequence
   * @param string|NULL       $key
   * @param StrategyInterface $strategy
   */
  public function __construct($sequence, $key, StrategyInterface $strategy) {
    $this->sequence = $sequence;
    $this->key = $key;
    $this->strategy = $strategy;
  }

  /**
   * @return int
   */
  public function getSequence() {
    return $this->sequence;
  }

  /**
   * @return NULL|string
   */
  public function getKey() {
    return $this->key;
  }

  /**
   * @return string
   */
  public function getStrategyName() {
    return $this->strategy->getName();
  }

  /**
   * Format an invoice number as a string.
   *
   * @return string
   */
  public function __toString() {
    return $this->strategy->format($this);
  }
}
