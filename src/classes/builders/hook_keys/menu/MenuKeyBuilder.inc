<?php

/**
 * Class MenuKeyBuilder
 */
class MenuKeyBuilder extends HookKeyBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'hook' => 'menu'
    ), $args);
    parent::__construct($args);
  }
}