<?php

class EntityToolboxInfoPropertyDependentKeyBuilder extends EntityToolboxInfoKeyBuilder {
  /**
   * @var string $propertyType
   *   The entity_toolbox property type.
   */
  protected $propertyType;
  /**
   * @var array $propertyInfo
   *   The property type info.
   */
  protected $propertyInfo = array();
  /**
   * @var EntityToolboxPropertyBase $propertyInstance
   *   An instance of the property type.
   */
  protected $propertyInstance;

  /**
   * @var string $propertyReference
   */
  protected $propertyReference;

  /**
   * @var array $propertyReferenceInfo
   */
  protected $propertyReferenceInfo = array();

  /**
   * @var string $propertyName
   */
  protected $propertyName;

  /**
   * Sets the property info.
   */
  protected function setPropertyInfo($propertyInfo) {
    $this->propertyInfo = $propertyInfo;
  }

  protected function setPropertyType($type) {
    $this->propertyType = $type;
  }

  /**
   * Gets the property info.
   *
   * @return array
   */
  public function getPropertyInfo() {
    return $this->propertyInfo;
  }

  protected function preSetPropertyInstance() {
    $this->__set('hook_builder', $this->constructArgs['hook_builder']);
    $this->__set('property_name', $this->constructArgs['property_name']);
  }

  /**
   * Sets the property instance.
   *
   * @param EntityToolboxPropertyBase $propertyInstance
   *   The property instance.
   */
  protected function setPropertyInstance(EntityToolboxPropertyBase $propertyInstance) {
    $this->propertyInstance = $propertyInstance;
  }

  /**
   * Gets the property instance.
   * @return \EntityToolboxPropertyBase
   */
  protected function getPropertyInstance() {
    return $this->propertyInstance;
  }

  /**
   * @return string
   */
  public function getPropertyName() {
    return $this->propertyName;
  }

  /**
   * @param string $propertyName
   */
  public function setPropertyName($propertyName) {
    $this->propertyName = $propertyName;
  }

  /**
   * @return string
   */
  public function getPropertyReference() {
    return $this->propertyReference;
  }

  /**
   * @param string $propertyReference
   */
  public function setPropertyReference($propertyReference) {
    $this->propertyReference = $propertyReference;
  }

  /**
   * @return array
   */
  public function getPropertyReferenceInfo() {
    return $this->propertyReferenceInfo;
  }

  /**
   * @param array $propertyReferenceInfo
   */
  public function setPropertyReferenceInfo($propertyReferenceInfo) {
    $this->propertyReferenceInfo = $propertyReferenceInfo;
  }

  /**
   *
   */
  protected function postSetPropertyInstance() {
    $vars = $this->getPropertyInstance()->extractSelfVars();
    foreach ($vars as $var => $value) {
      $this->updateTemplateVars($var, $value);
    }
  }

  protected function keyBuilderGetInstance($keyBuilderClass, array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'property_name' => $this->constructArgs['property_name'],
    ), $args);

    return parent::keyBuilderGetInstance($keyBuilderClass, $args);
  }
}