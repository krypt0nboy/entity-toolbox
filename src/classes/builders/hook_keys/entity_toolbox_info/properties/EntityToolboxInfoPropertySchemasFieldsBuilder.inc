<?php

/**
 * Class PropertySchemasFieldsBuilder
 */
class EntityToolboxInfoPropertySchemasFieldsBuilder extends EntityToolboxInfoPropertyDependentKeyBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'self_key'             => 'schemas_fields',
        'model_class'          => 'EntityToolboxInfoPropertySchemasFieldsModel',
        'key_builders_classes' => array(
          'base'     => 'EntityToolboxInfoPropertySchemasFieldBuilder',
          'revision' => 'EntityToolboxInfoPropertySchemasFieldBuilder',
        ),
      ),
      $args
    );
    parent::__construct($args);
  }

  protected function buildBaseSchemasFields() {
    $build = $this->getKeyBuilder('base')->build();

    return $build;
  }

  protected function buildRevisionSchemasFields() {
  }

  protected function buildRelationSchemasFields() {
    return array();
  }

  protected function buildRelationRevisionSchemasFields() {
    return array();
  }
}