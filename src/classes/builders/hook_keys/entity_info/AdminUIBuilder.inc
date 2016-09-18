<?php

require_once 'EntityInfoKeyBuilder.inc';

/**
 * Class AdminUIBuilder
 */
class AdminUIBuilder extends EntityInfoKeyBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'model_class' => 'EntityInfoAdminUiModel',
      ),
      $args
    );
    parent::__construct($args);
  }
}