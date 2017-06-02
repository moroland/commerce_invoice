<?php
/**
 * @file
 * Provides views field for invoice numbers.
 */

namespace Drupal\commerce_invoice\InvoiceNumber;

class ViewsField extends \views_handler_field {

  /**
   * {@inheritdoc}
   */
  public function render($values) {
    $key = $this->get_value($values, 'number_key');
    $sequence = $this->get_value($values);
    $pattern_name = $this->get_value($values, 'number_pattern');

    $invoiceNumber = new InvoiceNumber($sequence, $key, $pattern_name);

    return (string) $invoiceNumber;
  }

  /**
   * {@inheritdoc}
   */
  public function click_sort($order) {
    $params = $this->options['group_type'] != 'group' ? array('function' => $this->options['group_type']) : array();
    $this->query->add_orderby($this->table_alias, 'number_pattern', $order, '', $params);
    $this->query->add_orderby($this->table_alias, 'number_key', $order, '', $params);
    $this->query->add_orderby($this->table_alias, 'number_sequence', $order, '', $params);
  }

}
