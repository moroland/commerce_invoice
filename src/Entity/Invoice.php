<?php
/**
 * @file
 * Invoice entity.
 */

namespace Drupal\commerce_invoice\Entity;

use Drupal\commerce_invoice\InvoiceNumber\InvoiceNumber;

class Invoice extends \Entity {

  const STATUS_CANCELED = 'canceled';
  const STATUS_PAID = 'paid';
  const STATUS_PENDING = 'pending';
  const STATUS_REFUND_PENDING = 'refund_pending';
  const STATUS_REFUNDED = 'refunded';

  public $invoice_id;
  public $revision_id;
  public $type = 'commerce_invoice';
  public $order_id;
  public $order_revision_id;
  public $number_pattern;
  public $number_sequence;
  public $number_key;
  public $uid;
  public $invoice_date;
  public $invoice_due;
  public $invoice_status = self::STATUS_PENDING;
  public $created;
  public $changed;
  public $revision_created;
  public $revision_uid;
  public $log;
  public $content;

  /**
   * Returns the invoice number pattern for this invoice.
   *
   * @todo bundle settings logic
   *
   * @return InvoiceNumberPattern
   */
  public function getNumberPattern() {
    if ($pattern = commerce_invoice_number_pattern_load($this->number_pattern)) {
      return $pattern;
    }

    throw new \RuntimeException('Invoice number pattern not found: ' . $this->number_pattern);
  }

  /**
   * Sets the invoice number.
   *
   * @param InvoiceNumber $number
   */
  public function setInvoiceNumber(InvoiceNumber $number) {
    $this->number_key = $number->getKey();
    $this->number_sequence = $number->getSequence();
    $this->number_pattern = $number->getPatternName();
  }

  /**
   * @return bool
   */
  public function hasInvoiceNumber() {
    return isset($this->number_sequence);
  }

  /**
   * Returns the invoice number.
   *
   * @return InvoiceNumber|NULL
   */
  public function getInvoiceNumber() {
    if (!isset($this->number_sequence)) {
      return NULL;
    }

    return new InvoiceNumber($this->number_sequence, $this->number_key, $this->number_pattern);
  }

  /**
   * {@inheritdoc}
   */
  protected function defaultUri() {
    return ['path' => 'admin/commerce/invoices/' . $this->identifier()];
  }

  /**
   * {@inheritdoc}
   */
  protected function defaultLabel() {
    return $this->hasInvoiceNumber()
      ? t('Invoice @number', ['@number' => $this->getInvoiceNumber()->__toString()])
      : t('Invoice');
  }

}
