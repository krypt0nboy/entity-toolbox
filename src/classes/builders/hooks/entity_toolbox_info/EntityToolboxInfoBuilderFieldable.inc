<?php

/**
 * Class EntityToolboxInfoBuilder
 *
 * Base build class for hook_entity_toolbox_info().
 */
class EntityToolboxInfoBuilderFieldable extends EntityToolboxInfoBuilder {
  /** {{@inheritdoc}} */
  public function __construct($entityType, array $rawData = array()) {
    parent::__construct($entityType, $rawData);
  }
}