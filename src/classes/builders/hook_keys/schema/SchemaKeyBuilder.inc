<?php

/**
 * Class SchemaKeyBuilder
 */
class SchemaKeyBuilder extends EntityToolboxDependentHookKeyBuilder {
  /**
   * @var string $schemaType
   */
  protected $schemaType;
  /**
   * @var array $schemaTypeInfo
   */
  protected $schemaTypeInfo = array();

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'hook' => 'schema',
    ), $args);
    parent::__construct($args);
  }

  /**
   * @return string
   */
  public function getSchemaType() {
    return $this->schemaType;
  }

  /**
   * @param string $schemaType
   */
  public function setSchemaType($schemaType) {
    $this->schemaType = $schemaType;
  }

  /**
   * @return array
   */
  public function getSchemaTypeInfo() {
    return $this->schemaTypeInfo;
  }

  /**
   * @param array $schemaTypeInfo
   */
  public function setSchemaTypeInfo($schemaTypeInfo) {
    $this->schemaTypeInfo = $schemaTypeInfo;
  }

  protected function preSetKeyBuildersClasses() {
    parent::preSetKeyBuildersClasses();
    $this->__set('schema_type', $this->constructArgs['schema_type']);
  }

  /**
   * @param $modelClass
   * @param $args
   *
   * @return ModelBase
   */
  protected function modelGetInstance($modelClass, array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'schema_type' => $this->constructArgs['schema_type']
    ), $args);

    return parent::modelGetInstance($modelClass, $args);
  }

  /** {{@inheritdoc}} */
  protected function keyBuilderGetInstance($keyBuilderClass, array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'schema_type' => $this->constructArgs['schema_type']
    ), $args);

    return parent::keyBuilderGetInstance($keyBuilderClass, $args);
  }
}