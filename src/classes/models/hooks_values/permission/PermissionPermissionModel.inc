<?php

/**
 * Class PermissionPermissionModel
 */
class PermissionPermissionModel extends PermissionRecursiveModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'structure' => array(
          'title'       => array(
            'type'   => 'string',
            'method' => 'buildTitle',
          ),
          'description' => array(
            'type'     => 'string',
            'method'   => 'buildDescription',
            'unset if' => 'is_empty:c:',
          ),
        )
      ), $args
    );
    parent::__construct($args);
  }
}