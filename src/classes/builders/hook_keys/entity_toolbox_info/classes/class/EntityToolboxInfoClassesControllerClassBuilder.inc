<?php

/**
 * Class ControllerClassBuilder
 */
class EntityToolboxInfoClassesControllerClassBuilder extends EntityToolboxInfoClassesClassBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'self_key'   => 'controller',
        'class_type' => 'controller',
      ),
      $args
    );
    parent::__construct($args);
  }
}