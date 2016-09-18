<?php

/**
 * Class EntityOperationInfoAddOperationBuilder
 */
class EntityOperationInfoAddOperationBuilder extends EntityOperationsInfoOperationBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(

      ),
      $args
    );
    parent::__construct($args);
  }
}