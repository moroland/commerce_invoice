<?php

namespace Drupal\commerce_invoice\InvoiceNumber\Strategy;

class Infinite extends DatabaseStrategyBase {

  /**
   * {@inheritdoc}
   */
  protected function getName() {
    return 'infinite';
  }

  /**
   * {@inheritdoc}
   */
  protected function getKey() {
    return NULL;
  }

}
