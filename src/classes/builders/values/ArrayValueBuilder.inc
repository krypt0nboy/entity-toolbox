<?php

/**
 * Class ArrayValueBuilder
 */
class ArrayValueBuilder extends ValueBuilder {
  /**
   * @var string $parentArrayKey
   *   The parent array key in $rawData.
   */
  protected $parentArrayKey;

  /**
   * ArrayValueBuilder constructor.
   *
   * @param null|string $entityType
   *   The entity type.
   * @param null|string $tableKey
   *   The current key name.
   * @param array       $rawData
   *   The passed raw data.
   * @param string      $parentArrayKey
   *   The parent array key in $rawData.
   */
  public function __construct($entityType, $tableKey, array $rawData = array(), $parentArrayKey = NULL) {
    parent::__construct($entityType, $tableKey, $rawData);
    $this->parentArrayKey = $parentArrayKey;
  }

}

