<?php

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
}
