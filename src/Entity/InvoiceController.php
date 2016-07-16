<?php

namespace Drupal\commerce_invoice\Entity;

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
    if (!$entity->getInvoiceNumber()) {
      $transaction = isset($transaction) ? $transaction : db_transaction();
      $strategy = $entity->getNumberStrategy();
      $lock_name = 'commerce_invoice_nr_' . $strategy->getName();
      while (!lock_acquire($lock_name)) {
        lock_wait($lock_name);
      }
      $entity->setInvoiceNumber($strategy->getNext());
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
