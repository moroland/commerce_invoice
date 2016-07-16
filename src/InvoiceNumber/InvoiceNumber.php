<?php

namespace Drupal\commerce_invoice\InvoiceNumber;

class InvoiceNumber {

  protected $sequence;
  protected $key;
  protected $strategyName;

  /**
   * Constructor.
   *
   * @param int    $sequence
   * @param string $key
   * @param string $strategyName
   */
  public function __construct($sequence, $key, $strategyName) {
    $this->sequence = $sequence;
    $this->key = $key;
    $this->strategyName = $strategyName;
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
  public function getStrategyName() {
    return $this->strategyName;
  }

  /**
   * Format an invoice number as a string.
   *
   * @return string
   */
  public function __toString() {
    if (!strlen($this->key)) {
      return (string) $this->sequence;
    }

    return $this->key . '--' . $this->sequence;
  }
}
