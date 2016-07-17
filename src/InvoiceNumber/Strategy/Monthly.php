<?php

namespace Drupal\commerce_invoice\InvoiceNumber\Strategy;

class Monthly extends StrategyBase {

  /**
   * {@inheritdoc}
   */
  protected function getKey() {
    return date('Y-m', REQUEST_TIME);
  }

}
