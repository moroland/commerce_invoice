<?php
/**
 * @file
 * The entity controller for invoices.
 */

namespace Drupal\commerce_invoice\Entity;

use Drupal\commerce_invoice\InvoiceNumber\Generator;

class InvoiceController extends \EntityAPIController {

  /**
   * {@inheritdoc}
   */
  public function saveRevision($entity) {
    if (!isset($entity->revision_created)) {
      $entity->revision_created = REQUEST_TIME;
    }
    if (!isset($entity->revision_uid)) {
      $entity->revision_uid = $GLOBALS['user']->uid;
    }

    return parent::saveRevision($entity);
  }

  /**
   * {@inheritdoc}
   */
  public function save($entity, \DatabaseTransaction $transaction = NULL) {
    /** @var Invoice $entity */
    if (empty($entity->created) || empty($entity->invoice_id)) {
      $entity->created = REQUEST_TIME;
    }
    if (empty($entity->changed)) {
      $entity->changed = REQUEST_TIME;
    }
    if (empty($entity->invoice_date)) {
      $entity->invoice_date = $entity->created;
    }
    // Default due date should be invoice_date + Net D x 24 x 60 x 60.
    if (empty($entity->invoice_due)) {
      $net_d = variable_get('commerce_invoice_net_d', 30);
      $entity->invoice_due = $entity->created + $net_d * 86400;
    }
    if (empty($entity->uid)) {
      if (!empty($entity->order_id) && !empty($entity->wrapper()->order->owner)) {
        $entity->uid = $entity->wrapper()->order->owner->getIdentifier();
      }
      else {
        $entity->uid = $GLOBALS['user']->uid;
      }
    }

    if (!$entity->hasInvoiceNumber()) {
      $pattern = $entity->getNumberPattern();
      $lock_name = 'commerce_invoice_nr_' . $pattern->name;
      while (!lock_acquire($lock_name)) {
        lock_wait($lock_name);
      }
      $generator = new Generator($pattern);
      $transaction = isset($transaction) ? $transaction : db_transaction();
      $entity->setInvoiceNumber($generator->getNext($entity));
    }

    try {
      return parent::save($entity, $transaction);
    }
    finally {
      unset($transaction);
      // Always release the invoice number lock.
      if (isset($lock_name)) {
        lock_release($lock_name);
      }
    }
  }

  /**
   * {@inheritdoc}
   */
  function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = []) {
    if ($view_mode === 'full') {
      $this->addInvoiceInfo($entity, $content);
    }

    return parent::buildContent($entity, $view_mode, $langcode, $content);
  }

  /**
   * Add a table of invoice information to the content render array.
   *
   * @param Invoice $invoice
   * @param array   &$content
   */
  protected function addInvoiceInfo(Invoice $invoice, array &$content) {
    $info = [];
    $info[t('Invoice ID')] = check_plain($invoice->invoice_id);
    $info[t('Owner')] = [
      '#theme' => 'username',
      '#account' => $invoice->wrapper()->owner->value(),
    ];
    $info[t('Invoice number')] = $invoice->hasInvoiceNumber()
      ? check_plain($invoice->getInvoiceNumber()->__toString())
      : t('Not yet generated');
    $info[t('Invoice date')] = check_plain(format_date($invoice->invoice_date));
    if ($invoice->invoice_due) {
      $info[t('Due date')] = check_plain(format_date($invoice->invoice_due));
    }
    $info[t('Status')] = commerce_invoice_statuses()[$invoice->invoice_status];
    $info[t('Order')] = isset($invoice->order_id)
      ? l($invoice->wrapper()->order->order_number->value(), 'admin/commerce/orders/' . $invoice->order_id)
      : t('None');
    $info[t('Order revision')] = isset($invoice->order_revision_id)
      ? check_plain($invoice->order_revision_id)
      : t('None');
    $pattern = $invoice->getNumberPattern();
    $info[t('Invoice number pattern')] = format_string('@label: <code>@pattern</code>', [
      '@label' => $pattern->label,
      '@pattern' => $pattern->pattern
    ]);
    $info[t('Created')] = check_plain(format_date($invoice->created));
    $info[t('Last modified')] = check_plain(format_date($invoice->changed));

    if (!empty($info)) {
      $content['info'] = ['#theme' => 'table', '#rows' => []];
      foreach ($info as $label => $value) {
        $content['info']['#rows'][] = [
          ['data' => $label, 'header' => TRUE],
          is_array($value) ? ['data' => $value] : $value,
        ];
      }
    }
  }

}
