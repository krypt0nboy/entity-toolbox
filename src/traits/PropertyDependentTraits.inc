<?php

/**
 * Class PropertyDependentTraits
 */
trait PropertyDependentTraits {
  /**
   * @var string $propertyName
   */
  protected $propertyName;
  /**
   * @var string $propertyType
   */
  protected $propertyType;
  /**
   * @var array $propertyInfo
   */
  protected $propertyInfo = array();
  /**
   * @var EntityToolboxPropertyBase $propertyInstance
   */
  protected $propertyInstance;
  /**
   * @var bool $isReference
   */
  protected $isReference;
  /**
   * @var bool $isMultiple
   */
  protected $isMultiple;
  /**
   * @var bool $serialize
   */
  protected $serialize;

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
  public function getPropertyType() {
    return $this->propertyType;
  }

  /**
   * @param string $propertyType
   */
  public function setPropertyType($propertyType) {
    $this->propertyType = $propertyType;
  }

  /**
   * @return EntityToolboxPropertyBase
   */
  public function getPropertyInstance() {
    return $this->propertyInstance;
  }

  /**
   * @param EntityToolboxPropertyBase $propertyInstance
   */
  public function setPropertyInstance($propertyInstance) {
    $this->propertyInstance = $propertyInstance;
  }

  /**
   * @return array
   */
  public function getPropertyInfo() {
    return $this->propertyInfo;
  }

  /**
   * @param array $propertyInfo
   */
  public function setPropertyInfo($propertyInfo) {
    $this->propertyInfo = $propertyInfo;
  }

  /**
   * @return boolean
   */
  public function getIsReference() {
    return $this->isReference;
  }

  /**
   * @param boolean $isReference
   */
  public function setIsReference($isReference) {
    $this->isReference = $isReference;
  }

  /**
   * @return boolean
   */
  public function getIsMultiple() {
    return $this->isMultiple;
  }

  /**
   * @param boolean $isMultiple
   */
  public function setIsMultiple($isMultiple) {
    $this->isMultiple = $isMultiple;
  }

  /** {{@inheritdoc}} */
  protected function postSetToolboxInfo() {
    if (!empty($this->toolboxInfo['properties'][$this->constructArgs['property_name']])) {
      $this->__set('property_info', $this->toolboxInfo['properties'][$this->constructArgs['property_name']]);
    }
  }

}