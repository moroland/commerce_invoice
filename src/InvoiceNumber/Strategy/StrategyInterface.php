<?php

namespace Drupal\commerce_invoice\InvoiceNumber\Strategy;

interface StrategyInterface {

  /**
   * Get the next invoice number for this strategy.
   *
   * @param bool $save
   *   Whether to update the last saved sequential number (default: TRUE). Set
   *   FALSE to find the next number without changing anything.
   *
   * @return string
   */
  public function getNext($save = TRUE);

}
