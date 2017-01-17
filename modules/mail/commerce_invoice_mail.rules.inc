<?php

/**
 * @file
 * Rules integration for the Commerce Invoice Mail module.
 */
use Drupal\commerce_invoice\Entity\Invoice;


/**
 * Implements hook_rules_action_info().
 */
function commerce_invoice_mail_rules_action_info() {
  $actions = array();

  $actions['commerce_invoice_mail_send'] = array(
    'base' => 'commerce_invoice_mail_action_send',
    'label' => t('Send an invoice by mail'),
    'parameter' => array(
      'commerce_invoice' => array(
        'type' => 'commerce_invoice',
        'label' => t('The invoice'),
      ),
    ),
    'group' => t('Commerce Invoice'),
  );

  return $actions;
}

/**
 * Action: Fetch current invoice in order.
 */
function commerce_invoice_mail_action_send(Invoice $invoice) {
  commerce_invoice_mail_send($invoice);
}