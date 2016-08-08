<?php

/**
 * Class SchemaRevisionBuilder
 */
class SchemaRevisionBuilder extends SchemaValueBuilder {
  /** {{@inheritdoc}} */
  public function __construct($entityType, $tableKey) {
    parent::__construct($entityType, $tableKey, "revision");
  }
}