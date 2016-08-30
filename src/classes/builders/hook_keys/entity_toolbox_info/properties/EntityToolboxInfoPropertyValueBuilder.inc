<?php

/**
 * Class PropertyValueBuilder
 */
class EntityToolboxInfoPropertyValueBuilder extends EntityToolboxInfoPropertyDependentKeyBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'self_key'    => 'classes',
        'model_class' => 'EntityToolboxInfoPropertyValueModel'
      ),
      $args
    );
    parent::__construct($args);
  }

  protected function buildFilter() {
  }

  protected function buildForbid() {
  }
}