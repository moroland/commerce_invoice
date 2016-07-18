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
      $transaction = isset($transaction) ? $transaction : db_transaction();
      $pattern = $entity->getNumberPattern();
      $lock_name = 'commerce_invoice_nr_' . $pattern->name;
      $generator = new Generator($pattern);
      while (!lock_acquire($lock_name)) {
        lock_wait($lock_name);
      }
      $entity->setInvoiceNumber($generator->getNext());
    }

    try {
      return parent::save($entity, $transaction);
    }
    finally {
      // Always release the invoice number lock.
      if (isset($lock_name)) {
        lock_release($lock_name);
      }
    }
  }

}
