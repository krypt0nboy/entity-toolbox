<?php

/**
 * Class HookModel
 */
class HookModel extends ModelBase {
  /**
   * @access protected
   * @var string $hook
   *   The hook name.
   */
  protected $hook;
  /**
   * @access protected
   * @var array $hookInfo
   */
  protected $hookInfo = array();

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

  /**
   * Getter for "hookInfo".
   *
   * @return array
   */
  public function getHookInfo() {
    return $this->hookInfo;
  }

  /**
   * Setter for "hookInfo".
   *
   * @param array $hookInfo
   *   The hook info to set.
   *
   * @see hook_hook_register_info().
   */
  public function setHookInfo($hookInfo) {
    $this->hookInfo = $hookInfo;
  }
}