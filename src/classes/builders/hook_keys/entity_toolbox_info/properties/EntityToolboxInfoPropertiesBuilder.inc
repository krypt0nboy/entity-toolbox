<?php

/**
 * Class PropertiesValueBuilder
 */
class EntityToolboxInfoPropertiesBuilder extends EntityToolboxInfoKeyBuilder {
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
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'self_key' => 'properties',
      ),
      $args
    );
    parent::__construct($args);
  }

  /**
   * @return array
   */
  public function getRequiredProperties() {
    return $this->requiredProperties;
  }

  /**
   * @param array $requiredProperties
   */
  protected function setRequiredProperties($requiredProperties) {
    $this->requiredProperties = $requiredProperties;
  }

  /**
   * @return array
   */
  public function getMissingRequiredProperties() {
    return $this->missingRequiredProperties;
  }

  /**
   * @param array $missingRequiredProperties
   */
  public function setMissingRequiredProperties($missingRequiredProperties) {
    $this->missingRequiredProperties = $missingRequiredProperties;
  }

  /** {{@inheritdoc}} */
  public function build() {
    $build               = array();
    $structure           = array();
    $propertyBuilders    = array();
    $propertiesInstances = array();
    $factoryArgs         = array(
      'fieldable' => $this->getHookBuilder()
                          ->getBuild('fieldable') ? 'Fieldable' : 'NotFieldable',
    );
    $this->extractMissingPropertyTypes();

    foreach ($this->getHookBuilder()
                  ->getRawProperties() as $property => $info) {
      $propertyTypeInstance        = property_type_get_instance($info['type'], $factoryArgs);
      $structure[$property]        = array(
        'type'   => 'array',
        'method' => 'buildProperty',
      );
      $propertyBuilders[$property] = array(
        'property_type'     => $info['type'],
        'property_instance' => $propertyTypeInstance,
        'self_key'          => $property,
        'property_name'     => $property,
      );
    }
    foreach ($this->missingRequiredProperties as $missingRequiredProperty) {
      $propertyTypeInstance            = property_type_get_instance($missingRequiredProperty, $factoryArgs);
      $propertyDefaultName             = $propertyTypeInstance->getDefaultName();
      $propertyName                    = $this->processValueTemplate($propertyDefaultName);
      $structure[$propertyName]        = array(
        'type'   => 'array',
        'method' => 'buildProperty',
      );
      $propertyBuilders[$propertyName] = array(
        'property_type'     => $missingRequiredProperty,
        'property_instance' => $propertyTypeInstance,
        'self_key'          => $propertyName,
        'property_name'     => $propertyName,
      );
    }
    $this->__set('structure', $structure);
    foreach ($propertyBuilders as $propName => $propertyBuilderArgs) {
      $this->setKeyBuilder($propName, $this->keyBuilderGetInstance('EntityToolboxInfoPropertyBuilder', $propertyBuilderArgs));
    }
    foreach ($this->getStructure() as $property => $params) {
      $this->setKeyBuild($property, $this->buildProperty($property));
    }

    return $this->build;
  }

  /**
   * Builds a property.
   *
   * @param string $property
   *   The property name.
   *
   * @return array
   */
  protected function buildProperty($property) {
    return $this->getKeyBuilder($property)->build();
  }

  /**
   * Extract the missing required properties.
   */
  public function extractMissingPropertyTypes() {
    $types = array();
    foreach ($this->getHookBuilder()
                  ->getRawProperties() as $name => $property) {
      $types[] = $property['type'];
    }
    $missing = array_diff($this->requiredProperties, array_unique($types));
    $this->__set('missing_required_properties', $missing);
  }
}