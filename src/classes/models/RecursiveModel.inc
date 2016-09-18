<?php

/**
 * Class RecursiveModel
 */
class RecursiveModel extends ModelBase {
  /**
   * @access protected
   * @var string $selfKey
   *   The key to access to data when placed in a parent array.
   */
  protected $selfKey;
  /**
   * @access protected
   * @var string $parentKey
   *   The parent data key.
   */
  protected $parentKey;

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    parent::__construct($args);
  }

  /**
   * @return string
   */
  public function getSelfKey() {
    return $this->selfKey;
  }

  /**
   * @param string $selfKey
   */
  public function setSelfKey($selfKey) {
    $this->selfKey = $selfKey;
  }

  /**
   * @return string
   */
  public function getParentKey() {
    return $this->parentKey;
  }

  /**
   * @param string $parentKey
   */
  public function setParentKey($parentKey) {
    $this->parentKey = $parentKey;
  }
}