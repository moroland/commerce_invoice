<?php

namespace Drupal\commerce_invoice\InvoiceNumber\Strategy;

abstract class DatabaseStrategyBase implements StrategyInterface {

  /**
   * Returns the strategy name, as a string that can be saved in the database.
   *
   * @return string
   */
  abstract protected function getName();

  /**
   * Returns the key which differentiates sequential numbers.
   *
   * @return string|NULL
   *   For example, a monthly strategy would return '2016-07'. A strategy that
   *   wants the sequence to auto-increment forever would return NULL.
   */
  abstract protected function getKey();

  /**
   * {@inheritdoc}
   */
  public function getNext($save = TRUE) {
    $key = $this->getKey();

    return $this->format($this->getNextInSequence($save, $key), $key);
  }

  /**
   * Format an invoice number as a string.
   *
   * @param int $sequence
   * @param string|NULL $key
   *
   * @return string
   */
  protected function format($sequence, $key) {
    if ($key === NULL) {
      return (string) $sequence;
    }

    return $key . '-' . $sequence;
  }

  /**
   * Calculates the next sequential number for this strategy and key.
   *
   * @param bool $save
   * @param string|NULL $key
   *
   * @return int
   */
  protected function getNextInSequence($save = TRUE, $key) {
    $lockName = $this->getLockName($key);
    if ($save) {
      while (!lock_acquire($lockName)) {
        lock_wait($lockName);
      }
    }

    $last = $this->getLastInSequence($key);
    $next = $last ? $last + 1 : 1;

    if ($save) {
      $this->saveLastInSequence($next, $key);
      lock_release($lockName);
    }

    return $next;
  }

  /**
   * Saves the last sequential number generated for this strategy and key.
   *
   * @param int $last
   * @param string|NULL $key
   */
  protected function saveLastInSequence($last, $key) {
    $key = array(
      'strategy' => $this->getName(),
      'key' => $key,
    );
    db_merge('commerce_invoice_number')
      ->key($key)
      ->fields($key + array('last' => $last))
      ->execute();
  }

  /**
   * Finds the last sequential number generated for this strategy and key.
   *
   * @param string|NULL $key
   *
   * @return int|FALSE
   *   The last sequential number or FALSE if no previous number is found.
   */
  protected function getLastInSequence($key) {
    $strategy = $this->getName();
    $last = db_query('SELECT last FROM {commerce_invoice_number} WHERE strategy = :strategy AND key = :key', array(
      ':strategy' => $strategy,
      ':key' => $key,
    ))->fetchField();

    return $last !== FALSE ? (int) $last : FALSE;
  }

  /**
   * Returns the lock name for lock_acquire() et al.
   *
   * @param string|NULL $key
   *
   * @return string
   */
  protected function getLockName($key) {
    $lockName = 'commerce_invoice_nr_' . $this->getName();
    if ($key !== NULL) {
      $lockName .= '_' . $key;
    }

    return $lockName;
  }
}
