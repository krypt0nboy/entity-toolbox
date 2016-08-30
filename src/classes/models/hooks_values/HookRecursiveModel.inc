<?php

/**
 * Class HookRecursiveModel
 */
class HookRecursiveModel extends RecursiveModel {
  /**
   * @access protected
   * @var string $hook
   *   The hook name.
   */
  protected $hook;

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    parent::__construct($args);
  }

  /**
   * Getter for "hook".
   *
   * @return string
   */
  public function getHook() {
    return $this->hook;
  }

  /**
   * Setter for "hook".
   *
   * @param string $hook
   *   The hook name.
   */
  public function setHook($hook) {
    $this->hook = $hook;
  }
}