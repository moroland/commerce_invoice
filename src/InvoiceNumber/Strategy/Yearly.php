<?php

namespace Drupal\commerce_invoice\InvoiceNumber\Strategy;

class Yearly extends DatabaseStrategyBase {

  /**
   * {@inheritdoc}
   */
  protected function getName() {
    return 'yearly';
  }

  /**
   * {@inheritdoc}
   */
  protected function getKey() {
    return date('Y', REQUEST_TIME);
  }

}
