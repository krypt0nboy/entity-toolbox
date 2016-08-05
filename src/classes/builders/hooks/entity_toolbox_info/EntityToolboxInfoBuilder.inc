<?php

/**
 * Class EntityToolboxInfoBuilder
 *
 * Base build class for hook_entity_toolbox_info().
 */
class EntityToolboxInfoBuilder extends HookBuilder {
  /** {{@inheritdoc}} */
  public function __construct($entityType, array $rawData = array()) {
    parent::__construct('entity_toolbox_info', $entityType, $rawData);
  }

  /** {{@inheritdoc}} */
  public function build() {
    $this->processedData['entity_type'] = new EntityTypeValueBuilder($this->entityType, $this->rawData);
  }
}