<?php

/**
 * Class ArrayValueBuilder
 */
class ArrayValueBuilder extends ValueBuilder {

  /**
   * @var string $valueKey
   *   The value key.
   */
  protected $valueKey;

  /**
   * @var array $struct
   */
  protected $struct = array();

  /**
   * ArrayValueBuilder constructor.
   *
   * @param null|string $entityType
   *   The entity type.
   * @param null|string $tableKey
   *   The current key name.
   * @param null|string $valueKey
   *   The current key name key.
   * @param array       $rawData
   *   The passed raw data.
   * @param array       $struct
   *   The array structure.
   */
  public function __construct($entityType, $tableKey, $valueKey, array $struct = array(), array $rawData = array()) {
	parent::__construct($entityType, $tableKey, $rawData);
	if (isset($valueKey)) {
	  $this->valueKey = $valueKey;
	}
	$this->struct = $struct;
  }

}

