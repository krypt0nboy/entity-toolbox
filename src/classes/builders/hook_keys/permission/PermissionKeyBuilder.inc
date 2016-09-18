<?php

/**
 * Class PermissionKeyBuilder
 */
class PermissionKeyBuilder extends HookKeyBuilder {
  /**
   * @var string $permissionType
   */
  protected $permissionType;

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'hook' => 'permission',
      ),
      $args
    );
    parent::__construct($args);
  }

  /**
   * @return string
   */
  public function getPermissionType() {
    return $this->permissionType;
  }

  /**
   * @param string $permissionType
   */
  public function setPermissionType($permissionType) {
    $this->permissionType = $permissionType;
  }
}

