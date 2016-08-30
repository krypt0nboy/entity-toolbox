<?php

/**
 * Class SchemaBuilder
 */
class SchemaBuilder extends EntityToolboxDependentHookBuilder {
  /**
   * @var array $schemas
   */
  protected $schemas = array();
  /**
   * @var array $schemaTypesInfo
   */
  protected $schemaTypesInfo = array();

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'hook' => 'schema',
    ),
      $args
    );
    parent::__construct($args);
    $this->prepareStructure();
  }

  /** {{@inheritdoc}} */
  public function build(array $rawData = array()) {
    $build = array();
    foreach ($this->getStructure() as $key => $params) {
      $schemaType  = $this->schemas[$key];
      $build[$key] = $this->buildSchema($key, $schemaType);
    }

    return $build;
  }

  /**
   * @return array
   */
  public function getSchemaTypesInfo() {
    return $this->schemaTypesInfo;
  }

  /**
   * @param array $schemaTypesInfo
   */
  protected function setSchemaTypesInfo($schemaTypesInfo) {
    $this->schemaTypesInfo = $schemaTypesInfo;
  }

  /**
   * Prepares the structure of the build.
   */
  protected function prepareStructure() {
    $schemas           = array();
    $structure         = array();
    $keyBuilderClasses = array();
    $propertyNames     = array();
    foreach ($this->toolboxInfo['tables'] as $schemaType => $value) {
      if (is_array($value)) {
        foreach ($value as $propertyName => $tableName) {
          $schemas[$tableName]       = $schemaType;
          $propertyNames[$tableName] = $propertyName;
        }
      }
      else {
        if ($value != '') {
          $schemas[$value] = $schemaType;
        }
      }
    }
    foreach ($schemas as $schema => $schemaType) {
      $structure[$schema]         = array(
        'type'   => 'array',
        'method' => 'buildSchema',
      );
      $class                      = class_exists(lowercase2camelcase($schemaType) . 'DrupalSchemaBuilder') ? lowercase2camelcase($schemaType) . 'DrupalSchemaBuilder' : 'DrupalSchemaBuilder';
      $keyBuilderClasses[$schema] = $class;
    }
    $this->schemas = $schemas;
    $this->setStructure($structure);
    $this->setKeyBuildersClasses($keyBuilderClasses);
    foreach (array_keys($this->structure) as $key) {
      $schemaType = $schemas[$key];
      $args       = array(
        'schema_type' => $schemaType
      );
      if (($schemaType == 'relation') || ($schemaType == 'relation_revision')) {
        $propertyName           = $propertyNames[$key];
        $reference              = $this->toolboxInfo['properties'][$propertyName]['reference'];
        $args['property_name']  = $propertyName;
        $args['reference']      = $reference;
        $args['reference_info'] = entity_get_info($reference);
      }
      $keyBuilder = $this->keyBuilderGetInstance($this->keyBuildersClasses[$key], $args);
      $this->setKeyBuilder($key, $keyBuilder);
    }
  }

  /**
   * @param $schemaName
   * @param $schemaType
   * @return array
   */
  protected function buildSchema($schemaName, $schemaType) {
    return $this->getKeyBuilder($schemaName)->build();
  }

}