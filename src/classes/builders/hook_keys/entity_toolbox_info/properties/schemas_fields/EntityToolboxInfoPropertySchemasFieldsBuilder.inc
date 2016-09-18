<?php

/**
 * Class PropertySchemasFieldsBuilder
 */
class EntityToolboxInfoPropertySchemasFieldsBuilder extends EntityToolboxInfoPropertiesSchemaDependentKeyBuilder {

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'self_key'    => 'schemas_fields',
        'model_class' => 'EntityToolboxInfoPropertySchemasFieldsModel',
      ),
      $args
    );
    parent::__construct($args);
  }

  /** {{@inheritdoc}} */
  protected function genStructureFromModel() {
    $structure          = parent::genStructureFromModel();
    $keyBuildersClasses = array();
    $keyBuildersArgs    = array();
    foreach (array_keys($structure) as $key) {
      $keyBuildersClasses[$key] = 'EntityToolboxInfoPropertySchemasFieldBuilder';
      $keyBuildersArgs[$key]    = array('schema_type' => $key);
    }
    $this->__set('key_builders_classes', $keyBuildersClasses);
    $this->__set('key_builders_args', $keyBuildersArgs);

    return $structure;
  }

  /**
   * @return mixed
   */
  protected function buildBaseSchemasFields() {
    return $this->getKeyBuilder('base')->build();
  }

  /**
   * @return mixed
   */
  protected function buildRevisionSchemasFields() {
    return $this->getKeyBuilder('revision')->build();
  }

  /**
   * @return mixed
   */
  protected function buildRelationSchemasFields() {
    return $this->getKeyBuilder('relation')->build();
  }

  /**
   * @return mixed
   */
  protected function buildRelationRevisionSchemasFields() {
    return $this->getKeyBuilder('relation_revision')->build();
  }
}