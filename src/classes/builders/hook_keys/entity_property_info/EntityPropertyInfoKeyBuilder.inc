<?php

/**
 * Class EntityPropertyInfoValueBuilder
 */
class EntityPropertyInfoKeyBuilder extends EntityToolboxDependentHookKeyBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'hook' => 'entity_property_info'
      ),
      $args
    );
    parent::__construct($args);
  }
}