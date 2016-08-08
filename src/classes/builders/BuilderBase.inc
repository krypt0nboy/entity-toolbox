<?php

/**
 * Class BuilderBase
 *
 * Base class to build data required by drupal available api's.
 */
class BuilderBase {
  /**
   * @var string $entityType
   *   The entity type.
   */
  protected $entityType;
  /**
   * @var array $rawData
   *   (Optional) The data retrieved/to retrieve and rebuild.
   */
  protected $rawData = array();
  /**
   * @var array $processedData
   *   The built/rebuilt data.
   */
  protected $processedData = array();

  /**
   * @var ValueBuilder[] $valuesBuilders
   *   Required values builders.
   */
  protected $valuesBuilders = array();

  /**
   * BuilderBase constructor.
   *
   * @param null|string $entityType
   *   The entity type.
   *
   * @throws EntityToolboxException
   */
  public function __construct($entityType = NULL, array $rawData = array()) {
    if (!isset($entityType)) {
      throw new MissingEntityTypeException();
    }
    $this->entityType = $entityType;
    if (!empty($rawData)) {
      $this->rawData = $rawData;
    }
  }

  /**
   * Sets the values builders required by the current builder.
   */
  protected function setValuesBuilders() {
  }

  /**
   * Returns a value builder.
   *
   * @param string $name
   *   The builder name.
   *
   * @return \ValueBuilder
   */
  protected function getValueBuilder($name) {
    if (!empty($this->valuesBuilders[$name])) {
      return $this->valuesBuilders[$name];
    }
  }

  /**
   * @return \ValueBuilder[]
   */
  protected function getValuesBuilders() {
    return $this->valuesBuilders;
  }

  /**
   * Return the built/rebuilt data.
   *
   * @return array
   */
  public function build() {
  }
}