<?php

/**
 * Class EntityClassBuilder
 */
class EntityToolboxInfoClassesEntityClassBuilder extends EntityToolboxInfoClassesClassBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'self_key' => 'entity',
        'class_type' => 'entity',
      ),
      $args
    );
    parent::__construct($args);
  }
}