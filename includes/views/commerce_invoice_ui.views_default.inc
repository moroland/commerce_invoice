<?php

/**
 * Views for the default invoice UI.
 */
 
/**
 * Implements hook_views_default_views()
 */
function commerce_invoice_ui_views_default_views() {
  $views = array();
  $view = new view;
  $view->name = 'commerce_invoice';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'commerce_invoice';
  $view->human_name = 'Commerce Invoice';
  $view->core = 7;
  $view->api_version = '3.0-alpha1';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Invoice';
  $handler->display->display_options['use_more_text'] = 'plus';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Réinitialiser';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Trier par';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Éléments par page';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Tout -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = 'Décalage';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relation: Commerce Invoice : Ordre */
  $handler->display->display_options['relationships']['order_id']['id'] = 'order_id';
  $handler->display->display_options['relationships']['order_id']['table'] = 'commerce_invoice';
  $handler->display->display_options['relationships']['order_id']['field'] = 'order_id';
  $handler->display->display_options['relationships']['order_id']['required'] = 0;
  /* Relation: Champs : Referenced customer profile */
  $handler->display->display_options['relationships']['commerce_customer_billing_profile_id']['id'] = 'commerce_customer_billing_profile_id';
  $handler->display->display_options['relationships']['commerce_customer_billing_profile_id']['table'] = 'field_data_commerce_customer_billing';
  $handler->display->display_options['relationships']['commerce_customer_billing_profile_id']['field'] = 'commerce_customer_billing_profile_id';
  $handler->display->display_options['relationships']['commerce_customer_billing_profile_id']['relationship'] = 'order_id';
  $handler->display->display_options['relationships']['commerce_customer_billing_profile_id']['required'] = 0;
  /* Champ: Commerce Invoice : Invoice number */
  $handler->display->display_options['fields']['invoice_number']['id'] = 'invoice_number';
  $handler->display->display_options['fields']['invoice_number']['table'] = 'commerce_invoice';
  $handler->display->display_options['fields']['invoice_number']['field'] = 'invoice_number';
  $handler->display->display_options['fields']['invoice_number']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['invoice_number']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['invoice_number']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['invoice_number']['alter']['external'] = 0;
  $handler->display->display_options['fields']['invoice_number']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['invoice_number']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['invoice_number']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['invoice_number']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['invoice_number']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['invoice_number']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['invoice_number']['alter']['html'] = 0;
  $handler->display->display_options['fields']['invoice_number']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['invoice_number']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['invoice_number']['hide_empty'] = 0;
  $handler->display->display_options['fields']['invoice_number']['empty_zero'] = 0;
  /* Champ: Commerce Invoice : Date de création */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'commerce_invoice';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Date';
  $handler->display->display_options['fields']['created']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['created']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['created']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['created']['alter']['external'] = 0;
  $handler->display->display_options['fields']['created']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['created']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['created']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['created']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['created']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['created']['alter']['html'] = 0;
  $handler->display->display_options['fields']['created']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['created']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['created']['hide_empty'] = 0;
  $handler->display->display_options['fields']['created']['empty_zero'] = 0;
  $handler->display->display_options['fields']['created']['date_format'] = 'long';
  /* Champ: Commerce Order : Order number */
  $handler->display->display_options['fields']['order_number']['id'] = 'order_number';
  $handler->display->display_options['fields']['order_number']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['order_number']['field'] = 'order_number';
  $handler->display->display_options['fields']['order_number']['relationship'] = 'order_id';
  $handler->display->display_options['fields']['order_number']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['external'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['order_number']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['order_number']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['html'] = 0;
  $handler->display->display_options['fields']['order_number']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['order_number']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['order_number']['hide_empty'] = 0;
  $handler->display->display_options['fields']['order_number']['empty_zero'] = 0;
  /* Champ: Customer profile : Addresse de facturation */
  $handler->display->display_options['fields']['commerce_customer_address']['id'] = 'commerce_customer_address';
  $handler->display->display_options['fields']['commerce_customer_address']['table'] = 'field_data_commerce_customer_address';
  $handler->display->display_options['fields']['commerce_customer_address']['field'] = 'commerce_customer_address';
  $handler->display->display_options['fields']['commerce_customer_address']['relationship'] = 'commerce_customer_billing_profile_id';
  $handler->display->display_options['fields']['commerce_customer_address']['label'] = 'Billing Address';
  $handler->display->display_options['fields']['commerce_customer_address']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['commerce_customer_address']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['commerce_customer_address']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['commerce_customer_address']['alter']['external'] = 0;
  $handler->display->display_options['fields']['commerce_customer_address']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['commerce_customer_address']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['commerce_customer_address']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['commerce_customer_address']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['commerce_customer_address']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['commerce_customer_address']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['commerce_customer_address']['alter']['html'] = 0;
  $handler->display->display_options['fields']['commerce_customer_address']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['commerce_customer_address']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['commerce_customer_address']['hide_empty'] = 0;
  $handler->display->display_options['fields']['commerce_customer_address']['empty_zero'] = 0;
  $handler->display->display_options['fields']['commerce_customer_address']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['commerce_customer_address']['field_api_classes'] = 0;
  /* Champ: Commande : Line items */
  $handler->display->display_options['fields']['commerce_line_items']['id'] = 'commerce_line_items';
  $handler->display->display_options['fields']['commerce_line_items']['table'] = 'field_data_commerce_line_items';
  $handler->display->display_options['fields']['commerce_line_items']['field'] = 'commerce_line_items';
  $handler->display->display_options['fields']['commerce_line_items']['relationship'] = 'order_id';
  $handler->display->display_options['fields']['commerce_line_items']['label'] = '';
  $handler->display->display_options['fields']['commerce_line_items']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['commerce_line_items']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['commerce_line_items']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['commerce_line_items']['alter']['external'] = 0;
  $handler->display->display_options['fields']['commerce_line_items']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['commerce_line_items']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['commerce_line_items']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['commerce_line_items']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['commerce_line_items']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['commerce_line_items']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['commerce_line_items']['alter']['html'] = 0;
  $handler->display->display_options['fields']['commerce_line_items']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['commerce_line_items']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['commerce_line_items']['hide_empty'] = 0;
  $handler->display->display_options['fields']['commerce_line_items']['empty_zero'] = 0;
  $handler->display->display_options['fields']['commerce_line_items']['click_sort_column'] = 'line_item_id';
  $handler->display->display_options['fields']['commerce_line_items']['settings'] = array(
    'view' => 'commerce_line_item_table|default',
  );
  $handler->display->display_options['fields']['commerce_line_items']['group_rows'] = 1;
  $handler->display->display_options['fields']['commerce_line_items']['delta_offset'] = '0';
  $handler->display->display_options['fields']['commerce_line_items']['delta_reversed'] = 0;
  $handler->display->display_options['fields']['commerce_line_items']['field_api_classes'] = 0;
  /* Champ: Commande : Order total */
  $handler->display->display_options['fields']['commerce_order_total']['id'] = 'commerce_order_total';
  $handler->display->display_options['fields']['commerce_order_total']['table'] = 'field_data_commerce_order_total';
  $handler->display->display_options['fields']['commerce_order_total']['field'] = 'commerce_order_total';
  $handler->display->display_options['fields']['commerce_order_total']['relationship'] = 'order_id';
  $handler->display->display_options['fields']['commerce_order_total']['label'] = 'Total de la commande';
  $handler->display->display_options['fields']['commerce_order_total']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['external'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['html'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['commerce_order_total']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['commerce_order_total']['hide_empty'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['empty_zero'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['click_sort_column'] = 'amount';
  $handler->display->display_options['fields']['commerce_order_total']['type'] = 'commerce_price_formatted_amount';
  $handler->display->display_options['fields']['commerce_order_total']['settings'] = array(
    'calculation' => FALSE,
  );
  $handler->display->display_options['fields']['commerce_order_total']['field_api_classes'] = 0;
  /* Filtre contextuel: Commerce Invoice : Invoice ID */
  $handler->display->display_options['arguments']['invoice_id']['id'] = 'invoice_id';
  $handler->display->display_options['arguments']['invoice_id']['table'] = 'commerce_invoice';
  $handler->display->display_options['arguments']['invoice_id']['field'] = 'invoice_id';
  $handler->display->display_options['arguments']['invoice_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['invoice_id']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['invoice_id']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['invoice_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['invoice_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['invoice_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['invoice_id']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['invoice_id']['not'] = 0;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'commerce/invoice/%';
  $translatables['commerce_invoice'] = array(
    t('Master'),
    t('Invoice'),
    t('plus'),
    t('Appliquer'),
    t('Réinitialiser'),
    t('Trier par'),
    t('Asc'),
    t('Desc'),
    t('Éléments par page'),
    t('- Tout -'),
    t('Décalage'),
    t('Order associated to the invoice'),
    t('Customer profile'),
    t('Invoice number'),
    t('Date'),
    t('Order number'),
    t('Billing Address'),
    t('Total de la commande'),
    t('Tous / Toutes'),
    t('Page'),
  );
  
  $views[$view->name] = $view;
  
  return $views;
}

  
