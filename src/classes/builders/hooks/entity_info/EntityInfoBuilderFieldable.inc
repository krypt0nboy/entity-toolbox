<?php

/**
 * Class EntityInfoBuilder
 *
 * Fieldable entity build class for hook_entity_info().
 */
class EntityInfoBuilderFieldable extends EntityInfoBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'model_class' => 'EntityInfoModelFieldable'
      ),
      $args
    );
    parent::__construct($args);
  }

  /**
   * @return mixed
   */
  protected function buildEntityKeys() {
    $keys = $this->toolboxInfo['keys'];
    unset($keys['bundle']);

    return $keys;
  }

  /**
   * @return array
   */
  protected function buildBundleKeys() {
    return array('bundle' => $this->toolboxInfo['keys']['bundle']);
  }
}