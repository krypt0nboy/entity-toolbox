<?php

/**
 * Class MenuItemBuilder
 */
class EntityOperationInfoMenuItemBuilder extends MenuItemBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(), $args);
    parent::__construct($args);
  }
}