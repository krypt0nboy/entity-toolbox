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

  /** {{@inheritdoc}} */
  protected function buildFields() {
    foreach ($this->toolboxInfo['properties'] as $name => $property) {
      $fieldName = !empty($property['schemas_fields']['base']) ? $property['schemas_fields']['base'] : $name;

    }
    if ($this->toolboxInfo['has_revisions']) {
      $this->addRevisionField();
    }
  }
}