<?php

/**
 * Class EntityToolboxInfoRecursiveModel
 */
class EntityToolboxInfoRecursiveModel extends HookRecursiveModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'hook' => 'entity_toolbox_info',
      ), $args
    );
    parent::__construct($args);
  }
}