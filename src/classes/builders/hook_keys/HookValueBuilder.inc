<?php

/**
 * Class HookValueBuilder
 */
class HookValueBuilder extends HookBuilder {
  /** {{@inheritdoc}} */
  public function __construct($hook, $entityType, array $args = array()) {
    $args += array(
      'hook' => $hook,
    );
    parent::__construct($args);
  }
}