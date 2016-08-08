<?php

/**
 * Class SchemaValueBuilder
 */
class SchemaValueBuilder extends ContribArrayBuilder {
  /**
   * @var string $schemaType
   */
  protected $schemaType;

  /**
   * @var array $schemaTypeInfo
   */
  protected $schemaTypeInfo = array();

  /**
   * @var string $description
   */
  protected $description;
  /**
   * @var array $fields
   */
  protected $fields = array();
  /**
   * @var array $indexes
   */
  protected $indexes = array();
  /**
   * @var array $uniqueKey
   */
  protected $uniqueKey = array();
  /**
   * @var string $defaultDescription
   */
  protected $defaultDescription;

  /** {{@inheritdoc}} */
  public function __construct($entityType, $tableKey = NULL, $schemaType) {
    parent::__construct($entityType, $tableKey);
    $this->schemaType = $schemaType;
  }

  /**
   * Builds the description.
   */
  protected function buildDescription() {
    $this->processedValueData['description'] = string_template_process($this->defaultDescription, array());

    return $this->processedValueData['description'];
  }

  /**
   * Builds the fields.
   */
  protected function buildFields() {
  }

  /**
   * Builds the table indexes.
   */
  protected function buildIndexes() {
  }

  /**
   * Builds the unique key.
   */
  protected function buildUniqueKey() {
  }

  /**
   * Adds a revision field.
   */
  protected function addRevisionField() {
  }

  /**
   * Returns the build info.
   *
   * @return array
   */
  public function build() {
    $this->buildDescription();
    $this->buildFields();
    $this->buildIndexes();
    $this->buildUniqueKey();

    return $this->processedValueData;
  }
}