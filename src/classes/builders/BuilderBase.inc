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
   * Return the built/rebuilt data.
   *
   * @return array
   */
  public function build() {
  }
}