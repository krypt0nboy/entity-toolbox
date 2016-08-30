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
  /**
   * @var string $entityType
   */
  protected $entityType;

  /** {{@inheritdoc}} */
  public function __construct($name, $entityType, array $args = array()) {
    $this->entityType = $entityType;
    $this->hook       = $name;
    $this->hookInfo   = entity_toolbox_hook_get_info($this->hook);
    parent::__construct($name, $args);
  }

  /** {{@inheritdoc}} */
  protected function setFactoryInfo() {
    $this->factoryInfo = array(
      'base class'  => $this->hookInfo['base class'],
      'model class' => !empty($this->hookInfo['builder model']) ? $this->hookInfo['builder model'] : $this->hookInfo['model class'],
    );
  }

  /** {{@inheritdoc}} */
  protected function setArgs(array $args = array()) {
    parent::setArgs($args);
  }

  /**
   * Returns a hook builder.
   *
   * @param array $rawData
   *   The raw data to rebuild if needed.
   *
   * @return HookBuilder
   */
  public function getInstance(array $rawData = array()) {
    $this->parseClassModel();
    $class = $this->getParsedModel();
    $class = class_exists($class) ? $class : $this->factoryInfo['base class'];

    return new $class(array('entity_type' => $this->entityType));
  }
}