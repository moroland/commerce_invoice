<?php

/**
 * @file
 * Default rules for the Commerce Invoice module.
 */

/**
 * Implements hook_default_rules_configuration().
 */
function commerce_invoice_default_rules_configuration() {
  $configs = [];

  $configs['commerce_invoice_create_new'] = entity_import('rules_config', '{ "commerce_invoice_create_new" : {
    "LABEL" : "Create an invoice when an order is created as Pending",
    "PLUGIN" : "reaction rule",
    "OWNER" : "rules",
    "REQUIRES" : [ "rules", "commerce_invoice", "entity" ],
    "ON" : { "commerce_order_insert" : [] },
    "IF" : [
      { "data_is" : { "data" : [ "commerce-order:status" ], "value" : "pending" } }
    ],
    "DO" : [
      { "commerce_invoice_create_from_order" : { "order" : [ "commerce-order" ], "cancel_existing" : 0 } }
    ]
  }
}');

  $configs['commerce_invoice_create_updated'] = entity_import('rules_config', '{ "commerce_invoice_create_updated" : {
    "LABEL" : "Create an invoice when an order is updated to Pending",
    "PLUGIN" : "reaction rule",
    "OWNER" : "rules",
    "REQUIRES" : [ "rules", "commerce_invoice", "entity" ],
    "ON" : { "commerce_order_update" : [] },
    "IF" : [
      { "data_is" : { "data" : [ "commerce-order:status" ], "value" : "pending" } },
      { "commerce_invoice_order_changed" : { "order" : [ "commerce-order" ] } }
    ],
    "DO" : [
      { "commerce_invoice_create_from_order" : { "order" : [ "commerce-order" ], "cancel_existing" : 1 } }
    ]
  }
}');

  $configs['commerce_invoice_complete_order'] = entity_import('rules_config', '{ "commerce_invoice_complete_order" : {
    "LABEL" : "Complete order when invoice is paid",
    "PLUGIN" : "reaction rule",
    "OWNER" : "rules",
    "REQUIRES" : [ "rules", "commerce_order", "commerce_invoice" ],
    "ON" : { "commerce_invoice_update" : [] },
    "IF" : [
      { "data_is" : { "data" : [ "commerce-invoice:status" ], "value" : "paid" } }
    ],
    "DO" : [
      { "entity_fetch" : {
          "USING" : {
            "type" : "commerce_order",
            "id" : [ "commerce-invoice:order:order-id" ]
          },
          "PROVIDE" : { "entity_fetched" : { "entity_fetched" : "Fetched entity" } }
        }
      },
      { "commerce_order_update_status" : { "commerce_order" : [ "entity-fetched" ], "order_status" : "completed" } }
    ]
  }
}');

  $configs['commerce_invoice_cancel_unpaid'] = entity_import('rules_config', '{ "commerce_invoice_cancel_unpaid" : {
    "LABEL" : "Cancel unpaid invoice",
    "PLUGIN" : "rule",
    "OWNER" : "rules",
    "TAGS" : [ "commerce_invoice" ],
    "REQUIRES" : [ "rules" ],
    "USES VARIABLES" : { "invoice" : { "label" : "Invoice", "type" : "commerce_invoice" } },
    "IF" : [
      { "NOT data_is" : { "data" : [ "invoice:status" ], "value" : "paid" } }
    ],
    "DO" : [
      { "data_set" : { "data" : [ "invoice:status" ], "value" : "canceled" } },
      { "entity_save" : { "data" : [ "invoice" ] } }
    ]
  }
}');

  $configs['commerce_invoice_cancel_on_order_cancel'] = entity_import('rules_config', '{ "commerce_invoice_cancel_on_order_cancel" : {
    "LABEL" : "Cancel invoice when the order is canceled",
    "PLUGIN" : "reaction rule",
    "OWNER" : "rules",
    "TAGS" : [ "commerce_invoice" ],
    "REQUIRES" : [ "rules", "commerce_invoice", "entity" ],
    "ON" : { "commerce_order_update" : [] },
    "IF" : [
      { "NOT data_is_empty" : { "data" : [ "commerce-order-unchanged" ] } },
      { "NOT data_is" : { "data" : [ "commerce-order-unchanged:state" ], "value" : "canceled" } },
      { "data_is" : { "data" : [ "commerce-order:state" ], "value" : "canceled" } },
      { "commerce_invoice_order_has_invoice" : { "order" : [ "commerce-order" ] } }
    ],
    "DO" : [
      { "commerce_invoice_load_current" : {
          "USING" : { "order" : [ "commerce-order" ] },
          "PROVIDE" : { "commerce_invoice" : { "commerce_invoice" : "Fetched invoice" } }
        }
      },
      { "component_commerce_invoice_cancel_unpaid" : { "invoice" : [ "commerce-invoice" ] } }
    ]
  }
}');

  return $configs;
}
