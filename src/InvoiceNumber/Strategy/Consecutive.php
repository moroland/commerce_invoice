<?php

namespace Drupal\commerce_invoice\InvoiceNumber\Strategy;

class Consecutive extends StrategyBase {

  /**
   * {@inheritdoc}
   */
  public function getName() {
    return 'consecutive';
  }

  /**
   * {@inheritdoc}
   */
  protected function getKey() {
    return '';
  }

}
