<?php

/**
 * Class EntityOperationsInfoOperationBuilder
 */
class EntityOperationsInfoOperationsBuilder extends EntityOperationsInfoKeyBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(),
      $args
    );
    parent::__construct($args);
  }
}