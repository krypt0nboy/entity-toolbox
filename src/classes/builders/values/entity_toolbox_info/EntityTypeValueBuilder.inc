<?php

/**
 * Class EntityTypeValueBuilder
 *
 * Build class to build the "entity_type" value in hook_entity_toolbox_info().
 */
class EntityTypeValueBuilder extends StringValueBuilder {
  /** {{@inheritdoc}} */
  public function __construct($entityType, array $rawData = array()) {
    parent::__construct($entityType, 'entity_type', $rawData, $this->entityType, FALSE);
  }
}