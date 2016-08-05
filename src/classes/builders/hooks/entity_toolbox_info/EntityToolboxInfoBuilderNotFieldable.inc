<?php

/**
 * Class EntityToolboxInfoBuilderNotFieldable
 *
 * Base build class for hook_entity_toolbox_info().
 */
class EntityToolboxInfoBuilderNotFieldable extends EntityToolboxInfoBuilder {
  /** {{@inheritdoc}} */
  public function __construct($entityType, array $rawData = array()) {
    parent::__construct($entityType, $rawData);
  }
}