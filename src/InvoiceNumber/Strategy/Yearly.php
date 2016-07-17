<?php

namespace Drupal\commerce_invoice\InvoiceNumber\Strategy;

class Yearly extends StrategyBase {

  /**
   * {@inheritdoc}
   */
  protected function getKey() {
    return date('Y', REQUEST_TIME);
  }

}
