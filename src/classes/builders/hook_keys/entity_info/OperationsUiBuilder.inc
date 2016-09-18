<?php

/**
 * Class OperationsUiBuilder
 */
class OperationsUiBuilder extends EntityInfoKeyBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'model_class' => 'EntityInfoOperationsUiModel',
      ),
      $args
    );
    parent::__construct($args);
  }
}