<?php

/**
 * Class SchemaDependentTraits
 */
trait SchemaDependentTraits {
  /**
   * @var string $schemaType
   */
  protected $schemaType;
  /**
   * @var string $schemaName
   */
  protected $schemaName;

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
   * @return string
   */
  public function getSchemaName() {
    return $this->schemaName;
  }

  /**
   * @param string $schemaName
   */
  public function setSchemaName($schemaName) {
    $this->schemaName = $schemaName;
  }
}