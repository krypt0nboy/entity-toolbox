<?php

/**
 * Class EntityOperationTypeBase
 */
class EntityOperationTypeBase {
  use EntityToolboxCommonTraits, EntityDependentTraits, TemplatingTraits;

  /**
   * @var string $defaultType
   */
  protected $defaultType;
  /**
   * @var array $defaultLabels
   */
  protected $defaultLabels = array();
  /**
   * @var $defaultHandler
   */
  protected $defaultHandler;
  /**
   * @var array $defaultProvision
   */
  protected $defaultProvision = array();

  /**
   * EntityOperationTypeBase constructor.
   * @param array $args
   */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'self_extract_marker' => 'default',
      'self_replace_marker' => 'default_entity_operation_type',
      'default_type'        => '',
      'default_labels'      => array(
        'lowercase' => '',
        'uppercase' => '',
        'camelcase' => '',
      ),
      'default_handler'     => 'EntityOperationsOperation%default_entity_operation_type_labels_camelcase%',
      'default_provision'   => array(
        'menu'        => array(),
        'views field' => array()
      ),
    ), $args);
    $this->constructSet($args);
  }

  /**
   * @param $args
   */
  protected function constructSet($args) {
    $this->setConstructArgs($args);
    foreach ($args as $argName => $arg) {
      $this->__set($argName, $arg);
    }
  }

  /**
   * @return string
   */
  public function getDefaultType() {
    return $this->defaultType;
  }

  /**
   * @param string $defaultType
   */
  public function setDefaultType($defaultType) {
    $this->defaultType = $defaultType;
  }

  /**
   * @return array
   */
  public function getDefaultLabels() {
    return $this->defaultLabels;
  }

  /**
   * @param array $defaultLabels
   */
  public function setDefaultLabels($defaultLabels) {
    $this->defaultLabels = $defaultLabels;
  }

  /**
   * @return mixed
   */
  public function getDefaultHandler() {
    return $this->defaultHandler;
  }

  /**
   * @param mixed $defaultHandler
   */
  public function setDefaultHandler($defaultHandler) {
    $this->defaultHandler = $defaultHandler;
  }

  /**
   * @return array
   */
  public function getDefaultProvision() {
    return $this->defaultProvision;
  }

  /**
   * @param array $defaultProvision
   */
  public function setDefaultProvision($defaultProvision) {
    $this->defaultProvision = $defaultProvision;
  }

}