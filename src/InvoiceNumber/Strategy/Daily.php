<?php

namespace Drupal\commerce_invoice\InvoiceNumber\Strategy;

class Daily extends StrategyBase {

  /**
   * {@inheritdoc}
   */
  protected function getKey() {
    return date('Y-m-d', REQUEST_TIME);
  }

}
