<?php

/**
 * Class HookBuilderFactory
 */
class HookBuilderFactory extends FactoryBase {
  /**
   * @var string $hook
   */
  protected $hook;
  /**
   * @var array $hookInfo
   */
  protected $hookInfo = array();

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    parent::__construct($args);
  }

  /**
   * @return string
   */
  public function getHook() {
    return $this->hook;
  }

  /**
   * @param string $hook
   */
  public function setHook($hook) {
    $this->hook = $hook;
  }

  /**
   *
   */
  protected function postSetHook() {
    $this->__set('hook_info', entity_toolbox_hook_get_info($this->hook));
  }

  /**
   * @return array
   */
  public function getHookInfo() {
    return $this->hookInfo;
  }

  /**
   * @param array $hookInfo
   */
  public function setHookInfo($hookInfo) {
    $this->hookInfo = $hookInfo;
  }

  /**
   *
   */
  protected function postSetHookInfo() {
    $this->__set('base_class', $this->hookInfo['base class']);
    if (!empty($this->hookInfo['model class'])) {
      $this->__set('model_class', $this->hookInfo['model class']);
    }
  }
}