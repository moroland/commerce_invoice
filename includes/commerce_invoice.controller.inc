<?php

/**
 * @file
 * The controller for the invoice entity containing the CRUD operations.
 */

/**
 * The controller class for invoices contains methods for the order CRUD
 * operations. The load method is inherited from the default controller.
 */
class CommerceInvoiceEntityController extends DrupalCommerceEntityController {

  /**
   * Create a default invoice.
   *
   * @param array $values
   *   An array of values to set, keyed by property name
   *
   * @return
   *   An invoice object with all default fields initialized.
   */
  public function create(array $values = array()) {
    return (object) ($values + array(
      'invoice_id' => '',
      'invoice_number' => '',
      'order_id' => 0,
      'uid' => '',
      'created' => '',
      'changed' => '',
      'type' => 'commerce_invoice',
    ));
  }

  /**
   * Saves an invoice.
   *
   * When saving an invoice, the function will automatically create an invoice number
   * based
   *
   * @param $invoice
   *   The full invoice object to save.
   * @param $transaction
   *   An optional transaction object.
   *
   * @return
   *   The saved invoice object.
   */
  public function save($invoice, DatabaseTransaction $transaction = NULL) {
    $transaction = !is_null($transaction) ? $transaction : db_transaction();
    try {
      $invoice->changed = REQUEST_TIME;

      // Inserting new invoice
      if (empty($invoice->invoice_id)) {
        $invoice->created = REQUEST_TIME;
        $invoice->invoice_number = $this->generate_invoice_id($invoice);

        $this->invoke('presave', $invoice);
        $invoice = $this->_save($invoice, $transaction);
        $this->invoke('insert', $invoice);
      }
      else {
        $this->invoke('presave', $invoice);
        $invoice = $this->_save($invoice, $transaction);
        $this->invoke('save', $invoice);
      }

      return $invoice;
    }
    catch (Exception $e) {
      $transaction->rollback();
      watchdog_exception('commerce_invoice', $e);
      throw $e;
    }
  }

  /**
   * Saves an invoice (helper function)
   *
   * @param $invoice
   *   The full invoice object to save.
   * @param $transaction
   *   An optional transaction object.
   *
   * @return
   *   The saved invoice object.
   */
  private function _save($invoice, DatabaseTransaction $transaction = NULL) {
    if (empty($invoice->invoice_id)) {
      // Save the new invoice
      drupal_write_record('commerce_invoice', $invoice);
      field_attach_insert('commerce_invoice', $invoice);
    }
    else {
      drupal_write_record('commerce_invoice', $invoice, 'invoice_id');
      field_attach_update('commerce_invoice', $invoice);
    }
    // Ignore slave server temporarily to give time for the
    // saved invoice to be propagated to the slave.
    db_ignore_slave();

    return $invoice;
  }

