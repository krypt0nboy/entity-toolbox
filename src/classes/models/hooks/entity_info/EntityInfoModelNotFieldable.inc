<?php

/**
 * Class EntityInfoModelNotFieldable
 */
class EntityInfoModelNotFieldable extends EntityInfoModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'structure' => array(
          'fieldable' => array(
            'default' => FALSE,
          ),
        )
      ),
      $args
    );
    parent::__construct($args);
  }
}