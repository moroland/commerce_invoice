<?php
/**
 * @file
 * Invoice Number Pattern entity
 */

namespace Drupal\commerce_invoice\Entity;

class InvoiceNumberPattern extends \Entity {

  public $name;
  public $label;
  public $skip_sequence;
  public $pattern;

  /**
   * Get the machine name of the default invoice number pattern.
   *
   * @return string
   */
  public static function getDefaultName() {
    return variable_get('commerce_invoice_default_number_pattern', 'monthly');
  }

  /**
   * Get the default invoice number pattern.
   *
   * @return InvoiceNumberPattern
   */
  public static function getDefault() {
    $name = static::getDefaultName();
    $default = commerce_invoice_number_pattern_load($name);
    if (!$default) {
      watchdog('commerce_invoice', 'Failed to find default invoice number pattern: @name', ['@name' => $name], WATCHDOG_ERROR);

      return entity_create('commerce_invoice_number_pattern', [
        'name' => 'default',
        'label' => t('Default'),
        'pattern' => '',
      ]);
    }

    return $default;
  }

  /**
   * Magic string conversion.
   *
   * @return string
   */
  public function __toString() {
    return (string) $this->name;
  }
}
