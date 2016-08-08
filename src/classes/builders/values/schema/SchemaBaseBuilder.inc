<?php

/**
 * Class SchemaBaseBuilder
 */
class SchemaBaseValueBuilder extends SchemaValueBuilder {
  /** {{@inheritdoc}} */
  public function __construct($entityType, $tableKey = NULL) {
    parent::__construct($entityType, $tableKey, "base");
    $this->defaultDescription = "The base table for %entity_type% entities.";
  }
}