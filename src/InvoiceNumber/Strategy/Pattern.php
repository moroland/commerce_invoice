<?php

namespace Drupal\commerce_invoice\InvoiceNumber\Strategy;

use Drupal\commerce_invoice\Entity\InvoiceNumberPattern;

class Pattern extends StrategyBase {

  protected $pattern = '';

  /**
   * @param InvoiceNumberPattern $entity
   *   An exportable invoice number pattern configuration object.
   */
  public function __construct(InvoiceNumberPattern $entity) {
    $this->setName($entity->name);
    $this->pattern = $entity->pattern;
  }

  /**
   * {@inheritdoc}
   */
  protected function getKey() {
    return token_replace($this->pattern);
  }

}
