<?php

/**
 * Class BaseDrupalSchemaBuilder
 */
class BaseDrupalSchemaBuilder extends DrupalSchemaBuilder {
  /** {{@inheritdoc}} */
  protected function buildDescription() {
    return $this->processValueTemplate('The base table for %toolbox_info_entity_type% entities.');
  }
}