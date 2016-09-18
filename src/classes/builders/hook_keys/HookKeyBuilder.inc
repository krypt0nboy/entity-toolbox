<?php

/**
 * Class HookKeyBuilder
 */
class HookKeyBuilder extends KeyBuilder {
  use ModuleDependentTraits;

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
   * @var HookBuilder $hookBuilder
   */
  protected $hookBuilder;

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

  /**
   * @return HookBuilder
   */
  public function getHookBuilder() {
    return $this->hookBuilder;
  }

  /**
   * @param HookBuilder $hookBuilder
   */
  public function setHookBuilder($hookBuilder) {
    $this->hookBuilder = $hookBuilder;
  }

  /** {{@inheritdoc}} */
  protected function autoSet() {
    parent::autoSet();
    $this->autoSetModuleInfo();
    $this->autoSetModuleEntities();
  }

  /** {{@inheritdoc}} */
  protected function keyBuilderGetInstance($keyBuilderClass, array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'hook'            => $this->hook,
      'hook_builder'    => $this->hookBuilder,
      'module'          => $this->module,
      'module_info'     => $this->moduleInfo,
      'module_entities' => $this->moduleEntities,
    ), $args);

    return parent::keyBuilderGetInstance($keyBuilderClass, $args);
  }

  /**
   * @return array
   */
  public function getUpdatedTemplateVars() {
    $vars = $this->getTemplateVars();
    if ($this->parentBuilder == $this->hookBuilder) {
      $parentTemplateVars = $this->getParentBuilder()->getTemplateVars();
      $vars += $parentTemplateVars;
    }
    else {
      $parentTemplateVars      = $this->getParentBuilder()->getTemplateVars();
      $hookBuilderTemplateVars = $this->getHookBuilder()->getTemplateVars();
      $vars += $hookBuilderTemplateVars;
      $vars += $parentTemplateVars;
    }

    return $vars;
  }
}