<?php

/**
 * Class SchemaKeyBuilder
 */
class SchemaKeyBuilder extends EntityToolboxDependentHookKeyBuilder {
  use SchemaDependentTraits;

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'hook' => 'schema',
    ), $args);
    parent::__construct($args);
  }

  /** {{@inheritdoc}} */
  protected function modelGetInstance($modelClass, array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'schema_type' => $this->constructArgs['schema_type']
    ), $args);

    return parent::modelGetInstance($modelClass, $args);
  }

  /** {{@inheritdoc}} */
  protected function keyBuilderGetInstance($keyBuilderClass, array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'schema_type' => $this->constructArgs['schema_type'],
    ), $args);

    return parent::keyBuilderGetInstance($keyBuilderClass, $args);
  }
}