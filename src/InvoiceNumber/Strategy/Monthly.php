<?php

namespace Drupal\commerce_invoice\InvoiceNumber\Strategy;

class Monthly extends DatabaseStrategyBase {

  /**
   * {@inheritdoc}
   */
  protected function getName() {
    return 'monthly';
  }

  /**
   * {@inheritdoc}
   */
  protected function getKey() {
    return date('Y-m', REQUEST_TIME);
  }

}
