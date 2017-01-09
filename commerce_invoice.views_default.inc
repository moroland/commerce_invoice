<?php
/**
 * @file
 * Default views for the Commerce Invoice module.
 */

/**
 * Implements hook_views_default_views().
 */
function commerce_invoice_views_default_views() {
  $views = array();

  $view = new view();
  $view->name = 'commerce_invoice_invoices';
  $view->description = 'An administrative list of invoices.';
  $view->tag = 'commerce_invoice';
  $view->base_table = 'commerce_invoice';
  $view->human_name = 'Invoices';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Invoices';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer commerce_invoice entities';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '25';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'invoice_id' => 'invoice_id',
    'invoice_number' => 'invoice_number',
    'invoice_date' => 'invoice_date',
    'order_number' => 'order_number',
    'commerce_invoice_total' => 'commerce_invoice_total',
    'invoice_status' => 'invoice_status',
    'name' => 'name',
    'created' => 'created',
    'nothing_1' => 'nothing_1',
    'nothing' => 'nothing',
    'ctools_dropdown' => 'ctools_dropdown',
  );
  $handler->display->display_options['style_options']['default'] = 'created';
  $handler->display->display_options['style_options']['info'] = array(
    'invoice_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'invoice_number' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'invoice_date' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'order_number' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'commerce_invoice_total' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'invoice_status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing_1' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'ctools_dropdown' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['empty_table'] = TRUE;
  /* No results behavior: Global: Unfiltered text */
  $handler->display->display_options['empty']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['empty']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['label'] = 'There are no invoices to display.';
  $handler->display->display_options['empty']['area_text_custom']['empty'] = TRUE;
  $handler->display->display_options['empty']['area_text_custom']['content'] = 'There are no invoices to display.';
  /* Relationship: Invoice: Owner uid */
  $handler->display->display_options['relationships']['owner']['id'] = 'owner';
  $handler->display->display_options['relationships']['owner']['table'] = 'commerce_invoice';
  $handler->display->display_options['relationships']['owner']['field'] = 'owner';
  /* Relationship: Invoice: Order order_id */
  $handler->display->display_options['relationships']['order']['id'] = 'order';
  $handler->display->display_options['relationships']['order']['table'] = 'commerce_invoice';
  $handler->display->display_options['relationships']['order']['field'] = 'order';
  /* Relationship: Invoice: Invoice number pattern */
  $handler->display->display_options['relationships']['number_pattern']['id'] = 'number_pattern';
  $handler->display->display_options['relationships']['number_pattern']['table'] = 'commerce_invoice';
  $handler->display->display_options['relationships']['number_pattern']['field'] = 'number_pattern';
  /* Field: Invoice: Invoice ID */
  $handler->display->display_options['fields']['invoice_id']['id'] = 'invoice_id';
  $handler->display->display_options['fields']['invoice_id']['table'] = 'commerce_invoice';
  $handler->display->display_options['fields']['invoice_id']['field'] = 'invoice_id';
  $handler->display->display_options['fields']['invoice_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['invoice_id']['separator'] = '';
  /* Field: Invoice: Invoice number */
  $handler->display->display_options['fields']['invoice_number']['id'] = 'invoice_number';
  $handler->display->display_options['fields']['invoice_number']['table'] = 'commerce_invoice';
  $handler->display->display_options['fields']['invoice_number']['field'] = 'invoice_number';
  $handler->display->display_options['fields']['invoice_number']['label'] = 'Number';
  $handler->display->display_options['fields']['invoice_number']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['invoice_number']['alter']['path'] = 'admin/commerce/invoices/[invoice_id]';
  /* Field: Invoice: Date */
  $handler->display->display_options['fields']['invoice_date']['id'] = 'invoice_date';
  $handler->display->display_options['fields']['invoice_date']['table'] = 'commerce_invoice';
  $handler->display->display_options['fields']['invoice_date']['field'] = 'invoice_date';
  $handler->display->display_options['fields']['invoice_date']['date_format'] = 'short';
  $handler->display->display_options['fields']['invoice_date']['second_date_format'] = 'long';
  /* Field: Commerce Order: Order number */
  $handler->display->display_options['fields']['order_number']['id'] = 'order_number';
  $handler->display->display_options['fields']['order_number']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['order_number']['field'] = 'order_number';
  $handler->display->display_options['fields']['order_number']['relationship'] = 'order';
  $handler->display->display_options['fields']['order_number']['link_to_order'] = 'admin';
  /* Field: Invoice: Total */
  $handler->display->display_options['fields']['commerce_invoice_total']['id'] = 'commerce_invoice_total';
  $handler->display->display_options['fields']['commerce_invoice_total']['table'] = 'field_data_commerce_invoice_total';
  $handler->display->display_options['fields']['commerce_invoice_total']['field'] = 'commerce_invoice_total';
  $handler->display->display_options['fields']['commerce_invoice_total']['label'] = 'Amount';
  $handler->display->display_options['fields']['commerce_invoice_total']['click_sort_column'] = 'amount';
  $handler->display->display_options['fields']['commerce_invoice_total']['settings'] = array(
    'calculation' => FALSE,
  );
  /* Field: Invoice: Status */
  $handler->display->display_options['fields']['invoice_status']['id'] = 'invoice_status';
  $handler->display->display_options['fields']['invoice_status']['table'] = 'commerce_invoice';
  $handler->display->display_options['fields']['invoice_status']['field'] = 'invoice_status';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'owner';
  $handler->display->display_options['fields']['name']['label'] = 'User';
  /* Field: Invoice: Created */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'commerce_invoice';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'long';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['label'] = 'Edit link';
  $handler->display->display_options['fields']['nothing_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nothing_1']['alter']['text'] = 'Edit';
  $handler->display->display_options['fields']['nothing_1']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing_1']['alter']['path'] = 'admin/commerce/invoices/[invoice_id]/edit';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'Delete link';
  $handler->display->display_options['fields']['nothing']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'Delete';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'admin/commerce/invoices/[invoice_id]/delete';
  /* Field: Global: Dropdown links */
  $handler->display->display_options['fields']['ctools_dropdown']['id'] = 'ctools_dropdown';
  $handler->display->display_options['fields']['ctools_dropdown']['table'] = 'views';
  $handler->display->display_options['fields']['ctools_dropdown']['field'] = 'ctools_dropdown';
  $handler->display->display_options['fields']['ctools_dropdown']['label'] = 'Links';
  $handler->display->display_options['fields']['ctools_dropdown']['fields'] = array(
    'nothing_1' => 'nothing_1',
    'nothing' => 'nothing',
  );
  $handler->display->display_options['fields']['ctools_dropdown']['check_access'] = 1;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/commerce/invoices';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Invoices';
  $handler->display->display_options['menu']['description'] = 'A list of invoices';
  $handler->display->display_options['menu']['weight'] = '2';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Per order */
  $handler = $view->new_display('page', 'Per order', 'order');
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Commerce Order: Order ID */
  $handler->display->display_options['arguments']['order_id']['id'] = 'order_id';
  $handler->display->display_options['arguments']['order_id']['table'] = 'commerce_order';
  $handler->display->display_options['arguments']['order_id']['field'] = 'order_id';
  $handler->display->display_options['arguments']['order_id']['relationship'] = 'order';
  $handler->display->display_options['arguments']['order_id']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['order_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['order_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['order_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['order_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['order_id']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['order_id']['validate']['type'] = 'numeric';
  $handler->display->display_options['path'] = 'admin/commerce/orders/%/invoices';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Invoices';
  $handler->display->display_options['menu']['description'] = 'Invoices for this order.';
  $handler->display->display_options['menu']['weight'] = '4';
  $handler->display->display_options['menu']['context'] = 1;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  $views[$view->name] = $view;

  return $views;
}
