<?php

/**
 * Class ClassesValueBuilder
 */
class EntityToolboxInfoClassesBuilder extends EntityToolboxInfoKeyBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'self_key'             => 'classes',
        'model_class'          => 'EntityToolboxInfoClassesModel',
        'key_builders_classes' => array(
          'entity'        => 'EntityToolboxInfoClassesEntityClassBuilder',
          'controller'    => 'EntityToolboxInfoClassesControllerClassBuilder',
          'ui controller' => 'EntityToolboxInfoClassesUiControllerClassBuilder',
        )
      ),
      $args
    );
    parent::__construct($args);
  }

  /**
   * Builds the entity class.
   *
   * @return array
   */
  public function buildEntityClass() {
    return $this->getKeyBuilder('entity')->build();
  }

  /**
   * Builds the entity controller class.
   */
  public function buildControllerClass() {
    return $this->getKeyBuilder('controller')->build();
  }

  /**
   * Builds the entity ui controller class.
   */
  public function buildUIControllerClass() {
    return $this->getKeyBuilder('ui controller')->build();
  }
}