<?php

/**
 * Class PropertyTablesBuilder
 */
class EntityToolboxInfoPropertyTablesBuilder extends EntityToolboxInfoPropertyDependentKeyBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'self_key' => 'tables',
      ),
      $args
    );
    parent::__construct($args);
  }

  /** {{@inheritdoc}} */
  protected function genDynamicStructure() {
    $structure = array();
    $schemas   = array(
      'relation',
      'relation_revision',
    );
    foreach ($schemas as $schemaType) {
      $structure[$schemaType] = array(
        'type'    => 'string',
        'default' => '%property_default_tables_' . $schemaType . '%',
      );
    }
    return $structure;
  }

  /** {{@inheritdoc}} */
  protected function buildRelationTables() {
    if ($this->getParentBuilder()->getBuild('multiple')) {
      return $this->buildKeyDefault('relation');
    }
  }

  /** {{@inheritdoc}} */
  protected function buildRelationRevisionTables() {
    if ($this->getParentBuilder()->getBuild('relation_revision')) {
      return $this->buildKeyDefault('relation_revision');
    }
  }
}