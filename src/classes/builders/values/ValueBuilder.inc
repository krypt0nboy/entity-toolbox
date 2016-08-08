<?php


/**
 * Class ValueBuilder
 *
 * Used to build the value of an array key.
 */
class ValueBuilder extends BuilderBase {

  /**
   * @var mixed $rawValueData
   *   The isolated raw value data from $rawData.
   */
  protected $rawValueData;

  /**
   * @var mixed $processedValueData
   *   The processed value data to return.
   */
  protected $processedValueData;

  /**
   * @var string $tableKey
   *   The current key name.
   */
  protected $tableKey;

  /**
   * ValueBuilder constructor.
   *
   * @param null|string $entityType
   *   The entity type.
   * @param null|string $tableKey
   *   The current key name.
   * @param array       $rawData
   *   The passed raw data.
   */
  public function __construct($entityType = NULL, $tableKey = NULL, array $rawData = array()) {
    parent::__construct($entityType, $rawData);
    $this->tableKey = $tableKey;
    $this->extractRawDataValue();
  }

  /**
   * Extracts the current key raw data from $rawData.
   */
  protected function extractRawDataValue() {
    if (!empty($this->rawData[$this->tableKey])) {
      $this->rawValueData = $this->rawData[$this->tableKey];
    }
  }

  /**
   * Builds the value.
   *
   * @return mixed
   */
  public function build() {
  }

  /**
   * Builds the default value to be merged in the method build().
   *
   * @return mixed
   */
  protected function buildDefault() {
  }

  /**
   * Determines how the value is considered to be excluded from buildDefault().
   *
   * @return bool
   */
  protected function valueIsNull() {
  }
}

