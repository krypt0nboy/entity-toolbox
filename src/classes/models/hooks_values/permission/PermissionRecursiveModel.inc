<?php

/**
 * Class MenuRecursiveModel
 */
class PermissionRecursiveModel extends HookRecursiveModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'hook' => 'permission',
      ), $args
    );
    parent::__construct($args);
  }
}