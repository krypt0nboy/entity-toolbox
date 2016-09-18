<?php

/**
 * Class EntityClassBuilder
 */
class EntityToolboxInfoClassesUiControllerClassBuilder extends EntityToolboxInfoClassesClassBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'self_key' => 'ui controller',
        'class_type' => 'ui controller',
      ),
      $args
    );
    parent::__construct($args);
  }
}