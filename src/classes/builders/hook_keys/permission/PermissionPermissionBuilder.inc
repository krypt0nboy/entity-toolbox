<?php

/**
 * Class PermissionPermissionBuilder
 */
class PermissionPermissionBuilder extends PermissionKeyBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'model_class' => 'PermissionPermissionModel'
      ),
      $args
    );
    parent::__construct($args);
  }

  protected function buildTitle() {}

  protected function buildDescription() {}
}