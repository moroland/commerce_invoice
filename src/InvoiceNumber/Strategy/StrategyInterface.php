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
   * Returns the next invoice number for this strategy.
   *
   * @return InvoiceNumber
   */
  public function getNext();

  /**
   * Formats an invoice number as a string.
   *
   * @param InvoiceNumber $number
   *
   * @return string
   */
  public function format(InvoiceNumber $number);

}
