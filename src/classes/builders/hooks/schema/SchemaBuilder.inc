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
  }

  /** {{@inheritdoc}} */
  public function build(array $rawData = array()) {
    $this->setPhase(self::PHZ__BUILD);
    $this->preBuild();
    foreach (array_keys($this->getStructure()) as $schemaName) {
      $schemaType = $this->schemas[$schemaName];
      $this->setKeyBuild($schemaName, $this->buildSchema($schemaName, $schemaType));
    }
    $this->validateBuild();
    $this->postBuild();

    return $this->deliver();
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
   * @return array
   */
  public function getSchemas() {
    return $this->schemas;
  }

  /**
   * @param array $schemas
   */
  public function setSchemas($schemas) {
    $this->schemas = $schemas;
  }

  /** {{@inheritdoc}} */
  protected function genDynamicStructure() {
    $structure          = array();
    $keyBuildersClasses = array();
    $keyBuildersArgs    = array();
    $schemas            = $this->extractSchemas();
    $properties         = $this->extractRelationSchemasMatchingPropertyName();
    foreach ($schemas as $schema => $schemaType) {
      $class              = $this->guessSchemaBuilderClass($schemaType);
      $structure[$schema] = array(
        'type'   => 'array',
        'method' => 'buildSchema',
      );
      $keyBuilderArgs     = array(
        'schema_type' => $schemaType,
        'schema_name' => $schema,
      );
      if (in_array($schema, array_keys($properties))) {
        $propertyName                     = $properties[$schema];
        $reference                        = $this->toolboxInfo['properties'][$propertyName]['reference'];
        $keyBuilderArgs['property_name']  = $propertyName;
        $keyBuilderArgs['reference']      = $reference;
        $keyBuilderArgs['reference_info'] = $this->entityGetCachedInfo($reference);
      }
      $keyBuildersClasses[$schema] = $class;
      $keyBuildersArgs[$schema]    = $keyBuilderArgs;
    }
    $this->__set('schemas', $schemas);
    $this->__set('key_builders_classes', $keyBuildersClasses);
    $this->__set('key_builders_args', $keyBuildersArgs);

    return $structure;
  }

  /**
   * Extract and returns the entity toolbox schemas for this entity type.
   *
   * @return array
   */
  protected function extractSchemas() {
    $schemas = array();
    foreach ($this->toolboxInfo['tables'] as $schemaType => $value) {
      if (is_array($value)) {
        foreach ($value as $propertyName => $tableName) {
          $schemas[$tableName]       = $schemaType;
          $propertyNames[$tableName] = $propertyName;
        }
      }
      else {
        if (!empty($value)) {
          $schemas[$value] = $schemaType;
        }
      }
    }

    return $schemas;
  }

  /**
   * Extract the matching ref property names.
   *
   * @return array
   */
  protected function extractRelationSchemasMatchingPropertyName() {
    $properties = array();
    foreach ($this->toolboxInfo['tables'] as $schemaType => $value) {
      if (is_array($value)) {
        foreach ($value as $propertyName => $tableName) {
          $properties[$tableName] = $propertyName;
        }
      }
    }

    return $properties;
  }

  /**
   * Guess and returns a schema type builder class.
   *
   * @param string $schemaType
   *   The schema type.
   *
   * @return string
   */
  protected function guessSchemaBuilderClass($schemaType) {
    return class_exists(lowercase2camelcase($schemaType) . 'DrupalSchemaBuilder') ? lowercase2camelcase($schemaType) . 'DrupalSchemaBuilder' : 'DrupalSchemaBuilder';
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