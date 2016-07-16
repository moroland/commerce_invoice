<?php

namespace Drupal\commerce_invoice\InvoiceNumber\Strategy;

class Yearly extends StrategyBase {

  /**
   * {@inheritdoc}
   */
  public function getName() {
    return 'yearly';
  }

  /**
   * {@inheritdoc}
   */
  protected function getKey() {
    return date('Y', REQUEST_TIME);
  }

}
