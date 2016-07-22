<?php

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
    if (empty($entity->uid)) {
      $entity->uid = $GLOBALS['user']->uid;
    }

    if (!$entity->hasInvoiceNumber()) {
      $pattern = $entity->getNumberPattern();
      $lock_name = 'commerce_invoice_nr_' . $pattern->name;
      while (!lock_acquire($lock_name)) {
        lock_wait($lock_name);
      }
      $generator = new Generator($pattern);
      $transaction = isset($transaction) ? $transaction : db_transaction();
      $entity->setInvoiceNumber($generator->getNext());
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
    /** @var Invoice $entity */
    $info = [];

    $info[t('Invoice ID')] = check_plain($entity->invoice_id);
    $info[t('Owner')] = [
      '#theme' => 'username',
      '#account' => $entity->wrapper()->owner->value(),
    ];
    $info[t('Invoice number')] = $entity->hasInvoiceNumber()
      ? [
        '#theme' => 'commerce_invoice_number',
        '#invoice_number' => $entity->getInvoiceNumber(),
      ]
      : t('Not yet generated');
    $info[t('Invoice date')] = check_plain(format_date($entity->invoice_date));
    $info[t('Status')] = commerce_invoice_statuses()[$entity->invoice_status];
    $info[t('Order')] = isset($entity->order_id)
      ? l($entity->wrapper()->order->order_number->value(), 'admin/commerce/orders/' . $entity->order_id)
      : t('None');
    $info[t('Order revision')] = isset($entity->order_revision_id)
      ? check_plain($entity->order_revision_id)
      : t('None');
    $pattern = $entity->getNumberPattern();
    $info[t('Invoice number pattern')] = format_string('@label: <code>@pattern</code>', [
      '@label' => $pattern->label,
      '@pattern' => $pattern->pattern
    ]);
    $info[t('Created')] = check_plain(format_date($entity->created));
    $info[t('Last modified')] = check_plain(format_date($entity->changed));

    if (!empty($info)) {
      $content['info'] = ['#theme' => 'table', '#rows' => []];
      foreach ($info as $label => $value) {
        $content['info']['#rows'][] = [
          ['data' => $label, 'header' => TRUE],
          is_array($value) ? ['data' => $value] : $value,
        ];
      }
    }

    return parent::buildContent($entity, $view_mode, $langcode, $content);
  }

}
