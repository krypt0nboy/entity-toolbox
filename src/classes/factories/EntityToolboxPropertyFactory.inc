<?php

/**
 * Class EntityToolboxPropertyFactory
 */
class EntityToolboxPropertyFactory extends FactoryBase {
  /**
   * @var string $propertyType
   *   The property type.
   */
  protected $propertyType;
  /**
   * @var array $propertyTypeInfo
   *   The property type info.
   */
  protected $propertyTypeInfo = array();

  /** {{@inheritdoc}} */
  public function __construct($name, array $args = array()) {
    $this->propertyTypeInfo = entity_toolbox_property_type_get_info($name);
    $this->propertyType     = $name;
    parent::__construct($name, $args);
  }

  /** {{@inheritdoc}} */
  protected function setFactoryInfo() {
    $this->factoryInfo = array(
      'base class'  => $this->propertyTypeInfo['base class'],
      'model class' => !empty($this->propertyTypeInfo['model class']) ? $this->propertyTypeInfo['model class'] : $this->propertyTypeInfo['base class'],
    );
  }

  /** {{@inheritdoc}} */
  protected function setArgs(array $args = array()) {
    parent::setArgs($args);
  }

  /**
   * Returns a property type instance.
   *
   * @return EntityToolboxPropertyBase
   */
  public function getInstance() {
    $this->parseClassModel();
    $class = $this->getParsedModel();

    return new $class();
  }
}