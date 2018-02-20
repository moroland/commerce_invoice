<?php

/**
 * @file
 * Documentation for the commerce_invoice module.
 */

use Drupal\commerce_invoice\Entity\Invoice;

/**
 * Allows modules to alter the list of available Commerce Invoice statuses.
 *
 * @param array $statuses
 *  An array of commerce invoice statues.
 */
function hook_commerce_invoice_statuses_alter(&$statuses) {
  // Remove a status.
  unset($statuses[Invoice::STATUS_REFUND_PENDING]);
  // Add a status.
  $statuses['past_due'] = t('Past due');
}
