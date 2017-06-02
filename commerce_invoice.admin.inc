<?php
/**
 * @file
 * Administrative form and page callbacks for the Commerce Invoice module.
 */
use Drupal\commerce_invoice\Entity\Invoice;

/**
 * Settings form for the Commerce Invoice module.
 */
function commerce_invoice_settings_form($form, &$form_state) {
  $form['commerce_invoice_default_number_pattern'] = [
    '#title' => t('Default invoice number pattern'),
    '#type' => 'select',
    '#options' => commerce_invoice_number_pattern_options_list(),
    '#default_value' => \Drupal\commerce_invoice\Entity\InvoiceNumberPattern::getDefaultName(),
    '#description' => t('The default pattern used to create invoice numbers (<a href="@url">administer patterns</a>).', [
      '@url' => url('admin/commerce/config/invoice/numbers'),
    ]),
  ];

  return system_settings_form($form);
}

/**
 * Form callback for an invoice number pattern.
 *
 * @param array $form
 * @param array &$form_state
 * @param \Drupal\commerce_invoice\Entity\InvoiceNumberPattern $pattern
 * @param string $op
 *
 * @return array
 */
function commerce_invoice_number_pattern_form($form, &$form_state, \Drupal\commerce_invoice\Entity\InvoiceNumberPattern $pattern, $op = 'edit') {
  $form['label'] = array(
    '#title' => t('Name'),
    '#type' => 'textfield',
    '#default_value' => $pattern->label,
    '#required' => TRUE,
  );

  $form['name'] = array(
    '#type' => 'machine_name',
    '#default_value' => $pattern->name,
    '#disabled' => entity_has_status('commerce_invoice_number_pattern', $pattern, ENTITY_IN_CODE) || $op === 'edit',
    '#machine_name' => array(
      'exists' => 'commerce_invoice_number_pattern_load',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this pattern. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['pattern'] = array(
    '#type' => 'textfield',
    '#title' => t('Pattern'),
    '#description' => t('The pattern for invoice numbers.')
      . '<br />' . t('By default an integer will be appended. Include the special token <code>@sequence_token</code> to place the integer manually.', array(
        '@sequence_token' => \Drupal\commerce_invoice\InvoiceNumber\InvoiceNumber::SEQUENCE_TOKEN,
      ))
      . '<br />' . t('This integer is calculated sequentially based on the pattern (after system tokens have been replaced).'),
    '#default_value' => $pattern->pattern,
    '#required' => TRUE,
  );

  $form['skip_sequence'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hide sequence integer'),
    '#description' => t('Do not append sequence integer to the invoice number pattern.')
      . '<br />' . t('WARNING: If you check the checkbox, make sure the above pattern provides unique invoice numbers. Failure to do so may result in multiple invoices with same numbers.'),
    '#default_value' => $pattern->skip_sequence,
  );

  $form['token_help'] = array(
    '#theme' => 'token_tree',
    '#token_types' => array('date', 'site', 'commerce_invoice'),
    '#global_types' => FALSE,
  );

  $form['actions'] = array(
    '#type' => 'actions',
  );
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Form API submit callback for the pattern form.
 */
function commerce_invoice_number_pattern_form_submit(&$form, &$form_state) {
  /** @var \Drupal\commerce_invoice\Entity\InvoiceNumberPattern $pattern */
  $pattern = entity_ui_form_submit_build_entity($form, $form_state);
  $pattern->save();
  $form_state['redirect'] = 'admin/commerce/config/invoice/numbers';
}

/**
 * Entity API form callback for an invoice.
 *
 * @param array $form
 * @param array &$form_state
 * @param \Drupal\commerce_invoice\Entity\Invoice $invoice
 * @param string $op
 *
 * @return array
 */
function commerce_invoice_form($form, &$form_state, Invoice $invoice, $op = 'edit') {
  $wrapper = $invoice->wrapper();

  if (!empty($invoice->order_id)) {
    $form['order_id'] = array(
      '#type' => 'item',
      '#title' => t('Order'),
      '#markup' => l($wrapper->order->order_number->value(), 'admin/commerce/orders/' . $wrapper->order->getIdentifier()),
      '#weight' => -100,
    );
    if (isset($invoice->order_revision_id)) {
      $form['order_id']['#markup'] .= ' ' . t('(revision ID: @id)', ['@id' => $invoice->order_revision_id]);
    }
  }

  $form['invoice_status'] = array(
    '#type' => 'select',
    '#options' => commerce_invoice_statuses(),
    '#default_value' => $invoice->invoice_status,
    '#required' => TRUE,
    '#title' => t('Invoice status'),
    '#weight' => -80,
  );

  $form['invoice_date'] = array(
    '#type' => 'date_select',
    '#weight' => -61,
    '#title' => t('Invoice date'),
    '#date_format' => 'Y-m-d',
    '#default_value' => date('Y-m-d H:i:s', !empty($invoice->invoice_date) ? $invoice->invoice_date : REQUEST_TIME),
  );

  $net_s = variable_get('commerce_invoice_net_d', 30) * 86400;
  $form['invoice_due'] = array(
    '#type' => 'date_select',
    '#weight' => -60,
    '#title' => t('Invoice due'),
    '#date_format' => 'Y-m-d',
    '#default_value' => date('Y-m-d H:i:s', !empty($invoice->invoice_due) ? $invoice->invoice_due : REQUEST_TIME + $net_s),
  );

  field_attach_form('commerce_invoice', $invoice, $form, $form_state);

  // Hide the invoice total field from direct editing.
  $form['commerce_invoice_total']['#access'] = FALSE;

  $form['additional_settings'] = [
    '#type' => 'vertical_tabs',
    '#weight' => 99,
  ];

  $form['invoice_number'] = [
    '#type' => 'fieldset',
    '#title' => t('Invoice number'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#group' => 'additional_settings',
    '#weight' => -70,
  ];
  $form['invoice_number']['number_pattern'] = [
    '#title' => t('Invoice number pattern'),
    '#type' => 'select',
    '#options' => commerce_invoice_number_pattern_options_list(),
    '#default_value' => $invoice->number_pattern ?: \Drupal\commerce_invoice\Entity\InvoiceNumberPattern::getDefaultName(),
    '#description' => t('The pattern used to generate the invoice number (<a href="@url">administer patterns</a>).', [
      '@url' => url('admin/commerce/config/invoice/numbers'),
    ]),
    '#disabled' => empty($invoice->is_new),
    '#required' => TRUE,
  ];

  $form['user'] = [
    '#type' => 'fieldset',
    '#title' => t('User information'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#group' => 'additional_settings',
    '#weight' => -60,
    '#attached' => array(
      'js' => array(
        drupal_get_path('module', 'commerce_invoice') . '/commerce_invoice.js',
        array(
          'type' => 'setting',
          'data' => array('anonymous' => variable_get('anonymous', t('Anonymous'))),
        ),
      ),
    ),
  ];
  $form['user']['owner'] = array(
    '#type' => 'textfield',
    '#weight' => 90,
    '#autocomplete_path' => 'user/autocomplete',
    '#default_value' => !empty($invoice->uid) ? $wrapper->owner->name->raw() : '',
    '#title' => t('Owner'),
    '#description' => t('If left empty, this will default to the order owner.'),
  );

  $form['actions'] = array(
    '#type' => 'actions',
    '#weight' => 100,
  );
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  if (!empty($invoice->invoice_id)) {
    $form['actions']['delete'] = array(
      '#type' => 'link',
      '#title' => t('Delete'),
      '#href' => 'admin/commerce/invoices/' . $invoice->invoice_id . '/delete',
    );
  }

  return $form;
}

/**
 * Validation callback for the invoice form.
 */
function commerce_invoice_form_validate(&$form, &$form_state) {
  $invoice = $form_state['commerce_invoice'];
  if (!empty($form_state['values']['owner'])) {
    // Given username exists.
    if ($account = user_load_by_name($form_state['values']['owner'])) {
      $form_state['values']['uid'] = $account->uid;
    }
    // Given username does not exist.
    else {
      form_set_error('owner', t('The username %name does not exist.', array('%name' => $form_state['values']['owner'])));
    }
  }
  // Username was not provided, try getting it from the attached order.
  elseif (!empty($invoice) && !empty($invoice->order_id)) {
    $uid = $invoice->wrapper()->order->owner->uid->value();
    $form_state['values']['uid'] = $uid;
  }
  // Default to anonymous.
  else {
    $form_state['values']['uid'] = 0;
  }
}

/**
 * Form API submit callback for the invoice form.
 */
function commerce_invoice_form_submit(&$form, &$form_state) {
  if (!empty($form_state['values']['invoice_date']) && !is_numeric($form_state['values']['invoice_date'])) {
    $invoice_date = strtotime($form_state['values']['invoice_date']);
  }

  if (!empty($form_state['values']['invoice_due']) && !is_numeric($form_state['values']['invoice_due'])) {
    $invoice_due = strtotime($form_state['values']['invoice_due']);
  }

  /** @var \Drupal\commerce_invoice\Entity\Invoice $invoice */
  $invoice = entity_ui_form_submit_build_entity($form, $form_state);
  if (!empty($invoice_date)) {
    $invoice->invoice_date = $invoice_date;
  }
  if (!empty($invoice_due)) {
    $invoice->invoice_due = $invoice_due;
  }

  commerce_invoice_calculate_total($invoice);

  $invoice->save();

  $form_state['redirect'] = 'admin/commerce/invoices';
}

/**
 * Form callback for invoicing orders.
 *
 * @param array $form
 * @param array &$form_state
 * @param int $order_id
 *
 * @return array
 */
function commerce_invoice_create_from_order_form($form, &$form_state, $order_id) {
  drupal_set_title(t('Create invoice for the order @order_id', ['@order_id' => $order_id]));
  $order = commerce_order_load($order_id);
  $form['order_id'] = [
    '#type' => 'value',
    '#value' => $order_id
  ];
  $form['number_pattern'] = [
    '#title' => t('Invoice number pattern'),
    '#type' => 'select',
    '#options' => commerce_invoice_number_pattern_options_list(),
    '#default_value' => \Drupal\commerce_invoice\Entity\InvoiceNumberPattern::getDefaultName(),
    '#description' => t('The pattern used to generate the invoice number (<a href="@url">administer patterns</a>).', [
      '@url' => url('admin/commerce/config/invoice/numbers'),
    ]),
    '#required' => TRUE,
  ];
  $form['cancel_existing'] = [
    '#type' => 'checkbox',
    '#title' => t('Cancel existing.'),
    '#description' => t('Cancel all other invoices for the order.'),
    '#default_value' => 1,
  ];
  $form['invoice_status'] = [
    '#type' => 'select',
    '#title' => t('Invoice status'),
    '#options' => commerce_invoice_statuses(),
    '#description' => t('Choose the status of the new invoice.'),
    '#default_value' => _commerce_invoice_suggest_invoice_status($order),
  ];
  $form['actions'] = ['#type' => 'actions'];
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Create'),
  );

  return $form;
}

/**
 * Form API submit callback for invoicing orders.
 */
function commerce_invoice_create_from_order_form_submit($form, &$form_state) {
  $order_id = $form_state['values']['order_id'];
  $number_pattern = $form_state['values']['number_pattern'];
  $cancel_existing = $form_state['values']['cancel_existing'];
  $status = $form_state['values']['invoice_status'];
  $order = commerce_order_load($order_id);
  $number_pattern = commerce_invoice_number_pattern_load($number_pattern);

  $invoice = commerce_invoice_create_from_order($order, $number_pattern, $cancel_existing, $status);

  $url = url('/admin/commerce/invoices/' . $invoice->invoice_id);
  $number = $invoice->getInvoiceNumber();
  drupal_set_message(t('Invoice <a href="@url">@number</a> created', [
    '@url' => $url,
    '@number' => $number,
  ]));
  $form_state['redirect'] = 'admin/commerce/orders/' . $order_id . '/invoices';
}
