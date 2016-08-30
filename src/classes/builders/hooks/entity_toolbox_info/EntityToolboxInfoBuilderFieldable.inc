<?php

/**
 * Class EntityToolboxInfoBuilder
 *
 * Base build class for hook_entity_toolbox_info().
 */
class EntityToolboxInfoBuilderFieldable extends EntityToolboxInfoBuilder {

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'model_class'          => 'EntityToolboxInfoModelFieldable',
      'key_builders_classes' => array(
        'classes'    => 'EntityToolboxInfoClassesBuilderFieldable',
        'properties' => 'EntityToolboxInfoPropertiesBuilderFieldable',
        'operations' => 'EntityToolboxInfoOperationsBuilderFieldable',
      )
    ), $args);
    parent::__construct($args);
  }

  public function build() {
    return parent::build();
  }

  /**
   * Builds the classes.
   *
   * @return array
   */
  protected function buildClasses() {
    return parent::buildClasses();
  }

  /**
   * Builds the properties.
   *
   * @return array
   */
  protected function buildProperties() {
    return parent::buildProperties();
  }

  /**
   * Builds the tables.
   *
   * @return string
   */
  protected function buildTables() {
    return parent::buildTables();
  }

  /**
   * Builds the operations.
   *
   * @return array
   */
  protected function buildOperations() {
    return parent::buildOperations();
  }

  /**
   * Builds the keys.
   *
   * @return array
   */
  protected function buildKeys() {
    return parent::buildKeys();
  }
}