  /**
   * Generates invoice id
   *
   * @param object $invoice The invoice to generate an invoice number for.
   *
   * @return
   *   The generated invoice id
   */
  protected function generate_invoice_id($invoice) {
    // TODO: there is probably a better way to do this
    // Invoice generation method
    $method = variable_get('commerce_invoice_number_method', COMMERCE_INVOICE_METHOD_YEAR);
    if ($method == COMMERCE_INVOICE_METHOD_CALLBACK) {
      $function_name = variable_get('commerce_invoice_number_callback', '');
      if (empty($function_name) || !function_exists($function_name)) {
        drupal_set_message(t('No valid callback defined for invoice number generation.'), 'error');
        return t('no-invoice-number');
      } else {
        return $function_name($invoice);
      }
    }

    // Get last invoice created
    $result = db_select('commerce_invoice', 'i')
      ->fields('i')
      ->orderBy('created', 'DESC')
      ->range(0, 1)
      ->execute();
    if ($record = $result->fetchAssoc()) {
      $last_number = $record['invoice_number'];
      switch($method) {
        case COMMERCE_INVOICE_METHOD_INFINITE:
          $last_id = $record['invoice_id'];
          $id = $last_id + 1;
          $return = str_replace('[invoice_id]', $id, $method);
          break;
        case COMMERCE_INVOICE_METHOD_YEAR:
          // Are we in the same year as the last invoice
          $dash_pos = strpos($last_number, '-');
          $last_year = substr($last_number, 0, $dash_pos);
          if ($last_year == date('Y')) {
            // Get last invoice id
            $last_id = strstr($last_number, '-');
            $last_id = str_replace('-', '', $last_id);
            // Increment invoice id
            $id = $last_id + 1;
            $return = $last_year.'-'.$id;
          }
          else {
            // Reset invoice id to 1
            $return = date('Y').'-1';
          }
          break;
        case COMMERCE_INVOICE_METHOD_MONTH:
          $parts = explode('-', $last_number);
          $last_year = $parts[0];
          $last_month = $parts[1];
          $last_id = $parts[2];
          $year = date('Y');
          $month = date('m');
          if ($last_year == $year) {
            if ($last_month == $month) {
              $id = $last_id + 1;
            }
            else {
              $id = 1;
            }
          }
          else {
            $id = 1;
          }
          $return = date('Y') . '-' . date('m') . '-' . $id;
          break;
      }
      return $return;

    }
    else {
      // First invoice being generated
      $id = 1;
      $result = str_replace('[invoice_id]', $id, $method);
      return date($result);
    }
  }

  /**
   * Deletes multiple invoices by ID.
   *
   * @param $invoice_ids
   *   An array of invoice IDs to delete.
   * @param $transaction
   *  An optional transaction object.
   *
   * @return
   *   TRUE on success, FALSE otherwise.
   */
  public function delete($invoice_ids, DatabaseTransaction $transaction = NULL) {
    if (!empty($invoice_ids)) {
      $invoices = $this->load($invoice_ids, array());

      $transaction = isset($transaction) ? $transaction : db_transaction();

      try {
        db_delete('commerce_invoice')
          ->condition('invoice_id', $invoice_ids, 'IN')
          ->execute();

        // Reset the cache as soon as the changes have been applied.
        $this->resetCache($invoice_ids);

        foreach ($invoices as $id => $invoice) {
          $this->invoke('delete', $invoice);
        }

        // Ignore slave server temporarily to give time for the
        // saved invoice to be propagated to the slave.
        db_ignore_slave();
      }
      catch (Exception $e) {
        $transaction->rollback();
        watchdog_exception('commerce_invoice', $e);
        throw $e;
      }

      // Clear the page and block and line_item_load_multiple caches.
      cache_clear_all();
      $this->resetCache();
    }

    return TRUE;
  }

  /**
   * Builds a structured array representing the entity's content.
   *
   * The content built for the entity will vary depending on the $view_mode
   * parameter.
   *
   * @param $entity
   *   An entity object.
   * @param $view_mode
   *   View mode, e.g. 'administrator'
   * @param $langcode
   *   (optional) A language code to use for rendering. Defaults to the global
   *   content language of the current request.
   * @return
   *   The renderable array.
   */
  public function buildContent($invoice, $view_mode = 'administrator', $langcode = NULL, $content = array()) {
    // Load the order this invoice is attached to.
    $order = commerce_order_load($invoice->order_id);

    $order_build_content = entity_build_content('commerce_order', $order, $view_mode, $langcode);
    foreach($order_build_content as $field => $instance){
      if(substr($field,0,1) != '#' || $field == '#attached'){
        $content[$field] = $instance;
      }
    }

    $content['invoice_number'] = array(
      '#markup' => theme('commerce_invoice_number', array('invoice_number' => $invoice->invoice_number, 'label' => t('Invoice number:'), 'invoice' => $invoice)),
    );

    $content['created'] = array(
      '#markup' => theme('commerce_invoice_created', array('created' => format_date($invoice->created, 'short'), 'label' => t('Date:'), 'invoice' => $invoice)),
    );

    return parent::buildContent($invoice, $view_mode, $langcode, $content);
  }
}
