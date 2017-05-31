<?php

/**
 * @file
 * Rules integration for the Commerce Invoice PDF module.
 */
use Drupal\commerce_invoice\Entity\Invoice;

/**
 * Implements hook_rules_action_info().
 */
function commerce_invoice_pdf_rules_action_info() {
  $actions = array();

  $actions['commerce_invoice_pdf_create'] = array(
    'base' => 'commerce_invoice_pdf_action_create',
    'label' => t('Create a PDF'),
    'parameter' => [
      'invoice' => [
        'type' => 'commerce_invoice',
        'label' => t('Invoice'),
      ],
      'recreate' => [
        'type' => 'boolean',
        'label' => t('Recreate existing'),
        'description' => t('Recreate (replace) the file if it already exists.'),
        'default value' => 1,
      ],
    ],
    'group' => t('Commerce Invoice'),
  );

  if (module_exists('advancedqueue')) {
    $actions['commerce_invoice_pdf_create']['parameter']['queue'] = [
      'type' => 'boolean',
      'label' => t('Use Advanced Queue'),
      'description' => t('Do not create PDF immediately. Instead, add the task to Advanced Queue.'),
      'default value' => 1,
      'optional' => TRUE,
    ];
  }

  return $actions;
}

/**
 * Rules action: Create a PDF file for a given invoice entity.
 *
 * @param Invoice $invoice
 *   The invoice entity
 * @param boolean $recreate
 *   Whether to recreate (replace) the file if it already exists.
 * @param boolean $queue
 *   Whether to add the PDF creation into a queue or not.
 */
function commerce_invoice_pdf_action_create(Invoice $invoice, $recreate, $queue = FALSE) {
  if (!$queue) {
    _commerce_invoice_pdf_ensure_default_theme();
    commerce_invoice_pdf_create($invoice, TRUE, $recreate);
  }
  else {
    $queue = DrupalQueue::get('commerce_invoice_pdf_create_queue');
    $task = array(
      'invoice_id' => $invoice->invoice_id,
      'recreate' => $recreate,
    );
    $queue->createItem($task);
  }
}
