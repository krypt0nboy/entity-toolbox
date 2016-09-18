<?php

/**
 * Class EntityInfoRecursiveModel
 */
class EntityInfoRecursiveModel extends HookRecursiveModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'hook'      => 'entity_info',
      ),
      $args
    );
    parent::__construct($args);
  }
}