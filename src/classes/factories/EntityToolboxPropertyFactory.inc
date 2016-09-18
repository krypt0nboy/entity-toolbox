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
  /**
   * @var bool $fieldable
   */
  protected $fieldable;

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    parent::__construct($args);
  }

  /**
   * @return boolean
   */
  public function getFieldable() {
    return $this->fieldable;
  }

  /**
   * @param boolean $fieldable
   */
  public function setFieldable($fieldable) {
    $this->fieldable = $fieldable;
  }

  /**
   * @return string
   */
  public function getPropertyType() {
    return $this->propertyType;
  }

  /**
   * @param string $propertyType
   */
  public function setPropertyType($propertyType) {
    $this->propertyType = $propertyType;
  }

  protected function postSetPropertyType() {
    $this->__set('property_type_info', entity_toolbox_property_type_get_info($this->propertyType));
  }

  /**
   * @return array
   */
  public function getPropertyTypeInfo() {
    return $this->propertyTypeInfo;
  }

  /**
   * @param array $propertyTypeInfo
   */
  public function setPropertyTypeInfo($propertyTypeInfo) {
    $this->propertyTypeInfo = $propertyTypeInfo;
  }

  protected function postSetPropertyTypeInfo() {
    $this->__set('base_class', $this->propertyTypeInfo['base class']);
    if (!empty($this->propertyTypeInfo['model class'])) {
      $this->__set('model_class', $this->propertyTypeInfo['model class']);
    }
  }

  /** {{@inheritdoc}} */
  protected function initTemplateVars() {
    $this->updateTemplateVar('fieldable', $this->fieldable ? 'Fieldable' : 'NotFieldable');
  }
}