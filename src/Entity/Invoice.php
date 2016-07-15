<?php

namespace Drupal\commerce_invoice\Entity;

use Drupal\commerce_invoice\InvoiceNumber\Strategy\Monthly;
use Drupal\commerce_invoice\InvoiceNumber\Strategy\StrategyInterface;

class Invoice extends \Entity {

  public $invoice_id;
  public $revision_id;
  public $type = 'commerce_invoice';
  public $order_id;
  public $order_revision_id;
  public $uid;
  public $invoice_date;
  public $invoice_status;
  public $quantity;
  public $created;
  public $changed;
  public $revision_created;
  public $revision_uid;
  public $log;

  /**
   * @todo bundle settings logic
   *
   * @return StrategyInterface
   */
  public function getNumberStrategy() {
    return new Monthly();
  }
}
