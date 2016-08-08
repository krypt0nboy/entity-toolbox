<?php

/**
 * Class ClassValueBuilder
 */
class ClassValueBuilder extends ValueBuilder {
  /** {{@inheritdoc}} */
  public function __construct($entityType, $tableKey, array $rawData = array()) {
    parent::__construct($entityType, $tableKey, $rawData);
  }
}

/**
 * Class EntityClassValueBuilder
 */
class EntityClassValueBuilder extends ClassValueBuilder {
  public function __construct($entityType, array $rawData = array()) {
    parent::__construct($entityType, "entity", $rawData);
  }
}