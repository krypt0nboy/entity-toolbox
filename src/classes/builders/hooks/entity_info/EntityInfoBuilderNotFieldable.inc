<?php

/**
 * Class EntityInfoBuilder
 *
 * Not fieldable entity build class for hook_entity_info().
 */
class EntityInfoBuilderNotFieldable extends EntityInfoBuilder {
  /**
   * EntityInfoBuilder constructor.
   * @param null|string $entityType
   */
  public function __construct($entityType) {
    parent::__construct($entityType);
  }
}