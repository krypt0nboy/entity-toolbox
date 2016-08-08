<?php

/**
 * Class PropertyValueBuilder
 */
class PropertyValueBuilder extends ArrayBuilder {
  /**
   * @var bool $fieldable
   *   If $this->entityType is fieldable.
   */
  protected $fieldable;

  /**
   * @var string $propertyType
   *   The entity_toolbox property type.
   */
  protected $propertyType;

  /**
   * @var array $propertyInfo
   */
  protected $propertyInfo = array();

  /**
   * @var array $defaults
   *   The default values for a property type.
   */
  protected $defaults = array();

  /** {{@inheritdoc}} */
  public function __construct($entityType, $tableKey, array $rawData, $propertyType = NULL, $fieldable = NULL) {
    parent::__construct($entityType, $tableKey, $rawData);
    $this->propertyType = $propertyType;
    $this->fieldable    = $fieldable;
    $this->propertyInfo = $this->setPropertyInfo();
  }

  /**
   * Sets the property info.
   */
  protected function setPropertyInfo() {
    $info = entity_toolbox_property_type_get_info($this->propertyType);
    if (!empty($info[$this->fieldable])) {
      $this->propertyInfo = $info[$this->fieldable];
    }
    else {
      $this->propertyInfo = $info['all'];
    }
  }

}

/**
 * Class PropertyBuilderIdFieldable
 */
class PropertyBuilderId extends PropertyValueBuilder {
  /** {{@inheritdoc}} */
  public function __construct($entityType, $tableKey = NULL, array $rawData = array()) {
    parent::__construct($entityType, $tableKey, $rawData);
  }
}