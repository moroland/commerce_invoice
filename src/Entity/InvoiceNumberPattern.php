<?php

namespace Drupal\commerce_invoice\Entity;

class InvoiceNumberPattern extends \Entity {

  public $name;
  public $label;
  public $pattern;

  /**
   * Get the default invoice number pattern.
   *
   * @return InvoiceNumberPattern
   */
  public static function getDefault() {
    $name = variable_get('commerce_invoice_default_number_pattern', 'consecutive');
    $default = commerce_invoice_number_pattern_load($name);
    if (!$default) {
      if ($name !== 'default') {
        watchdog('commerce_invoice', 'Failed to find default invoice number pattern: @name', ['@name' => $name], WATCHDOG_ERROR);
      }

      return entity_create('commerce_invoice_number_pattern', [
        'name' => 'default',
        'label' => t('Default'),
        'pattern' => '',
      ]);
    }

    return $default;
  }

  /**
   * Set this as the default invoice number pattern.
   */
  public function setAsDefault() {
    if (empty($this->name)) {
      watchdog('commerce_invoice', 'Cannot set an invoice number pattern as the default: it has no name.', [], WATCHDOG_NOTICE);
    }
    else {
      variable_set('commerce_invoice_default_number_pattern', $this->name);
    }
  }
}
