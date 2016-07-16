<?php

namespace Drupal\commerce_invoice\InvoiceNumber\Strategy;

class Daily extends StrategyBase {

  /**
   * {@inheritdoc}
   */
  public function getName() {
    return 'daily';
  }

  /**
   * {@inheritdoc}
   */
  protected function getKey() {
    return date('Y-m-d', REQUEST_TIME);
  }

}
