<?php

/**
 * Class MenuItemBuilder
 */
class MenuItemBuilder extends MenuKeyBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $this->mergeConstructArgs(array(
      'model_class' => 'MenuItemModel'
    ), $args);
    parent::__construct($args);
  }
}