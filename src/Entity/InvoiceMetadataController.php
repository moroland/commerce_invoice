<?php

namespace Drupal\commerce_invoice\Entity;

use Drupal\commerce_invoice\InvoiceNumber\InvoiceNumber;

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
      'setter callback' => 'entity_property_verbatim_set',
      'required' => TRUE,
      'schema field' => 'type',
    );
    $properties['owner'] = array(
      'type' => 'user',
      'label' => t('Owner'),
      'description' => t('The owner of the invoice.'),
      'setter callback' => 'entity_property_verbatim_set',
      'required' => TRUE,
      'schema field' => 'uid',
    );
    $properties['order'] = array(
      'type' => 'commerce_order',
      'label' => t('Order'),
      'description' => t('The order for the invoice.'),
      'setter callback' => 'entity_property_verbatim_set',
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
    $properties['status'] = array(
      'type' => 'integer',
      'label' => t('Status'),
      'description' => t('The invoice status.'),
      'options list' => 'commerce_invoice_statuses',
      'setter callback' => 'entity_property_verbatim_set',
      'required' => TRUE,
      'schema field' => 'invoice_status',
    );
    $properties['invoice_date'] = array(
      'type' => 'date',
      'label' => t('Date'),
      'description' => t('The invoice date.'),
    );
    $properties['invoice_number'] = array(
      'type' => 'text',
      'label' => t('Invoice number'),
      'description' => t('The invoice number.'),
      'getter callback' => get_class() . '::invoiceNumberGetter',
    );
    $properties['number_strategy'] = array(
      'type' => 'token',
      'label' => t('Number strategy'),
      'description' => t('The strategy used to calculate the invoice number.'),
    );
    $properties['created'] = array(
      'type' => 'date',
      'label' => t('Created'),
      'description' => t('The date when the invoice was created.'),
    );
    $properties['changed'] = array(
      'type' => 'date',
      'label' => t('Changed'),
      'description' => t('The date when the invoice was last modified.'),
    );

    return $info;
  }

  /**
   * Getter callback for an invoice number.
   *
   * @param Invoice $invoice
   *
   * @return string
   */
  public static function invoiceNumberGetter(Invoice $invoice) {
    $number = new InvoiceNumber(
      $invoice->number_sequence,
      $invoice->number_key,
      $invoice->getNumberStrategy()
    );

    return $number->__toString();
  }

}
