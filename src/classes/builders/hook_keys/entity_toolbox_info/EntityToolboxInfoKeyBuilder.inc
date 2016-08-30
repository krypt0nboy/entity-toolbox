<?php

/**
 * Class EntityToolboxInfoValueBuilder
 */
class EntityToolboxInfoKeyBuilder extends EntityDependentHookKeyBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'hook' => 'entity_toolbox_info',
      ),
      $args
    );
    parent::__construct($args);
  }

  protected function keyBuilderGetInstance($keyBuilderClass, array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'hook_builder' => $this->hookBuilder,
    ), $args);

    return parent::keyBuilderGetInstance($keyBuilderClass, $args);
  }
}