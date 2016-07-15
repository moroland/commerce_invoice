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
    if (!isset($entity->invoice_number)) {
      $entity->invoice_number = $entity->getNumberStrategy()->getNext();
    }

    return parent::save($entity, $transaction);
  }

}
