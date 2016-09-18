<?php

/**
 * Class EntityToolboxInfoPropertySchemaFieldBuilder
 */
class EntityToolboxInfoPropertySchemasFieldBuilder extends EntityToolboxInfoPropertiesSchemaDependentKeyBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'model_class' => 'EntityToolboxInfoPropertySchemasFieldModel',
      ),
      $args
    );
    parent::__construct($args);
  }

  /** {{@inheritdoc}} */
  protected function modelGetInstance($modelClass, array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'schema_type' => $this->constructArgs['schema_type']
    ), $args);

    return parent::modelGetInstance($modelClass, $args);
  }

  /**
   * @param $build
   * @return null
   */
  protected function validateSize($build) {
    if ($this->isValueTemplate($build)) {
      return NULL;
    }
  }

  /**
   * @param $build
   * @return null
   */
  protected function validateScale($build) {
    if (is_string($build) || ($build == 0)) {
      return NULL;
    }
  }

  /**
   * @param $build
   * @return null
   */
  protected function validatePrecision($build) {
    if (is_string($build) || ($build == 0)) {
      return NULL;
    }
  }
}