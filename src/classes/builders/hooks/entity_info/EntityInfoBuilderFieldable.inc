<?php

/**
 * Class EntityInfoBuilder
 *
 * Fieldable entity build class for hook_entity_info().
 */
class EntityInfoBuilderFieldable extends EntityInfoBuilder {
  /**
   * EntityInfoBuilder constructor.
   * @param null|string $entityType
   */
  public function __construct($entityType) {
    parent::__construct($entityType);
  }

  public function build() {
    $this->processedData += parent::build();
    $this->processedData['fieldable']      = TRUE;
    $this->processedData['bundles']        = array();
    $this->processedData['bundle keys']    = array(
      'bundle' => 'type'
    );
  }
}