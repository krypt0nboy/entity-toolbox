<?php

/**
 * Class SchemaRecursiveModel
 */
class SchemaRecursiveModel extends HookRecursiveModel {
  /**
   * @var string $schemaType
   */
  protected $schemaType;

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'hook' => 'schema',
      ),
      $args
    );
    parent::__construct($args);
  }

  /**
   *
   */
  protected function preSetStructure() {
    $this->__set('schema_type', $this->constructArgs['schema_type']);
  }

  /**
   * @return mixed
   */
  public function getSchemaType() {
    return $this->schemaType;
  }

  /**
   * @param mixed $schemaType
   */
  public function setSchemaType($schemaType) {
    $this->schemaType = $schemaType;
  }
}