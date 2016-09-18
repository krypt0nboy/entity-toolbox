<?php

/**
 * Class PermissionPermissionModel
 */
class PermissionAdministerPermissionModel extends PermissionPermissionModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(), $args
    );
    parent::__construct($args);
  }
}