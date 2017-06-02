<?php
/**
 * @file
 * Provides entity metadata integration.
 */

namespace Drupal\commerce_invoice\Entity;

class InvoiceMetadataController extends \EntityDefaultMetadataController {

  /**
   * {@inheritdoc}
   */
  public function entityPropertyInfo() {
    $info = array();
    $properties = &$info['commerce_invoice']['properties'];

    $properties['invoice_id'] = array(
      'type' => 'integer',
      'label' => t('Invoice ID'),
      'description' => t('The primary identifier for an invoice.'),
      'validation callback' => 'entity_metadata_validate_integer_positive',
      'schema field' => 'invoice_id',
    );
    $properties['type'] = array(
      'type' => 'token',
      'label' => t('Type'),
      'description' => t('The invoice type'),
      'required' => TRUE,
      'schema field' => 'type',
    );
    $properties['owner'] = array(
      'type' => 'user',
      'label' => t('Owner'),
      'description' => t('The owner of the invoice.'),
      'required' => TRUE,
      'schema field' => 'uid',
    );
    $properties['order'] = array(
      'type' => 'commerce_order',
      'label' => t('Order'),
      'description' => t('The order for the invoice.'),
      'required' => TRUE,
      'schema field' => 'order_id',
    );
    $properties['order_revision'] = array(
      'type' => 'integer',
      'label' => t('Order revision'),
      'description' => t('The order revision for the invoice.'),
      'required' => TRUE,
      'schema field' => 'order_revision_id',
    );
    $properties['invoice_status'] = array(
      'type' => 'integer',
      'label' => t('Status'),
      'description' => t('The invoice status.'),
      'options list' => 'commerce_invoice_statuses',
      'required' => TRUE,
      'schema field' => 'invoice_status',
    );
    $properties['invoice_date'] = array(
      'type' => 'date',
      'label' => t('Date'),
      'description' => t('The invoice date.'),
      'schema field' => 'invoice_date',
    );
    $properties['invoice_due'] = array(
      'type' => 'date',
      'label' => t('Due date'),
      'description' => t('The invoice due date.'),
      'schema field' => 'invoice_due',
    );
    $properties['invoice_number'] = array(
      'type' => 'text',
      'label' => t('Invoice number'),
      'description' => t('The invoice number.'),
      'getter callback' => array($this, 'invoiceNumberGetter'),
      'computed' => TRUE,
    );
    $properties['number_pattern'] = array(
      'type' => 'commerce_invoice_number_pattern',
      'label' => t('Invoice number pattern'),
      'description' => t('The pattern used to generate the invoice number.'),
      'schema field' => 'number_pattern',
    );
    $properties['created'] = array(
      'type' => 'date',
      'label' => t('Created'),
      'description' => t('The date when the invoice was created.'),
      'schema field' => 'created',
    );
    $properties['changed'] = array(
      'type' => 'date',
      'label' => t('Changed'),
      'description' => t('The date when the invoice was last modified.'),
      'schema field' => 'changed',
    );

    return $info;
  }

  /**
   * Getter callback for invoice_number.
   */
  public function invoiceNumberGetter(Invoice $invoice) {

    return (string) $invoice->getInvoiceNumber();
  }

}
