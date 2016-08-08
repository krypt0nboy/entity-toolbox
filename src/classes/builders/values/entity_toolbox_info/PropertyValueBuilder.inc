<?php

/**
 * Class PropertyValueBuilder
 */
class PropertyValueBuilder extends ArrayValueBuilder {
  /**
   * @var string $propertyType
   *   The entity_toolbox property type.
   */
  protected $propertyType;
  /**
   * @var array $defaults
   *   The default values for a property type.
   */
  protected $defaults = array();

  /** {{@inheritdoc}} */
  public function __construct($entityType, $tableKey, array $rawData, $propertyType = NULL) {
    parent::__construct($entityType, $tableKey, $rawData);
    $this->propertyType = $propertyType;
    $info               = entity_toolbox_property_type_get_info($this->propertyType);
    $this->defaults     = $info['default'];
  }
}

/**
 * Class PropertyValueBuilderIdFieldable
 */
class PropertyValueBuilderIdFieldable extends PropertyValueBuilder {
  /** {{@inheritdoc}} */
  public function __construct($entityType, $tableKey = NULL, array $rawData = array()) {
    parent::__construct($entityType, $tableKey, $rawData);
  }
}