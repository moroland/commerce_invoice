<?php

class CommerceInvoiceEntity extends Entity {

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

}
