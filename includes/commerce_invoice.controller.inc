<?php

/**
 * @file
 * The controller for the invoice entity containing the CRUD operations.
 */

/**
 * The controller class for invoices contains methods for the order CRUD
 * operations. The load method is inherited from the default controller.
 */
class CommerceInvoiceEntityController extends DrupalDefaultEntityController {

  /**
   * Create a default invoice.
   *
   * @param $order_id
   *   The ID of the order the invoice belongs to.
   *
   * @return
   *   An invoice object with all default fields initialized.
   */
  public function create($order_id = 0) {
    return (object) array(
      'invoice_id' => '',
      'invoice_number' => '',
      'order_id' => $order_id,
      'created' => '',
      'changed' => '',
    );
  }

  /**
   * Saves an invoice.
   *
   * When saving an invoice, the function will automatically create an invoice number
   * based 
   *
   * @param $invoice
   *   The full invoice object to save.
   *
   * @return
   *   The saved invoice object.
   */
  public function save($invoice) {
    $transaction = db_transaction();

    try {
      $invoice->changed = REQUEST_TIME;
      
      // Inserting new invoice
      if (empty($invoice->invoice_id)) {
        $invoice->created = REQUEST_TIME;
        $invoice->invoice_number = $this->generate_invoice_id();
        
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
    catch (Exception $e) {
      $transaction->rollback();
      watchdog_exception('commerce_invoice', $e);
      throw $e;
    }
  }
  
  /**
   * Generates invoice id
   * 
   * @return
   *   The generated invoice id
   */
  protected function generate_invoice_id() {
    // TODO: there is probably a better way to do this
    // Invoice generation method
    $method = variable_get('commerce_invoice_number_method', COMMERCE_INVOICE_METHOD_YEAR);
    // Get last invoice created
    $result = db_select('invoice', 'i')
      ->fields('i')
      ->orderBy('created', 'DESC')
      ->range(0, 1);
    if ($record = $result->fetchObject()) {
      $last_number = $record->invoice_number;
      switch($method) {
        case COMMERCE_INVOICE_METHOD_INFINITE:
          $last_id = $record->invoice_id;
          $id = $last_id + 1;
          $return = str_replace('[invoice_id]', $id, $method);
          break;
        case COMMERCE_INVOICE_METHOD_YEAR:
          // Are we in the same year as the last invoice
          $last_year = strstr($last_number, '-', TRUE);
          $last_year = str_replace('-', '', $last_year);
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
          $return = date('Y').'-'.date('m').$id;
          break;
      }
      return $return;
            
    }
    else {
      // First invoice being generated
      $id = 1;
      $return = str_replace('[invoice_id]', $id, $method);
      return date($result);
    }
  }
  
  /**
   * Deletes multiple invoices by ID.
   *
   * @param $invoice_ids
   *   An array of invoice IDs to delete.
   *
   * @return
   *   TRUE on success, FALSE otherwise.
   */
  public function delete($invoice_ids) {
    if (!empty($invoice_ids)) {
      $invoices = $this->load($invoice_ids, array());

      $transaction = db_transaction();

      try {
        db_delete('commerce_invoice')
          ->condition('invoice_id', $invoice_ids, 'IN')
          ->execute();

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
}
      
      
