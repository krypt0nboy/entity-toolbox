<?php

/**
 * Class PropertiesValueBuilder
 */
class PropertiesValueBuilder extends ArrayBuilder {
  /**
   * @var array $requiredProperties
   *   The required properties for an entity type.
   */
  protected $requiredProperties = array();

  /**
   * @var array $missingRequiredProperties
   *   The missing required properties.
   */
  protected $missingRequiredProperties = array();

  /** {{@inheritdoc}} */
  public function __construct($entityType, array $rawData = array(), array $requiredProperties = array()) {
    parent::__construct($entityType, "properties", $rawData);
  }

  /**
   * @return string[]
   */
  public function extractMissingPropertyTypes() {
    $types = array();
    foreach ($this->rawValueData as $name => $property) {
      $types[] = $property['type'];
    }

    $this->missingRequiredProperties = array_diff(array_unique($types), $this->requiredProperties);
  }

  public function build() {

  }
}

/**
 * Class PropertiesValueBuilderFieldable
 */
class PropertiesValueBuilderFieldable extends PropertiesValueBuilder {
  /** {{@inheritdoc}} */
  public function __construct($entityType, array $rawData) {
    $required = array(
      'id',
      'bundle',
      'name',
      'created',
      'changed',
      'author',
      'status',
    );
    parent::__construct($entityType, $rawData, $required);
  }

  /** {{@inheritdoc}} */
  public function build() {
    foreach ($this->missingRequiredProperties as $missingRequiredProperty) {
      $propertyTypeInfo = entity_toolbox_property_type_get_info($missingRequiredProperty);
    }
  }
}

/**
 * Class PropertiesValueBuilderNotFieldable
 */
class PropertiesValueBuilderNotFieldable extends PropertiesValueBuilder {
  /** {{@inheritdoc}} */
  public function __construct($entityType, array $rawData) {
    $required = array(
      'id',
      'name',
    );
    parent::__construct($entityType, $rawData, $required);
  }

  /** {{@inheritdoc}} */
  public function build() {

  }
}