<?php

/**
 * Class KeysValueBuilder
 */
class EntityToolboxInfoKeysBuilder extends EntityToolboxInfoKeyBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'self_key'    => 'keys',
      ),
      $args
    );
    parent::__construct($args);
  }
}