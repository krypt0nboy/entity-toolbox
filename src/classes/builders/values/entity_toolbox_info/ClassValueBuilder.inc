<?php

/**
 * Class ClassValueBuilder
 */
class ClassValueBuilder extends StringValueBuilder {
  /** {{@inheritdoc}} */
  public function __construct($entityType, $tableKey, array $rawData = array()) {
    parent::__construct($entityType, $tableKey, $rawData);
  }
}

/**
 * Class EntityClassValueBuilder
 */
class EntityClassValueBuilder extends ClassValueBuilder {
  /** {{@inheritdoc}} */
  public function __construct($entityType, array $rawData = array()) {
    parent::__construct($entityType, "entity", $rawData);
  }
}