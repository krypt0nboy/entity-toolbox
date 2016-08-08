<?php

/**
 * Class ArrayBuilder
 */
class ArrayBuilder extends ValueBuilder {
  /** {{@inheritdoc}} */
  public function __construct($entityType, $tableKey, array $rawData = array()) {
    parent::__construct($entityType, $tableKey, $rawData);
  }

  /**
   * @return array
   */
  public function build() {
  }
}