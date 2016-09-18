<?php

/**
 * Class EntityToolboxInfoBuilderNotFieldable
 *
 * Base build class for hook_entity_toolbox_info().
 */
class EntityToolboxInfoBuilderNotFieldable extends EntityToolboxInfoBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'model_class'          => 'EntityToolboxInfoModelNotFieldable',
      'key_builders_classes' => array(
        'classes'    => 'EntityToolboxInfoClassesBuilderNotFieldable',
        'properties' => 'EntityToolboxInfoPropertiesBuilderNotFieldable',
        'operations' => 'EntityToolboxInfoOperationsBuilderNotFieldable',
      )
    ), $args);
    parent::__construct($args);
  }

  /**
   * Builds "bundle_of".
   *
   * @return string
   */
  protected function buildBundleOf() {
    return preg_replace('/_type/', '', $this->entityType);
  }
}