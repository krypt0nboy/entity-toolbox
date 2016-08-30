<?php

/**
 * Class EntityPropertyInfoPropertiesBuilder
 */
class EntityPropertyInfoPropertiesBuilder extends EntityPropertyInfoKeyBuilder {
  /**
   * @var array $properties
   */
  protected $properties = array();

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
   *
   */
  protected function postSetToolboxInfo() {
    $this->__set('properties', $this->toolboxInfo['properties']);
    $structure         = array();
    $keyBuilderClasses = array();
    foreach ($this->properties as $property => $info) {
      $structure[$property] = array(
        'type'   => 'array',
        'method' => 'buildProperty',
      );
      $keyBuilderClass      = 'EntityPropertyInfoPropertyBuilder';
      if (!empty($info['reference'])) {
        $keyBuilderClass = $info['multiple'] ? 'EntityPropertyInfoReferenceMultiplePropertyBuilder' : 'EntityPropertyInfoReferencePropertyBuilder';
      }
      $keyBuilderClasses[$property] = $keyBuilderClass;
    }
    $this->__set('structure', $structure);
    $this->setKeyBuildersClasses($keyBuilderClasses);
    foreach ($this->getKeyBuildersClasses() as $key => $keyBuildersClass) {
      $args = array(
        'property_type' => $this->toolboxInfo['properties'][$key]['type'],
        'property_name' => $key,
      );
      $this->setKeyBuilder($key, $this->keyBuilderGetInstance($keyBuildersClass, $args));
    }
    $updatedStructure = $this->getStructure();
    $added            = array_diff(array_keys($updatedStructure), array_keys($structure));
  }

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
    $build = array();
    foreach ($this->structure as $key => $params) {
      $build[$key] = $this->buildProperty($key);
    }

    return $build;
  }

  /**
   * @param $property
   * @return array
   */
  protected function buildProperty($property) {
    return $this->getKeyBuilder($property)->build();
  }
}