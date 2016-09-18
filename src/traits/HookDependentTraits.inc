<?php

/**
 * Class HookDependentTraits
 */
trait HookDependentTraits {
  /**
   * @var null|string $hook
   *   The hook for which the data is built/rebuilt.
   */
  protected $hook;
  /**
   * @var array $hookInfo
   *   The hook info declared in entity toolbox.
   *
   * @see hook_hook_register_info().
   */
  protected $hookInfo = array();

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
   * Sets hookInfo after hook has been set.
   */
  protected function postSetHook() {
    $this->setHookInfo(entity_toolbox_hook_get_info($this->hook));
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