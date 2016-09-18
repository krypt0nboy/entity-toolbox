<?php

/**
 * Class EntityPropertyInfoPropertiesBuilder
 */
class EntityPropertyInfoPropertiesBuilder extends EntityPropertyInfoKeyBuilder {
  /**
   * @var array $properties
   */
  protected $properties = array();
  /**
   * @var array $referenceProperties
   */
  protected $referenceProperties = array();

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
  public function getProperties() {
    return $this->properties;
  }

  /**
   * @param array $properties
   */
  public function setProperties($properties) {
    $this->properties = $properties;
  }

  /**
   * @return array
   */
  public function getReferenceProperties() {
    return $this->referenceProperties;
  }

  /**
   * @param array $referenceProperties
   */
  public function setReferenceProperties($referenceProperties) {
    $this->referenceProperties = $referenceProperties;
  }

  /** {{@inheritdoc}} */
  protected function constructSet($args) {
    parent::constructSet($args);
    $this->__set('properties', $this->toolboxInfo['properties']);
  }

  /** {{@inheritdoc}} */
  protected function genDynamicStructure() {
    $structure          = array();
    $keyBuildersClasses = array();
    $keyBuildersArgs    = array();
    $refProps           = $this->extractReferenceProperties(TRUE);
    foreach ($this->properties as $property => $info) {
      $propIsRef            = in_array($refProps, $property);
      $propIsMulti          = $info['multiple'];
      $structure[$property] = array(
        'type'   => 'array',
        'method' => 'buildProperty',
      );
      $keyBuilderClass      = 'EntityPropertyInfoPropertyBuilder';
      if ($propIsRef) {
        $keyBuilderClass = $propIsMulti ? 'EntityPropertyInfoReferenceMultiplePropertyBuilder' : 'EntityPropertyInfoReferencePropertyBuilder';
      }
      $keyBuildersArgs[$property]    = array(
        'property_type' => $this->toolboxInfo['properties'][$property]['type'],
        'property_name' => $property,
      );
      $keyBuildersClasses[$property] = $keyBuilderClass;
      if ($propIsRef) {
        $numProp                      = $info['self_numeric_property'];
        $structure[$numProp]          = array(
          'type'   => 'array',
          'method' => 'buildProperty',
        );
        $numPropBuilderClass          = $propIsMulti ? 'EntityPropertyInfoReferenceNumericMultiplePropertyBuilder' : 'EntityPropertyInfoNumericReferencePropertyBuilder';
        $keyBuildersClasses[$numProp] = $numPropBuilderClass;
        $keyBuildersArgs[$numProp]    = array(
          'property_name'  => $numProp,
          'reference'      => $info['reference'],
          'reference_info' => $this->entityGetCachedInfo($info['reference']),
        );
      }
    }
    $this->__set('key_builders_classes', $keyBuildersClasses);
    $this->__set('key_builders_args', $keyBuildersArgs);

    return $structure;
  }

  /** {{@inheritdoc}} */
  protected function alterStructure() {

  }

  /**
   * Extracts and set the reference properties name.
   *
   * @param bool $autoSet
   *
   * @return array
   */
  protected function extractReferenceProperties($autoSet = FALSE) {
    $extract = array();
    foreach ($this->properties as $property => $info) {
      if (!empty($info['reference'])) {
        $extract[] = $property;
      }
    }
    $this->setReferenceProperties($extract);

    return $this->referenceProperties;
  }

  /**
   * @param array $args
   * @return \BuilderBase
   */
  public function addProperty(array $args = array()) {
    $structure                         = array();
    $structure[$args['property_name']] = array(
      'type'   => 'array',
      'method' => 'buildProperty',
    );
    $keyBuilderClass                   = $args['key_builder_class'];
    $keyBuilderArgs                    = array(
      'property_type'              => $args['property_type'],
      'property_name'              => $args['property_name'],
      'reference'                  => $args['reference'],
      'reference_info'             => $args['reference_info'],
      'reference_property_builder' => $args['reference_property_builder'],
    );
    $this->structure += $structure;
    $keyBuilder = $this->keyBuilderGetInstance($keyBuilderClass, $keyBuilderArgs);
    $this->setKeyBuilder($args['property_name'], $keyBuilder);

    return $this->getKeyBuilder($args['property_name']);
  }

  /** {{@inheritdoc}} */
  public function build() {
    foreach (array_keys($this->structure) as $key) {
      $this->setKeyBuild($key, $this->buildProperty($key));
    }
    $this->validateBuild();

    return $this->deliver();
  }

  /**
   * @param $property
   * @return array
   */
  protected function buildProperty($property) {
    return $this->getKeyBuilder($property)->build();
  }
}