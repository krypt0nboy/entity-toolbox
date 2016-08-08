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

  /** {{@inheritdoc}} */
  public function build() {
  }

  /**
   * Build default properties.
   */
  protected function buildDefault() {
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
    $default = $this->buildDefault();
    foreach ($this->rawValueData as $name => $property) {

    }

    $this->processedValueData = array_merge($default, $this->processedValueData);

    return $this->processedValueData;
  }

  /** {{@inheritdoc}} */
  protected function buildDefault() {
    $default = array();
    foreach ($this->missingRequiredProperties as $missingRequiredProperty) {
      $propertyInfo = entity_toolbox_property_type_get_info($missingRequiredProperty)['fieldable'];
      $builder      = new $propertyInfo['builder']($this->entityType);
    }

    return $default;
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