<?php

/**
 * Class PermissionPermissionsBuilder
 */
class PermissionPermissionsBuilder extends PermissionKeyBuilder{
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $this->mergeConstructArgs(
      array(
        'hook' => 'permission',
      ),
      $args
    );
    parent::__construct($args);
  }
}