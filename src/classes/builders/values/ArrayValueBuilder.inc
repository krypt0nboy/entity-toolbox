<?php

/**
 * Class ArrayValueBuilder
 */
class ArrayValueBuilder extends ValueBuilder {

  /**
   * ArrayValueBuilder constructor.
   *
   * @param null|string $entityType
   *   The entity type.
   * @param null|string $tableKey
   *   The current key name.
   * @param array       $rawData
   *   The passed raw data.
   */
  public function __construct($entityType, $tableKey, array $rawData = array()) {
    parent::__construct($entityType, $tableKey, $rawData);
  }

}

