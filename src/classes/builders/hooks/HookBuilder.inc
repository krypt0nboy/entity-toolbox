<?php


/**
 * Class HookBuilder
 *
 * Used to build a hook data.
 */
class HookBuilder extends BuilderBase {
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

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    if (empty($args['hook'])) {
      throw new HookNameNotProvided();
    }
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

  /**
   * @param       $keyBuilderClass
   * @param array $args
   *
   * @return mixed
   */
  protected function keyBuilderGetInstance($keyBuilderClass, array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'hook'         => $this->getHook(),
      'hook_builder' => $this,
    ), $args);

    return parent::keyBuilderGetInstance($keyBuilderClass, $args);
  }
}