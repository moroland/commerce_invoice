<?php

namespace Drupal\commerce_invoice_pdf\Views;

/**
 * @file
 * Views field handler to display a download link for the current invoice on an order.
 */

class PdfOrderFieldHandler extends PdfFieldHandler {

  /**
   * Overrides parent::render().
   */
  public function render($values) {
    $order_id = $this->get_value($values);

    $op = !empty($this->options['op']) ? $this->options['op'] : 'view';

    // Mock order object, no need for the whole thing.
    $order = new \stdClass();
    $order->order_id = $order_id;

    if ($invoice = commerce_invoice_load_current($order)) {
      $link = ['path' => 'invoices/' . $invoice->invoice_id . '/pdf'];
      if ($op === 'download') {
        $link['query']['download'] = 1;
      }
      $this->options['alter']['make_link'] = TRUE;
      $this->options['alter'] = array_merge($this->options['alter'], $link);

      return $this->options['text'];
    }
  }
}
