<?php

/**
 * Class BaseDrupalSchemaBuilder
 */
class BaseDrupalSchemaBuilder extends DrupalSchemaBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    parent::__construct($args);
  }

  /** {{@inheritdoc}} */
  public function build() {
    $build = parent::build();

    return $build;
  }

  /** {{@inheritdoc}} */
  protected function buildDescription() {
    return $this->processValueTemplate('The base table for %toolbox_info_entity_type% entities.');
  }
}