<?php

/**
 * Class EntityInfoBuilder
 *
 * Base build class for hook_entity_info().
 */
class EntityInfoBuilder extends ContribHookBuilder {
  /**
   * EntityInfoBuilder constructor.
   * @param null|string $entityType
   */
  public function __construct($entityType) {
    parent::__construct('entity_info', $entityType);
  }
}