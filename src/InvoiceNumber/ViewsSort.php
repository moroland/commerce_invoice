<?php
/**
 * @file
 * Provides views sort handler for invoice numbers.
 */

namespace Drupal\commerce_invoice\InvoiceNumber;

class ViewsSort extends \views_handler_sort {

  /**
   * {@inheritdoc}
   */
  public function query() {
    $this->ensure_my_table();
    $this->query->add_orderby($this->table_alias, 'number_pattern', $this->options['order']);
    $this->query->add_orderby($this->table_alias, 'number_key', $this->options['order']);
    $this->query->add_orderby($this->table_alias, 'number_sequence', $this->options['order']);
  }

}
