<?php

class CommerceInvoiceEntityController extends EntityAPIController {

  /**
   * {@inheritdoc}
   */
  public function saveRevision($entity) {
    if (!empty($entity->is_new_revision) || !empty($entity->revision) || !empty($entity->is_new)) {
      $entity->revision_created = REQUEST_TIME;
      $entity->revision_uid = $GLOBALS['user']->uid;
      if (!isset($entity->log)) {
        $entity->log = '';
      }
    }

    return parent::saveRevision($entity);
  }

}
