<?php

/**
 * Class EntityInfoBuilder
 *
 * Not fieldable entity build class for hook_entity_info().
 */
class EntityInfoBuilderNotFieldable extends EntityInfoBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'model_class' => 'EntityInfoModelNotFieldable'
      ),
      $args
    );
    parent::__construct($args);
  }
}