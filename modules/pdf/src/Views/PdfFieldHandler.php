<?php

namespace Drupal\commerce_invoice_pdf\Views;

/**
 * @file
 * Views field handler to display a download link for an invoice PDF.
 */

class PdfFieldHandler extends \views_handler_field {

  /**
   * {@inheritdoc}
   */
  public function option_definition() {
    $options = parent::option_definition();
    $options['op'] = array(
      'default' => 'view',
    );
    $options['text'] = array(
      'default' => 'View PDF',
      'translatable' => TRUE,
    );
    return $options;
  }

  /**
   * Overrides parent::options_form().
   */
  public function options_form(&$form, &$form_state) {
    $form['op'] = array(
      '#type' => 'select',
      '#title' => t('Link type'),
      '#default_value' => $this->options['op'],
      '#options' => array(
        'view' => t('View (open PDF in browser)'),
        'download' => t('Force download'),
      ),
    );
    $form['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to display'),
      '#default_value' => $this->options['text'],
    );
    parent::options_form($form, $form_state);
  }

  /**
   * Overrides parent::render().
   */
  public function render($values) {
    $entity_id = $this->get_value($values);

    $op = !empty($this->options['op']) ? $this->options['op'] : 'view';

    $link = ['path' => 'invoices/' . $entity_id . '/pdf'];
    if ($op === 'download') {
      $link['query']['download'] = 1;
    }
    $this->options['alter']['make_link'] = TRUE;
    $this->options['alter'] = array_merge($this->options['alter'], $link);

    return $this->options['text'];
  }
}
