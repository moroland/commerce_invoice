<?php

/**
 * @file
 * Default rules for the Commerce Invoice Mail module.
 */

/**
 * Implements hook_default_rules_configuration().
 */
function commerce_invoice_mail_default_rules_configuration() {
  $configs = [];

  $configs['commerce_invoice_mail_send_on_creation'] = entity_import('rules_config', '{ "commerce_invoice_mail_send_on_creation" : {
    "LABEL" : "Send invoice by email on creation",
    "PLUGIN" : "reaction rule",
    "OWNER" : "rules",
    "REQUIRES" : [ "commerce_invoice_mail", "commerce_invoice" ],
    "ON" : { "commerce_invoice_insert" : [] },
    "DO" : [
      { "commerce_invoice_mail_send" : { "commerce_invoice" : [ "commerce_invoice" ] } }
    ]
  }
}');

  return $configs;
}
