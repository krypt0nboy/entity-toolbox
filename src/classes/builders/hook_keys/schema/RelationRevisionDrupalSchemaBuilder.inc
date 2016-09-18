<?php

/**
 * Class RelationRevisionDrupalSchemaBuilder
 */
class RelationRevisionDrupalSchemaBuilder extends RelationDrupalSchemaBuilder {
  /** {{@inheritdoc}} */
  protected function buildDescription() {
    return $this->processValueTemplate('A relation table between %toolbox_info_entity_type% and %reference_info_entity_type%.');
  }
}