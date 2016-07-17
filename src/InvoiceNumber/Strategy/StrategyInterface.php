<?php

namespace Drupal\commerce_invoice\InvoiceNumber\Strategy;

use Drupal\commerce_invoice\InvoiceNumber\InvoiceNumber;

interface StrategyInterface {

  /**
   * Returns the name of this strategy.
   *
   * @return string
   */
  public function getName();

  /**
   * Sets the name of this strategy.
   *
   * @param string $name
   */
  public function setName($name);

  /**
   * Returns the next invoice number for this strategy.
   *
   * @return InvoiceNumber
   */
  public function getNext();

}
